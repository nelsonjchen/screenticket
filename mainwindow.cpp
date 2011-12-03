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
#include <QFile>
#include <QByteArray>

#include "mainwindow.h"


MainWindow *g_mainWindow;


MainWindow::MainWindow( QWidget * parent ) : QMainWindow(parent)
{
    setupUi(this);
    
    m_fileToWatch = "";
    m_printerTitle = "";
    mui_printerTitle->setVisible(false);
    
}



void MainWindow::setFileToWatch(QString fileName)
{
    if (!fileName.isEmpty()) {
        m_fileToWatch = fileName;

	/// 
	QFile file;
	if ( file.exists(fileName) ) {

	    m_watcher = new QFileSystemWatcher(this);
	    m_watcher->addPath(m_fileToWatch);
    
            connect(m_watcher, SIGNAL(fileChanged(const QString)), this, SLOT(ticketPrinterFileChanged(const QString)));
	} else {
	    mui_ticket->setHtml("<b>Error:</b> File not found.");
        } // end if
    
    } // end if
}


void MainWindow::setPrinterTitle(QString title)
{
    if (!title.isEmpty()) {
	m_printerTitle = title;
	mui_printerTitle->setVisible(true);
	mui_printerTitle->setText(title);
    } // end if
}


void MainWindow::on_mui_quit_clicked()
{
    QCoreApplication::exit();
}


void MainWindow::ticketPrinterFileChanged(const QString &path)
{
    /// Lee todo el archivo y lo anyade a lo que hay.
    QFile file(path);
    if (file.open(QIODevice::ReadOnly)) {

        QByteArray blob = file.readAll();        
        mui_ticket->append(convertEscPosToQString(blob));
    
    } else {
	mui_ticket->append("NO SE HA PODIDO LEER ARCHIVO");
    } // end if

}



QString MainWindow::convertEscPosToQString(QByteArray blob)
{
    QString result("");
    char c;

    /// 1D 21 XX = Selecciona tamanyo caracter.
    for (int i=0; i < blob.size(); i++) {
    
	switch (blob[i])
	{
	  
	    case 0x09: /// Horizontal tab
		result.append("&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;");
		break;

	    case 0x0a: /// Line feed
		result.append("<br />");
		c = blob[i];
		break;

	    case 0x0c: /// Print and recover to page mode
		c = blob[i];
		break;

	    case 0x0d: /// Print and carriage return
		c = blob[i];
		break;

	    case 0x18: /// Cancel print data in page mode
		c = blob[i];
		break;
	  
	    case 0x10:
		i++;
		switch (blob[i])
		{
		    case 0x4: /// Real-time status transmission
			i++;
			c = blob[i];
			break;
			
		    case 0x5: /// Real-time request to printer
			i++;
			c = blob[i];
			break;
			
		    case 0x14: /// Real-time output of specified pulse
			i++;
			c = blob[i]; /// n
			i++;
			c = blob[i]; /// m
			i++;
			c = blob[i]; /// t
			break;
			
		} // end switch
		break;
	  
	    case 0x1b:
		i++;
		switch (blob[i])
		{
		    case 0x0c: /// Print data in page mode
			i++;
			c = blob[i];
			break;

		    case 0x20: /// Set character right space amount
			i++;
			c = blob[i];
			break;

		    case 0x21: /// Batch print mode
			i++;
			c = blob[i];
			break;
			
		    case 0x24: /// Name Specify absolute position
			i++;
			c = blob[i]; /// nL
			i++;
			c = blob[i]; /// nH
			break;
			
		    case 0x25: /// Specify/cancel download character set
			i++;
			c = blob[i];
			break;
			
		    case 0x26: /// Define download characters
			// TODO
			break;
			
		    case 0x2a: /// Specify bit image mode
			// TODO
			break;
			
		    case 0x2d: /// Specify/cancels underline mode
			i++;
			/// Mira si <u> existe en la lista. Si existe se cierra y se elimina de la lista.
			/// En caso contrario se abre la etiqueta y se registra en la lista de tags abiertas.
			if (m_tags.lastIndexOf("<u>") != -1) {
			    m_tags.erase( m_tags.begin() + m_tags.lastIndexOf("<u>") );
			    result.append("</u>");
			} else {
			    m_tags.push_back(QString("<u>"));
			    result.append("<u>");
			} // end if
			break;
			
		    case 0x32: /// Set default line spacing
			i++;
			c = blob[i];
			break;
			
		    case 0x33: /// Set line feed amount
			i++;
			c = blob[i];
			break;
			
		    case 0x3d: /// Select peripheral device
			i++;
			c = blob[i];
			break;
			
		    case 0x3f: /// Delete download characters
			i++;
			c = blob[i];
			break;
			
		    case 0x40: /// Initialize printer
			c = blob[i];
			break;
			
		    case 0x44: /// Set horizontal tab position
			// TODO
			break;
			
		    case 0x45: /// Specify/cancel emphasized characters
			i++;
			c = blob[i];
			break;
			
		    case 0x47: /// Specify/cancel double printing
			i++;
			c = blob[i];
			break;
			
		    case 0x4a: /// Print and Paper Feed
			i++;
			c = blob[i];
			break;
			
		    case 0x4c: /// Select page mode
			i++;
			c = blob[i];
			break;
			
		    case 0x4d: /// Select character font
			i++;
			c = blob[i];
			break;
			
		    case 0x52: /// Select international characters
			i++;
			c = blob[i];
			break;
			
		    case 0x53: /// Select standard mode
			c = blob[i];
			break;

		    case 0x54: /// Select character print direction in page mode
			i++;
			c = blob[i];
			break;
			
		    case 0x56: /// Specify/cancel character 90 degree clockwise rotation
			i++;
			c = blob[i];
			break;
			
		    case 0x57: /// Set print region in page mode
			// TODO
			break;
			
		    case 0x5c: /// Specify relative position
			i++;
			c = blob[i]; /// nL
			i++;
			c = blob[i]; /// nH
			break;
			
		    case 0x61: /// Position alignment
			i++;
			c = blob[i];
			break;
			
		    case 0x63:
			i++;
			
			switch (blob[i])
			{
			    case 0x33: /// Select paper out sensor to enable at paper out signal output
				i++;
				c = blob[i];
				break;

			    case 0x34: /// Select paper out sensor to enable at printing stop
				i++;
				c = blob[i];
				break;

			    case 0x35: /// Enable/disable panel switches
				i++;
				c = blob[i];
				break;
			} // end switch
			
			break;
			
		    case 0x64: /// Print and feed paper n lines
			i++;
			c = blob[i];
			break;
			
		    case 0x70: /// Specify pulse
			i++;
			c = blob[i]; /// m
			i++;
			c = blob[i]; /// t1
			i++;
			c = blob[i]; /// t2
			break;
			
		    case 0x74: /// Select character code table
			i++;
			c = blob[i];
			break;
			
		    case 0x7b: /// Specify/cancel upside-down printing
			i++;
			c = blob[i];
			break;
			
		} // end switch
		break;
		
	    case 0x1c:
		// TODO
		break;
	  
	    case 0x1d:
		i++;
		switch (blob[i])
		{
		    case 0x0c: /// Top of form of mark paper
			c = blob[i];
			break;

		    case 0x21: /// Select character size
			i++;
			c = blob[i];
			break;

		    case 0x24: /// Specify absolute position for character vertical direction in page mode
			i++;
			c = blob[i]; /// nL
			i++;
			c = blob[i]; /// nH
			break;

		    case 0x2a: /// Define download bit images
			// TODO
			break;

		    case 0x28: /// Test print
			// TODO
			break;

		    case 0x2f: /// Print download bit images
			i++;
			c = blob[i];
			break;

		    case 0x3a: /// Start/execute macro definition
			i++;
			c = blob[i];
			break;

		    case 0x3c: /// Mechanically initialize printer
			c = blob[i];
			break;

		    case 0x42: /// Specify/cancel white/black inverted printing
			i++;
			c = blob[i];
			break;

		    case 0x43: /// Set counter print mode
			// TODO
			break;

		    case 0x45: /// Set printing speed
			i++;
			c = blob[i];
			break;

		    case 0x48: /// Select HRI character print position
			i++;
			c = blob[i];
			break;

		    case 0x49: /// Transmission of Printer ID
			i++;
			c = blob[i];
			break;

		    case 0x4c: /// Set left margin
			i++;
			c = blob[i]; /// nL
			i++;
			c = blob[i]; /// nH
			break;

		    case 0x50: /// Set basic calculated pitch
			i++;
			c = blob[i]; /// x
			i++;
			c = blob[i]; /// y
			break;

		    case 0x54: /// Move to top of line
			i++;
			c = blob[i];
			break;

		    case 0x56:
			i++;
			c = blob[i]; /// m

			switch (blob[i])
			{
			    /// Cut paper
			    case 0:
			    case 1:
			    case 48:
			    case 49:
				result.append("<hr />");
				break;
			  
			    /// Cut paper
			    case 65:
			    case 66:
				i++;
				c = blob[i]; /// n
				result.append("<hr />");
				break;
			} // end switch
			break;

		    case 0x57: /// Set print region width
			i++;
			c = blob[i]; /// nL
			i++;
			c = blob[i]; /// nH
			break;

		    case 0x5c: /// Specify relative position for character vertical direction in page mode
			i++;
			c = blob[i]; /// nL
			i++;
			c = blob[i]; /// nH
			break;

		    case 0x5e: /// Execute macro
			i++;
			c = blob[i]; /// r
			i++;
			c = blob[i]; /// t
			i++;
			c = blob[i]; /// m
			break;

		    case 0x61: /// Enable/disable transmission of automatic status
			i++;
			c = blob[i];
			break;

		    case 0x62: /// Specify/cancel smoothing
			i++;
			c = blob[i];
			break;

		    case 0x63: /// Print counter
			c = blob[i];
			break;

		    case 0x66: /// Select HRI character font
			i++;
			c = blob[i];
			break;

		    case 0x68: /// Set bar code height
			i++;
			c = blob[i];
			break;

		    case 0x6B: /// Print bar code
			// TODO:
			break;

		    case 0x72: /// Transmission of status
			i++;
			c = blob[i];
			break;
			
		    case 0x76: /// Print raster bit images
			// TODO:
			break;

		    case 0x77: /// Set bar code horizontal size
			i++;
			c = blob[i];
			break;
			
		} // end switch
		break;
		
		// 0x1c TODO
		// 0x0c TODO
		
		
	    default:
		result.append(QString(blob.at(i)));
		break;

	} // end switch

    } // end for

    return result;
}

