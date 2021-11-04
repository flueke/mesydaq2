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
#ifndef MCPD8_H
#define MCPD8_H

#include <qobject.h>
#include <qstring.h>
#include <qfile.h>

#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <arpa/inet.h>

class mesydaq2;

/**
representation of mcpd-8 central module

	@author Gregor Montermann <g.montermann@mesytec.com>
*/
class mcpd8 : public QObject
{
Q_OBJECT
public:
    mcpd8(QObject *parent = 0, const char *name = 0);

    ~mcpd8();
    bool setId(unsigned short mcpdid);
    bool setOutstring(QString str);
    bool setDac(unsigned short dac, unsigned short val);
    bool setProtocol(unsigned short* addr);
    bool setParamSource(unsigned short param, unsigned short source);
    bool setCounterCell(unsigned short * celldata);
    bool setAuxTimer(unsigned short tim, unsigned short val);
    unsigned char getId(void);
    void getProtocol(unsigned short * addr);
    unsigned short getRunId(void);
    bool setRunId(unsigned short runid);
    void getCounterCell(unsigned char cell, unsigned short * celldata);
    unsigned long getParameter(unsigned short param);
    bool setParameter(unsigned short param, unsigned long val);
    unsigned short getAuxTimer(unsigned short timer);
    void stdInit(void);
    unsigned short getParamSource(unsigned short param);
    bool setStream(unsigned short strm);
    bool getStream(void);
    bool serialize(QFile * fi);
    void communicate(bool yesno);
    bool isBusy(void);
    QString getIpAddress(void);
    void buildIpStr();
    sockaddr_in getInetAddr();
    void setIpAddress(QString addrStr);
    void setTermination(bool truth);
    void setMaster(bool truth);
    void fillTiming(unsigned short * buf);
    void fillCounterCell(unsigned char cell, unsigned short * buf);
    void fillAuxTimer(unsigned char timer, unsigned short * buf);
    void fillParamSource(unsigned char param, unsigned short * buf);
    bool isMaster();
    bool isTerminated();
    bool isOnline(void);
    void timeout();
    void setVersion(unsigned char maj, unsigned char min);
    void setOnline();
    bool isConfigured();
    void setConfigured(bool truth);
    void answered(void);
    bool isResponding(void);

public:
    bool modified;
protected:
    unsigned char id;
    // communication params
    unsigned char ipAddress[4];
    QString ipAddrStr;
    sockaddr_in inetAddr;

    unsigned char cmdIpAddress[4];
	unsigned char dataIpAddress[4];
	unsigned short cmdPort;
	unsigned short dataPort;

	bool master;
	bool terminate;

	// 8 counter cells, trig source in [0], compare reg in [1]
	unsigned char counterCell[8][2];
	// four auxiliary timers, capture values
	unsigned short auxTimer[4];
	// four parameters (transmitted in buffer header), 9 possible sources
	unsigned char paramSource[4];
	// two DACs
	unsigned short dac[2];
	// two ADCs
	unsigned short adc[2];

	// one output, one input string for RS-232
	QString outString;
	QString inString;
    mesydaq2 * theApp;
    QString str;
    unsigned short runId;
    bool stream;
    unsigned long parameter[4];
    bool commActive;
    bool commFailed;
    unsigned char timeoutCounter;
    unsigned char majVer;
    unsigned char minVer;
    QString verString;
    bool online;
    QString pstring;
    bool configured;
};

#endif
