# # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #
# OpenOS                                                                #
# GPL license - opensource project                                      #
# Developed by One Solution Network                                     #
#                                                                       #
# File: Makefile                                                        #
#                                                                       #
# Utilities: Compile the entire program                                 #
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
# # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #

MODULES		=				\
			RemoteAccess		\
			BackupManager

PROGRAM		=	openos

DEBUG_MODE	=	yes

CPP		=	g++

AR		=	ar

CFLAGS		=	-W -Wall -Wextra -ansi -pedantic

LDFLAGS		=	-L.

PROGRAM_OBJECT	=	$(PROGRAM_SOURCES:.cpp=.o)

LIBRAIRIES	=	$(MODULES:%=libraries/%.a)

ROOTDIR		=	$(shell pwd)

CUSER		=	$(shell whoami)

OPSYS		=	$(shell uname -s)

HOSTNAME	=	$(shell uname -n)

KERNELR		=	$(shell uname -r)

KERNELV		=	$(shell uname -v)

PROCESS		=	$(shell uname -p)

DEBUGFLAGS	=
ifeq ($(DEBUG_MODE), yes)
DEBUGFLAGS	=	-g
endif

PROGRAM_SOURCES	=	sources/main.cpp		\
			sources/headquarters.cpp	\
			sources/openOS.cpp		\
			sources/socket.cpp		\
			sources/session.cpp		\
			sources/config.cpp		\
			sources/logs.cpp		\
			sources/error.cpp		\
			sources/options.cpp		\
			sources/printMessage.cpp

all		:	$(MODULES) $(PROGRAM)

$(PROGRAM)	:	$(PROGRAM_OBJECT)
			$(CPP) -o $@ $(CFLAGS) $(DEBUGFLAGS) $^ $(LDFLAGS) $(LIBRAIRIES)

$(MODULES)	:
			@cd modules/$@/ ; make -f Makefile

.PHONY		: 	clean fclean re list help $(PROGRAM) $(MODULES)

clean		:
			@rm -vf *.o
			@rm -vf sources/*.o

fclean		:	clean
			@rm -vf *~
			@rm -vf \#*\#
			@rm -vf sources/*~
			@rm -vf sources/\#*\#
			@rm -vf headers/*~
			@rm -vf headers/\#*\#
			@rm -vf $(PROGRAM)

re		:	fclean all

list		:
			@echo "PROGRAM NAME    $(PROGRAM)"
			@echo "CPP COMPILER    $(CPP)"
			@echo "COMPILER FLAGS  $(CFLAGS)"
			@echo "DEBUG MODE      $(DEBUG_MODE)"
			@echo "LDFLAGS         $(LDFLAGS)"
			@echo "DIRECTORY       $(ROOTDIR)"
			@echo "OPERATING SYS   $(OPSYS)"
			@echo "CURRENT USER    $(CUSER)"
			@echo "HOSTNAME        $(HOSTNAME)"
			@echo "KERNEL RELEASE  $(KERNELR)"
			@echo "KERNEL VERSION  $(KERNELV)"
			@echo "PROCESSOR       $(PROCESS)"
			@echo "MODULES         $(MODULES)"
			@echo "LIBRAIRIES      $(LIBRAIRIES)"
			@echo "OPENOS SOURCES  $(PROGRAM_SOURCES)"

help		:
			@echo "make            To compile the OpenOS program in current environment"
			@echo "make <module>   To compile the specified module"
			@echo "make help       To get this listing"
			@echo "make clean      Remove *.o"
			@echo "make fclean     Remove *.o, executable files and temporary files"
			@echo "make re         Similar to make fclean + make all"
			@echo "make list       List the compilers in current environment"