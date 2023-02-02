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

    // FIXME (flueke): Putting mesydaq2 on the stack or setting the
    // Qt::WA_DeleteOnClose attribute actually leads to a segfault when closing
    // the window. Possibly timers still running and invoking slots on an object
    // that has already been destroyed.
    mainWin = new mesydaq2();

    auto args = app.arguments();

    if (auto flagIndex = args.indexOf("-f");
        flagIndex > 0 && flagIndex + 1 < args.size())
    {
        mainWin->setConfigfilename(args[flagIndex+1]);
    }

    mainWin->initSystem();
    mainWin->show();
    // mainWin has WDestructiveClose flag by default, so it will delete itself.

    return app.exec();
}
