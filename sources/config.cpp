/*# # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #
# OpenOS                                                                #
# GPL license - opensource project                                      #
# Developed by One Solution Network                                     #
#                                                                       #
# File: config.cpp                                                      #
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

#include <stdlib.h>

#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <map>

using namespace std;

extern string		OPENOS_USER;

string			epurString(string str) {
  string::iterator	it;
  string		ret = "";

  for (it = str.begin() ; it != str.end() && (*it == ' ' || *it == '\t' || *it == '\n') ; ++it) {}
  for ( ; it != str.end() ; ++it) {
    if (*it == ' ' || *it == '\t' || *it == '\n') {
      for ( ; it != str.end() && (*it == ' ' || *it == '\t' || *it == '\n') ; ++it) {}
      if (it == str.end() || *it == '#')
	return (ret);
      ret += ' ';
    }
    if (*it == '#')
      return (ret);
    ret += *it;
  }
  return (ret);
}

string		 Headquarters::getConfigLine(string title, string line) {
  if (this->isConfigTitleExist(title) == false)
    return (_NULL_);

  vector<string> vecarray;
  istringstream  iss;
  string	 word;

  vecarray = getConfigTitle(title);
  for (vector<string>::iterator it = vecarray.begin(); it != vecarray.end(); ++it) {
    iss.str(*it);
    getline(iss, word, '=');
    if (epurString(word) == line) {
      getline(iss, word, '=');
      return (epurString(word));
    }
  }
  return (_NULL_);
}

void		Headquarters::checkRequireConfigLine(string title, string *tab) {
  for (int i = 0; tab[i] != _NULL_; i++) {
    if (getConfigLine(title, tab[i]) == _NULL_) {
      string	errmsg("Missing require configuration information : ");
      string	info("You may try following command(s): sudo cp ");
      string	s;

      this->printMessage(errmsg.append(tab[i]), CRITICAL);
      info += (string)this->ConfigFile + (string)" ." + (string)this->ConfigFile + (string)".old2";
      this->printMessage(info, INFO);

      info = "                                  sudo cp .";
      info += (string)this->ConfigFile + (string)".old1" + (string)" " + (string)this->ConfigFile;
      this->printMessage(info, INFO);

      info = "                                  sudo chown ";
      
      info += ::OPENOS_USER.append(" ") += this->ConfigFile;
      this->printMessage(info, INFO);

      info = "                                  sudo chmod 0644 ";
      info.append(this->ConfigFile);
      this->printMessage(info, INFO);

      exit(EXIT_FAILURE);
    }
  }
}

void		Headquarters::checkRequireConfigLine(string *tab) {this->checkRequireConfigLine(PROGNAME, tab);}

void		Headquarters::printAllConfig() {
  for (vector<string>::iterator it = this->ConfigBuffer.begin(); it != this->ConfigBuffer.end(); ++it)
    cout << *it << endl;
}

void		Headquarters::printConfig(string title) {
  if (this->isConfigTitleExist(title) == false)
    return ;

  vector<string> vecarray;

  vecarray = getConfigTitle(title);
  for (vector<string>::iterator it = vecarray.begin(); it != vecarray.end(); ++it)
    cout << *it << endl;
}

void		Headquarters::printConfig() {this->printConfig(PROGNAME);}

vector<string>	 Headquarters::getConfigTitle(string title) {
  vector<string> vecarray;

  if (this->isConfigTitleExist(title) == false)
    return (vecarray);

  string	 search_start = '[' + title + ']';
  string	 search_end = "[/" + title + ']';

  for (vector<string>::iterator it = this->ConfigBuffer.begin(); it != this->ConfigBuffer.end(); ++it) {
    if (*it == search_start) {
      for (++it ; it != this->ConfigBuffer.end() && *it != search_end ; ++it)
	vecarray.push_back(*it);
    }
  }
  return (vecarray);
}

bool		Headquarters::isConfigTitleExist(string title) {
  string	search = '[' + title + ']';

  for (vector<string>::iterator it = this->ConfigBuffer.begin(); it != this->ConfigBuffer.end(); ++it) {
    if (*it == search)
      return (true);
  }
  return (false);
}

void		Headquarters::ReadConfigFile() {
  if (!(this->ConfigFdi.is_open()))
    this->OpenInputConfigFile();

  string	line;

  while (!(this->ConfigFdi.eof())) {
    getline(this->ConfigFdi, line);
    line = epurString(line);
    if (line.length() > 2)
      this->ConfigBuffer.push_back(line);
  }
  this->CloseConfigFile();
}

void		Headquarters::OpenInputConfigFile() {
  if (this->ConfigFdi.is_open())
    this->CloseConfigFile();
  this->ConfigFdi.open(this->ConfigFile, fstream::in);
  if (!(this->ConfigFdi.is_open())) {
    string	errmsg("Couldn't open [READ] config file : ");
    string	info("You may try following command(s): sudo chown ");

    this->printMessage(errmsg.append(this->ConfigFile), CRITICAL);
    info += ::OPENOS_USER.append(" ") += this->ConfigFile;
    this->printMessage(info, INFO);

    info = "                                  sudo chmod 0644 ";
    info.append(this->ConfigFile);
    this->printMessage(info, INFO);
    exit(EXIT_FAILURE);
  }
}

void		Headquarters::CloseConfigFile() {
  if (this->ConfigFdi.is_open())
    this->ConfigFdi.close();
  else {
    string	errmsg("Couldn't close config file : ");
    this->error(errmsg.append(this->ConfigFile), false);
  }
}

string		Headquarters::getConfigLine(string line) {return (this->getConfigLine(PROGNAME, line));}
