/*# # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #
# OpenOS                                                                #
# GPL license - opensource project                                      #
# Developed by One Solution Network                                     #
#                                                                       #
# File: headquarters.cpp                                                #
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
#include <string.h>

#include <iostream>

using namespace std;

/*# # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #
#                Default values for openOS options                      #
# # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #*/

string		OPENOS_USER	=	DEFAULT_USER;
time_t		OPENOS_DELAY	=	DEFAULT_DELAY;
bool		OPENOS_COLOR	=	false;

/*# # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #*/

Headquarters::Headquarters() : SessionFile("/etc/openOS/.session"),
			       ConfigFile("/etc/openOS/openOS.ini"),
			       LogsFile("/var/log/openOS") {
  /*string	SocketMessage;*/
    string	HostIP = "127.0.0.1";

  this->loadOptions();

  this->printWelcomeMessage();
  //this->addLogs(SYSTEM_START, SYSTEM);
  this->printMessage(SYSTEM_START, SYSTEM);

  this->ReadConfigFile();

  this->DecryptSessionFile();

  this->setSessionTitle(PROGNAME);

  this->HostIP = new char[HostIP.size() + 1];
  this->HostIP[HostIP.size()] = '\0';
  memcpy(this->HostIP, HostIP.c_str(), HostIP.size());

  //this->printAllConfig();

  string	tab[] = {
    "user",
    _NULL_
  };

  this->checkRequireConfigLine(tab);

  /*SocketMessage = "GET /?test=1 \n\n";

  this->HostIP = new char[HostIP.size() + 1];
  this->HostIP[HostIP.size()] = '\0';
  memcpy(this->HostIP, HostIP.c_str(), HostIP.size());

  this->SocketMessage = new char[SocketMessage.size() + 1];
  this->SocketMessage[SocketMessage.size()] = '\0';
  memcpy(this->SocketMessage, SocketMessage.c_str(), SocketMessage.size());

  this->SocketMessageSize = SocketMessage.size();

  this->HostPort = 80;

  this->printSession();
  */
}

Headquarters::~Headquarters() {
  this->EncryptSessionFile();
  this->addLogs(SYSTEM_END, SYSTEM);
  this->printMessage(SYSTEM_END, SYSTEM);
}

char		*Headquarters::getSocketMessage()	{return (this->SocketMessage);}
string		Headquarters::getSocketAnswer()		{return (this->SocketAnswer);}
string		Headquarters::getHostIP()		{return (this->HostIP);}
int		Headquarters::getHostPort()		{return (this->HostPort);}

void		Headquarters::setSocketMessage(char *SocketMessage)	{this->SocketMessage = SocketMessage;}
void		Headquarters::setHostIP(char *HostIP)			{this->HostIP = HostIP;}
void		Headquarters::setHostPort(int HostPort)			{this->HostPort = HostPort;}
void		Headquarters::setSocketAnswer(string SocketAnswer)	{this->SocketAnswer = SocketAnswer;}
