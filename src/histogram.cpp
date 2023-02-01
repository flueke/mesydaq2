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
#include "histogram.h"
#include "mesydaq2.h"

#include <math.h>

#include <qtextstream.h>

histogram::histogram(QObject *parent)
 : QObject(parent)
{
	id = 0;
	clearAllHist();
}

histogram::~histogram()
{
}

bool histogram::incVal(unsigned char chan, unsigned short linear, unsigned short energy, unsigned long time)
{
	if(linear > 959 || energy > 959){
		return false;
	}
	posHist[chan][linear]++;
	posHist[chan+8][energy]++;
	totalCounts++;
	chanCounts[chan]++;
	chanCounts[chan+8]++;
	posHist[CHANNELS-2][linear]++;
	posHist[CHANNELS-1][energy]++;

	if(posHist[chan][linear] > maximum[chan][0]){
		maximum[chan][0] = posHist[chan][linear];
		maximum[chan][1] = linear;
	}
	if(posHist[chan+8][energy] > maximum[chan+8][0]){
		maximum[chan+8][0] = posHist[chan+8][energy];
		maximum[chan+8][1] = energy;
	}
	if(posHist[CHANNELS-2][linear] > maximum[CHANNELS-2][0]){
		maximum[CHANNELS-2][0] = posHist[CHANNELS-2][linear];
		maximum[CHANNELS-2][1] = linear;
	}
	if(posHist[CHANNELS-1][energy] > maximum[CHANNELS-1][0]){
		maximum[CHANNELS-1][0] = posHist[CHANNELS-1][energy];
		maximum[CHANNELS-1][1] = energy;
	}

	// remember values for mean calculation
	floatingMean[chan][meanPos[chan]] = linear;
	floatingMean[chan+8][meanPos[chan+8]] = energy;
	floatingMean[CHANNELS+1][meanPos[CHANNELS+1]] = linear;
	floatingMean[CHANNELS+2][meanPos[CHANNELS+2]] = energy;

	meanPos[chan]++;
	meanPos[chan+8]++;
	if(meanCount[chan]<255)
		meanCount[chan]++;
	if(meanCount[chan+8]<255)
		meanCount[chan+8]++;

	meanPos[CHANNELS+1]++;
	if(meanCount[CHANNELS+1]<255)
		meanCount[CHANNELS+1]++;

	meanPos[CHANNELS+2]++;
	if(meanCount[CHANNELS+2]<255)
		meanCount[CHANNELS+2]++;

	// process timing
	// do data reduction:
	for(unsigned char c=0; c < twidth; c++)
		time /= 2;

	// already a previous value?
	if(lastTime){
		// calculate timing difference
		unsigned long deltat = time - lastTime;
//		unsigned long deltat = 100 + 4*(time - lastTime);
		lastTime = time;
//		if(deltat > 50 && deltat < 150){
//			deltat*= 10;
			if(deltat > 959)
				deltat = 959;
			posHist[CHANNELS][(unsigned short)deltat]++;
			if(posHist[CHANNELS][deltat] > maximum[CHANNELS][0]){
				maximum[CHANNELS][0] = posHist[CHANNELS][deltat];
				maximum[CHANNELS][1] = deltat;
			}
			floatingMean[CHANNELS][meanPos[CHANNELS]] = deltat;
			meanPos[CHANNELS]++;
			if(meanCount[CHANNELS]<255)
				meanCount[CHANNELS]++;
		}
//	}
	else
		lastTime = time;

	return true;
}


/*!
    \fn histogram::clearHist(unsigned int channel)
 */
void histogram::clearHist(unsigned int channel)
{
//	qDebug("clear %d", channel);
	maximum[CHANNELS-1][0] = 0;
	maximum[CHANNELS-1][1] = 0;
	for(int j=0;j<LINBINS; j++){
		posHist[CHANNELS-1][j] -= posHist[channel][j];
		posHist[channel][j] = 0;
		if(posHist[CHANNELS-1][j] > maximum[CHANNELS-1][0]){
			maximum[CHANNELS-1][0] = posHist[CHANNELS-1][j];
			maximum[CHANNELS-1][1] = j;
		}
	}
	totalCounts -= chanCounts[channel];
	chanCounts[CHANNELS-1] -= chanCounts[channel];

	chanCounts[channel] = 0;
	maximum[channel][0] = 0;
	maximum[channel][1] = 0;
	meanCount[channel] = 0;
	meanPos[channel] = 0;
}


/*!
    \fn histogram::clearAllHist(void);
 */
void histogram::clearAllHist(void)
{
 	for(int i=0;i<CHANNELS+1;i++){
		for(int j=0;j<LINBINS; j++){
			posHist[i][j] = 0;
		}
		chanCounts[i] = 0;
		maximum[i][0] = 0;
		maximum[i][1] = 0;
		meanCount[i] = 0;
		meanPos[i] = 0;
	}
	totalCounts = 0;
	twidth = 1;
	lastTime = 0;
}

/*!
    \fn histogram::getTotalCounts(void)
 */
unsigned long histogram::getTotalCounts(void)
{
    return totalCounts;
}


/*!
    \fn histogram::copyLine(channel)
 */
void histogram::copyLine(unsigned int channel, unsigned long * pLineBuffer)
{
	if(channel <= CHANNELS){
	    for(unsigned int i=0; i < 960; i++){
    		pLineBuffer[i] = posHist[channel][i];
//    		if(pLineBuffer[i] > 0)
//    			qDebug("%d: %ld", i, pLineBuffer[i]);
    	};
    }
}


/*!
    \fn histogram::max(unsigned int channel)
 */
unsigned long int histogram::max(unsigned int channel)
{
	if(channel <= CHANNELS)
		return maximum[channel][0];
	else
		return 0;
}


/*!
    \fn histogram::maxpos(unsigned char channel)
 */
unsigned short histogram::maxpos(unsigned int channel)
{
    return maximum[channel][1];
}

/*!
    \fn histogram::getMean(float* vals)
 */
void histogram::getMean(unsigned short chan, float* vals)
{
	float m = 0;
	float s = 0;
	unsigned char c;

	// calculate mean for given channel:
	if(meanCount[chan] > 0){
		for(c=0;c<meanCount[chan];c++)
			m += floatingMean[chan][c];
		m = m / meanCount[chan];

		// calculate sigma
		for(c = 0; c < meanCount[chan]; c++)
			s += pow((float)floatingMean[chan][c] - m, 2);
		s = sqrt(s / meanCount[chan]);
		s = 2.3 * s;
	}
	vals[0] = m;
	vals[1] = s;
//	qDebug("chan: %d, mean: %f +/- %f", chan, m, s);
	return;
}


/*!
    \fn histogram::setWidth(unsigned char width)
 */
void histogram::setWidth(unsigned char width)
{
    twidth = width;
}


/*!
    \fn histogram::setId(unsigned char mcpdId)
 */
void histogram::setId(unsigned char mcpdId)
{
    id = mcpdId;
}


/*!
    \fn histogram::writeHistogram(QFile f)
 */
bool histogram::writeHistogram(QFile* f)
{
  unsigned int i, j, k;

	QTextStream t( f );        // use a text stream
	QString s;
	// Title
    t << "position data: 1 row title (8 x 8 detectors), position data in columns";
    t << '\r' << '\n';
    t << '\t';
    for(i = 0; i < 64; i++){
      t << i << '\t';
    }
    t << '\r' << '\n';
    for(i = 0; i < 960; i++){
      t << i << '\t';
      for(k = 0; k < 8 ; k++){
	      for(j = 0; j < 8 ; j++){
    	    t << posHist[16*k+j][i];
        	t << '\t';
      		}
      }
      t << '\r' << '\n';
    }

    t << '\r' << '\n';
    t << "amplitude/energy data: 1 row title (8 x 8 detectors), amplitude data in columns";
    t << '\r' << '\n';
    t << '\t';
    for(i = 0; i < 64; i++){
      t << i << '\t';
    }
    t << '\r' << '\n';
    for(i = 0; i < 960; i++){
      t << i << '\t';
      for(k = 0; k < 8 ; k++){
	      for(j = 0; j < 8 ; j++){
    	    t << posHist[16*k+j+8][i];
        	t << '\t';
      		}
      }
      t << '\r' << '\n';
    }
    t << '\r' << '\n';
	return true;
}

