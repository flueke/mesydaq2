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

#include <QMap>
#include <qobject.h>
#include <qsocketnotifier.h>
#include <QUdpSocket>

#include "structures.h"

class mesydaq2;

class networkDevice : public QObject
{
Q_OBJECT

signals:
    void bufferReceived(void);

public:
    explicit networkDevice(QObject *parent = 0);

    ~networkDevice();
    PMDP_PACKET getSbufpointer();
	PMDP_PACKET getRbufpointer();
	qint64 sendBuffer(unsigned char id, PMDP_PACKET buf);
    void setAddress(unsigned char id, QString addr);
    QString getAddress(unsigned char id);

private:
    QUdpSocket *socket_;
    QMap<unsigned char, QString> ipAddress;
	PMDP_PACKET netBuf, recBuf;
    mesydaq2 * theApp;

    QMap<QString, QHostAddress> lookupCache_;

private slots:
	void readSocketData();
};


#endif
