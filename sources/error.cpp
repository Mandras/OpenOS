/*# # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #
# OpenOS                                                                #
# GPL license - opensource project                                      #
# Developed by One Solution Network                                     #
#                                                                       #
# File: error.cpp                                                       #
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

#include <unistd.h>
#include <stdlib.h>

#include <iostream>

using namespace std;

extern bool	option_c;

void		Headquarters::error(string ModuleName, string ErrorDescription, bool isCritical) {
  if (isCritical == true) {
    printMessage(ModuleName, ErrorDescription, CRITICAL);
    this->addLogs(ModuleName, ErrorDescription, CRITICAL);
    exit(EXIT_FAILURE);
  }
  printMessage(ModuleName, ErrorDescription, ERROR);
  this->addLogs(ModuleName, ErrorDescription, ERROR);
}

void		Headquarters::error(string ErrorDescription, bool isCritical) {this->error(PROGNAME, ErrorDescription, isCritical);}
