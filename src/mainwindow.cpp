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
#include "mainwindow.h"
#include "mdefines.h"
#include "mcpd8.h"
#include "mpsd8.h"
#include "measurement.h"

#include "qpushbutton.h"
#include "qcombobox.h"
#include "qspinbox.h"
#include "qlineedit.h"
#include "qcheckbox.h"
#include "qmessagebox.h"
#include "qfiledialog.h"
#include "qpainter.h"
#include "qpen.h"
#include "qradiobutton.h"
#include "qfont.h"

#include <math.h>


mainWindow::mainWindow(QWidget* parent, const char* name, WFlags fl)
 : mesydaq2mainwindow(parent, name, fl)
{
	theApp = (mesydaq2 *) parent;
	pBuffer = (unsigned short *) &cmdBuffer;
    height = 480;
    histHeight = 480;
    yStart = 480;
    histOffset = 60;
    width = 960;
    xstep = 1;
    ystep = 1;
    scale = 1;
    dispMax = 10;
    dispRange = dispMax;
    dispLog = false;
    dispThresh = false;
    dispLoThresh = 0;
    multi = false;
    dispNum = 0;
    dontSend = false;
}


mainWindow::~mainWindow()
{
}

void mainWindow::startStopSlot()
{
	if(startStopButton->isOn()){
		// get timing binwidth
		theApp->setTimingwidth(timingBox->value());

		// get latest preset entry
		if(theApp->meas->isMaster(TCT))
			theApp->meas->setPreset(TCT, tPreset->value(), true);
		if(theApp->meas->isMaster(EVCT))
			theApp->meas->setPreset(EVCT, evPreset->value(), true);
		if(theApp->meas->isMaster(M1CT))
			theApp->meas->setPreset(M1CT, m1Preset->value(), true);
		if(theApp->meas->isMaster(M2CT))
			theApp->meas->setPreset(M2CT, m2Preset->value(), true);

		startStopButton->setText("Stop");
		theApp->startAll();
		// set device id to 0 -> will be filled by mesydaq for master
		cmdBuffer[0] = 0;
	}
	else{
		startStopButton->setText("Start");
		theApp->stopAll();
	}
}

void mainWindow::sendCellSlot()
{
	cmdBuffer[0] = mcpdId->value();
	cmdBuffer[1] = SETCELL;
	cmdBuffer[2] = (unsigned short) cellSource->currentItem();
	cmdBuffer[3] = (unsigned short) cellTrigger->currentItem();
	cmdBuffer[4] = (unsigned short) cellCompare->value();
	theApp->protocol("set cell", 2);
	theApp->sendCommand(pBuffer);
}

void mainWindow::sendParamSlot()
{
	cmdBuffer[0] = mcpdId->value();
	cmdBuffer[1] = SETPARAM;
	cmdBuffer[2] = (unsigned short) param->value();
	cmdBuffer[3] = (unsigned short) paramSource->currentItem();
	theApp->protocol("set parameter", 2);
	theApp->sendCommand(pBuffer);
}

void mainWindow::sendAuxSlot()
{
	bool ok;
	QString str;
	unsigned short compare;

	str = compareAux->text();
	compare = (unsigned short) (str.toInt(&ok,0));
	cmdBuffer[0] = mcpdId->value();
	cmdBuffer[1] = SETAUXTIMER;
	cmdBuffer[2] = (unsigned short) timer->value();
	cmdBuffer[3] = compare;
	theApp->protocol("set aux timer", 2);
	theApp->sendCommand(pBuffer);
}

void mainWindow::resetTimerSlot()
{
	cmdBuffer[0] = mcpdId->value();
	cmdBuffer[1] = SETCLOCK;
	cmdBuffer[2] = 0;
	cmdBuffer[3] = 0;
	cmdBuffer[4] = 0;
	theApp->protocol("reset timer", 2);
	theApp->sendCommand(pBuffer);
}

void mainWindow::setTimingSlot()
{
	cmdBuffer[0] = mcpdId->value();
	cmdBuffer[1] = SETTIMING;
	if(master->isChecked()){
		cmdBuffer[2] = 1;
		resetTimer->setEnabled(true);
	}
	else{
		cmdBuffer[2] = 0;
		resetTimer->setEnabled(false);
	}
	if(terminate->isChecked())
		cmdBuffer[3] = 1;
	else
		cmdBuffer[3] = 0;
	theApp->protocol("set timing", 2);
	theApp->sendCommand(pBuffer);
}

void mainWindow::setMcpdIdSlot()
{
	unsigned short id = (unsigned short) deviceId->value();
	cmdBuffer[0] = mcpdId->value();
	cmdBuffer[1] = SETID;
	cmdBuffer[2] = id;
	theApp->sendCommand(pBuffer);
}

void mainWindow::setStreamSlot()
{
	unsigned short id = (unsigned short) deviceId->value();
	cmdBuffer[0] = mcpdId->value();
	cmdBuffer[1] = QUIET;
	if(statusStream->isChecked())
		cmdBuffer[2] = 1;
	else
		cmdBuffer[2] = 0;
	pstring.sprintf("Set stream %d", cmdBuffer[2]);
	theApp->protocol(pstring, 2);
	theApp->sendCommand(pBuffer);
}

void mainWindow::setIpUdpSlot()
{
	bool ok;
	QString stri;
	unsigned char ip0, ip1, ip2, ip3;
	unsigned char dip0, dip1, dip2, dip3;
	unsigned char cip0, cip1, cip2, cip3;
	unsigned short cUdp, dUdp;

	if(modifyIp->isChecked()){
		stri = mcpdIpAddress0->text();
		ip0 = (unsigned char) (stri.toInt(&ok));
		stri = mcpdIpAddress1->text();
		ip1 = (unsigned char) (stri.toInt(&ok));
		stri = mcpdIpAddress2->text();
		ip2 = (unsigned char) (stri.toInt(&ok));
		stri = mcpdIpAddress3->text();
		ip3 = (unsigned char) (stri.toInt(&ok));
	}
	else{
		ip0 = 0;
		ip1 = 0;
		ip2 = 0;
		ip3 = 0;
	}

	if(dataThisPc->isChecked()){
		dip0 = 0;
		dip1 = 0;
		dip2 = 0;
		dip3 = 0;
	}
	else{
		stri = dataIpAddress0->text();
		dip0 = (unsigned char) (stri.toInt(&ok));
		stri = dataIpAddress1->text();
		dip1 = (unsigned char) (stri.toInt(&ok));
		stri = dataIpAddress2->text();
		dip2 = (unsigned char) (stri.toInt(&ok));
		stri = dataIpAddress3->text();
		dip3 = (unsigned char) (stri.toInt(&ok));
	}

	if(cmdThisPc->isChecked()){
		cip0 = 0;
		cip1 = 0;
		cip2 = 0;
		cip3 = 0;
	}
	else{
		stri = cmdIpAddress0->text();
		cip0 = (unsigned char) (stri.toInt(&ok));
		stri = cmdIpAddress1->text();
		cip1 = (unsigned char) (stri.toInt(&ok));
		stri = cmdIpAddress2->text();
		cip2 = (unsigned char) (stri.toInt(&ok));
		stri = cmdIpAddress3->text();
		cip3 = (unsigned char) (stri.toInt(&ok));
	}

	cUdp = (unsigned short) cmdUdpPort->value();
	dUdp = (unsigned short) dataUdpPort->value();

	// fill buffer
	cmdBuffer[0] = mcpdId->value();
	cmdBuffer[1] = SETPROTOCOL;
	cmdBuffer[2] = ip0;
	cmdBuffer[3] = ip1;
	cmdBuffer[4] = ip2;
	cmdBuffer[5] = ip3;
	cmdBuffer[6] = dip0;
	cmdBuffer[7] = dip1;
	cmdBuffer[8] = dip2;
	cmdBuffer[9] = dip3;
	cmdBuffer[10] = cUdp;
	cmdBuffer[11] = dUdp;
	cmdBuffer[12] = cip0;
	cmdBuffer[13] = cip1;
	cmdBuffer[14] = cip2;
	cmdBuffer[15] = cip3;
	theApp->sendCommand(pBuffer);
}

void mainWindow::setPulserSlot()
{
	qDebug("pulserSlot");

	if(dontSend){
		dontSend = false;
		return;
	}
	qDebug("send");
	bool ok;
	unsigned short id = (unsigned short) devid->value();
	unsigned short mod = module->value();
	unsigned short chan = pulsChan->value();

	unsigned char ampl;
	if(pulsampRadio1->isChecked())
		ampl = (unsigned char) pulsAmp1->text().toInt(&ok);
	else
		ampl = (unsigned char) pulsAmp2->text().toInt(&ok);

	unsigned short pos;
	if(pulsLeft->isChecked())
		pos = 0;
	if(pulsRight->isChecked())
		pos = 1;
	if(pulsMid->isChecked())
		pos = 2;

	unsigned short pulse;
	if(pulserButton->isOn()){
		pulse = 1;
		pulserButton->setPaletteForegroundColor(QColor(238,0,0));
	}
	else{
		pulse = 0;
		pulserButton->setPaletteForegroundColor(QColor(0,0,0));
	}

	cmdBuffer[0] = id;
	cmdBuffer[1] = SETPULSER;
	cmdBuffer[2] = mod;
	cmdBuffer[3] = chan;
	cmdBuffer[4] = pos;
	cmdBuffer[5] = ampl;
	cmdBuffer[6] = pulse;
	theApp->sendCommand(pBuffer);
}

void mainWindow::setGainSlot()
{
	bool ok;
	unsigned short id = (unsigned short) devid->value();
	unsigned short addr = module->value();
	unsigned short chan = channel->text().toUInt(&ok, 0);
	float gainval = gain->text().toFloat(&ok);

	if(gainval < 0.5)
		gainval = 0.5;
	if(gainval > 1.88)
		gainval = 1.88;

	cmdBuffer[0] = id;
	cmdBuffer[1] = SETGAIN;
	cmdBuffer[2] = addr;
	if(comgain->isChecked())
		cmdBuffer[3] = 8;
	else
		cmdBuffer[3] = chan;

	cmdBuffer[4] = theApp->myMpsd[addr]->calcGainpoti(gainval);
	qDebug("set gain to potival: %d", cmdBuffer[4]);
	theApp->sendCommand(pBuffer);
}

void mainWindow::setThresholdSlot()
{
	bool ok;
	unsigned short id = (unsigned short) devid->value();
	unsigned short addr = module->value();
	unsigned short thresh = threshold->text().toUInt(&ok, 0);
	cmdBuffer[0] = id;
	cmdBuffer[1] = SETTHRESH;
	cmdBuffer[2] = addr;
	cmdBuffer[3] = theApp->myMpsd[addr]->calcThreshpoti(thresh);
	theApp->sendCommand(pBuffer);
}

void mainWindow::allPulserSlot()
{
	theApp->allPulserOff();
}

void mainWindow::selectListfileSlot()
{
  theApp->getListfilename();
  dispFiledata();
}

void mainWindow::acqListfileSlot()
{
	if(acqListfile->isChecked())
		theApp->acqListfile(true);
	else
		theApp->acqListfile(false);
}

/*!
    \fn mainWindow::update(void)
 */
void mainWindow::update(void)
{
   	unsigned short id = (unsigned short) mcpdId->value();
    pstring.sprintf("%ld", theApp->dataRxd);
    dataRx->setText(pstring);
    pstring.sprintf("%ld", theApp->cmdTxd);
    cmdTx->setText(pstring);
    pstring.sprintf("%ld", theApp->cmdRxd);;
    cmdRx->setText(pstring);
    pstring = buildTimestring(theApp->headertime, true);
    hTimeText->setText(pstring);
    pstring = buildTimestring(theApp->meas->getMeastime(), false);
    mTimeText->setText(pstring);

    // parameter values for selected ID
    pstring.sprintf("%lu", theApp->myMcpd[id]->getParameter(0));
    param0->setText(pstring);
    pstring.sprintf("%lu", theApp->myMcpd[id]->getParameter(1));
    param1->setText(pstring);
    pstring.sprintf("%lu", theApp->myMcpd[id]->getParameter(2));
    param2->setText(pstring);
    pstring.sprintf("%lu", theApp->myMcpd[id]->getParameter(3));
    param3->setText(pstring);

	theApp->meas->calcMeanRates();

    // measurement values
    // counters and rates
    pstring.sprintf("%lu", theApp->meas->getCounter(EVCT));
    totalCounts->setText(pstring);
    pstring.sprintf("%lu", theApp->meas->getCounter(TCT));
    tSecsText->setText(pstring);
    pstring.sprintf("%lu", theApp->meas->getRate(EVCT));
    eventRate->setText(pstring);
    pstring.sprintf("%lu", theApp->meas->getCounter(M1CT));
    monitor1->setText(pstring);
    pstring.sprintf("%lu", theApp->meas->getCounter(M2CT));
    monitor2->setText(pstring);
    pstring.sprintf("%lu", theApp->meas->getRate(M1CT));
    monRate1->setText(pstring);
    pstring.sprintf("%lu", theApp->meas->getRate(M2CT));
    monRate2->setText(pstring);

}

/*!
    \fn mainWindow::buildTimestring(unsigned long nsec)
 */
QString mainWindow::buildTimestring(unsigned long timeval, bool nano)
{
	// nsec = time in 100 nsecs
	//-> usec =
	//->
	QString str;
	unsigned long nsec, val, sec, min, hr;
	// calculate raw seconds
	if(nano){
		val = timeval / 10000000;
		nsec = timeval - (10000000 * val);
	}
	else{
		val = timeval / 1000;
		nsec = timeval - (1000 * val);
//		qDebug("%d %d %d", timeval, val, nsec);
	}
	// hours = val / 3600 (s/h)
	hr = val / 3600;
	// remaining seconds:
	val -= hr * 3600;
	// minutes:
	min = val / 60;
	// remaining seconds:
	sec = val - (min * 60);
//	qDebug("%x - %x - %x", theApp->ht[2], theApp->ht[1], theApp->ht[0]);
//	qDebug("%lu %lu %lu %lu %lu", nsecs, hr, min, sec, nsec);
	str.sprintf("%2lu:%2lu:%2lu", hr, min, sec);
	return str;
}


/*!
    \fn mainWindow::drawData(void)
 */
void mainWindow::drawData(void)
{
	float val2, val1;
	unsigned int start = 0;
	QString str, str2;
	QFont fo;
	QPainter p2;
	p2.begin(this->dataFrame);
	p2.setPen(QPen(black, 1, SolidLine));
	p2.setBrush(QBrush(black));
	fo = p2.font();
	fo.setStyleStrategy(QFont::PreferAntialias);
	fo.setPointSize(8);
	p2.setFont(fo);
	if(zoomBox->isChecked()){
		start = zoomStart->value();
	}

	if(dispThresh)
		dispRange -= dispLoThresh;

	if(dispLog){
		dispRange = ceil(log10(dispRange));
	}

	if(dispRange > 0)
		ystep = histHeight / dispRange;
	else
		ystep = 1;

//	qDebug("dispRange: %f, height: %d, ystep: %f", dispRange, height, ystep);

	dispChannelCounts = 0;
	for(unsigned int i=start; i<start+dispLen; i++){
		val2 = 0;
		val1 = 0;
		if(dispLog){
			if(pDispBuffer[i] >0)
				val1 = log10(pDispBuffer[i]) * ystep;
			if((pDispBuffer[i+1] > 0) && (i < start+dispLen-1))
				val2 = log10(pDispBuffer[i+1]) * ystep;
		}
		else
		{
			val1 = pDispBuffer[i] * ystep;
			if(i < start+dispLen-1)
				val2 = pDispBuffer[i+1] * ystep;
		}
		// horizontal line
		p2.drawLine((i-start)*xstep, yStart-val1,(i+1-start)*xstep, yStart-val1);
		// vertical line right
		p2.drawLine((i+1-start)*xstep, yStart-val1, (i+1-start)*xstep, yStart-val2);
		dispChannelCounts += pDispBuffer[i];
	}
	if(multi){
		str.sprintf("mcpd: %d, mpsd: %d, channel: %d", dispMcpd->value(), dispMpsd->value(), dispNum);
		p2.drawText(10, 20 + yStart - 60, str);
		str.sprintf("Total counts: %d", dispChannelCounts);
		p2.drawText(10, 30 + yStart - 60, str);	}
	else{
		str.sprintf("showing: ");
		if(dispAll->isChecked()){
			if(dispAllPos->isChecked())
				str.append("position sum (all channels)");
			else
				str.append("amplitude sum (all channels)");
		}
		else{
			if(dispChan->value() > 7){
				str2.sprintf("mcpd: %d, mpsd: %d, channel: %d", dispMcpd->value(), dispMpsd->value(), dispChan->value()-8);
				str.append(str2);
				str.append(" (amplitude)");
			}
			else{
				str2.sprintf("mcpd: %d, mpsd: %d, channel: %d", dispMcpd->value(), dispMpsd->value(), dispChan->value());
				str.append(str2);
				str.append(" (position)");
			}
		}
		p2.drawText(10, 20, str);
		str.sprintf("Total counts: %d", dispChannelCounts);
		p2.drawText(10, 30, str);	}
	if(acqListfile->isChecked()){
		str.sprintf("current listfile: ");
		str.append(listFilename->text());
	}
	else
		str.sprintf(" ");
	p2.drawText(500, 20, str);



	p2.end();

}


/*!
    \fn mainWindow::setData(unsigned long * data, unsigned int len)
 */
void mainWindow::setData(unsigned long * data, unsigned int len, unsigned long int max)
{
//    qDebug("setData, max: %ld", max);
    unsigned long int m = max * 1.1;
    unsigned int start = 0;
    pDispBuffer = data;
    dispLen = len;
    xstep = 1;
    // zoom display?
    if(zoomBox->isChecked()){
    	// reduce displayed data
    	dispLen = len / 4;
    	//get start value
    	start = zoomStart->value();
    	xstep = 4;
    	// and search for mnaximum in zoomed area:
    	m = 0;
    	for(unsigned int j=start; j<start+dispLen; j++)
    		if(pDispBuffer[j] > m)
    			m = pDispBuffer[j] * 1.1;
    }
    dispMax = 10;
    dispRange = dispMax;
    scale = 1;

    // reduce data in case of threshold settings:
    if(dispThresh){
    	for(unsigned int i = start; i < dispLen; i++){
//    		if(pDispBuffer[i] > dispLoThresh && pDispBuffer[i] < dispHiThresh)
//    			pDispBuffer[i] -= dispLoThresh;
//    		else{
				if(pDispBuffer[i] < dispLoThresh)
					pDispBuffer[i] = 0;
				if(pDispBuffer[i] > dispHiThresh)
					pDispBuffer[i] = dispHiThresh;
//	    	}
    	}
    }
   	// check for upper threshold
	if(dispThresh){
		if(dispHiThresh < max){
			dispMax = dispHiThresh;
//	    	dispRange = dispMax - dispLoThresh;
	    	dispRange = dispMax;
	    }
	    else{
		    // calculate maximum
	    	while(m > dispMax){
	    		if(m < 100)
					dispMax *= 2.0;
				else
					dispMax *= 1.3;
			}
        	dispRange = dispMax;
    	}
   	}
    else{
	    // calculate maximum
    	while(m > dispMax){
    		if(m < 100)
				dispMax *= 2.0;
			else
				dispMax *= 1.3;
		}
       	dispRange = dispMax;
    }
}


/*!
    \fn mainWindow::drawDataGrid(void)
 */
void mainWindow::drawDataGrid(void)
{
	QPainter p2;
	QString str;

	// clear old grid:
  	p2.begin(this->mainFrame);
	p2.setPen(QPen(black, 1, NoPen));
	p2.setBrush(QBrush(lightGray));
	p2.drawRect(mainFrame->contentsRect());
  	p2.end();

	// clear old frame:
  	p2.begin(this->dataFrame);
	p2.setPen(QPen(black, 1, NoPen));
	p2.setBrush(QBrush(white));
	p2.drawRect(mainFrame->contentsRect());
	p2.end();

}

/*!
    \fn mainWindow::drawXAxis(void)
 */
void mainWindow::drawXAxis(void)
{
	QPainter p2;
	QString str;
	QFont fo;
	unsigned int start = 0;
	unsigned int step = width / 4;
	unsigned int scalestep = step;
	if(zoomBox->isChecked()){
		start = zoomStart->value();
		scalestep = step / 4;
	}
 	p2.begin(this->mainFrame);
	p2.setPen(QPen(black, 1, SolidLine));
	p2.setBrush(QBrush(black));

	fo = p2.font();
	fo.setStyleStrategy(QFont::PreferAntialias);
	fo.setPointSize(8);
	p2.setFont(fo);

  	if(zoomBox->isChecked()){
		for(int i=0;i<5;i++){
			p2.drawLine(80+i*step, 23+height, 80+i*step, 10+height);
			str.sprintf("%d", start+scalestep * i);
			p2.drawText(70+i*step, 35+height, str);
		}
		for(int i=0;i<960;i+=20)
			p2.drawLine(80+i, 15+height, 80+i, 10+height);
		for(int i=0;i<960;i+=40){
			p2.drawLine(80+i, 20+height, 80+i, 10+height);
		}
	}
	else{
		for(int i=0;i<5;i++){
			p2.drawLine(80+i*step, 23+height, 80+i*step, 10+height);
			str.sprintf("%d", start+scalestep * i);
			p2.drawText(70+i*step, 35+height, str);
		}
		for(int i=0;i<960;i+=10)
			p2.drawLine(80+i, 15+height, 80+i, 10+height);
		for(int i=0;i<960;i+=50)
			p2.drawLine(80+i, 20+height, 80+i, 10+height);
	}
  	p2.end();
}

/*!
    \fn mainWindow::drawYAxis(void)
 */
void mainWindow::drawYAxis(void)
{
	QPainter p2;
	QString str;
	QFont fo;

	p2.begin(this->mainFrame);
  	// draw y-axis
	p2.setPen(QPen(black, 1, SolidLine));
	p2.setBrush(QBrush(black));
	fo = p2.font();
	fo.setStyleStrategy(QFont::PreferAntialias);
	fo.setPointSize(8);
	p2.setFont(fo);

	unsigned int step = histHeight / 10;
  	unsigned int logrange = ceil(log10(dispRange));
  	float logstep = histHeight / logrange;
  	// y-Axis
	if(dispLog){
//		qDebug("logrange: %d, logstep: %f", logrange, logstep);
		for(unsigned char c = 0; c <= logrange; c++){
			for(unsigned char d = 1; d < 11; d++){
				float offset = c*logstep + log10(d)*logstep;
				p2.drawLine(70, 10+yStart-offset, 80, 10+yStart-offset);
			}
			str.sprintf("10E%d", c);
			p2.drawText(20, 15+yStart-c*logstep, str);
		}
	}
	else{
		for(int i=0;i<11;i++){
			p2.drawLine(70, 10+yStart-i*step, 80, 10+yStart-i*step);
			str.sprintf("%ld", (unsigned long int)(dispRange / 10) * i);
			p2.drawText(20, 15+yStart-i*step, str);
		}
  	}
  	p2.end();
}

/*!
    \fn mainWindow::draw(void)
 */
void mainWindow::draw(void)
{
	dispId = dispMcpd->value();
	if(!multi || (multi && dispNum == 0)){
		drawDataGrid();
		drawXAxis();
	}
	drawYAxis();
	drawData();
	drawOpData();
//	displayMpsdSlot();
}

void mainWindow::clearAllSlot()
{
	theApp->clearAllHist();
}

void mainWindow::clearMcpdSlot()
{
	unsigned int start = dispMcpd->value() * 64;
	for(unsigned int i = start; i < start+64; i++)
		theApp->clearChanHist(i);
	theApp->draw();
}

void mainWindow::clearMpsdSlot()
{
	unsigned int start = dispMpsd->value() * 8 + dispMcpd->value() * 64;
//	qDebug("clearMpsd: %d", start);
	for(unsigned int i = start; i < start+8; i++)
		theApp->clearChanHist(i);
	theApp->draw();
}

void mainWindow::clearChanSlot()
{
	unsigned long chan = dispChan->value() + dispMpsd->value() * 8 + dispMcpd->value() * 64;
//	qDebug("clearChan: %d",chan);
	theApp->clearChanHist(chan);
	theApp->draw();
}


void mainWindow::replayListfileSlot()
{
 QString name = QFileDialog::getOpenFileName(theApp->getListfilepath(), "mesydaq data files (*.mdat);;all files (*.*);;really all files (*)", this, "Load...");
  if(!name.isEmpty()){
    theApp->readListfile(name);
  }
}

void mainWindow::setRunIdSlot()
{
	unsigned short runid = (unsigned short) devid->value();
	cmdBuffer[0] = 0;
	cmdBuffer[1] = SETRUNID;
	cmdBuffer[2] = runid;
	theApp->sendCommand(pBuffer);
	pstring.sprintf("Set run ID to %d", runid);
	theApp->protocol(pstring, 2);
}

/*!
    \fn mainWindow::dispMcpdSlot(void)
 */
void mainWindow::displayMcpdSlot(void)
{
    QString str;
    unsigned short values[4];
    unsigned char val[4];
    // retrieve displayed ID
    unsigned char id = mcpdId->value();

    // now get and display parameters:

    // master / termination:
    if(theApp->myMcpd[id]->isMaster()){
    	master->setChecked(true);
    	mcpdMasterText1->setText("Master");
    }
    else{
    	master->setChecked(false);
    	mcpdMasterText1->setText("Slave");
    }
    if(theApp->myMcpd[id]->isTerminated())
    	terminate->setChecked(true);
    else
    	terminate->setChecked(false);

    // get cell parameters
    theApp->myMcpd[id]->getCounterCell(cellSource->currentItem(), values);
    cellTrigger->setCurrentItem(values[0]);
	cellCompare->setValue(values[1]);

    // get parameter settings
    paramSource->setCurrentItem(theApp->myMcpd[id]->getParamSource(param->value()));

	// get timer settings
	str.sprintf("%x", theApp->myMcpd[id]->getAuxTimer(timer->value()));
	compareAux->setText(str);

	// get stream setting
	statusStream->setChecked(theApp->myMcpd[id]->getStream());

	// get ip contact address and use it for mesydaq ip
	str = theApp->netDev[0]->getAddress(id);
	splitAddress(str, &val[0]);

	str.sprintf("%d", val[0]);
	mIpAddress0->setText(str);
	str.sprintf("%d", val[1]);
	mIpAddress1->setText(str);
	str.sprintf("%d", val[2]);
	mIpAddress2->setText(str);
	str.sprintf("%d", val[3]);
	mIpAddress3->setText(str);

	// display online status:
	if(theApp->myMcpd[id]->isOnline())
		mcpdStatusText1->setText("Online");
	else
		mcpdStatusText1->setText("OFFLINE");

	// display configuration status:
	if(theApp->myMcpd[id]->isConfigured())
		mcpdConfigText1->setText("Configured");
	else
		mcpdConfigText1->setText("Not configured");
}


/*!
    \fn mainWindow::dispMpsdSlot(void)
 */
void mainWindow::displayMpsdSlot(void)
{
    QString dstr;

    // retrieve displayed ID
    unsigned char id = devid_2->value();
    unsigned char mod = module->value();

    // Status display:
	if(theApp->myMpsd[8*id]->getMpsdId())
		dstr.sprintf("%d", theApp->myMpsd[8*id]->getMpsdId());
	else
		dstr.sprintf("off");
	status0->setText(dstr);
	if(theApp->myMpsd[8*id+1]->getMpsdId())
		dstr.sprintf("%d", theApp->myMpsd[8*id+1]->getMpsdId());
	else
		dstr.sprintf("off");
	status1->setText(dstr);
	if(theApp->myMpsd[8*id+2]->getMpsdId())
		dstr.sprintf("%d", theApp->myMpsd[8*id+2]->getMpsdId());
	else
		dstr.sprintf("off");
	status2->setText(dstr);
	if(theApp->myMpsd[8*id+3]->getMpsdId())
		dstr.sprintf("%d", theApp->myMpsd[8*id+3]->getMpsdId());
	else
		dstr.sprintf("off");
	status3->setText(dstr);
	if(theApp->myMpsd[8*id+4]->getMpsdId())
		dstr.sprintf("%d", theApp->myMpsd[8*id+4]->getMpsdId());
	else
		dstr.sprintf("off");
	status4->setText(dstr);
	if(theApp->myMpsd[8*id+5]->getMpsdId())
		dstr.sprintf("%d", theApp->myMpsd[8*id+5]->getMpsdId());
	else
		dstr.sprintf("off");
	status5->setText(dstr);
	if(theApp->myMpsd[8*id+6]->getMpsdId())
		dstr.sprintf("%d", theApp->myMpsd[8*id+6]->getMpsdId());
	else
		dstr.sprintf("off");
	status6->setText(dstr);
	if(theApp->myMpsd[8*id+7]->getMpsdId())
		dstr.sprintf("%d", theApp->myMpsd[8*id+7]->getMpsdId());
	else
		dstr.sprintf("off");
	status7->setText(dstr);

	// gain:
	unsigned char chan = channel->value();
	dstr.sprintf("%1.2f", theApp->myMpsd[8*id+mod]->getGainval(chan, 0));
	gain->setText(dstr);

	// threshold:
	dstr.sprintf("%d", theApp->myMpsd[8*id+mod]->getThreshold(0));
	threshold->setText(dstr);

	// pulser:
	// on/off
   	dontSend = true;
	if(theApp->myMpsd[8*id+mod]->isPulserOn()){
		pulserButton->setOn(true);
		pulserButton->setPaletteForegroundColor(QColor(238,0,0));
	}
	else{
		pulserButton->setOn(false);
		pulserButton->setPaletteForegroundColor(QColor(0,0,0));
	}
	// channel
   	dontSend = true;
	pulsChan->setValue((int)theApp->myMpsd[8*id+mod]->getPulschan());
	// amplitude
	dstr.sprintf("%3.0f", theApp->myMpsd[8*id+mod]->getPulsamp(0));
//	pulsAmp->setValue((int)theApp->myMpsd[8*id+mod]->getPulsamp());
	// position
   	dontSend = true;
	switch(theApp->myMpsd[8*id+mod]->getPulspos()){
		case 0:
			pulsLeft->setChecked(true);
		break;
		case 1:
			pulsRight->setChecked(true);
		break;
		case 2:
			pulsMid->setChecked(true);
		break;
	}

	// mode
	if(theApp->myMpsd[8*id+mod]->getMode())
		amp->setChecked(true);
	else
		pos->setChecked(true);
	dontSend = false;
}



void mainWindow::scanPeriSlot()
{
	unsigned short id = (unsigned short) devid->value();
	theApp->scanPeriph(id);
}

void mainWindow::setModeSlot(int mode)
{
	unsigned short id = (unsigned short) devid->value();
	unsigned short addr = module->value();

	cmdBuffer[0] = id;
	cmdBuffer[1] = SETMODE;
	cmdBuffer[2] = addr;
	cmdBuffer[3] = mode;
	qDebug("set mode %d to %d", addr, mode);
	theApp->sendCommand(pBuffer);
}

void mainWindow::saveSetupSlot()
{
	theApp->saveSetup();
}

void mainWindow::restoreSetupSlot()
{
	theApp->loadSetup(true);
	theApp->initHardware();
}


void mainWindow::redrawSlot()
{
	draw();
}


/*!
    \fn mainWindow::processDispData()
 */
void mainWindow::processDispData()
{
    /// @todo implement me
}

void mainWindow::applyThreshSlot()
{
	bool ok;
	if(useThresh->isChecked()){
		dispThresh = true;
		dispHiThresh = hiLim->text().toUInt(&ok, 0);
		dispLoThresh = loLim->text().toUInt(&ok, 0);
		qDebug("lo: %ld, hi: %ld", dispLoThresh, dispHiThresh);
	}
	else
		dispThresh = false;
}

void mainWindow::linlogSlot()
{
	if(log->isChecked()){
		dispLog = true;
		qDebug("log");
	}
	else{
		dispLog = false;
		qDebug("lin");
	}
}


/*!
    \fn mainWindow::drawOpData()
 */
void mainWindow::drawOpData()
{
	float meansigma[2];

	QString str;
    // display mean and sigma:
    if(dispAll->isChecked()){
		if(dispAllPos->isChecked())
			theApp->hist[dispId]->getMean(CHANNELS+1, meansigma);
		else
			theApp->hist[dispId]->getMean(CHANNELS+2, meansigma);
		str.sprintf("%1.1f", meansigma[0]);
		meanText->setText(str);
		str.sprintf("%1.1f", meansigma[1]);
		sigmaText->setText(str);
	}
	else{
		theApp->hist[dispId]->getMean(dispMpsd->value()*8*2 + dispChan->value(), meansigma);
		str.sprintf("%1.1f", meansigma[0]);
		meanText->setText(str);
		str.sprintf("%1.1f", meansigma[1]);
		sigmaText->setText(str);
	}

	// pulser warning
	bool pulswarn = false;
	for(unsigned char c=0; c<8;c++){
		if(theApp->myMpsd[c]->isPulserOn())
			pulswarn = true;
	}

	if(pulswarn)
		str.sprintf("PULSER ON!");
	else
		str.sprintf(" ");
	pulserWarning->setText(str);
}


void mainWindow::writeRegisterSlot()
{
	bool ok;
	unsigned short id = (unsigned short) devid->value();
	unsigned short addr = module->value();
	unsigned short reg = registerSelect->value();
	unsigned short val = registerValue->text().toUInt(&ok, 0);
	cmdBuffer[0] = id;
	cmdBuffer[1] = WRITEPERIREG;
	cmdBuffer[2] = addr;
	cmdBuffer[3] = reg;
	cmdBuffer[4] = val;
	theApp->sendCommand(pBuffer);
}

void mainWindow::readRegisterSlot()
{
	bool ok;
	unsigned short id = (unsigned short) devid->value();
	unsigned short addr = module->value();
	unsigned short reg = registerSelect->value();
	cmdBuffer[0] = id;
	cmdBuffer[1] = READPERIREG;
	cmdBuffer[2] = addr;
	cmdBuffer[3] = reg;
	theApp->sendCommand(pBuffer);
}

void mainWindow::selectConfigpathSlot()
{
    QString name;
    name = QFileDialog::getExistingDirectory(theApp->getListfilepath(), this, 0,"Select Listfile Path...");
    if(!name.isEmpty())
    	theApp->setConfigfilepath(name);
    dispFiledata();
}


void mainWindow::selectHistpathSlot()
{
    QString name;
    name = QFileDialog::getExistingDirectory(theApp->getListfilepath(), this, 0,"Select Listfile Path...");
    if(!name.isEmpty())
    	theApp->setHistfilepath(name);
    dispFiledata();
}


void mainWindow::selectListpathSlot()
{
    QString name;
    name = QFileDialog::getExistingDirectory(theApp->getListfilepath(), this, 0,"Select Listfile Path...");
    if(!name.isEmpty())
    	theApp->setListfilepath(name);
    dispFiledata();
}




/*!
    \fn mainWindow::dispFiledata(void)
 */
void mainWindow::dispFiledata(void)
{
    configfilename->setText(theApp->getConfigfilename());
    if(theApp->getHistfilename().isEmpty())
    	histfilename->setText("-");
    else
    	histfilename->setText(theApp->getHistfilename());

    configfilepath->setText(theApp->getConfigfilepath());
    histfilepath->setText(theApp->getHistfilepath());
    listfilepath->setText(theApp->getListfilepath());
}


/*!
    \fn mainWindow::getDispId(void)
 */
unsigned char mainWindow::getDispId(void)
{
   return dispMcpd->value();
}


void mainWindow::writeHistSlot()
{
	theApp->writeHistograms();
}


void mainWindow::ePresetSlot(bool pr)
{
	if(pr){
		m1PresetButton->setOn(false);
		m2PresetButton->setOn(false);
		tPresetButton->setOn(false);
		evPreset->setEnabled(true);
		m1Preset->setEnabled(false);
		m2Preset->setEnabled(false);
		tPreset->setEnabled(false);
		theApp->meas->setPreset(EVCT, evPreset->value(), true);
	}
	else{
		evPreset->setEnabled(false);
		theApp->meas->setPreset(EVCT, evPreset->value(), false);
	}
}


void mainWindow::tPresetSlot(bool pr)
{
	if(pr){
		m1PresetButton->setOn(false);
		m2PresetButton->setOn(false);
		ePresetButton->setOn(false);
		tPreset->setEnabled(true);
		m1Preset->setEnabled(false);
		m2Preset->setEnabled(false);
		evPreset->setEnabled(false);
		theApp->meas->setPreset(TCT, tPreset->value(), true);
	}
	else{
		tPreset->setEnabled(false);
		theApp->meas->setPreset(TCT, tPreset->value(), false);
	}
}


void mainWindow::m1PresetSlot(bool pr)
{
	if(pr){
		ePresetButton->setOn(false);
		m2PresetButton->setOn(false);
		tPresetButton->setOn(false);
		m1Preset->setEnabled(true);
		m2Preset->setEnabled(false);
		evPreset->setEnabled(false);
		tPreset->setEnabled(false);
		theApp->meas->setPreset(M1CT, m1Preset->value(), true);
	}
	else{
		m1Preset->setEnabled(false);
		theApp->meas->setPreset(M1CT, m1Preset->value(), false);
	}
}


void mainWindow::m2PresetSlot(bool pr)
{
	if(pr){
		m1PresetButton->setOn(false);
		ePresetButton->setOn(false);
		tPresetButton->setOn(false);
		m2Preset->setEnabled(true);
		m1Preset->setEnabled(false);
		evPreset->setEnabled(false);
		tPreset->setEnabled(false);
		theApp->meas->setPreset(M2CT, m2Preset->value(), true);
	}
	else{
		m2Preset->setEnabled(false);
		theApp->meas->setPreset(M2CT, m2Preset->value(), false);
	}
}


/*!
    \fn mainWindow::updatePresets(void)
 */
void mainWindow::updatePresets(void)
{
    // presets
    evPreset->setValue(theApp->meas->getPreset(EVCT));
    tPreset->setValue(theApp->meas->getPreset(TCT));
    m1Preset->setValue(theApp->meas->getPreset(M1CT));
    m2Preset->setValue(theApp->meas->getPreset(M2CT));

    // check for master preset counter
    if(theApp->meas->isMaster(EVCT))
    	ePresetButton->setOn(true);
    else
    	ePresetButton->setOn(false);

    if(theApp->meas->isMaster(M1CT))
    	m1PresetButton->setOn(true);
    else
    	m1PresetButton->setOn(false);

    if(theApp->meas->isMaster(M2CT))
    	m2PresetButton->setOn(true);
    else
    	m2PresetButton->setOn(false);

    if(theApp->meas->isMaster(TCT))
    	tPresetButton->setOn(true);
    else
    	tPresetButton->setOn(false);


    // Caress values
    pstring.sprintf("%d", theApp->meas->getCarHeight());
    caressHeight->setText(pstring);
    pstring.sprintf("%d", theApp->meas->getCarWidth());
    caressWidth->setText(pstring);
    pstring.sprintf("%d", theApp->meas->getRun());
    caressRun->setText(pstring);
}

void mainWindow::tResetSlot()
{
	theApp->meas->clearCounter(TCT);
	update();
}

void mainWindow::eResetSlot()
{
	theApp->meas->clearCounter(EVCT);
	update();
}

void mainWindow::m1ResetSlot()
{
	theApp->meas->clearCounter(M1CT);
	update();
}

void mainWindow::m2ResetSlot()
{
	theApp->meas->clearCounter(M2CT);
	update();
}



/*!
    \fn mainWindow::updateCaress(void)
 */
void mainWindow::updateCaress(void)
{
    QString str;
	str.sprintf("%d", theApp->meas->getCarWidth());
	caressWidth->setText(str);
	str.sprintf("%d", theApp->meas->getCarHeight());
	caressHeight->setText(str);
	str.sprintf("%d", theApp->meas->getRun());
	caressRun->setText(str);
}

void mainWindow::applyMIpSlot()
{
	bool ok;
	QString stri, addr;
	unsigned char ip0, ip1, ip2, ip3;

	// get text entries
	stri = mIpAddress0->text();
	addr = stri;
	ip0 = (unsigned char) (stri.toInt(&ok));
	stri = mIpAddress1->text();
	addr.append("." + stri);
	ip1 = (unsigned char) (stri.toInt(&ok));
	stri = mIpAddress2->text();
	addr.append("." + stri);
	ip2 = (unsigned char) (stri.toInt(&ok));
	stri = mIpAddress3->text();
	addr.append("." + stri);
	ip3 = (unsigned char) (stri.toInt(&ok));

	// set address in interface table
	theApp->setMcpdAddress(mcpdId->value(), addr);
}


/*!
    \fn mainWindow::splitAddress(QString addrStr, unsigned char * addrByte)
 */
void mainWindow::splitAddress(QString addrStr, unsigned char * addrByte)
{
    QString s;

    // split into numerical address tuple
    s = addrStr.left(addrStr.find("."));
    addrByte[0] = s.toUShort();

    addrStr = addrStr.mid(addrStr.find(".")+1);
    s = addrStr.left(addrStr.find("."));
    addrByte[1] = s.toUShort();

    addrStr = addrStr.mid(addrStr.find(".")+1);
    s = addrStr.left(addrStr.find("."));
    addrByte[2] = s.toUShort();

    addrStr = addrStr.mid(addrStr.find(".")+1);
    s = addrStr.left(addrStr.find("."));
    addrByte[3] = s.toUShort();
}

void mainWindow::debugLevelSlot(int level)
{
	theApp->setDebugLevel((unsigned char)level);
}

void mainWindow::mcpdSearchSlot()
{
	qDebug("search %d", mcpdId->value());
	theApp->searchMcpd(mcpdId->value());
}


void mainWindow::pulsertestSlot(bool on)
{
	if(on){
		theApp->startPulsertest();
	}
	else{
		theApp->stopPulsertest();
	}
}


/*!
    \fn mainWindow::setDispMode(bool mult, unsigned char num)
 */
void mainWindow::setDispMode(bool mult, unsigned char num)
{
    multi = mult;
    dispNum = num;
	// adjust height and offset:
    if(multi){
    	histHeight = 60;
    	yStart = (dispNum+1) * 60;
    }
    else{
    	histHeight = 480;
    	yStart = 480;
    }
}

void mainWindow::assignCounterSlot()
{
	unsigned char cpu1, cpu2, counter1, counter2;
	cpu1 = (unsigned char) cpuMon1box->value();
	cpu2 = (unsigned char) cpuMon2box->value();
	counter1 = (unsigned char) counterMon1box->value();
	counter2 = (unsigned char) counterMon2box->value();
	theApp->meas->assignCounter(0, cpu1, counter1);
	theApp->meas->assignCounter(1, cpu2, counter2);
}

/*!
    \fn mainWindow::dispCounterAssign(void)
 */
void mainWindow::dispCounterAssign(void)
{
    unsigned char ca[4];
    theApp->meas->getCounterAssign(ca);
    cpuMon1box->setValue(ca[0]);
    cpuMon2box->setValue(ca[2]);
    counterMon1box->setValue(ca[1]);
    counterMon2box->setValue(ca[3]);
}



#include "mainwindow.moc"

