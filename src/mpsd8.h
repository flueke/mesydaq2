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
#ifndef MPSD8_H
#define MPSD8_H

#include <qobject.h>
#include <qstring.h>
#include <qfile.h>

class mesydaq2;

/**
representation of mpsd-8 peripheral module

	@author Gregor Montermann <g.montermann@mesytec.com>
*/
class mpsd8 : public QObject
{
Q_OBJECT
public:
    mpsd8(QObject *parent = 0, const char *name = 0);

    ~mpsd8();
    void setMcpdId(unsigned char id);
    void setMpsdId(unsigned char bus, unsigned char id);
    void setPulser(unsigned char chan, unsigned char amp = 128, unsigned char pos = 2, unsigned char on = 0, unsigned char preset = 0);
    void setThreshold(unsigned char threshold, unsigned char preset = 0);
    void setThreshpoti(unsigned char thresh, unsigned char preset = 0);
    void setPulserpoti(unsigned char chan, unsigned char val = 128, unsigned char pos = 2, unsigned char on = 0, unsigned char preset = 0);
    void setGain(unsigned char channel, float gainv, unsigned char preset = 0);
	void setGain(unsigned char channel, unsigned char gain, unsigned char preset = 0);
    void setMode(bool amplitude, unsigned char preset = 0);
    unsigned char getMpsdId(void);
    void setAmpmode(bool yesno, unsigned char preset = 0);
    unsigned char getGainpoti(unsigned char chan, unsigned char preset = 0);
    unsigned char getThreshpoti(unsigned char preset = 0);
    unsigned char getThreshold(unsigned char preset = 0);
    unsigned char calcThreshpoti(unsigned char tval);
    unsigned char calcGainpoti(float fval);
    float calcGainval(unsigned char ga);
    unsigned char calcThreshval(unsigned char thr);
    float getGainval(unsigned char chan, unsigned char preset = 0);
    bool comGain();
    unsigned char getMcpdId();
    unsigned char getPulspos(unsigned char preset = 0);
    unsigned char getPulsamp(unsigned char preset = 0);
    unsigned char getPulspoti(unsigned char preset = 0);
    unsigned char getPulschan(unsigned char preset = 0);
    unsigned char isPulserOn();
    bool getMode(unsigned char preset = 0);
    unsigned char calcPulspoti(unsigned char val, float gv);
    unsigned char calcPulsamp(unsigned char val, float gv);
    unsigned short getInternalreg(unsigned char reg, unsigned char preset = 0);
    void setInternalreg(unsigned char reg, unsigned short val, unsigned char preset = 0);
    bool serialize(QFile * fi);

protected:
    unsigned char mcpdId;
    unsigned char mpsdId;
    unsigned char gainpoti[9][2];
    float gainval[9][2];
    bool comgain;
    unsigned char threshpoti[2];
    unsigned char threshval[2];
    unsigned char pulspos[2];
    unsigned char pulspoti[2];
    float pulsamp[2];
    unsigned char pulschan[2];
    unsigned char pulser[2];
    bool ampmode[2];
    mesydaq2 * theApp;
    QString str;
    float g1;
    float g2;
    float t1;
    float t2;
    float p1;
    float p2;
    unsigned char busNum;
    unsigned short internalReg[3][2];
};

#endif
