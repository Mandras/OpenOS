/*# # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #
# OpenOS                                                                #
# GPL license - opensource project                                      #
# Developed by One Solution Network                                     #
#                                                                       #
# File: session.cpp                                                     #
#                                                                       #
# Utilities:                                                            #
#                                                                       #
# # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #
#                                                                       #
# This file is part of OpenOS Project.                                  #
#                                                                       #
# OpenOS is free software: you can redistribute it and/or modify        #
# it under the terms of the GNU General Public License as published by  #
# the Free Software Foundation, either version 3 of the License, or     #
# (at your option) any later version.                                   #
#                                                                       #
# OpenOS is distributed in the hope that it will be useful,             #
# but WITHOUT ANY WARRANTY; without even the implied warranty of        #
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         #
# GNU General Public License for more details.                          #
#                                                                       #
# You should have received a copy of the GNU General Public License     #
# along with OpenOS.  If not, see <http://www.gnu.org/licenses/>        #
#                                                                       #
# # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #*/

#include "../headers/OpenOS.hpp"

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

string		Headquarters::StringToHex(const string& input) {
  static const	char* const lut = "0123456789ABCDEF";
  size_t	len = input.length();
  string	output;

  output.reserve(2 * len);
  for (size_t i = 0; i < len; ++i) {
    const	unsigned char c = input[i];
    output.push_back(lut[c >> 4]);
    output.push_back(lut[c & 15]);
  }
  return (output);
}

string		Headquarters::HexToString(const string& input) {
  static const	char* const lut = "0123456789ABCDEF";
  size_t	len = input.length();
  bool		error = false;
  
  if (len & 1) {
    string	errmsg("Session data is corrupted [BAD SIZE]");
    this->error(errmsg, false);
    error = true;
  }

  string	output;

  output.reserve(len / 2);
  for (size_t i = 0; i < len; i += 2) {
    char	a = input[i];
    const char* p = lower_bound(lut, lut + 16, a);
    if (*p != a) {
      string	errmsg("Session data is corrupted [NOT A HEX DIGIT]");
      this->error(errmsg, false);
      error = true;
    }
    
    char	b = input[i + 1];
    const char* q = lower_bound(lut, lut + 16, b);
    if (*q != b) {
      string	errmsg("Session data is corrupted [NOT A HEX DIGIT]");
      this->error(errmsg, false);
      error = true;
    }    
    output.push_back(((p - lut) << 4) | (q - lut));
  }
  if (error == true)
    this->restoreSession();
  return (output);
}

void		Headquarters::restoreSession() {
  this->printMessage("Trying to restore session data", INFO);
  this->OpenOutputSessionFile();
  if (!(this->SessionFdo.is_open()))
    return ;
  for (vector<string>::iterator it = this->SessionBuffer.begin(); it != this->SessionBuffer.end(); ++it) {
    this->SessionFdo << this->StringToHex(*it) << endl;
  }
  this->CloseSessionFile();
}

void		Headquarters::printAllSession() {
  for (vector<string>::iterator it = this->SessionBuffer.begin(); it != this->SessionBuffer.end(); ++it)
    cout << *it << endl;
}

void		Headquarters::printSession() {
  this->printSession("Headquarters");
}

void		Headquarters::printSession(string title) {
  if (this->isSessionTitleExist(title) == false)
    return ;

  vector<string> vecarray;

  vecarray = getSessionTitle(title);
  for (vector<string>::iterator it = vecarray.begin(); it != vecarray.end(); ++it)
    cout << *it << endl;
}

void		Headquarters::setSessionTitle(string title) {
  if (this->isSessionTitleExist(title) == true)
    return ;
  this->SessionBuffer.push_back('[' + title + ']');
  this->SessionBuffer.push_back("[/" + title + ']');
}

vector<string>	 Headquarters::getSessionTitle(string title) {
  vector<string> vecarray;

  if (this->isSessionTitleExist(title) == false)
    return (vecarray);

  string	 search_start = '[' + title + ']';
  string	 search_end = "[/" + title + ']';

  for (vector<string>::iterator it = this->SessionBuffer.begin(); it != this->SessionBuffer.end(); ++it) {
    if (*it == search_start) {
      for (++it ; it != this->SessionBuffer.end() && *it != search_end ; ++it)
	vecarray.push_back(*it);
    }
    if (it == this->SessionBuffer.end()) {
      string	errmsg("Can't find title end stream in session's buffer : ");
      this->error(errmsg.append(search_end), true);
    }
  }
  return (vecarray);
}

void		Headquarters::insertSessionLine(string title, string line) {
  if (this->isSessionTitleExist(title) == false)
    return ;

  vector<string> newSessionLine;
  string	 search = '[' + title + ']';

  for (vector<string>::iterator it = this->SessionBuffer.begin(); it != this->SessionBuffer.end(); ++it) {
    if (*it == search) {
      newSessionLine.push_back(*it);
      newSessionLine.push_back(line);
    }
    else
      newSessionLine.push_back(*it);
  }
  this->SessionBuffer = newSessionLine;
}

bool		Headquarters::isSessionTitleExist(string title) {
  string	search = '[' + title + ']';

  for (vector<string>::iterator it = this->SessionBuffer.begin(); it != this->SessionBuffer.end(); ++it) {
    if (*it == search)
      return (true);
  }
  return (false);
}

void		Headquarters::EncryptSessionFile() {
  this->OpenOutputSessionFile();
  if (!(this->SessionFdo.is_open()))
    return ;
  for (vector<string>::iterator it = this->SessionBuffer.begin(); it != this->SessionBuffer.end(); ++it) {
    this->SessionFdo << this->StringToHex(*it) << endl;
  }
  this->CloseSessionFile();
}

void		Headquarters::DecryptSessionFile() {
  this->SessionBuffer.clear();
  this->OpenInputSessionFile();
  if (!(this->SessionFdi.is_open()))
    return ;

  string	line;

  while (!(this->SessionFdi.eof())) {
    getline(this->SessionFdi, line);
    if (line.length() > 0)
      this->SessionBuffer.push_back(this->HexToString(line));
  }
  this->CloseSessionFile();
}

void		Headquarters::OpenOutputSessionFile() {
  if (this->SessionFdo.is_open())
    this->CloseSessionFile();
  this->SessionFdo.open(this->SessionFile, fstream::out | fstream::trunc);
  if (!(this->SessionFdo.is_open())) {
    string	errmsg("Couldn't open [WRITE] session file : ");
    this->error(errmsg.append(this->SessionFile), false);
  }
}

void		Headquarters::OpenInputSessionFile() {
  if (this->SessionFdi.is_open())
    this->CloseSessionFile();
  this->SessionFdi.open(this->SessionFile, fstream::in);
  if (!(this->SessionFdi.is_open())) {
    string	errmsg("Couldn't open [READ] session file : ");
    this->error(errmsg.append(this->SessionFile), false);
  }
}

void		Headquarters::CloseSessionFile() {
  if (this->SessionFdi.is_open())
    this->SessionFdi.close();
  else if (this->SessionFdo.is_open())
    this->SessionFdo.close();
  else {
    string	errmsg("Couldn't close session file : ");
    this->error(errmsg.append(this->SessionFile), false);
  }
}
