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
#include "measurement.h"
#include "mesydaq2.h"
#include "mdefines.h"
#include "histogram.h"
#include "datacruncher.h"

measurement::measurement(QObject *parent, const char *name)
 : QObject(parent, name)
{
	online = false;
	working = true;

	theApp = (mesydaq2*) parent;
	meastime_msec = 0;
	starttime_msec = 0;
	stoptime_msec = 0;
	ratetime_msec = 0;

	events = 0;
	mon1 = 0;
	mon2 = 0;

	running = false;
	starting = false;
	stopping = false;
	rateflag = false;
	listmode = false;
	remote = false;

	runNumber = 0;

	carHistHeight = 128;
	carHistWidth = 128;
	carStep = 0;

    for(unsigned char c = 0; c < 8; c++){
    	rate[10][c] = 0;
    	counter[0][c] = 0;
    	counter[1][c] = 0;
    	preset[c] = 0;
    	counterStart[c] = 0;
    	counterOffset[c] = 0;
    	master[c] = false;
    	stopped[c] = false;
		ratecount[c] = 0;
		ratepointer[c] = 0;
   }
   // assign mon0 to MCPD-ID 0
   monAssign[0][0] = 0;
   // assign mon0 to counter0
   monAssign[0][1] = 0;
   // assign mon0 to MCPD-ID 0
   monAssign[1][0] = 0;
   // assign mon0 to counter1
   monAssign[1][1] = 1;
}

measurement::~measurement()
{
}

/*!
    \fn measurement::setCurrentTime(unsigend long msecs)
 */
void measurement::setCurrentTime(unsigned long msecs)
{
    curtime_msec = msecs;
    if(running){
    	meastime_msec = curtime_msec - starttime_msec;
		setCounter(TCT, msecs/1000);
	}
}

/*!
    \fn measurement::getMeastime(void)
 */
unsigned long measurement::getMeastime(void)
{
    return meastime_msec;
}

/*!
    \fn measurement::getMeastime(unsigned short * time)
 */
void measurement::getMeastime(unsigned short * time)
{
    unsigned long calc;
    // calculate hours
    time[3] = (unsigned short)(meastime_msec / 3600000);
    // remaining
    calc = meastime_msec - time[3] * 3600000;
    // calculate minutes:
    time[2] = (unsigned short)(calc / 60000);
    // remaining
    calc = calc - time[2] * 60000;
    // calculate seconds:
    time[1] = (unsigned short)(calc - 1000);
    // calculate miliseconds
    time[0] = calc - time[1] * 1000;
    qDebug("meastime: %ul, %d %d %d %d", meastime_msec, time[4], time[3], time[2], time[1], time[0]);
}


/*!
    \fn measurement::start(unsigned long time)
 */
void measurement::start(unsigned long time)
{
    starting = false;
    running = true;
    stopping = false;
    starttime_msec = time;
	rateflag = false;
    for(unsigned char c = 0; c < 8; c++){
    	stopped[c] = false;
    	rate[10][c] = 0;
		ratecount[c] = 0;
		ratepointer [c] = 0;
		if(c == TCT){
			counter[1][c] = counterOffset[c];
		    counterStart[TCT] = time / 1000;
		}
    }
}


/*!
    \fn measurement::stop(unsigned long time)
 */
void measurement::stop(unsigned long time)
{
    starting = false;
    running = false;
    stopping = false;
    stoptime_msec = time;
 	counterOffset[TCT] = counter[1][TCT];
}


/*!
    \fn measurement::setCounter(unsigned int cNum, unsigned long long val)
 */
void measurement::setCounter(unsigned int cNum, unsigned long long val)
{
    QString str;

    // set counter

    if(cNum < 8)
   		counter[1][cNum] = counterOffset[cNum] + val - counterStart[cNum];

	// if counter is reset: clear rate buffers
	if(val == 0){
		for(unsigned char c = 0; c < 11; c++)
			rate[c][cNum] = 0;
		counterOffset[cNum] = 0;
		counterStart[cNum] = 0;
	}

	// is counter master and is limit reached?
	if(master[cNum] && (preset[cNum] > 0)){
		if(counter[1][cNum] >= preset[cNum] && !stopping){
			str.sprintf("stop on counter %d, value: %d, preset: %d", cNum, counter[1][cNum], preset[cNum]);
			theApp->protocol(str, 1);
			stopped[cNum] = true;
			stopping = true;
			theApp->stopAll();
		}
	}
}


/*!
    \fn measurement::calcRates()
 */
void measurement::calcRates()
{
    unsigned long tval;

    if(meastime_msec == 0)
    	return;
    if(ratetime_msec >= meastime_msec){
    	ratetime_msec = meastime_msec;
    	return;
    }
    if(rateflag = true){
		unsigned long tval = (meastime_msec - ratetime_msec);

		for(unsigned char c = 0; c < 8; c++){
			if(ratecount[c] < 10)
				ratecount[c]++;
			if(ratecount[c] > 1)
				rate[ratepointer[c]][c] = (counter[1][c] - counter[0][c]) * 1000 / tval;
			else
				rate[ratepointer[c]][c] = 0;
			counter[0][c] = counter[1][c];
			ratepointer[c]++;
			if(ratepointer[c] == 10)
				ratepointer[c] = 0;
		}
	}
	ratetime_msec = meastime_msec;
	rateflag = true;
}

/*!
    \fn measurement::calcMeanRates()
 */
void measurement::calcMeanRates()
{
	unsigned long val2;

	for(unsigned char c = 0; c < 8; c++){
		val2 = 0;
		for(unsigned char d = 1; d < ratecount[c]; d++)
			val2 += rate[d][c];
		if(ratecount[c] > 1)
			rate[10][c] = val2 / (ratecount[c] - 1);
		else
			rate[10][c] = 0;
	}
}

/*!
    \fn measurement::getCounter(unsigned char cNum)
 */
unsigned long long measurement::getCounter(unsigned char cNum)
{
    if(cNum < 8)
    	return counter[1][cNum];
    else
    	return 0;
}


/*!
    \fn measurement::getRate(unsigned char cNum)
 */
unsigned long measurement::getRate(unsigned char cNum)
{
    if(cNum < 8)
    	return rate[10][cNum];
    else
    	return 0;
}




/*!
    \fn measurement::isOk(void)
 */
unsigned char measurement::isOk(void)
{
    if(online && working){
//    	qDebug("online&working");
    	return 0;
    }
    if(online){
    	if(!working){
//    		qDebug("online not working");
    		return 1;
    	}
    }
    else{
//    	qDebug("not online, not working");
    	return 2;
    }
}


/*!
    \fn measurement::setOnline(bool truth)
 */
void measurement::setOnline(bool truth)
{
	QString str;

	online = truth;
	if(online)
		str.sprintf("MCPD online");
	else
		str.sprintf("MCPD offline");
	theApp->protocol(str, 2);
}


/*!
    \fn measurement::setPreset(unsigned char cNum, unsigned long prval, bool mast)
 */
void measurement::setPreset(unsigned char cNum, unsigned long prval, bool mast)
{
    if(cNum < 8){
	    if(mast){
    		// clear all other master flags
    		for(unsigned char c=0;c<8;c++)
    			master[cNum] = false;
    		// set new master
    		master[cNum] = true;
    	}
    	else
    		// just clear master
    		master[cNum] = false;

    	preset[cNum] = prval;
    	if(cNum == EVCT || cNum == M1CT || cNum == M2CT)
    		if(master[cNum])
    			theApp->setCountlimit(cNum, prval);
			else
    			theApp->setCountlimit(cNum, 0);
    }
}


/*!
    \fn measurement::getPreset(unsigned char cNum)
 */
unsigned long measurement::getPreset(unsigned char cNum)
{
    if(cNum < 8)
    	return preset[cNum];
    else
    	return 0;
}


/*!
    \fn measurement::setRunnumber(unsigned int number)
 */
void measurement::setRunnumber(unsigned int number)
{
	runNumber = number;
}


/*!
    \fn measurement::setListmode(bool truth)
 */
void measurement::setListmode(bool truth)
{
	listmode = truth;
	theApp->acqListfile(listmode);
}


/*!
    \fn measurement::setCarHistSize(unsigned int h, unsigned int w)
 */
void measurement::setCarHistSize(unsigned int h, unsigned int w)
{
    carHistWidth = w;
    carHistHeight = h;

}


/*!
    \fn measurement::remote(bool truth)
 */
void measurement::setRemote(bool truth)
{
    remote = truth;
}


/*!
    \fn measurement::remoteStart(void)
 */
bool measurement::remoteStart(void)
{
    return remote;
}


/*!
    \fn measurement::setStep(unsigned int step)
 */
void measurement::setStep(unsigned int step)
{
    carStep = step;
}


/*!
    \fn measurement::getCarWidth()
 */
unsigned int measurement::getCarWidth()
{
    return carHistWidth;
}


/*!
    \fn measurement::getCarHeight()
 */
unsigned int measurement::getCarHeight()
{
    return carHistHeight;
}


/*!
    \fn measurement::getRun()
 */
unsigned int measurement::getRun()
{
    return runNumber;
}

/*!
    \fn measurement::isMaster(unsigned char cNum)
 */
bool measurement::isMaster(unsigned char cNum)
{
	return(master[cNum]);
}



/*!
    \fn measurement::clearCounter(unsigned char cNum)
 */
void measurement::clearCounter(unsigned char cNum)
{
    if(cNum > 7)
		return;

	if(cNum == TCT){
		if(running){
			counterStart[cNum] += counter[1][cNum];
			counterStart[cNum] -= counterOffset[cNum];
			counterOffset[cNum] = 0;
		}
	}

    if(cNum == EVCT)
    	events = 0;
    if(cNum == M1CT)
    	mon1 = 0;
    if(cNum == M2CT)
    	mon2 = 0;

	counter[1][cNum] = 0;

	for(unsigned char c = 0; c < 11; c++)
		rate[c][cNum] = 0;
	counterOffset[cNum] = 0;

	ratecount[cNum] = 0;
	ratepointer[cNum] = 0;
}

/*!
    \fn measurement::hasStopped(unsigned char cNum)
 */
bool measurement::hasStopped(unsigned char cNum)
{
    if(cNum < 8){
    	return stopped[cNum];
    }
    else
    	return false;
}

/*!
    \fn measurement::copyCounters(void)
 */
void measurement::copyCounters(void)
{
	setCounter(EVCT, events);
	setCounter(M1CT, mon1);
	setCounter(M2CT, mon2);
}


/*!
    \fn measurement::limitReached(unsigned char cNum)
 */
bool measurement::limitReached(unsigned char cNum)
{
    if(cNum >= 8)
    	return false;

    if(master[cNum] && (counter[1][cNum] >= preset[cNum]))
    	return true;
    else
    	return false;
}



/*!
    \fn measurement::setMaxBytes(unsigned long num)
 */
void measurement::setMaxBytes(unsigned long num)
{
    /// @todo implement me
}


/*!
    \fn measurement::incBytesWritten(unsigned int num)
 */
void measurement::incBytesWritten(unsigned int num)
{
    /// @todo implement me
}


/*!
    \fn measurement::assignCounter(unsigned char counter, unsigned char cpu,  unsigned char cnt)
 */
void measurement::assignCounter(unsigned char counter, unsigned char cpu,  unsigned char cnt)
{
    monAssign[counter][0] = cpu;
    monAssign[counter][1] = cnt;
	theApp->dc->setCounterAssign(monAssign[0][0], monAssign[0][1], monAssign[1][0], monAssign[1][1]);
}


/*!
    \fn measurement::getCounterAssign(unsigned char* ca)
 */
void measurement::getCounterAssign(unsigned char* ca)
{
    ca[0] = monAssign[0][0];
    ca[1] = monAssign[0][1];
    ca[2] = monAssign[1][0];
    ca[3] = monAssign[1][1];
}


/*!
    \fn measurement::serialize(QFile * fi)
 */
void measurement::serialize(QFile * fi)
{
	unsigned char c;
	QTextStream t( fi );        // use a text stream

	t << "monitor1 = " << monAssign[0][0] << " " << monAssign[0][1];
	t << '\r' << '\n';
	t << "monitor1 = " << monAssign[0][0] << " " << monAssign[0][1];
	t << '\r' << '\n';
}

#include "measurement.moc"