/*# # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #
# OpenOS                                                                #
# GPL license - opensource project                                      #
# Developed by One Solution Network                                     #
#                                                                       #
# File: options.cpp                                                     #
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
#include <cstring>

using namespace std;

extern char	**argv;
extern char	**envp;
extern int	argc;

extern string	OPENOS_USER;
extern time_t	OPENOS_DELAY;
extern bool	OPENOS_COLOR;

bool		isValidAndSetOption_D(int i) {
  if (!(i < ::argc)) return (false);
  for (int j = 0 ; ::argv[i][j] != '\0' ; j++) if (::argv[i][j] < '0' || ::argv[i][j] > '9') return (false);
  if (atoi(::argv[i]) <= 0) return (false);
  ::OPENOS_DELAY = atoi(::argv[i]);
  return (true);
}

void		Headquarters::loadOptions() {
  string	option = "option: ";
  int		i;

  for (i = 1 ; i < ::argc ; i++) {
    if (strcmp(::argv[i], "-c") == 0 || strcmp(::argv[i], "--color") == 0)
      this->setColorOn();
    else if (strcmp(::argv[i], "-d") == 0 || strcmp(::argv[i], "--delay") == 0)
      if (isValidAndSetOption_D(i + 1) == true) i++;
      else this->error(option.append(::argv[i]) + " require a valid time_t argument", true);
    else this->error(option.append(::argv[i]) + " unknow option, please see -h or --help", true);
  }
}
