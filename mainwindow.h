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

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtGui>
#include <QMainWindow>
#include <QFileSystemWatcher>
#include <QList>

class MainWindow;

#include "ui_mainwindowbase.h"


class MainWindow : public QMainWindow, public Ui_MainWindowBase
{
    Q_OBJECT
    
private:
    QFileSystemWatcher *m_watcher;
    QString m_fileToWatch;
    QString m_printerTitle;
    QString m_cupsPrinter;
    QString convertEscPosToQString(QByteArray blob);
    QList<QString> m_tags;

public:
    MainWindow( QWidget * parent = 0 );
    void setFileToWatch(QString fileName);
    void setPrinterTitle(QString title);


public slots:
    void on_mui_quit_clicked();
    void ticketPrinterFileChanged(const QString &path);

};

extern MainWindow *g_mainWindow;


#endif

