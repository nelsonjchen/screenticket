#/********************************************************************************
#*                                                                               *
#*    Copyright (C) 2011 Todo-Redes. <http://www.todo-redes.com>                 *
#*    Fco. Javier M. C. <fcojavmc@todo-redes.com>                                *
#*                                                                               *
#*    This file is part of ScreenTicket.                                         *
#*                                                                               *
#*    ScreenTicket is free software: you can redistribute it and/or modify       *
#*    it under the terms of the GNU General Public License as published by       *
#*    the Free Software Foundation, either version 3 of the License, or          *
#*    (at your option) any later version.                                        *
#*                                                                               *
#*    ScreenTicket is distributed in the hope that it will be useful,            *
#*    but WITHOUT ANY WARRANTY; without even the implied warranty of             *
#*    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the               *
#*    GNU General Public License for more details.                               *
#*                                                                               *
#*    You should have received a copy of the GNU General Public License          *
#*    along with ScreenTicket. If not, see <http://www.gnu.org/licenses/>.       *
#*                                                                               *
#*********************************************************************************/




HEADERS =   mainwindow.h

SOURCES =   main.cpp \
	    mainwindow.cpp

FORMS =     mainwindowbase.ui


DESTDIR = $$(PWD)

target.path = /usr/bin/

sources.files = $$SOURCES $$HEADERS $$RESOURCES *.pro
INSTALLS += target

