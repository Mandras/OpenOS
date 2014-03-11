/*# # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #
# OpenOS                                                                #
# GPL license - opensource project                                      #
# Developed by One Solution Network                                     #
#                                                                       #
# File: Headquarters.hpp                                                #
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

#ifndef	HEADQUARTERS
#define	HEADQUARTERS

#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

#define PROGNAME	"OpenOS"
#define PROGVERSION	"0.1"
#define DEFAULT_USER	"openos"
#define DEFAULT_DELAY	5

#define	OPENOS_RECVSIZE	1024
#define	_NULL_		"\0"

#define SYSTEM_START	"Has started, loading modules ..."
#define MODULE_START	"Has been launch"
#define SYSTEM_END	"Stop, exiting ..."
#define MODULE_END	"Stop"

#define STRING_CRITICAL	"CRITICAL"
#define STRING_ERROR	" ERROR  "
#define	STRING_WARNING	"WARNING "
#define STRING_INFO	"  INFO  "
#define STRING_SYSTEM	" SYSTEM "
#define STRING_MODULE	" MODULE "
#define STRING_DEFAULT	" ------ "

#define C_RED		"\033[1;31m"
#define C_GREEN		"\033[1;32m"
#define C_YELLOW	"\033[1;33m"
#define C_BLUE		"\033[1;34m"
#define C_PURPLE	"\033[1;35m"
#define C_CYAN		"\033[1;36m"
#define C_DEFAULT	"\033[0m"

enum {
  CRITICAL,
  ERROR,
  WARNING,
  INFO,
  SYSTEM,
  MODULE
};

class			Headquarters {
private :
  const char		*SessionFile;
  const char		*ConfigFile;
  const char		*LogsFile;
  vector<string>	SessionBuffer;
  vector<string>	ConfigBuffer;
  string		EncryptKey;
  char			SocketBuffer[OPENOS_RECVSIZE];
  unsigned int		SocketMessageSize;
  char			*SocketMessage;
  ifstream		SessionFdi;
  ofstream		SessionFdo;
  ifstream		ConfigFdi;
  ofstream		LogsFdo;

protected :
  char			*HostIP;
  unsigned int		HostPort;
  string		SocketAnswer;

public :
  Headquarters();
  ~Headquarters();

  string		getHostIP();

protected :
  void			error(string, string, bool);
  void			addLogs(string, string, int);

  vector<string>	getSessionTitle(string);
  void			setSessionTitle(string);
  void			insertSessionLine(string, string);
  void			printSession(string);

  vector<string>	getConfigTitle(string);
  string		getConfigLine(string, string);
  void			printConfig(string);
  void			checkRequireConfigLine(string, string *);

  void			printMessage(string, string, int);
  void			printWelcomeMessage();

  string		getSocketAnswer();
  char			*getSocketMessage();
  int			getHostPort();

  void			setSocketMessage(char *);
  void			setHostIP(char *);
  void			setHostPort(int);
  void			setSocketAnswer(string);

private :
  void			error(string, bool);
  void			addLogs(string, int);
  void			WriteLog(string, string, string);
  void			checkRequireConfigLine(string *);
  string		getConfigLine(string);
  void			ReadConfigFile();
  void			loadOptions();
  void			printAllSession();
  void			printAllConfig();
  void			printSession();
  void			printConfig();
  void			printMessage(string, int);
  void			printMessage(string);
  void			sendSocket();
  bool			isSessionTitleExist(string);
  bool			isConfigTitleExist(string);
  void			EncryptSessionFile();
  void			DecryptSessionFile();
  void			restoreSession();
  void			OpenInputConfigFile();
  void			OpenOutputSessionFile();
  void			OpenInputSessionFile();
  void			OpenOutputLogsFile();
  void			CloseConfigFile();
  void			CloseSessionFile();
  void			CloseLogsFile();
  void			setColorOn();
  void			setEncryptKey(string);
  string		getEncryptKey();
  string		StringToHex(const string &);
  string		HexToString(const string &);
};

#endif
