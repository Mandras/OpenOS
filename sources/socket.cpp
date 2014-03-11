/*# # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #
# OpenOS                                                                #
# GPL license - opensource project                                      #
# Developed by One Solution Network                                     #
#                                                                       #
# File: socket.cpp                                                      #
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
#include <sys/socket.h>
#include <arpa/inet.h>
#include <resolv.h>
#include <iostream>

using namespace std;

void     Headquarters::sendSocket(void) {
  struct sockaddr_in addr;
  int	 s;
  
  if ((s = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
    cerr << "Error 01: creating socket failed!\n";
    close(s);
    return;
  }

  addr.sin_family = AF_INET;
  addr.sin_port = htons(this->HostPort);
  inet_aton(this->HostIP, &addr.sin_addr);

  if ((connect(s, (sockaddr *) &addr, sizeof(addr))) != 0) {
    cerr << "Error 02: conecting to server failed!\n";
    close(s);
    return;
  }

  send(s, this->SocketMessage, this->SocketMessageSize, 0);

  ssize_t len = 0;

  this->SocketAnswer = "";
  while ((len = recv(s, this->SocketBuffer, OPENOS_RECVSIZE, 0)) > 0) {
    this->SocketBuffer[len] = '\0';
    this->SocketAnswer += this->SocketBuffer;
  }

  close(s);
  return;
}

