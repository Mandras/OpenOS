/*# # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #
# OpenOS                                                                #
# GPL license - opensource project                                      #
# Developed by One Solution Network                                     #
#                                                                       #
# File: logs.cpp                                                        #
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
#include <cstdio>
#include <ctime>
#include <fstream>

using namespace std;

extern string	PROTECTED_CRITICAL;
extern string	PROTECTED_ERROR;
extern string	OPENOS_USER;

void		Headquarters::addLogs(string ModuleName, string LogDescription, int ErrorLvl) {
  string	LogType;

  switch (ErrorLvl)      {
  case CRITICAL    :     {	LogType = STRING_CRITICAL;    break; }
  case ERROR       :     {	LogType = STRING_ERROR;       break; }
  case WARNING     :     {	LogType = STRING_WARNING;     break; }
  case INFO        :     {	LogType = STRING_INFO;        break; }
  case SYSTEM      :     {	LogType = STRING_SYSTEM;      break; }
  case MODULE      :     {	LogType = STRING_MODULE;      break; }
  default          :     {	LogType = STRING_DEFAULT;            }
  }
  this->OpenOutputLogsFile();
  this->WriteLog(ModuleName, LogDescription, LogType);
  this->CloseLogsFile();
}

void		Headquarters::WriteLog(string ModuleName, string LogDescription, string LogType) {
  time_t	rawtime;
  struct tm	*timeinfo;
  char		Date[80];

  time(&rawtime);
  timeinfo = localtime(&rawtime);
  strftime(Date, 80,"%Y-%m-%d %H:%M:%S", timeinfo);

  if (!(this->LogsFdo.is_open()))
    this->OpenOutputLogsFile();
  this->LogsFdo << Date << " [" << LogType << "]\t" << ModuleName << ": " << LogDescription << endl;
}

void		Headquarters::OpenOutputLogsFile() {
  if (this->LogsFdo.is_open())
    this->CloseLogsFile();
  this->LogsFdo.open(this->LogsFile, fstream::out | fstream::app);
  if (!(this->LogsFdo.is_open())) {
    string	errmsg("Couldn't open [WRITE] logs file : ");
    string	info("You may try following command(s): sudo chown ");

    this->printMessage(errmsg.append(this->LogsFile), CRITICAL);
    info += ::OPENOS_USER.append(" ") += this->LogsFile;
    this->printMessage(info, INFO);

    info = "                                  sudo chmod 0640 ";
    info.append(this->LogsFile);
    this->printMessage(info, INFO);

    exit(EXIT_FAILURE);
  }
}

void		Headquarters::CloseLogsFile() {
  if (this->LogsFdo.is_open())
    this->LogsFdo.close();
  else {
    string	errmsg("Couldn't close logs file : ");
    this->printMessage(errmsg.append(this->LogsFile), ERROR);
  }
}

void		Headquarters::addLogs(string LogDescription, int ErrorLvl) {this->addLogs(PROGNAME, LogDescription, ErrorLvl);}
