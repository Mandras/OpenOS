/*# # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #
# OpenOS                                                                #
# GPL license - opensource project                                      #
# Developed by One Solution Network                                     #
#                                                                       #
# File: main.cpp                                                        #
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
#include <signal.h>

#include <iostream>
#include <limits>

using namespace std;

char			**argv;
char			**envp;
int			argc;

const int		MAX_INT			=       numeric_limits<int>::max();
const int		MIN_INT			=       numeric_limits<int>::min();
const long int		MAX_LONG_INT		=       numeric_limits<long int>::max();
const long int		MIN_LONG_INT		=       numeric_limits<long int>::min();
const short int		MAX_SHORT_INT		=	numeric_limits<short int>::max();
const short int		MIN_SHORT_INT		=	numeric_limits<short int>::min();
const unsigned int	MAX_UNSIGNED_INT	=       numeric_limits<unsigned int>::max();
const unsigned int	MIN_UNSIGNED_INT	=       numeric_limits<unsigned int>::min();
const unsigned long int MAX_UNSIGNED_LONG_INT	=       numeric_limits<unsigned long int>::max();
const unsigned long int MIN_UNSIGNED_LONG_INT	=       numeric_limits<unsigned long int>::min();

bool			LOOP			=	true;
bool			ENDL			=	false;

extern string		PROTECTED_SYSTEM;
extern time_t		OPENOS_DELAY;

void			printPing(string HostIP, int C) {
  time_t		rawtime;
  struct tm		*timeinfo;
  char			Date[80];

  time(&rawtime);
  timeinfo = localtime(&rawtime);
  strftime(Date, 80,"%Y-%m-%d %H:%M:%S", timeinfo);
  cout << "\r" << flush;
  cout << Date << " [" << ::PROTECTED_SYSTEM << "]\tPing: " << HostIP
       << " | Response: C_WAIT_ALL (" << C << " pings)" << flush;
  ::ENDL = true;
}

void			bindCtrlC(int sig) {
  time_t		rawtime;
  struct tm		*timeinfo;
  char			Date[80];

  time(&rawtime);
  timeinfo = localtime(&rawtime);
  strftime(Date, 80,"%Y-%m-%d %H:%M:%S", timeinfo);

  ::LOOP = false;
  (void) signal(SIGINT, SIG_DFL);
  if (::ENDL == true)
    cout << endl;
  ::ENDL = false;
  cout << Date << " [" << ::PROTECTED_SYSTEM << "]\t"
       << PROGNAME << ": Receive signal: " << sig << endl;
}

int			main(int argc, char **argv, char **envp) {
  ::argv = argv;
  ::envp = envp;
  ::argc = argc;

  unsigned long int	C = ::MIN_UNSIGNED_LONG_INT;
  OpenOS		OS;

  (void) signal(SIGINT, &bindCtrlC);

  for (C++; ::LOOP ; C++) {
    if (C == ::MAX_UNSIGNED_LONG_INT)
      C = ::MIN_UNSIGNED_LONG_INT;
    printPing(OS.getHostIP(), C);
    sleep(::OPENOS_DELAY);
  }

  return (EXIT_SUCCESS);
}
