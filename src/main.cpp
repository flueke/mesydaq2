/***************************************************************************
 *   Copyright (C) 2008 by Gregor Montermann   *
 *   g.montermann@mesytec.com   *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/


#include "mesydaq2.h"
#include <qapplication.h>
#include <qdir.h>
#include <qstring.h>

int main(int argc, char **argv)
{
    QApplication app(argc, argv);
    mesydaq2 *mainWin = 0;

    mainWin = new mesydaq2();
    QString s;
    unsigned char c;
    for(c = 0; c < argc; c++){
		s.sprintf("%s", argv[c]);
		if(s.find("-f") >= 0){
		    s.sprintf("%s",argv[c+1]);
		    mainWin->setConfigfilename(s);
			break;
		}
	}
    mainWin->initSystem();
    app.setMainWidget( mainWin );
    mainWin->show();
    // mainWin has WDestructiveClose flag by default, so it will delete itself.
    return app.exec();
}

