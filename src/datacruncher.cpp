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
#include "datacruncher.h"
#include "mesydaq2.h"
#include "mdefines.h"
#include "histogram.h"
#include "mcpd8.h"
#include "mpsd8.h"
#include "measurement.h"
//#include "mainwindow.h"

dataCruncher::dataCruncher(QObject *parent, const char *name)
 : QObject(parent, name)
{
	theApp = (mesydaq2 *) parent;
	for(unsigned char c = 0; c < 8; c++)
		countLimit[c] = 0;

	mon1counter = 0;
	mon2counter = 1;
	mon1cpu = 0;
	mon2cpu = 0;
}


dataCruncher::~dataCruncher()
{
}

/*!
    \fn dataCruncher::analyzeCmd(PMDP_PACKET pPacket, unsigned char daq)
 */
void dataCruncher::analyzeCmd(PMDP_PACKET pPacket, unsigned char daq, histogram * hist)
{
	unsigned short cmd, err;
	unsigned char devnum;
	QString str;

	// extract cmd and error code
	cmd = pPacket->cmd & 0x00FF;
	err = (pPacket->cmd & 0xFF00) / 0x100;


	str.sprintf("analyze cmd %d from %d (cmd: %d, error: %d)", pPacket->cmd, pPacket->deviceId, cmd, err);
	theApp->protocol(str, 2);
	switch(cmd){
			case START:
				if(theApp->myMcpd[pPacket->deviceId]->isMaster())
					theApp->startedDaq();
				theApp->update();
			break;

			case STOP:
				if(theApp->myMcpd[pPacket->deviceId]->isMaster())
					theApp->stoppedDaq();
				theApp->update();
			break;

			case READID:
			// extract the retrieved MPSD-8 IDs:
			for(unsigned char c = 0; c < 8; c++){
//				qDebug("id: %d, %d", 8*pPacket->deviceId+c, pPacket->data[c]);
				theApp->myMpsd[8*pPacket->deviceId+c]->setMpsdId(8*pPacket->deviceId+c, pPacket->data[c]);
			}
			theApp->listIds = false;
			if(theApp->meas->isOk() > 0)
				theApp->meas->setOnline(true);
			theApp->dispMpsd();
		break;

		case GETVER:
			theApp->myMcpd[pPacket->deviceId]->setVersion(pPacket->data[0], pPacket->data[1]);
			theApp->myMcpd[pPacket->deviceId]->setOnline();
		break;
		case SETGAIN:
			// extract the set gain values:
			// set common gain:
			if(pPacket->bufferLength == 21){
				for(unsigned char c = 0; c < 8; c++){
					devnum = 8*pPacket->deviceId+pPacket->data[0];
					if(pPacket->data[2+c] != theApp->myMpsd[devnum]->getGainpoti(c, 1)){
						pstring.sprintf("Error setting gain, mod %d, chan %d is: %d, should be: %d", devnum, c, pPacket->data[2+c], theApp->myMpsd[devnum]->getGainpoti(c, 1));
						theApp->protocol(pstring, 0);
						// set back to received value
					}
					theApp->myMpsd[devnum]->setGain(c, (unsigned char)pPacket->data[2+c], 0);
				}
			}
			// set one channel
			else{
				devnum = 8*pPacket->deviceId+pPacket->data[0];
				if(pPacket->data[2] != theApp->myMpsd[devnum]->getGainpoti(pPacket->data[1], 1)){
					pstring.sprintf("Error setting gain, mod %d, chan %d is: %d, should be: %d", devnum, pPacket->data[1], pPacket->data[2], theApp->myMpsd[devnum]->getGainpoti(pPacket->data[1], 1));
					theApp->protocol(pstring, 0);
					// set back to received value
				}
				theApp->myMpsd[devnum]->setGain(pPacket->data[1], (unsigned char)pPacket->data[2], 0);
			}
			theApp->dispMpsd();
		break;

		case SETTHRESH:
			// extract the set thresh value:
			devnum = 8*pPacket->deviceId+pPacket->data[0];
			if(pPacket->data[1] != theApp->myMpsd[devnum]->getThreshpoti(1)){
				pstring.sprintf("Error setting threshold, mod %d, is: %d, should be: %d", devnum, pPacket->data[1], theApp->myMpsd[devnum]->getThreshpoti(1));
				theApp->protocol(pstring, 0);
			}
			theApp->myMpsd[devnum]->setThreshpoti(pPacket->data[1], 0);
			theApp->dispMpsd();
		break;

		case SETMODE:
			// extract the set mode:
			devnum = 8*pPacket->deviceId+pPacket->data[0];
			if(pPacket->data[1] == 1)
				theApp->myMpsd[devnum]->setAmpmode(true, 0);
			else
				theApp->myMpsd[devnum]->setAmpmode(false, 0);
		break;

		case SETPULSER:
			devnum = 8*pPacket->deviceId+pPacket->data[0];
			if(pPacket->data[3] != theApp->myMpsd[devnum]->getPulspoti(1)){
				pstring.sprintf("Error setting pulspoti, mod %d, is: %d, should be: %d", devnum, pPacket->data[3], theApp->myMpsd[devnum]->getPulspoti(1));
				theApp->protocol(pstring, 0);
			}
			theApp->myMpsd[devnum]->setPulserpoti(pPacket->data[1], pPacket->data[3], pPacket->data[2], pPacket->data[4], 0);
			theApp->dispMpsd();
		break;

		case WRITEPERIREG:
			devnum = 8*pPacket->deviceId+pPacket->data[0];
			if(pPacket->data[2] != theApp->myMpsd[devnum]->getInternalreg(pPacket->data[1], 1)){
				pstring.sprintf("Error setting internal mpsd-register, mod %d, is: %d, should be: %d", devnum, pPacket->data[3], theApp->myMpsd[devnum]->getPulspoti(1));
				theApp->protocol(pstring, 0);
			}
			theApp->myMpsd[devnum]->setInternalreg(pPacket->data[1], pPacket->data[2], 0);
		break;

		case WRITEREGISTER:
//			qDebug("writeregister");
		break;

		case SETPROTOCOL:
			qDebug("Answer to set protocol received:");
			qDebug("mcpd-ip address: %d.%d.%d.%d", pPacket->data[0], pPacket->data[1], pPacket->data[2], pPacket->data[3]);
			qDebug("data pc address: %d.%d.%d.%d", pPacket->data[4], pPacket->data[5], pPacket->data[6], pPacket->data[7]);
			qDebug("cmd pc address: %d.%d.%d.%d", pPacket->data[10], pPacket->data[11], pPacket->data[12], pPacket->data[13]);
			qDebug("cmd port: %d, data port: %d", pPacket->data[8], pPacket->data[9]);
			theApp->netDev[0]->setAddress(pPacket->deviceId, theApp->myMcpd[pPacket->deviceId]->getIpAddress());
		default:
		break;
	}
}

void dataCruncher::analyzeBuffer(PDATA_PACKET pd, unsigned char daq, histogram* hist)
{
	unsigned char id, chan, mod, slot, trigId, dataId, offs;
	unsigned short data0, data1, time, counter = 0;
	unsigned long data, delta;
	unsigned long long htim, tim;
	unsigned int i, j;
	unsigned long long var = 0;
	unsigned short neutrons = 0;
	unsigned short triggers = 0;

	htim = pd->time[0] + 0x10000ULL * pd->time[1] + 0x100000000ULL * pd->time[2];

	if(pd->bufferType == 0x0000 || pd->bufferType == 0x0001){

		id = pd->deviceId;
		offs = 8*id;
		// extract parameter values:
		for(i = 0; i < 4; i++){
			var = 0;
			for(j = 0; j < 3; j++){
				var *= 0x10000ULL;
				var += pd->param[i][2-j];
			}
			theApp->myMcpd[pd->deviceId]->setParameter((unsigned char)i, var);
//			theApp->meas->setCounter(i, var);
		}
		// data length = (buffer length - header length) / (3 words per event) - 4 parameters.
 		unsigned int datalen = (pd->bufferLength - pd->headerLength) / 3;
		if(datalen>0){
			for(i = 0; i <	datalen; i++){
				tim = 0x10000 * (pd->data[counter+1] & 0x0007) + pd->data[counter];
				tim += htim;
				delta = tim - lastTime;
				lastTime = tim;
				// not neutron event (counter, chopper, ...)
				if((pd->data[counter+2] & 0x8000) == 0x8000){
					triggers++;
					trigId = (pd->data[counter+2] & 0x7000) / 0x1000;
					dataId = (pd->data[counter+2] & 0x0F00) / 0x100;
					data = (pd->data[counter+2] & 0x00FF) * 0x10000 + (pd->data[counter+1] & 0xFFF8) / 8;
					time = (unsigned short) tim;
//					qDebug("id: %d, trigId: %d, dataId: %d, data: %d, time %lu", pd->deviceId, trigId, dataId, data, tim);
					// dispatch events:
					if(dataId == mon1counter && id == mon1cpu){
							if((countLimit[MON1ID] == 0) || (theApp->meas->mon1 < countLimit[MON1ID]))
								theApp->meas->mon1++;
					}
					if(dataId == mon2counter && id == mon2cpu){
							if((countLimit[MON2ID] == 0) || (theApp->meas->mon2 < countLimit[MON2ID]))
								theApp->meas->mon2++;
					}
				}
				// neutron event:
				else{
					neutrons++;
					mod = (pd->data[counter+2] & 0x7000) / 0x1000;
					slot = (pd->data[counter+2] & 0x0780) / 0x80;
					chan = 8 * 2 * mod + slot;
					data1 = (pd->data[counter+2] & 0x007F) * 8 + (pd->data[counter+1] & 0xE000) / 8192;
					data0 = (pd->data[counter+1] & 0x1FF8) / 8;
//					qDebug("%d %d %lu", pd->deviceId, chan, tim);
					if((countLimit[EVID] == 0) || (theApp->meas->events < countLimit[EVID])){
						theApp->hist[id]->incVal(chan, data0, data1, tim);
						theApp->hist[MCPDS]->incVal(chan, data0, data1, tim);
						theApp->meas->events++;
					}
				}
				counter += 3;
			}
		}
	}
	lastHt = htim;
	// now copy auxiliary counter values into operational counters
	theApp->meas->copyCounters();
}



/*!
    \fn dataCruncher::reset(void)
 */
void dataCruncher::reset(void)
{
    lastHt = 0;
    lastTime = 0;
    oldDelta = 0;
}



/*!
    \fn dataCruncher::setLimit(unsigned long lim)
 */
void dataCruncher::setLimit(unsigned char cNum, unsigned long lim)
{
    countLimit[cNum] = lim;
}

/*!
    \fn dataCruncher::setCounterAssign(unsigned char cpu0, unsigned char counter0, unsigned char cpu1, unsigned char counter1)
 */
void dataCruncher::setCounterAssign(unsigned char cpu0, unsigned char counter0, unsigned char cpu1, unsigned char counter1)
{
    mon1cpu = cpu0;
    mon2cpu = cpu1;
    mon1counter = counter0;
    mon2counter = counter1;
}
