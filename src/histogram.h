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
#ifndef HISTOGRAM_H
#define HISTOGRAM_H

#include <qobject.h>
#include "mdefines.h"

#include <qfile.h>

/**
	@author Gregor Montermann <g.montermann@mesytec.com>
*/
class histogram : public QObject
{
Q_OBJECT
public:
    histogram(QObject *parent = 0, const char *name = 0);

    ~histogram();

	bool incVal(unsigned char chan, unsigned short linear, unsigned short energy, unsigned long time);
    void clearAllHist(void);
    void clearHist(unsigned int channel);
    unsigned long getTotalCounts(void);
    void copyLine(unsigned int channel, unsigned long * pLineBuffer);
    unsigned long int max(unsigned int channel);
    unsigned short maxpos(unsigned int channel);
    void getMean(unsigned short chan, float* vals);
    void setWidth(unsigned char width);
    void setId(unsigned char mcpdId);
    bool writeHistogram(QFile* f);

protected:
    unsigned long int posHist[CHANNELS+1][LINBINS];
    unsigned long chanCounts[CHANNELS+1];
    unsigned long int maximum[CHANNELS+1][2];
    unsigned long totalCounts;
    unsigned long lasttime;
    unsigned int floatingMean[CHANNELS+3][255];
    unsigned char meanCount[CHANNELS+3];
    unsigned char meanPos[CHANNELS+3];
    unsigned long lastTime;
    unsigned char twidth;
    unsigned char id;
};

#endif


