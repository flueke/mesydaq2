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
#ifndef STRUCTURES_H
#define STRUCTURES_H

typedef struct _MDP_PACKET
{
	unsigned short bufferLength;
	unsigned short bufferType;
	unsigned short headerLength;
	unsigned short bufferNumber;
	unsigned short cmd;
	unsigned char deviceStatus;
	unsigned char deviceId;
	unsigned short time[3];
	unsigned short headerChksum;
	unsigned short data[750];
} MDP_PACKET, *PMDP_PACKET;

typedef struct _DATA_PACKET
{
	unsigned short bufferLength;
	unsigned short bufferType;
	unsigned short headerLength;
	unsigned short bufferNumber;
	unsigned short cmd;
	unsigned char deviceStatus;
	unsigned char deviceId;
	unsigned short time[3];
	unsigned short param[4][3];
	unsigned short data[750];
} DATA_PACKET, *PDATA_PACKET;

#define BUFTYPE		0x8000
#define CMDBUFLEN	1
#define CMDHEADLEN	10
#define STDBUFLEN	1

#endif
