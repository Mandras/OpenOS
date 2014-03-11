/*# # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #
# OpenOS                                                                #
# GPL license - opensource project                                      #
# Developed by One Solution Network                                     #
#                                                                       #
# File: RemoteAccess.hpp                                                #
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

#ifndef  REMOTEACCESS
#define  REMOTEACCESS

#include "../../../headers/Headquarters.hpp"

#include <iostream>
#include <vector>

using namespace std;

class		RemoteAccess : virtual protected Headquarters {
private :
  static const string	moduleName;
  bool			isActivate;
public :
  RemoteAccess();
  ~RemoteAccess();

  bool			getIsActivate();
  string		getModuleName();

private :
  string		getConfigLine(string);
  void			error(string, bool);
  void			addLogs(string, int);
  vector<string>	getSessionTitle();
  void			insertSessionLine(string);
  void			printSession();
  void			checkRequireConfigLine(string *);
  void			printMessage(string, int);
  void			printMessage(string);

protected :

  vector<string>	getConfigTitle();
  void			printConfig();
};

#endif
