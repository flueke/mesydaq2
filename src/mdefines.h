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

// general definitions for mesydaq
//

// official commands
#define RESET 0
#define START 1
#define STOP 2
#define CONTINUE 3
#define SETID 4
#define SETPROTOCOL 5
#define SETTIMING 6
#define SETCLOCK 7
#define SETRUNID 8
#define SETCELL 9
#define SETAUXTIMER 10
#define SETPARAM 11
#define GETPARAM 12
#define SETGAIN 13
#define SETTHRESH 14
#define SETPULSER 15
#define SETMODE 16
#define SETDAC 17
#define SENDSERIAL 18
#define READSERIAL 19
#define SCANPERI 20
#define GET_BUS_CAPABILITIES 22
#define SET_BUS_CAPABILITIES 23

// internal commands
#define WRITEFPGA 30
#define WRITEREGISTER 31
#define READREGISTER 32
#define READFPGA 33
#define SETPOTI 34
#define GETPOTI 35
#define READID 36
#define DATAREQUEST 37
#define QUIET 50
#define GETVER 51
#define READPERIREG 52
#define WRITEPERIREG 53

// CARESS cmds
#define CAR_INIT		1
#define CAR_RELEASE		2
#define CAR_START		3
#define CAR_STOP		4
#define CAR_DRIVE		5
#define CAR_LOAD		6
#define CAR_LOADBLOCK	7
#define CAR_READ		8
#define CAR_READBLOCKP	9
#define CAR_READBLOCKM	10

// CARESS sub cmds
#define CAR_MASTER			1
#define CAR_SLAVE			2
#define CAR_RESET			3

// histogram sizes
// 128 channels + 1 sum per MCPD
#define CHANNELS 130
#define LINBINS 1024
#define TIMEBINS 1024

// daq status values
#define IDLE 0
#define RUNNING 1
#define STARTED 2
#define STOPPED 3

// log levels
#define LOG_LEVEL_TRACE     3
#define LOG_LEVEL_DEBUG     2
#define LOG_LEVEL_INFO      1
#define LOG_LEVEL_ERROR     0

// number of MCPDs
#define MCPDS 8

// CARESS counter mapping
#define EVCT	4
#define M1CT	0
#define M2CT	1
#define TCT		5
#define HISTO	99

// DataID mapping
#define MON1ID	0
#define MON2ID	1
#define MON3ID	2
#define MON4ID	3
#define TTL1ID	4
#define TTL2ID	5
#define ADC1ID	6
#define ADC2ID	7
#define EVID	8

#define QSL QStringLiteral