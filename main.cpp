/********************************************************************************
*                                                                               *
*    Copyright (C) 2011 Todo-Redes. <http://www.todo-redes.com>                 *
*    Fco. Javier M. C. <fcojavmc@todo-redes.com>                                *
*                                                                               *
*    This file is part of ScreenTicket.                                         *
*                                                                               *
*    ScreenTicket is free software: you can redistribute it and/or modify       *
*    it under the terms of the GNU General Public License as published by       *
*    the Free Software Foundation, either version 3 of the License, or          *
*    (at your option) any later version.                                        *
*                                                                               *
*    ScreenTicket is distributed in the hope that it will be useful,            *
*    but WITHOUT ANY WARRANTY; without even the implied warranty of             *
*    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the               *
*    GNU General Public License for more details.                               *
*                                                                               *
*    You should have received a copy of the GNU General Public License          *
*    along with ScreenTicket. If not, see <http://www.gnu.org/licenses/>.       *
*                                                                               *
*********************************************************************************/

#include <stdio.h>

#include <QApplication>
#include <QString>
#include <QStringList>

#include "mainwindow.h"

#define PROGRAM_VERSION "1.0.0"


int main(int argc, char * argv[])
{
    int r = 0;
    
    try {

        QApplication app(argc, argv);

	QStringList args = app.arguments();
	
	QRegExp rxCupsPrinter("--file=(.{1,})");
	QRegExp rxPrinterTitle("--title=(.{1,})");
	QRegExp rxVersion("--version");
	QRegExp rxHelp("--help");

	g_mainWindow = new MainWindow;
        g_mainWindow->show();
        bool runProgram = false;
        bool showHelp = true;
	
	for (int i = 1; i < args.size(); ++i) {
	
	    if (rxCupsPrinter.indexIn(args.at(i)) != -1 ) {
		g_mainWindow->setFileToWatch(rxCupsPrinter.cap(1));
		runProgram = true;
	    } // end if

	    if (rxPrinterTitle.indexIn(args.at(i)) != -1 ) {
		g_mainWindow->setPrinterTitle(rxPrinterTitle.cap(1));
	    } // end if
	
	    if (rxVersion.indexIn(args.at(i)) != -1 ) {
		QString version = QString("ScreenTicket v.") + QString(PROGRAM_VERSION) + QString("\n\n");
        fprintf(stdout, version.toLatin1());
		fprintf(stdout, "Copyright (C) 2011 Todo-Redes <http://www.todo-redes.com>.\n");
		fprintf(stdout, "Fco. Javier M. C. <fcojavmc@todo-redes.com>\n");
		fprintf(stdout, "License GPLv3+: GNU GPL version 3 or later <http://gnu.org/licenses/gpl.html>.\n");
		fprintf(stdout, "This is free software: you are free to change and redistribute it.\n");
		fprintf(stdout, "There is NO WARRANTY, to the extent permitted by law.\n");

		runProgram = false;
		showHelp = false;
	    } // end if
	    
	    if (rxHelp.indexIn(args.at(i)) != -1 ) {
		runProgram = false;
		break;
	    } // end if
	
	} // end for 


	if (runProgram) {
	    r = app.exec();
	} else {
	    if (showHelp) {
		fprintf(stdout, "Usage: screenticket --file=<file> [--title=<title>]\n\n");
		fprintf(stdout, "Arguments:\n");
		fprintf(stdout, "  --file=FILE       File to monitor, like CUPS printer redirected to this file.\n");
		fprintf(stdout, "  --title=TITLE     Title to show at the top of the GUI layout.\n");
		fprintf(stdout, "  --version         Shows the version of the program.\n");
		fprintf(stdout, "  --help            Shows this help text.\n\n");
		fprintf(stdout, "Copyright (c) 2011 Todo-Redes. <http://www.todo-redes.com>. License GPLv3+: GNU GPL version 3 or later <http://gnu.org/licenses/gpl.html>.");
		fprintf(stdout, "This is free software: you are free to change and redistribute it. There is NO WARRANTY, to the extent permitted by law.\n");
	    } // end if
        } // end if


    } catch (...) {
	fprintf(stderr, "EXCEPCION\n");
    } // end try

    return r;
}



