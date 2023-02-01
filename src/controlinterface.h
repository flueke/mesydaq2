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
#ifndef CONTROLINTERFACE_H
#define CONTROLINTERFACE_H

#include <qobject.h>

class mesydaq2;

/**
Interface class for external control (caress, ...)

	@author Gregor Montermann <g.montermann@mesytec.com>
*/
class controlInterface : public QObject
{
Q_OBJECT
public:
    explicit controlInterface(QObject *parent = 0);

    ~controlInterface();
    void caressTask();
    bool isActive(void);
    void completeCar();
    void extractCaressHeader();
    void createTestheader(void);;
    void completeCaressFileheader(void);
    QString caressListfilename;

public:
	bool asyncTaskPending;
    bool caressTaskPending;
    unsigned int caressTaskNum;
    unsigned int caressSubTaskNum;
    unsigned char caressMaster;
    unsigned char caressDevice;
    unsigned long * transferBuffer;
    unsigned long caressStartChannel;
    unsigned long caressEndChannel;
    unsigned long caressHistoSize;
    unsigned int caressHeight;
    unsigned int caressWidth;
    unsigned long caressPreset;
    bool systemStatus;
    QString caressHeader;
    QString caressRunnumber;
    QString caressFilename;
    QString caressDatadir;
    unsigned long caressMaxfilesize;
    QString carFileH;
    unsigned char caressFilefragment;
    unsigned long caressStarttime;
    unsigned int caressHlen;
    QString caressBaseFilename;
    bool caressInitialized;

protected:
    mesydaq2 *  theApp;
};

#endif
