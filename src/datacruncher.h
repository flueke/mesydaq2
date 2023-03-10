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
#ifndef DATACRUNCHER_H
#define DATACRUNCHER_H

#include <array>
#include <qobject.h>

#include "structures.h"

#include "qstring.h"

class mesydaq2;
class histogram;
class mpsd8;

/**
	@author Gregor Montermann <g.montermann@mesytec.com>
*/
class dataCruncher : public QObject
{
Q_OBJECT
public:
    explicit dataCruncher(QObject *parent = nullptr);

    ~dataCruncher();
    void analyzeBuffer(PDATA_PACKET pd, unsigned char daq, histogram* hist);
    void analyzeCmd(PMDP_PACKET pPacket, unsigned char daq, histogram* hist);
    void reset(void);
    void setLimit(unsigned char cNum, unsigned long lim);
    void setCounterAssign(unsigned char cpu0, unsigned char counter0, unsigned char cpu1, unsigned char counter1);

private:
    mesydaq2 * theApp;
    unsigned long lastHt;
    unsigned long lastTime;
    unsigned long oldDelta;
    QString pstring;
    std::array<unsigned long , 9> countLimit;
    unsigned char mon1cpu;
    unsigned char mon2cpu;
    unsigned char mon1counter;
    unsigned char mon2counter;
};

#endif
