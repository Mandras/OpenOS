# # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #
# OpenOS                                                                #
# GPL license - opensource project                                      #
# Developed by One Solution Network                                     #
#                                                                       #
# File: Makefile                                                        #
#                                                                       #
# Utilities: Compile the entire module as a library                     #
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

NAME			=	RemoteAccess

AR			=	ar

ARFLAGS			=	rcs

CPP			=	g++

CFLAGS			=	-W -Wall -Wextra -ansi -pedantic

MODULE_OBJECT 		=	$(MODULE_SOURCES:.cpp=.o)

MODULE			=	../../libraries/$(NAME).a

LDFLAGS			=

INCLUDES		=

DEBUG			=	no

DEBUGFLAGS		=
ifeq ($(DEBUG), yes)
DEBUGFLAGS		=	-g
endif

MODULE_SOURCES		=	sources/RemoteAccess.cpp

.SUFFIXES		:	.cpp

all			:	$(MODULE)

default			:	$(MODULE)

.cpp.o			:
				$(CPP) $(INCLUDES) $(CFLAGS) -c $< -o $@

$(MODULE)		:	$(MODULE_OBJECT)
				$(AR) $(ARFLAGS) $(MODULE) $(MODULE_OBJECT)

.PHONY			:	clean fclean re

clean			:
				@rm -vf *.o
				@rm -vf sources/*.o

fclean			:	clean
				@rm -vf *~
				@rm -vf \#*\#
				@rm -vf sources/*~
				@rm -vf sources/\#*\#
				@rm -vf headers/*~
				@rm -vf headers/\#*\#
				@rm -vf $(MODULE)

re			:	fclean all