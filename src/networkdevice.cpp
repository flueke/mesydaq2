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

#include <unistd.h>

#include "mesydaq2.h"
#include "mcpd8.h"

networkDevice::networkDevice(QObject *parent)
 : QObject(parent)
 , socket_(new QUdpSocket(this))
{
	netBuf = new (MDP_PACKET);
	recBuf = new (MDP_PACKET);
	theApp = qobject_cast<mesydaq2 *>(parent);

	connect(socket_, &QUdpSocket::readyRead, this, &networkDevice::readSocketData);
}

networkDevice::~networkDevice()
{
	delete netBuf;
	delete recBuf;
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
qint64 networkDevice::sendBuffer(unsigned char id, PMDP_PACKET buf)
{
	if (socket_->state() != QAbstractSocket::BoundState)
	{
		if (!socket_->bind(QHostAddress::Any, 54321))
		{
			theApp->protocol(
				QSL("Could not bind udp socket to local port 54321!"
					"Old MCPD communication will not work."),
				LOG_LEVEL_ERROR);
		}

		qDebug() << "bound to adress" << socket_->localAddress().toString() << ", port" << socket_->localPort();
	}

	QHostAddress destAddr(ipAddress[id]);
	auto result = socket_->writeDatagram(reinterpret_cast<const char *>(buf), sizeof(*buf), destAddr, 54321);
	return result;
}


/*!
    \fn networkDevice::readSocketData();
 */
void networkDevice::readSocketData()
{
	size_t nDatagrams = 0;
	while (socket_->hasPendingDatagrams())
	{
		// read socket data into receive buffer
		auto res = socket_->readDatagram(reinterpret_cast<char *>(recBuf), sizeof(*recBuf));
		if (res >= 0)
		{
			// notify
			emit bufferReceived();
			++nDatagrams;
		}
	}

	theApp->protocol(QSL("networkDevice::readSocketData() received %1 datagrams").arg(nDatagrams),
					 LOG_LEVEL_TRACE);
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
