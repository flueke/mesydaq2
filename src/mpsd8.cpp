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
#include "mpsd8.h"
#include "mesydaq2.h"

#include <qtextstream.h>

mpsd8::mpsd8(QObject *parent)
    : QObject(parent)
{
    theApp = (mesydaq2 *)parent;
    mcpdId = 0;
    mpsdId = 0;
    busNum = 0;

    /* Note (flueke): for the arrays below index 0 represents the last value read
     * from the hardware, index 0 is the last value set in the gui or loaded from
     * config and sent to the hardware. */

    for (unsigned char c = 0; c < 9; c++)
    {
        gainpoti[c][0] = 92;
        gainval[c][0] = 1.0;
        gainpoti[c][1] = 92;
        gainval[c][1] = 1.0;
    }
    comgain = true;
    threshpoti[1] = 22;
    threshval[1] = 10;
    pulsamp[1] = 50;
    pulspoti[1] = 38;
    pulspos[1] = 2;
    pulser[1] = false;
    ampmode[1] = false;

    threshpoti[0] = 22;
    threshval[0] = 10;
    pulsamp[0] = 50;
    pulspoti[0] = 38;
    pulspos[0] = 2;
    pulser[0] = false;
    ampmode[0] = false;

    // set calibration factors for gain, threshold and pulser calculation
    g1 = 0.5;
    g2 = 184.783;
    t1 = 0;
    t2 = 0.4583;
    p1 = 4.167;
    p2 = 1.2083;
}

mpsd8::~mpsd8()
{
}

/*!
    \fn mpsd8::setMcpdId(unsigned char id)
 */
void mpsd8::setMcpdId(unsigned char id)
{
    mcpdId = id;
}

/*!
    \fn mpsd8::setMpsdId(unsigned char id)
 */
void mpsd8::setMpsdId(unsigned char bus, unsigned char id)
{
    mpsdId = id;
    mcpdId = bus / 8;
    busNum = bus - 8 * mcpdId;

    if (theApp->listIds)
    {
        str.sprintf("MPSD id on MCPD %d, bus %d: %d", mcpdId, busNum, id);
        theApp->logMessage(str, 2);
    }
}

/*!
    \fn mpsd8::setGain(unsigned char channel, float gain, bool preset)
 */
void mpsd8::setGain(unsigned char channel, float gainv, unsigned char preset)
{
    // boundary check
    if (gainv > 1.88)
        gainv = 1.88;
    if (gainv < 0.5)
        gainv = 0.5;

    unsigned char val = calcGainpoti(gainv);

    if (channel == 8)
    {
        for (unsigned char c = 0; c < 8; c++)
        {
            gainpoti[c][preset] = val;
            gainval[c][preset] = gainv;
        }
        comgain = true;
    }
    else
    {
        gainpoti[channel][preset] = val;
        gainval[channel][preset] = gainv;
        comgain = false;
    }

    if (preset)
        str.sprintf("gainval preset %d, %d, %d to %2.2f (%d)", mcpdId, busNum, channel, gainval[channel][preset], gainpoti[channel][preset]);
    else
        str.sprintf("gainval %d, %d,  %d to %2.2f (%d)", mcpdId, busNum, channel, gainval[channel][preset], gainpoti[channel][preset]);
    theApp->logMessage(str, 2);
}

/*!
    \fn mpsd8::setGain(unsigned char channel, unsigned char gain)
 */
void mpsd8::setGain(unsigned char channel, unsigned char gain, unsigned char preset)
{
    float gv = calcGainval(gain);
    if (channel == 8)
    {
        for (unsigned char c = 0; c < 8; c++)
        {
            gainpoti[c][preset] = gain;
            gainval[c][preset] = gv;
        }
        comgain = true;
    }
    else
    {
        gainpoti[channel][preset] = gain;
        gainval[channel][preset] = gv;
        comgain = false;
    }

    if (preset)
        str.sprintf("gain preset %d, %d, %d to %d (%2.2f)", mcpdId, busNum, channel, gainpoti[channel][preset], gainval[channel][preset]);
    else
        str.sprintf("gain %d,  %d, %d to %d (%2.2f)", mcpdId, busNum, channel, gainpoti[channel][preset], gainval[channel][preset]);
    theApp->logMessage(str, 2);
}

/*!
    \fn mpsd8::setThreshold(unsigned char threshold)
 */
void mpsd8::setThreshold(unsigned char threshold, unsigned char preset)
{
    // boundary check
    if (threshold > 100)
        threshold = 100;

    threshpoti[preset] = calcThreshpoti(threshold);
    threshval[preset] = threshold;

    if (preset)
        str.sprintf("threshold preset %d, %d to %d (%d)", mcpdId, busNum, threshval[preset], threshpoti[preset]);
    else
        str.sprintf("threshold %d, %d to %d (%d)", mcpdId, busNum, threshval[preset], threshpoti[preset]);
    theApp->logMessage(str, 2);
}

/*!
    \fn mpsd8::setThrespoti(unsigned char thresh)
 */
void mpsd8::setThreshpoti(unsigned char thresh, unsigned char preset)
{
    threshpoti[preset] = thresh;
    threshval[preset] = calcThreshval(thresh);

    if (preset)
        str.sprintf("threshpoti preset %d, %d to %d (%d)", mcpdId, busNum, threshpoti[preset], threshval[preset]);
    else
        str.sprintf("threshpoti %d, %d to %d (%d)", mcpdId, busNum, threshpoti[preset], threshval[preset]);
    theApp->logMessage(str, 2);
}

/*!
    \fn mpsd8::setPulserpoti(unsigned char thresh, unsigned char chan)
 */
void mpsd8::setPulserpoti(unsigned char chan, unsigned char val, unsigned char pos, unsigned char on, unsigned char preset)
{
    if (pos > 2)
        pulspos[preset] = 2;
    else
        pulspos[preset] = pos;

    if (chan > 7)
        pulschan[preset] = 7;
    else
        pulschan[preset] = chan;

    pulspoti[preset] = val;
    pulsamp[preset] = calcPulsamp(val, gainval[chan][0]);

    pulser[preset] = on;

    if (preset)
        str.sprintf("pulser preset %d, %d to pos %d, poti %d - ampl %2.0f", mcpdId, busNum, pulspos[preset], pulspoti[preset], pulsamp[preset]);
    else
        str.sprintf("pulser %d, bus %d to pos %d, poti %d - ampl %2.0f", mcpdId, busNum, pulspos[preset], pulspoti[preset], pulsamp[preset]);
    theApp->logMessage(str, 2);
}

/*!
    \fn mpsd8::setPulser(unsigned char chan, unsigned char amp = 128, unsigned char pos = 2, bool on = true)
 */
void mpsd8::setPulser(unsigned char chan, unsigned char amp, unsigned char pos, unsigned char on, unsigned char preset)
{
    if (pos > 2)
        pulspos[preset] = 2;
    else
        pulspos[preset] = pos;

    if (chan > 7)
        pulschan[preset] = 7;
    else
        pulschan[preset] = chan;

    pulspoti[preset] = calcPulspoti(amp, gainval[chan][0]);
    pulsamp[preset] = amp;

    pulser[preset] = on;

    if (preset)
        str.sprintf("pulser preset %d, bus %d to pos %d, ampl %2.0f - poti %d", mcpdId, busNum, pulspos[preset], pulsamp[preset], pulspoti[preset]);
    else
        str.sprintf("pulser %d, bus %d to pos %d, ampl %2.0f - poti %d", mcpdId, busNum, pulspos[preset], pulsamp[preset], pulspoti[preset]);
    theApp->logMessage(str, 2);
}

/*!
    \fn mpsd8::setMode(bool amplitude)
 */
void mpsd8::setMode(bool amplitude, unsigned char preset)
{
    ampmode[preset] = amplitude;
}

/*!
    \fn mpsd8::getMpsdId(void)
 */
unsigned char mpsd8::getMpsdId(void)
{
    return mpsdId;
}

/*!
    \fn mpsd8::setAmpmode(bool yesno)
 */
void mpsd8::setAmpmode(bool yesno, unsigned char preset)
{
    ampmode[preset] = yesno;
}

/*!
    \fn mpsd8::getGain(unsigned char chan)
 */
unsigned char mpsd8::getGainpoti(unsigned char chan, unsigned char preset)
{
    return gainpoti[chan][preset];
}

/*!
    \fn mpsd8::getThreshold(void)
 */
unsigned char mpsd8::getThreshold(unsigned char preset)
{
    return threshval[preset];
}

/*!
    \fn mpsd8::getThreshpoti(void)
 */
unsigned char mpsd8::getThreshpoti(unsigned char preset)
{
    return threshpoti[preset];
}

/*!
    \fn mpsd8::calcGainpoti(float fval)
 */
unsigned char mpsd8::calcGainpoti(float fval)
{
    unsigned char ug;
    float fg;

    fg = (fval - g1) * g2;
    ug = (unsigned char)fg;
    if ((fg - ug) > 0.5)
        ug++;
    //	qDebug("gainval: %1.2f, gainpoti: %d", fval, ug);
    return ug;
}

/*!
    \fn mpsd8::calcThreshpoti(unsigned char tval)
 */
unsigned char mpsd8::calcThreshpoti(unsigned char tval)
{
    unsigned char ut;
    float ft;

    ft = (tval - t1) / t2;
    ut = (unsigned char)ft;
    if ((ft - ut) > 0.5)
        ut++;

    //	qDebug("threshold: %d, threshpoti: %d", tval, ut);
    return ut;
}

/*!
    \fn mpsd8::calcGainval(unsigned char ga)
 */
float mpsd8::calcGainval(unsigned char ga)
{
    float fgain = g1 + (float)ga / g2;
    // round to two decimals:
    float fg = 100.0 * fgain;
    unsigned short g = (unsigned short)fg;
    float test = fg - g;
    if (test >= 0.5)
        g++;

    fgain = (float)g / 100.0;
    //	qDebug("gainpoti: %d, gainval: %1.2f", ga, fgain);
    return fgain;
}

/*!
    \fn mpsd8::calcThreshval(unsigned char thr)
 */
unsigned char mpsd8::calcThreshval(unsigned char thr)
{
    float ft = t1 + (float)thr * t2;
    unsigned char t = (unsigned char)ft;
    float diff = ft - t;
    if (diff > 0.5)
        t++;
    //	qDebug("threshpoti: %d, threshval: %d", t, thr);
    return t;
}

/*!
    \fn mpsd8::getGainval(unsigned char chan)
 */
float mpsd8::getGainval(unsigned char chan, unsigned char preset)
{
    return gainval[chan][preset];
}

/*!
    \fn mpsd8::comGain()
 */
bool mpsd8::comGain()
{
    return comgain;
}

/*!
    \fn mpsd8::getMcpdId()
 */
unsigned char mpsd8::getMcpdId()
{
    return mcpdId;
}

/*!
    \fn mpsd8::isPulserOn()
 */
unsigned char mpsd8::isPulserOn()
{
    return pulser[0];
}

/*!
    \fn mpsd8::getPulschan()
 */
unsigned char mpsd8::getPulschan(unsigned char preset)
{
    return pulschan[preset];
}

/*!
    \fn mpsd8::getPulsamp()
 */
unsigned char mpsd8::getPulsamp(unsigned char preset)
{
    return pulsamp[preset];
}

/*!
    \fn mpsd8::getPulspos()
 */
unsigned char mpsd8::getPulspos(unsigned char preset)
{
    return pulspos[preset];
}

/*!
    \fn mpsd8::getPulspoti()
 */
unsigned char mpsd8::getPulspoti(unsigned char preset)
{
    return pulspoti[preset];
}

/*!
    \fn mpsd8::getMode()
 */
bool mpsd8::getMode(unsigned char preset)
{
    return ampmode[preset];
}

/*!
    \fn mpsd8::calcPulspoti(unsigned char val)
 */
unsigned char mpsd8::calcPulspoti(unsigned char val, float gv)
{

    float pamp = (val / gv - p1) / p2;
    unsigned char pa = (unsigned char)pamp;

    if (pamp - pa > 0.5)
        pa++;

    //     qDebug("pulsval: %d, pulspoti: %d", val, pa);
    return pa;
}

/*!
    \fn mpsd8::calcPulsamp(unsigned char val)
 */
unsigned char mpsd8::calcPulsamp(unsigned char val, float gv)
{
    float pa = (p1 + (val * p2)) * gv;
    unsigned char pamp = (unsigned char)pa;
    if (pa - pamp > 0.5)
        pamp++;

    //    qDebug("pulspoti: %d, pulsval: %d", val, pamp);

    return pa;
}

/*!
    \fn mpsd8::setInternalreg(unsigned char reg, unsigned short val, unsigned char preset)
 */
void mpsd8::setInternalreg(unsigned char reg, unsigned short val, unsigned char preset)
{
    internalReg[reg][preset] = val;

    if (preset)
        str.sprintf("register preset %d, %d, %d to %d", mcpdId, busNum, reg, internalReg[reg][preset]);
    else
        str.sprintf("register %d, %d, %d, to %d", mcpdId, busNum, reg, internalReg[reg][preset]);
    theApp->logMessage(str, 2);
}

/*!
    \fn mpsd8::getInternalreg(unsigned char reg, unsigned char preset)
 */
unsigned short mpsd8::getInternalreg(unsigned char reg, unsigned char preset)
{
    return (internalReg[reg][preset]);
}

/*!
    \fn mpsd8::serialize(QFile * fi)
 */
bool mpsd8::serialize(QFile *fi)
{
    unsigned char c;
    QTextStream t(fi); // use a text stream

    t << "[MPSD-8]";
    t << '\r' << '\n';
    t << "id = " << 8 * mcpdId + busNum;
    t << '\r' << '\n';
    for (c = 0; c < 8; c++)
    {
        t << "gain" << c << " = " << gainpoti[c][0];
        t << '\r' << '\n';
    }
    t << "threshold = " << threshpoti[0];
    t << '\r' << '\n';

    return true;
}
