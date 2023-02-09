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
#include "mcpd8.h"
#include "mesydaq2.h"
#include "mdefines.h"

#include <qtextstream.h>

mcpd8::mcpd8(QObject *parent)
    : QObject(parent)
{
    theApp = (mesydaq2 *)parent;
    stdInit();
}

mcpd8::~mcpd8()
{
}

/*!
    \fn mcpd8::setId(unsigned char mcpdid)
 */
bool mcpd8::setId(unsigned short mcpdid)
{
    if (mcpdid > 8)
    {
        str.sprintf("Error: Set id value (%d) for mcpd-8 #%d too high! Id set to 8.", mcpdid, id);
        theApp->logMessage(str, 0);
        id = 8;
        return false;
    }
    else
    {
        str.sprintf("Set id for mcpd-8 #%d to %d.", id, mcpdid);
        id = mcpdid;
        theApp->logMessage(str, 2);
        return true;
    }
}

/*!
    \fn mcpd8::getId(void)
 */
unsigned char mcpd8::getId(void)
{
    return id;
}

/*!
    \fn mcpd8::setAuxTimer(unsigned char tim, unsigned short val)
 */
bool mcpd8::setAuxTimer(unsigned short tim, unsigned short val)
{
    if (tim > 3)
        auxTimer[3] = val;
    else
        auxTimer[tim] = val;
    str.sprintf("mcpd %d: set auxiliary timer %d to %d.", id, tim, val);
    theApp->logMessage(str, 2);
    return true;
}

/*!
    \fn mcpd8::setCounterCell(unsigned char * celldata)
 */
// celldata[0] = cell, celldata[1] = trig, celldata[2] = comp
bool mcpd8::setCounterCell(unsigned short *celldata)
{
    bool errorflag = false;
    if (celldata[0] > 7)
    {
        str.sprintf("Error: mcpd %d: trying to set counter cell #%d. Range exceeded! Max. cell# is 7", id, celldata[0]);
        theApp->logMessage(str, 0);
        errorflag = true;
    }
    if (celldata[1] > 7)
    {
        str.sprintf("Error: mcpd %d: trying to set counter cell trigger # to %d. Range exceeded! Max. trigger# is 7", id, celldata[1]);
        theApp->logMessage(str, 0);
        errorflag = true;
    }
    if (celldata[2] > 22)
    {
        str.sprintf("Error: mcpd %d: trying to set counter cell compare value to %d. Range exceeded! Max. value is 22", id, celldata[2]);
        theApp->logMessage(str, 0);
        errorflag = true;
    }
    if (errorflag)
        return false;

    counterCell[celldata[0]][0] = celldata[1];
    counterCell[celldata[0]][1] = celldata[2];
    str.sprintf("mcpd %d: set counter cell %d: trigger # is %d, compare value %d.", id, celldata[0], celldata[1], celldata[2]);
    theApp->logMessage(str, 2);

    return true;
}

/*!
    \fn mcpd8::getCounterCell(unsigned char *)
 */
void mcpd8::getCounterCell(unsigned char cell, unsigned short *celldata)
{
    celldata[0] = counterCell[cell][0];
    celldata[1] = counterCell[cell][1];
}

/*!
    \fn mcpd8::setParam(unsigned char param, unsigned char source)
 */
bool mcpd8::setParamSource(unsigned short param, unsigned short source)
{
    if (param > 3 || source > 8)
        return false;
    else
        paramSource[param] = source;
    str.sprintf("mcpd %d: set parameter source %d to %d.", id, param, source);
    theApp->logMessage(str, 2);
    return true;
}

/*!
    \fn mcpd8::getParamSource(unsigned short param)
 */
unsigned short mcpd8::getParamSource(unsigned short param)
{
    if (param > 3)
        return 0;
    else
        return (paramSource[param]);
}

void mcpd8::setBusCapabilities(unsigned activeCapabilities, unsigned availableCapabilities)
{
    qDebug() << __PRETTY_FUNCTION__ << "active:" << activeCapabilities << ", available:" << availableCapabilities;
    activeBusCapabilities_ = activeCapabilities;
    availableBusCapabilities_ = availableCapabilities;
}

void mcpd8::setBusCapabilities(unsigned activeCapabilities)
{
    qDebug() << __PRETTY_FUNCTION__ << "active:" << activeCapabilities;
    activeBusCapabilities_ = activeCapabilities;
}

unsigned mcpd8::getActiveBusCapabilities() const
{
    return activeBusCapabilities_;
}

unsigned mcpd8::getAvailableBusCapabilities() const
{
    return availableBusCapabilities_;
}

/*!
    \fn mcpd8::setProtocol(unsigned char type, unsigned char* addr)
 */
bool mcpd8::setProtocol(unsigned short *addr)
{
    // addresses are in addr buffer like follows:
    // own addr: [0].[1].[2].[3]
    // data addr: [4].[5].[6].[7]
    // cmd port [8]
    // data port [9]
    // cmd addr [10].[11].[12].[13]
    // if first address byte == 0, or port == 0: don't change!
    unsigned char c;
    QString str;
    if (addr[10] > 0)
    {
        for (c = 10; c < 14; c++)
            cmdIpAddress[c - 10] = (unsigned char)addr[c];
        str.sprintf("mcpd #%d: cmd ip address set to %d.%d.%d.%d", id, cmdIpAddress[0], cmdIpAddress[1], cmdIpAddress[2], cmdIpAddress[3]);
        theApp->logMessage(str, 2);
    }
    if (addr[4] > 0)
    {
        for (c = 4; c < 8; c++)
            dataIpAddress[c - 4] = (unsigned char)addr[c];
        str.sprintf("mcpd #%d: data ip address set to %d.%d.%d.%d", id, dataIpAddress[0], dataIpAddress[1], dataIpAddress[2], dataIpAddress[3]);
        theApp->logMessage(str, 2);
    }
    if (addr[8] > 0)
    {
        cmdPort = addr[8];
        str.sprintf("mcpd #%d: cmd port set to %d", id, cmdPort);
        theApp->logMessage(str, 2);
    }
    if (addr[9] > 0)
    {
        dataPort = addr[9];
        str.sprintf("mcpd #%d: data port set to %d", id, dataPort);
        theApp->logMessage(str, 2);
    }
    if (addr[0] > 0)
    {
        for (c = 0; c < 4; c++)
            ipAddress[c] = (unsigned char)addr[c];
        buildIpStr();
        str.sprintf("mcpd #%d: own ip address set to %d.%d.%d.%d", id, ipAddress[0], ipAddress[1], ipAddress[2], ipAddress[3]);
        theApp->logMessage(str, 2);
    }
    return true;
}

/*!
    \fn mcpd8::getProtocol(unsigned short addr*)
 */
void mcpd8::getProtocol(unsigned short *addr)
{
    unsigned char c;
    for (c = 0; c < 4; c++)
    {
        addr[c] = cmdIpAddress[c];
        addr[c + 4] = dataIpAddress[c];
        addr[c + 10] = ipAddress[c];
    }
    addr[8] = cmdPort;
    addr[9] = dataPort;
}

/*!
    \fn mcpd8::setDac(unsigned char dac, unsigned short val)
 */
bool mcpd8::setDac(unsigned short dac, unsigned short val)
{
    return true;
}

/*!
    \fn mcpd8::setOutstring(QString str)
 */
bool mcpd8::setOutstring(QString str)
{
    return true;
}

/*!
    \fn mcpd8::setRunId(unsigned short runid)
 */
bool mcpd8::setRunId(unsigned short runid)
{
    if (master)
    {
        runId = runid;
        str.sprintf("mcpd %d: set run ID to %d", id, runId);
        theApp->logMessage(str, 1);
        return true;
    }
    else
    {
        str.sprintf("Error: trying to set run ID on mcpd %d - not master!", id);
        theApp->logMessage(str, 0);
        return false;
    }
}

/*!
    \fn mcpd8::getRunId(void)
 */
unsigned short mcpd8::getRunId(void)
{
    return runId;
}

/*!
    \fn mcpd8::setParameter(unsigned char param, unsigned long val)
 */
bool mcpd8::setParameter(unsigned short param, unsigned long val)
{
    if (param > 3)
        return false;

    parameter[param] = val;

    return true;
}

/*!
    \fn mcpd8::getParameter(unsigned char param)
 */
unsigned long mcpd8::getParameter(unsigned short param)
{
    if (param > 3)
        return 0;
    else
        return parameter[param];
}

/*!
    \fn mcpd8::getAuxTimer(unsigned short timer)
 */
unsigned short mcpd8::getAuxTimer(unsigned short timer)
{
    if (timer > 3)
        return 0;
    else
        return auxTimer[timer];
}

/*!
    \fn mcpd8::stdInit(void)
 */
void mcpd8::stdInit(void)
{
    unsigned char c;

    for (c = 0; c < 4; c++)
    {
        cmdIpAddress[c] = 0;
        dataIpAddress[c] = 0;
        ipAddress[c] = 0;
    }
    ipAddrStr.sprintf("192.168.168.121");

    memset(&inetAddr, 0, sizeof(inetAddr));
    inetAddr.sin_family = AF_INET;
    inetAddr.sin_port = htons(54321);
    inetAddr.sin_addr.s_addr = inet_addr(ipAddrStr.toLatin1().constData());

    cmdPort = 54321;
    dataPort = 54321;

    master = false;
    terminate = false;

    for (c = 0; c < 4; c++)
    {
        counterCell[c][0] = 7;
        counterCell[c][1] = 22;
    }

    for (c = 4; c < 7; c++)
    {
        counterCell[c][0] = 0;
        counterCell[c][1] = 0;
    }

    for (c = 0; c < 4; c++)
    {
        auxTimer[c] = 0;
        paramSource[c] = c;
        parameter[c] = c;
    }
    inString.sprintf(" ");
    outString.sprintf(" ");

    runId = 0;

    stream = false;

    commActive = false;
    commFailed = false;

    online = false;

    configured = false;

    timeoutCounter = 0;

    id = 0;
}

/*!
    \fn mcpd8::setStream(unsigned short strm)
 */
bool mcpd8::setStream(unsigned short strm)
{
    if (strm)
        stream = true;
    else
        stream = false;

    return true;
}

/*!
    \fn mcpd8::getStream(void)
 */
bool mcpd8::getStream(void)
{
    return stream;
}

/*!
    \fn mcpd8::serialize(QFile * fi)
 */
bool mcpd8::serialize(QFile *fi)
{
    unsigned char c;
    QTextStream t(fi); // use a text stream

    t << "[MCPD-8]";
    t << '\r' << '\n';
    t << "id = " << id;
    t << '\r' << '\n';
    t << "ipAddress = " << ipAddress[0] << '.' << ipAddress[1] << '.' << ipAddress[2] << '.' << ipAddress[3];
    t << '\r' << '\n';
    t << "master = ";
    if (master)
        t << 1;
    else
        t << 0;
    t << '\r' << '\n';
    t << "terminate = ";
    if (terminate)
        t << 1;
    else
        t << 0;
    t << '\r' << '\n';
    for (c = 0; c < 8; c++)
    {
        t << "counterCell" << c << " = " << counterCell[c][0] << " " << counterCell[c][1];
        t << '\r' << '\n';
    }
    for (c = 0; c < 4; c++)
    {
        t << "auxTimer" << c << " = " << auxTimer[c];
        t << '\r' << '\n';
    }
    for (c = 0; c < 4; c++)
    {
        t << "paramSource" << c << " = " << paramSource[c];
        t << '\r' << '\n';
    }
    t << '\r' << '\n';

    return true;
}

/*!
    \fn mcpd8::communicate(bool yesno)
 */
void mcpd8::communicate(bool yesno)
{
    commActive = yesno;
}

/*!
    \fn mcpd8::isBusy(void)
 */
bool mcpd8::isBusy(void)
{
    return commActive;
}

/*!
    \fn mcpd8::getIpAddress(void)
 */
QString mcpd8::getIpAddress(void)
{
    return ipAddrStr;
}

/*!
    \fn mcpd8::buildIpStr()
 */
void mcpd8::buildIpStr(void)
{
    QString str;
    ipAddrStr = "";
    for (unsigned char c = 0; c < 4; c++)
    {
        str.sprintf("%d", ipAddress[c]);
        ipAddrStr.append(str);
        if (c < 3)
            ipAddrStr.append(".");
    }
}

/*!
    \fn mcpd8::getInetAddr()
 */
sockaddr_in mcpd8::getInetAddr()
{
    return inetAddr;
}

/*!
    \fn mcpd8::setIpAddress(QString addrStr)
 */
void mcpd8::setIpAddress(QString addrStr)
{
    // split into numerical address tuple

    auto parts = addrStr.split(".");

    for (int i = 0; i < parts.size() && i < 4; ++i)
        ipAddress[i] = parts[i].toUInt();

    // and finally set inetAddr
    memset(&inetAddr, 0, sizeof(inetAddr));
    inetAddr.sin_family = AF_INET;
    inetAddr.sin_port = htons(54321);
    inetAddr.sin_addr.s_addr = inet_addr(ipAddrStr.toLatin1().constData());

    //    qDebug("ip address set to"+ipAddrStr);
}

/*!
    \fn mcpd8::setMaster(bool truth)
 */
void mcpd8::setMaster(bool truth)
{
    master = truth;
}

/*!
    \fn mcpd8::setTermination(bool truth)
 */
void mcpd8::setTermination(bool truth)
{
    terminate = truth;
}

/*!
    \fn mcpd8::fillTiming(unsigned short * buf)
 */
void mcpd8::fillTiming(unsigned short *buf)
{
    buf[0] = id;
    buf[1] = SETTIMING;
    if (master)
        buf[2] = 1;
    else
        buf[2] = 0;
    if (terminate)
        buf[3] = 1;
    else
        buf[3] = 0;
}

/*!
    \fn mcpd8::fillCounterCell(unsigned char cell, unsigned short * buf)
 */
void mcpd8::fillCounterCell(unsigned char cell, unsigned short *buf)
{
    buf[0] = id;
    buf[1] = SETCELL;
    buf[2] = cell;
    buf[3] = counterCell[cell][0];
    buf[4] = counterCell[cell][1];
}

/*!
    \fn mcpd8::fillAuxTimer(unsigned char timer, unsigned short * buf)
 */
void mcpd8::fillAuxTimer(unsigned char timer, unsigned short *buf)
{
    buf[0] = id;
    buf[1] = SETAUXTIMER;
    buf[2] = timer;
    buf[3] = auxTimer[timer];
}

/*!
    \fn mcpd8::fillParamSource(unsigned char param, unsigned short * buf)
 */
void mcpd8::fillParamSource(unsigned char param, unsigned short *buf)
{
    buf[0] = id;
    buf[1] = SETPARAM;
    buf[2] = param;
    buf[3] = paramSource[param];
}

/*!
    \fn mcpd8::isMaster()
 */
bool mcpd8::isMaster()
{
    return master;
}

/*!
    \fn mcpd8::isTerminated()
 */
bool mcpd8::isTerminated()
{
    return terminate;
}

/*!
    \fn mcpd8::timeout()
 */
void mcpd8::timeout()
{
    commActive = false;
    commFailed = true;

    timeoutCounter++;

    if (timeoutCounter > 5 && online)
    {
        online = false;
        pstring.sprintf("timeout #%d in mcpd-8 id %d. Device set offline", timeoutCounter, id);
        theApp->logMessage(pstring, 0);
    }
    #if 0
    else
    {
        pstring.sprintf("timeout #%d in mcpd-8 id %d.", timeoutCounter, id);
        theApp->logMessage(pstring, 2);
    }
    #endif
}

/*!
    \fn mcpd8::isOnline(void)
 */
bool mcpd8::isOnline(void)
{
    return online;
}

/*!
    \fn mcpd8::setVersion(unsigned char maj, unsigned char min)
 */
void mcpd8::setVersion(unsigned char maj, unsigned char min)
{
    majVer = maj;
    minVer = min;
    verString.sprintf("%d.%d", maj, min);
    QString str;
    str.sprintf("MCPD-8 id %d, version: ", id);
    str.append(verString);
    theApp->logMessage(str, 2);
}

/*!
    \fn mcpd8::setOnline()
 */
void mcpd8::setOnline()
{
    online = true;
}

/*!
    \fn mcpd8::setConfigured(bool truth)
 */
void mcpd8::setConfigured(bool truth)
{
    configured = truth;
}

/*!
    \fn mcpd8::isConfigured()
 */
bool mcpd8::isConfigured()
{
    return configured;
}

/*!
    \fn mcpd8::answered(void)
 */
void mcpd8::answered(void)
{
    commActive = false;
    commFailed = false;
    online = true;
    timeoutCounter = 0;
}

/*!
    \fn mcpd8::isResponding(void)
 */
bool mcpd8::isResponding(void)
{
    if (commFailed)
        return false;
    else
        return true;
}
