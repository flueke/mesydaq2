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
#ifndef MEASUREMENT_H
#define MEASUREMENT_H

#include <qobject.h>
#include <qfile.h>

class mesydaq2;
class datacruncher;

/**
	@author Gregor Montermann <g.montermann@mesytec.com>
*/
class measurement : public QObject
{
Q_OBJECT
public:
    measurement(QObject *parent = 0, const char *name = 0);

    ~measurement();
    void getMeastime(unsigned short * time);
    unsigned long getMeastime(void);
    void setCurrentTime(unsigned long msecs);
    void stop(unsigned long time);
    void start(unsigned long time);
    void calcRates();
    void setCounter(unsigned int cNum, unsigned long long val);
    unsigned long getRate(unsigned char cNum);
    unsigned long long getCounter(unsigned char cNum);
    void calcMeanRates();
    unsigned char isOk(void);
    void setOnline(bool truth);
    unsigned long getPreset(unsigned char cNum);
    void setPreset(unsigned char cNum, unsigned long prval, bool mast);
    void setRunnumber(unsigned int number);
    void setListmode(bool truth);
    void setCarHistSize(unsigned int h, unsigned int w);
    void setRemote(bool truth);
    bool remoteStart(void);
    void setStep(unsigned int step);
    unsigned int getCarHeight();
    unsigned int getCarWidth();
    unsigned int getRun();
    bool isMaster(unsigned char cNum);
    void clearCounter(unsigned char cNum);
    bool hasStopped(unsigned char cNum);
    void copyCounters(void);
    bool limitReached(unsigned char cNum);
    void incBytesWritten(unsigned int num);
    void setMaxBytes(unsigned long num);
    void assignCounter(unsigned char counter, unsigned char cpu,  unsigned char cnt);
    void getCounterAssign(unsigned char* ca);
    void serialize(QFile * fi);
    unsigned long events;
    unsigned long mon1;    
    unsigned long mon2;
protected:
    unsigned long starttime_msec;
    unsigned long stoptime_msec;
    unsigned long meastime_msec;
    unsigned long curtime_msec;
    unsigned long ratetime_msec;
    bool running;
    bool starting;
    bool stopping;
    mesydaq2* theApp;
    unsigned long long counter[2][8];
    unsigned long long counterStart[8];
    unsigned long long counterOffset[8];
    unsigned long long preset[8];
    bool master[8];
    bool stopped[8];
    unsigned long rate[11][8];
    unsigned char ratecount[8];
    unsigned char ratepointer[8];
    bool rateflag;
    bool online;
    bool working;
    unsigned int runNumber;
    bool listmode;
    unsigned int carHistHeight;
    unsigned int carHistWidth;
    bool remote;
    unsigned int carStep;
    unsigned char monAssign[2][2];
};

#endif
