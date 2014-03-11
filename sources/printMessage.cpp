/*# # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #
# OpenOS                                                                #
# GPL license - opensource project                                      #
# Developed by One Solution Network                                     #
#                                                                       #
# File: printMessage.cpp                                                #
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

using namespace std;

extern bool	OPENOS_COLOR;

string		PROTECTED_CRITICAL    = STRING_CRITICAL;
string		PROTECTED_ERROR       = STRING_ERROR;
string		PROTECTED_WARNING     = STRING_WARNING;
string		PROTECTED_INFO        = STRING_INFO;
string		PROTECTED_SYSTEM      = STRING_SYSTEM;
string		PROTECTED_MODULE      = STRING_MODULE;
string		PROTECTED_DEFAULT     = STRING_DEFAULT;

void		Headquarters::printMessage(string ModuleName, string Message, int MessageLvl) {
  string	MessageType = ::PROTECTED_DEFAULT;
  time_t	rawtime;
  struct tm	*timeinfo;
  char		Date[80];

  time(&rawtime);
  timeinfo = localtime(&rawtime);
  strftime(Date, 80,"%Y-%m-%d %H:%M:%S", timeinfo);

  switch (MessageLvl)    {
  case CRITICAL    :     {       MessageType = ::PROTECTED_CRITICAL;     break; }
  case ERROR       :     {       MessageType = ::PROTECTED_ERROR;        break; }
  case WARNING     :     {       MessageType = ::PROTECTED_WARNING;      break; }
  case INFO        :     {       MessageType = ::PROTECTED_INFO;         break; }
  case SYSTEM      :     {       MessageType = ::PROTECTED_SYSTEM;       break; }
  case MODULE      :     {       MessageType = ::PROTECTED_MODULE;       break; }
  default          :     {       MessageType = ::PROTECTED_DEFAULT;             }
  }

  if (MessageLvl == CRITICAL || MessageLvl == ERROR)
    cerr << Date << " [" << MessageType << "]\t" << ModuleName << ": " << Message << endl;
  else
    cout << Date << " [" << MessageType << "]\t" << ModuleName << ": " << Message << endl;
}

void		Headquarters::setColorOn() {

  ::OPENOS_COLOR = true;

  ::PROTECTED_CRITICAL = C_RED      +  ::PROTECTED_CRITICAL +  C_DEFAULT;
  ::PROTECTED_ERROR    = C_RED      +  ::PROTECTED_ERROR    +  C_DEFAULT;
  ::PROTECTED_WARNING  = C_YELLOW   +  ::PROTECTED_WARNING  +  C_DEFAULT;
  ::PROTECTED_INFO     = C_BLUE     +  ::PROTECTED_INFO     +  C_DEFAULT;
  ::PROTECTED_SYSTEM   = C_CYAN     +  ::PROTECTED_SYSTEM   +  C_DEFAULT;
  ::PROTECTED_MODULE   = C_GREEN    +  ::PROTECTED_MODULE   +  C_DEFAULT;
  ::PROTECTED_DEFAULT  = C_DEFAULT  +  ::PROTECTED_DEFAULT  +  C_DEFAULT;
}

void		Headquarters::printMessage(string Message, int MessageLvl) {this->printMessage(PROGNAME, Message, MessageLvl);}

void		Headquarters::printMessage(string Message) {this->printMessage(PROGNAME, Message, -1);}

void		Headquarters::printWelcomeMessage() {
  cout << "# # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #" << endl;
  cout << "#                               OpenOS    v0.2                                  #" << endl;
  cout << "# # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #" << endl;
}

