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
#include "networkdevice.h"
#include "mesydaq2.h"
#include "mcpd8.h"

networkDevice::networkDevice(QObject *parent, const char *name)
 : QObject(parent, name)
{
	netBuf = new (MDP_PACKET);
	recBuf = new (MDP_PACKET);
	theApp = (mesydaq2 *) parent;	
}


networkDevice::~networkDevice()
{
	notifyNet->setEnabled(false);
	delete notifyNet;
	delete netBuf;
	delete recBuf;
}


/*!
    \fn networkDevice::initSocket(unsigned char id)
 */
int networkDevice::initSockets(struct ifreq * pIfreq, unsigned char n)
{
	static char str[128];
//	size_t length;

	// receive socket (server socket, udp type)
	rxSockfd = socket(AF_INET, SOCK_DGRAM, 0);
//	qDebug("rxSockfd %d", rxSockfd);
	
	// create receive socket address structure
	memcpy(&rxAddr, (struct sockaddr_in*)&pIfreq->ifr_addr, sizeof(sockaddr_in));

//	bzero(&rxAddr, sizeof(rxAddr));
	rxAddr.sin_family = AF_INET;
	rxAddr.sin_port = htons(54321);
//	rxAddr.sin_addr.s_addr = INADDR_ANY;
	
//	qDebug("binding to socket port: %d", ntohs(rxAddr.sin_port));
	inet_ntop(AF_INET, &rxAddr.sin_addr.s_addr, str, sizeof(str)); 
//	qDebug("binding to ip address %20s", str); 
	const int on = 1;
	
//	qDebug("setsockopt %d", setsockopt(rxSockfd, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on))); 
	setsockopt(rxSockfd, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on)); 
	
	// bind receive socket
//	qDebug("bind: %d", bind(rxSockfd,(const struct sockaddr*)&rxAddr, sizeof(rxAddr)));
	bind(rxSockfd,(const struct sockaddr*)&rxAddr, sizeof(rxAddr));
	 
	// check socket
	struct sockaddr_in checkAddr;
	bzero(&checkAddr, sizeof(checkAddr));
	socklen_t len;
//	qDebug("getname: %d", getsockname(rxSockfd, (sockaddr*)&checkAddr, &len));
	getsockname(rxSockfd, (sockaddr*)&checkAddr, &len);
//	qDebug("bound to socket port: %d", ntohs(checkAddr.sin_port));
//	qDebug("tried port: %d", ntohs(rxAddr.sin_port));
	inet_ntop(AF_INET, &checkAddr.sin_addr.s_addr, str, sizeof(str)); 
	qDebug("bound to ip address %s, port: %d", str, ntohs(checkAddr.sin_port)); 
	
	// establish socket notifier
	notifyNet = new QSocketNotifier(rxSockfd, QSocketNotifier::Read);
	notifyNet->setEnabled(false);
	connect (notifyNet, SIGNAL (activated(int)), this, SLOT (readSocketData()));
	notifyNet->setEnabled(true);
	return(rxSockfd);
}


/*!
    \fn networkDevice::getSbufpointer()
 */
PMDP_PACKET networkDevice::getSbufpointer()
{
    return netBuf;
}

/*!
    \fn networkDevice::getRbufpointer()
 */
PMDP_PACKET networkDevice::getRbufpointer()
{
	return recBuf;
}

/*!
    \fn networkDevice::sendBuffer()
 */
int networkDevice::sendBuffer(unsigned char id, PMDP_PACKET buf)
{
	QString pstring, str2;
//	static char str[128];
//	size_t length;
	struct sockaddr_in addr;
	bzero(&addr, sizeof(addr));
	addr.sin_family = AF_INET;
	addr.sin_port = htons(54321);
	addr.sin_addr.s_addr = inet_addr(ipAddress[id].latin1());
	pstring.sprintf("send buffer to: ");
	pstring.append(ipAddress[id]);
//	str2.sprintf(", rxSockfd %d", rxSockfd);
//	pstring.append(str2);
	theApp->protocol(pstring, 3);
	sendto(rxSockfd, buf, 200, 0, (const struct sockaddr*)&addr, sizeof(addr));
	return 1;
}


/*!
    \fn networkDevice::readSocketData();
 */
void networkDevice::readSocketData()
{
//	unsigned short * pData = (unsigned short *) recBuf;
	// read socket data into receive buffer
	int res = read(rxSockfd,recBuf,1520);
	// notify
	emit bufferReceived();
}


/*!
    \fn networkDevice::setAddress(unsigned char id, QString addr)
 */
void networkDevice::setAddress(unsigned char id, QString addr)
{
    QString pstring;
    ipAddress[id] = addr;
	pstring.sprintf("Changed contact ip adress for MCPD-ID %d to ", id);
	pstring.append(addr);
	theApp->protocol(pstring, 2);
}

/*!
    \fn networkDevice::getAddress(unsigned char id)
 */
QString networkDevice::getAddress(unsigned char id)
{
    return(ipAddress[id]);
}



#include "networkdevice.moc"


