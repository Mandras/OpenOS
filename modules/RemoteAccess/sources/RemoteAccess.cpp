/*# # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #
# OpenOS                                                                #
# GPL license - opensource project                                      #
# Developed by One Solution Network                                     #
#                                                                       #
# File: RemoteAccess.cpp                                                #
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

#include "../headers/RemoteAccess.hpp"

#include <iostream>
#include <vector>

using namespace std;

const string RemoteAccess::moduleName = "RemoteAccess";

RemoteAccess::RemoteAccess() : isActivate(true) {
  string	tab[] = {
    _NULL_
  };
  this->checkRequireConfigLine(tab);
  this->addLogs(MODULE_START, MODULE);
  this->printMessage(MODULE_START, MODULE);
  this->Headquarters::setSessionTitle(this->getModuleName());
}

RemoteAccess::~RemoteAccess() {
  this->addLogs(MODULE_END, MODULE);
  this->printMessage(MODULE_END, MODULE);
}

bool		RemoteAccess::getIsActivate() {return (this->isActivate);}

string		RemoteAccess::getModuleName() {return (this->moduleName);}

void		RemoteAccess::error(string ErrorDescription, bool isCritical) {
  this->Headquarters::error(this->getModuleName(), ErrorDescription, isCritical);
}

void		RemoteAccess::addLogs(string LogDescription, int ErrorLvl) {
  this->Headquarters::addLogs(this->getModuleName(), LogDescription, ErrorLvl);
}

vector<string>	RemoteAccess::getSessionTitle() {
  return (this->Headquarters::getSessionTitle(this->getModuleName()));
}

void		RemoteAccess::checkRequireConfigLine(string *tab) {
  this->Headquarters::checkRequireConfigLine(this->getModuleName(), tab);
}

void		RemoteAccess::insertSessionLine(string line) {
  this->Headquarters::insertSessionLine(this->getModuleName(), line);
}

void		RemoteAccess::printSession() {
  this->Headquarters::printSession(this->getModuleName());
}

vector<string>	RemoteAccess::getConfigTitle() {
  return (this->Headquarters::getConfigTitle(this->getModuleName()));
}

void		RemoteAccess::printConfig() {
  this->Headquarters::printConfig(this->getModuleName());
}

string		RemoteAccess::getConfigLine(string line) {
  return (this->Headquarters::getConfigLine(this->getModuleName(), line));
}

void		RemoteAccess::printMessage(string Message, int MessageLvl) {
  this->Headquarters::printMessage(this->getModuleName(), Message, MessageLvl);
}

void		RemoteAccess::printMessage(string Message) {
  this->Headquarters::printMessage(this->getModuleName(), Message, -1);
}
