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
#ifndef NETWORKDEVICE_H
#define NETWORKDEVICE_H

#include <qobject.h>

#include <qobject.h>
#include <qsocketnotifier.h>

#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <arpa/inet.h>

#include "structures.h"

class mesydaq2;
class mcpd8;

/**
Base class for network devices like MCPD-2, MCPD-8

	@author Gregor Montermann <g.montermann@mesytec.com>
*/
class networkDevice : public QObject
{
Q_OBJECT
public:
    explicit networkDevice(QObject *parent = 0);

    ~networkDevice();
    int initSockets(struct ifreq * pIfreq, unsigned char n);
    PMDP_PACKET getSbufpointer();
	PMDP_PACKET getRbufpointer();
	int sendBuffer(unsigned char id, PMDP_PACKET buf);
    void setAddress(unsigned char id, QString addr);
    QString getAddress(unsigned char id);
	QSocketNotifier * notifyNet;

protected:
    QString ipAddress[8];
	int rxSockfd;
	int txSockfd;
	PMDP_PACKET netBuf, recBuf;
    mesydaq2 * theApp;
	struct sockaddr_in rxAddr;

public slots:
	void readSocketData();

signals:
    void bufferReceived(void);
};


#endif
