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


#include <qmainwindow.h>
//#include <klocale.h>

#include "mesydaq2.h"

#include "mesydaq2.h"
#include "mainwindow.h"
#include "mdefines.h"
#include "histogram.h"
#include "datacruncher.h"
#include "mpsd8.h"
#include "mcpd8.h"
#include "measurement.h"
#include "controlinterface.h"

#include <qmessagebox.h>
#include <qlineedit.h>
#include <qspinbox.h>
#include <qcheckbox.h>
#include <qfiledialog.h>
#include <qdatetime.h>
#include <qradiobutton.h>
#include <qdatetime.h>
#include <qpushbutton.h>
#include <qdir.h>
#include <qtextedit.h>
#include <qcombobox.h>

#include <time.h>
#include <net/if.h>
#include <sys/ioctl.h>
#include <sys/socket.h>
//#include <netinet/in.h>
//#include <sys/types.h>
#include <arpa/inet.h>


mesydaq2::mesydaq2()
    : QMainWindow( 0, "mesydaq2, by mesytec" )
{
    mainWin = new mainWindow(this);
    setCentralWidget(mainWin);
	mainWin->resize(1280, 980);
	dc = new dataCruncher(this);
	meas = new measurement(this);
	cInt = new controlInterface(this);
	progVersion.sprintf("mesydaq 2.8.3    29.09.2009");
	mainWin->versionLabel->setText(progVersion);
	configfilename.sprintf("mesycfg.mcfg");
}

mesydaq2::~mesydaq2()
{

	dispTimer->stop();
	delete dispTimer;
	theTimer->stop();
	delete theTimer;
	commTimer->stop();
	delete commTimer;

	for(unsigned char c = 0; c < numIf; c++)
		delete netDev[c];
	delete dc;
	delete meas;
	delete cInt;
	for(unsigned int i = 0; i < MCPDS; i++){
		for(unsigned int j = 0; j < 8; j++)
			delete myMpsd[j+8*i];
		delete hist[i];
		delete myMcpd[i];
	}
	delete mainWin;
}



/*!
    \fn mesydaq2::initNetwork(void)
 */
void mesydaq2::initNetwork(void)
{
	// check for usable interfaces
	findInterfaces();
	qDebug("found %d usable interfaces", numIf);
	for(unsigned char c =0; c < numIf; c++){
		netDev[c] = new networkDevice(this);
		netDev[c]->initSockets(&ifrs[c], c);
	}
	cmdBuf = netDev[0]->getSbufpointer();
	recBuf = netDev[0]->getRbufpointer();
	pDataBuf = (PDATA_PACKET) recBuf;
	connect(netDev[0], SIGNAL(bufferReceived(void)), this, SLOT(readBuf(void)));
}


/*!
    \fn mesydaq2::setSocket(unsigned char netDevice)
 */
int mesydaq2::setSocket(unsigned char netDevice)
{
	return netDevice;
}

/*!
    \fn mesydaq2::sendCommand(unsigned int cmd)
 */
// is the central command interface for mesydaq
// analyzes the command buffers, takes appropriate action
int mesydaq2::sendCommand(unsigned short * buffer)
{
	unsigned short cmd, buflen, id;

	// general buffer preparations:
	id = buffer[0];
	// get appropriate network device:

	cmd = buffer[1];
	cmdBuf->bufferType = BUFTYPE;
	cmdBuf->headerLength = CMDHEADLEN;
	cmdBuf->cmd = cmd;
	cmdBuf->bufferNumber = txCmdBufNum;
	cmdBuf->deviceId = id;

//	qDebug("processing cmd: %d, id: %d", cmd, id);

	// don't send commands to offline MCPDs if it is not GETVER, STOP!
	if((!myMcpd[id]->isOnline()) && cmd != GETVER && cmd != STOP)
		return -1;

	// now do some command specific things:
	switch(cmd){

		case RESET:
			buflen = 2;
		break;

		case START:
			buflen = 2;
			// start master
			if(buffer[2] == 1){
				if(!startDaq()){
					mainWin->startStopButton->setText("Start");
					mainWin->startStopButton->toggle();
					return 0;
				}
			}
		break;

		case STOP:
			buflen = 2;
			if(buffer[2] == 1)
				stopDaq();
		break;

		case CONTINUE:
			buflen = 2;
		break;

		case SETID:
			buflen = 3;
			cmdBuf->data[0] = buffer[2];
			myMcpd[id]->setId((unsigned char)id);
		break;

		case SETPROTOCOL:
			buflen = 16;
			for(int i=0; i<14; i++)
				cmdBuf->data[i] = buffer[i+2];
			// set data ip addr to this pc?
			if(cmdBuf->data[6] == 0 && cmdBuf->data[7] == 0){
				;
			}
			// set cmd ip addr to this pc?
			if(cmdBuf->data[12] == 0 && cmdBuf->data[13] == 0){
				;
			}
			// set cmd address
			myMcpd[id]->setProtocol(&cmdBuf->data[0]);
		break;

		case SETTIMING:
			buflen = 4;
			cmdBuf->data[0] = buffer[2];
			cmdBuf->data[1] = buffer[3];
		break;

		case SETCLOCK:
			buflen = 5;
			cmdBuf->data[0] = buffer[2];
			cmdBuf->data[1] = buffer[3];
			cmdBuf->data[2] = buffer[4];
		break;

		case SETRUNID:
			// run id in buffer 3
			buflen = 3;
			cmdBuf->data[0] = buffer[2];
		break;

		case SETCELL:
			buflen = 5;
			cmdBuf->data[0] = buffer[2];
			cmdBuf->data[1] = buffer[3];
			cmdBuf->data[2] = buffer[4];
			myMcpd[id]->setCounterCell(&cmdBuf->data[0]);
		break;

		case SETAUXTIMER:
			buflen = 4;
			cmdBuf->data[0] = buffer[2];
			cmdBuf->data[1] = buffer[3];
			myMcpd[id]->setAuxTimer(buffer[2], buffer[3]);
			break;

		case SETPARAM:
			buflen = 4;
			cmdBuf->data[0] = buffer[2];
			cmdBuf->data[1] = buffer[3];
			myMcpd[id]->setParamSource(buffer[2], buffer[3]);
			break;

		case SETGAIN:
			buflen = 5;
			cmdBuf->data[0] = buffer[2];
			cmdBuf->data[1] = buffer[3];
			cmdBuf->data[2] = buffer[4];
			myMpsd[8*id+buffer[2]]->setGain((unsigned char)buffer[3],
											(unsigned char)buffer[4], 1);
			break;

		case SETTHRESH:
			buflen = 4;
			cmdBuf->data[0] = buffer[2];
			cmdBuf->data[1] = buffer[3];
			myMpsd[8*id+buffer[2]]->setThreshpoti((unsigned char)buffer[3], 1);
			break;

		case SETPULSER:
			buflen = 6;
			cmdBuf->data[0] = buffer[2];
			cmdBuf->data[1] = buffer[3];
			cmdBuf->data[2] = buffer[4];
			myMpsd[8*id+buffer[2]]->setPulser(buffer[3], buffer[5], buffer[4], buffer[6], 1);
			cmdBuf->data[3] = myMpsd[8*id+buffer[2]]->getPulspoti(1);
			cmdBuf->data[4] = buffer[6];
			break;

		case SETMODE:
			buflen = 4;
			cmdBuf->data[0] = buffer[2];
			cmdBuf->data[1] = buffer[3];
			if(buffer[3] == 1)
				myMpsd[8*id+buffer[2]]->setMode(true);
			else
				myMpsd[8*id+buffer[2]]->setMode(false);
			break;

		case QUIET:
			buflen = 3;
			cmdBuf->data[0] = buffer[2];
			myMcpd[id]->setStream(buffer[2]);
			break;

		case READID:
			buflen = 3;
			cmdBuf->data[0] = buffer[2];
			break;

		case GETVER:
			buflen = 3;
			cmdBuf->data[0] = buffer[2];
			break;

		case READPERIREG:
			buflen = 4;
			cmdBuf->data[0] = buffer[2];
			cmdBuf->data[1] = buffer[3];
			break;

		case WRITEPERIREG:
			buflen = 5;
			cmdBuf->data[0] = buffer[2];
			cmdBuf->data[1] = buffer[3];
			cmdBuf->data[2] = buffer[4];
			myMpsd[8*id+buffer[2]]->setInternalreg(buffer[3], buffer[4], 1);
			break;

		case WRITEREGISTER:
			// 1 word length (buffer[2]) + 2 words per register (+ 2 overhead)
			buflen = buffer[2] * 2 + 3;
			cmdBuf->data[0] = buffer[2];
			for(unsigned char c = 0; c < buffer[2]*2; c+=2){
				cmdBuf->data[1+c] = buffer[3+c];
				cmdBuf->data[2+c] = buffer[4+c];
			}
			break;
	}

	cmdBuf->bufferLength = CMDHEADLEN + buflen;
	cmdBuf->data[buflen] = 0xFFFF;
	cmdBuf->headerChksum = 0;
	cmdBuf->headerChksum = calcChksum(cmdBuf);

//	for(unsigned char d = 0; d < buflen; d++)
//		qDebug("%d: %d", d, cmdBuf->data[d]);

	unsigned char retry;
	unsigned int timeoutLength;
	if(cmd == START || cmd == STOP){
		retry = 10;
		timeoutLength = 50;
	}
	else{
		retry = 2;
		timeoutLength = 1000;
	}

	while(retry){
		if(netDev[0]->sendBuffer(id, cmdBuf)){
			pstring.sprintf("sent cmd: %d to id: %d", cmd, id);
			protocol(pstring, 3);
			cmdTxd ++;
			txCmdBufNum++;
			cmdActive = true;
			myMcpd[id]->communicate(true);
			commId = id;
			dispatch[2] = 0;
//			commTimer->start(timeoutLength, true);
			// wait for answer
			while(myMcpd[commId]->isBusy())
				qApp->processEvents();
			// check if answer or timeout?
			if(myMcpd[id]->isResponding()){
				pstring.sprintf("received cmd answer: %d from id: %d, retry %d", cmd, id, retry);
				protocol(pstring, 3);
				break;
			}
			else{
				pstring.sprintf("no cmd answer: %d from id: %d", cmd, id);
				protocol(pstring, 2);
				retry--;
			}
		}
	}
	return 1;
}


/*!
    \fn mesydaq2::calcChksm(unsigned int * buffer, unsigned int len)
 */
unsigned short mesydaq2::calcChksum(PMDP_PACKET buffer)
{
	unsigned short chksum = 0;
	unsigned short * b = (unsigned short *)buffer;
	for (unsigned int i = 0; i < buffer->bufferLength; i++)
		chksum ^= b[i];
	return chksum;
}

/*!
    \fn mesydaq2::initValues()
 */
void mesydaq2::initValues()
{
	txCmdBufNum = 0;
	rxCmdBufNum = 0;
	dataBufNum = 0;
	dataRxd = 0;
	cmdRxd = 0;
	cmdTxd = 0;
	cmdActive = false;
	acquireListfile = false;
	listIds = false;
	listfilename.sprintf("");
	daq = IDLE;
	statuscounter[0] = 0;
	statuscounter[1] = 0;
	sep0 = 0x0000;
	sep5 = 0x5555;
	sepA = 0xAAAA;
	sepF = 0xFFFF;
	listPath.sprintf("/home");
	histPath.sprintf("/home");
	configPath.sprintf("/home");
	debugLevel = 1;
	ovwList = false;
	timingwidth = 1;
	numIf = 0;
}


/*!
    \fn mesydaq2::writeRegister(unsigned int id, unsigned int addr, unsigned int val)
 */
int mesydaq2::writeRegister(unsigned int id, unsigned int addr, unsigned int val)
{
	cmdBuf->data[0] = (unsigned short) id;
	for(unsigned int i = 1; i < 2*id+1; i+=2){
		cmdBuf->data[i] = (unsigned short) addr;
		cmdBuf->data[i+1] = (unsigned short) val;
	}
//	sendCommand(WRITEREGISTER, 2 * id + 1);
//	sendCommand(SETGAIN, 2 * id + 1);

	return 1;
}


/*!
    \fn mesydaq2::readBuf(void)
 */
void mesydaq2::readBuf(void)
{
	// cancel pending timouts
	unsigned char id = recBuf->deviceId;
//	dispatch[1] = 0;
//	qDebug("Slot read called!");
//qDebug("Length: %d, Type: %x, HLen: %d, BufNum: %x, id: %d, status: %x", recBuf->bufferLength, recBuf->bufferType, recBuf->headerLength, recBuf->bufferNumber, recBuf->deviceId, recBuf->deviceStatus);
	unsigned long tim;
	tim = 0;
	tim += recBuf->time[2];
	tim *= 0x10000;
	tim += recBuf->time[1];
	tim *= 0x10000;
	tim += recBuf->time[0];
//	unsigned long delta = tim - headertime;
	headertime = tim;
	timeMsecs = headertime / 10000;
	meas->setCurrentTime(timeMsecs);

	ht[0] = recBuf->time[0];
	ht[1] = recBuf->time[1];
	ht[2] = recBuf->time[2];

	status = recBuf->deviceStatus;
	if(recBuf->bufferType & 0x8000){
		cmdActive = false;
		cmdRxd++;
		myMcpd[recBuf->deviceId]->answered();
//		commTimer->stop();
		dc->analyzeCmd((PMDP_PACKET)pDataBuf, daq, hist[id]);
	}
	else{
		if(daq == RUNNING){
			unsigned short diff = pDataBuf->bufferNumber - lastBufnum;
			if(diff > 1){
				if(pDataBuf->bufferNumber != 0){
					lostBuffers++;
//					qDebug("Lost %d Buffers: current: %d, last: %d. Total: %d of %d", diff-1, pDataBuf->bufferNumber, lastBufnum, //lostBuffers, dataRxd);
				}
			}
			lastBufnum = pDataBuf->bufferNumber;
			if(acquireListfile && listfileOpen){
				if(meas->remoteStart()){
					if(bytesWritten + pDataBuf->bufferLength > cInt->caressMaxfilesize){
						changeCaressListfile();
						bytesWritten = cInt->caressHlen;
					}
				}
				unsigned short * pD;
				pD = (unsigned short *) &pDataBuf->bufferLength;
				unsigned int i;
				for(i = 0; i < pDataBuf->bufferLength; i++){
					datStream << pD[i];
	//				qDebug("%x", pD[i]);
				}
				writeBlockSeparator();
				bytesWritten = bytesWritten + 2 * pDataBuf->bufferLength + 8;
	//			qDebug("------------------");
			}
			dataRxd++;
			dc->analyzeBuffer(pDataBuf, daq, hist[id]);
		}
	}
}







/*!
    \fn mesydaq2::acqListfile(bool yesno)
 */
void mesydaq2::acqListfile(bool yesno)
{
    acquireListfile = yesno;
    if(acquireListfile){
    	protocol("Listfile recording on", 2);
    	if(!mainWin->acqListfile->isChecked())
    		mainWin->acqListfile->setChecked(true);
    }
    else{
    	protocol("Listfile recording off", 2);
    	if(mainWin->acqListfile->isChecked())
    		mainWin->acqListfile->setChecked(false);
    }
}


/*!
    \fn mesydaq2::setListfilename(QString name)
 */
void mesydaq2::setListfilename(QString name)
{
    listfilename = name;
}


/*!
    \fn mesydaq2::startedDaq(void)
 */
void mesydaq2::startedDaq(void)
{
    meas->start(timeMsecs);
    // maybe some remote control is interested?
   	cInt->completeCar();
    daq = RUNNING;
    mainWin->daqStatusLine->setText("RUNNING");
	protocol("daq started",1);
}


/*!
    \fn mesydaq2::stoppedDaq(void)
 */
void mesydaq2::stoppedDaq(void)
{
	meas->stop(timeMsecs);
    // maybe some remote control is interested?
   	cInt->completeCar();

	if(acquireListfile){
		if(datfile.isOpen()){
			writeClosingSignature();
			datfile.close();
			listfileOpen = false;
		}
	}
    daq = IDLE;
    mainWin->daqStatusLine->setText("IDLE");
    protocol("daq stopped",1);
}

/*!
    \fn mesydaq2::startDaq(void)
 */
bool mesydaq2::startDaq(void)
{
	lostBuffers = 0;
	// check for listfile
	if(acquireListfile){
		if(meas->remoteStart()){
			openCaressListfile();
			bytesWritten = cInt->caressHlen;
		}
		else{
			if(mainWin->listFilename->text().isEmpty()){
				if(listfilename.isEmpty()){
					if(!getListfilename()){
						ovwList = false;
						return false;
					}
				}
				else{
					listfilename = mainWin->listFilename->text();
				}
			}
			else
				listfilename = mainWin->listFilename->text();
			// o.k. - now try to use it:
			datfile.setName(listfilename);
			// now check if existing:
			// listfile already existing? Warning!
			if(QFile::exists(datfile.name())){
				qDebug("datfile exists");
				if(!ovwList){
					qDebug("no overwrite");
					int answer = QMessageBox::warning(
							this, "Listfile Exists -- Overwrite File",
							QString("Overwrite existing listfile?"),
							"&Yes", "&No", QString::null, 1, 1 );
					qDebug("answer: %d", answer);
					if(answer == 1){
						ovwList = false;
						return false;
					}
				}
			}
			// reset overwrite o.k. flag
			ovwList = false;
			// o.k. - successfully retrieved a listfile
			if(datfile.open(IO_WriteOnly)){
				listfileOpen = true;
				textStream.setDevice(&datfile);
				datStream.setDevice(&datfile);
				writeListfileHeader();
				writeHeaderSeparator();
  			}
  			else{
  				qDebug("error opening listmode file");
  			}
  		}
  	}
  	daq = STARTED;
    mainWin->daqStatusLine->setText("STARTED");
	protocol("daq start",1);
	return true;
}


/*!
    \fn mesydaq2::stopDaq(void)
 */
void mesydaq2::stopDaq(void)
{
    daq = STOPPED;
    mainWin->daqStatusLine->setText("STOPPED");
	protocol("daq stop", 1);}


/*!
    \fn mesydaq2::protocol(QString str, unsigned char level)
 */
void mesydaq2::protocol(QString str, unsigned char level)
{
    QDateTime datetime;
    QString datestring = datetime.currentDateTime().toString("hh:mm:ss.zzz");
    str.prepend(" - ");
    str.prepend(datestring);
    if(level <= debugLevel){
    	qDebug(str);
    	mainWin->protocolEdit->append(str);
    }
}

/*!
    \fn mesydaq2::protocolCaress(QString str, unsigned char level)
 */
void mesydaq2::protocolCaress(QString str, unsigned char level)
{
    QDateTime datetime;
    QString datestring = datetime.currentDateTime().toString("hh:mm:ss.zzz");
    str.prepend(" - ");
    str.prepend(datestring);
    if(level <= debugLevel){
    	qDebug(str);
    	mainWin->caressEdit->append(str);
    }
}

/*!
    \fn mesydaq2::initDevices(void)
 */
void mesydaq2::initDevices(void)
{
	unsigned char i;
    for(i=0; i<MCPDS; i++){
		myMcpd[i] = new mcpd8(this);
		myMcpd[i]->setId(i);
		hist[i] = new histogram(this);
		hist[i]->setId(i);
	}
	// common histogram for all MCPDs
	hist[MCPDS] = new histogram(this);
	hist[MCPDS]->setId(MCPDS);

    for(i=0; i<8*MCPDS; i++){
		myMpsd[i] = new mpsd8(this);
	}
}


/*!
    \fn mesydaq2::initTimers(void)
 */
void mesydaq2::initTimers(void)
{
    // display refresh timer
    dispTimer = new QTimer(this);
    connect(dispTimer, SIGNAL(timeout()), this, SLOT(dispTime()));
//    dispTimer->start(1000, false);

	// central dispatch timer
    theTimer = new QTimer(this);
    connect(theTimer, SIGNAL(timeout()), this, SLOT(centralDispatch()));
    theTimer->start(10, false);
    for(unsigned char c = 0; c < 10; c++)
    	dispatch[c] = 0;

	// communication timeout timer
    commTimer = new QTimer(this);
    connect(commTimer, SIGNAL(timeout()), this, SLOT(commTimeout()));
    commId = 99;

    // pulser test timer
    testTimer = new QTimer(this);
    connect(testTimer, SIGNAL(timeout()), this, SLOT(pulserTest()));

	testRunning = false;
}


/*!
    \fn mesydaq2::dispTime()
 */
void mesydaq2::dispTime()
{
	draw();
	mainWin->update();
}


/*!
    \fn mesydaq2::clearAllHist(void)
 */
void mesydaq2::clearAllHist(void)
{
	for(unsigned char c = 0; c <= MCPDS; c++)
		hist[c]->clearAllHist();
	dc->reset();
}


/*!
    \fn mesydaq2::clearChanHist(unsigned long chan)
 */
void mesydaq2::clearChanHist(unsigned long chan)
{
    hist[mainWin->getDispId()]->clearHist(chan);
}


/*!
    \fn mesydaq2::writeListfileHeader(void)
 */
void mesydaq2::writeListfileHeader(void)
{
	QString str;
/*	if(mainWin->newHeader->isChecked()){
		buildListfileheader();
		textStream << listfileHeader;
	}
	else{
*/		str. sprintf("mesytec psd listmode data\n");
		textStream << str;
		str. sprintf("header length: %d lines \n", 2);
		textStream << str;
//	}
}


/*!
    \fn mesydaq2::writeHeaderSeparator(void)
 */
void mesydaq2::writeHeaderSeparator(void)
{
	datStream << sep0 << sep5 << sepA << sepF;
}


/*!
    \fn mesydaq2::writeBlockSeparator(void)
 */
void mesydaq2::writeBlockSeparator(void)
{
	datStream << sep0 << sepF << sep5 << sepA;
}


/*!
    \fn mesydaq2::writeClosingSignature(void)
 */
void mesydaq2::writeClosingSignature(void)
{
	datStream << sepF << sepA << sep5 << sep0;
}


/*!
    \fn mesydaq2::readListfile(QString readfilename)
 */
void mesydaq2::readListfile(QString readfilename)
{
	QDataStream datStream;
	QTextStream textStream;
	QFile datfile;
	QString str;
	bool ok = false;
	unsigned short sep1, sep2, sep3, sep4;

	datfile.setName(readfilename);
	datfile.open(IO_ReadOnly);
	datStream.setDevice(&datfile);
	textStream.setDevice(&datfile);

	unsigned int blocks = 0;
	unsigned int bcount = 0;
//	unsigned int events = 0;

	qDebug("readListfile");
	str = textStream.readLine();
	qDebug(str);
	str = textStream.readLine();
	qDebug(str);
	datStream >> sep1 >> sep2 >> sep3 >> sep4;
	if((sep1 == sep0) && (sep2 == sep5) && (sep3 == sepA) && (sep4 == sepF)){
		ok = true;
	}
	while(ok){
		datStream >> sep1 >> sep2 >> sep3 >> sep4;
		// check for closing signature:
		if((sep1 == sepF) && (sep2 == sepA) && (sep3 == sep5) && (sep4 == sep0)){
			qDebug("EOF reached after %d buffers", blocks);
			break;
		}
		pDataBuf->bufferLength = sep1;
		pDataBuf->bufferType = sep2;
		pDataBuf->headerLength = sep3;
		pDataBuf->bufferNumber = sep4;
		if(pDataBuf->bufferLength > 729){
			qDebug("erroneous length: %d - aborting", pDataBuf->bufferLength);
			datStream >> sep1 >> sep2 >> sep3 >> sep4;
			qDebug("Separator: %x %x %x %x", sep1, sep2, sep3, sep4);
			break;
		}
		unsigned short * pD;
		pD = (unsigned short *) &pDataBuf->bufferLength;
		for(int i = 4; i < pDataBuf->bufferLength; i++)
			datStream >> pD[i];
		// hand over data buffer for processing
		dc->analyzeBuffer(pDataBuf, daq, hist[pDataBuf->deviceId]);
		// increment local counters
		blocks++;
		bcount++;
		//check for next separator:
		datStream >> sep1 >> sep2 >> sep3 >> sep4;
//		qDebug("Separator: %x %x %x %x", sep1, sep2, sep3, sep4);
		if((sep1 == sep0) && (sep2 == sepF) && (sep3 == sep5) && (sep4 == sepA)){
			ok = true;
		}
		else{
			qDebug("File structure error - read aborted after %d buffers", blocks);
			ok = false;
		}
		if(bcount == 1000){
			bcount = 0;
			draw();
//			kapp->processEvents();
		}
	}
	datfile.close();
	draw();
}


/*!
    \fn mesydaq2::draw(void)
 */
void mesydaq2::draw(void)
{
	unsigned char id = mainWin->getDispId();
	unsigned int chan = 0;
	// eight-fold display?
	if(mainWin->eightFoldBox->isChecked()){
		// call draw functions eight times
		for(unsigned char c = 0; c < 8; c++){
			// amplitude or position?
			if(mainWin->dispAllPos->isChecked())
				chan = mainWin->dispMpsd->value() * 16 + c;
			else
				chan = mainWin->dispMpsd->value() * 16 + c + 8;
			hist[id]->copyLine(chan, dispBuf);
			mainWin->setData(dispBuf, 960, hist[id]->max(chan));
			mainWin->setDispMode(true, c);
			mainWin->draw();
		}
	}
	else{
		if(mainWin->dispAll->isChecked()){
			if(mainWin->dispAllPos->isChecked()){
				chan = CHANNELS-2;
				hist[MCPDS]->copyLine(chan, dispBuf);
				mainWin->setData(dispBuf, 960, hist[MCPDS]->max(CHANNELS-2));
			}
			else{
				chan = CHANNELS-1;
				hist[MCPDS]->copyLine(chan, dispBuf);
				mainWin->setData(dispBuf, 960, hist[MCPDS]->max(CHANNELS-1));
			}
		}
		else{
			unsigned int chan = mainWin->dispMpsd->value() * 16;
			chan = mainWin->dispChan->value();
			hist[id]->copyLine(chan, dispBuf);
			mainWin->setData(dispBuf, 960, hist[id]->max(chan));
		}
		mainWin->setDispMode(false, chan);
		mainWin->draw();
	}
}


/*!
    \fn mesydaq2::scanPeriph(unsigned short id)
 */
void mesydaq2::scanPeriph(unsigned short id)
{
	commandBuffer[0] = id;
	commandBuffer[1] = READID;
	commandBuffer[2] = 2;
	sendCommand(commandBuffer);
}


/*!
    \fn mesydaq2::dispMpsd(void)
 */
void mesydaq2::dispMpsd(void)
{
    mainWin->displayMpsdSlot();
}


/*!
    \fn mesydaq2::initHardware(void)
 */
void mesydaq2::initHardware(void)
{
	// starts the init procedure:
	// 1) load config file
	// 2) check and initialize all configured and conneceted MCPDs
	// 2) check and configure alle all connected MPSDs

	//set init values:
	unsigned char c = 0, d = 0, mpsdid;
	pstring.sprintf("initializing hardware");
	protocol(pstring, 1);

	// scan connected MCPDs
	for(c = 0; c < MCPDS; c++){
		if(confMcpd[c]){
			pstring.sprintf("searching for mcpd %d", c);
			protocol(pstring, 2);
			getMcpdVersion(c);
			if(myMcpd[c]->isOnline()){
				initMcpd(c);
				listIds = true;
				scanPeriph(c);
			}
		}
	}

	unsigned char p = 0;
	for(c = 0; c < MCPDS*8; c++)
		if(myMpsd[c]->getMpsdId())
			p++;

	pstring.sprintf("%d mpsd-8 found during setup", p);
	protocol(pstring, 1);

	for(c=0; c<MCPDS; c++){
		if(confMcpd[c] && myMcpd[c]->isOnline()){
			pstring.sprintf("initialize MPSDs on mcpd #%d",c);
			protocol(pstring, 2);
			for(d=0; d<8; d++){
				mpsdid = myMpsd[c*8+d]->getMpsdId();
				if(mpsdid > 0){
					initMpsd(c, d);
				}
			}
		}
		else{
			pstring.sprintf("MCPD %d not configured - no setup", c);
			protocol(pstring, 2);
		}
	}
}


/*!
    \fn mesydaq2::saveSetup(void)
 */
bool mesydaq2::saveSetup(void)
{
  QString name;
  unsigned char cnt[4];
  name = QFileDialog::getSaveFileName(configPath, "mesydaq config files (*.mcfg);;all files (*.*)", this, "Load Config File...");
  if(name.isEmpty())
  	return false;

  configfilename = name;
  int i = configfilename.find(".mcfg");
  if(i == -1)
    configfilename.append(".mcfg");

	QDateTime dateTime;
	dateTime=QDateTime::currentDateTime();

	QFile f(configfilename);
	if ( f.open(IO_WriteOnly) ) {    // file opened successfully
		QTextStream t( &f );        // use a text stream
		QString s;
		// Title
		t << "mesydaq configuration file   ";
		t << dateTime.toString("dd.MM.yy") << " " << dateTime.toString("hh.mm.ss");
		t << '\r' << '\n';
		t << '\r' << '\n';
		t << "[MESYDAQ]";
		t << '\r' << '\n';
		// default paths
		t << "configPath =";
		t << configPath;
		t << '\r' << '\n';
		t << "histogramPath =";
		t << histPath;
		t << '\r' << '\n';
		t << "listfilePath =";
		t << listPath;
		t << '\r' << '\n';
		t << "debugLevel =";
		t << debugLevel;
		t << '\r' << '\n';
		meas->serialize(&f);
		t << '\r' << '\n';

		for(int i=0; i<MCPDS; i++){
	    	myMcpd[i]->serialize(&f);
	    }
		for(int i=0; i<8*MCPDS; i++)
			if(myMpsd[i]->getMpsdId())
				myMpsd[i]->serialize(&f);
  }
  f.close();
  return true;
}



/*!
    \fn mesydaq2::loadSetup(bool ask)
 */
bool mesydaq2::loadSetup(bool ask)
{
  QString name;
//  qDebug("loading setup, current dir"+QDir::currentDirPath());
  if(ask)
    name = QFileDialog::getOpenFileName(configPath, "mesydaq config files (*.mcfg);;all files (*.*)", this, "Load Config File...");
  else{
    name = configfilename; //QDir::homeDirPath() + "/mesydaq2/mesycfg.mcfg";
  }
  if(name.isEmpty())
  	return false;

  configfilename = name;

  QFile f(configfilename);

  QString s, str, s2;

  unsigned char section = 0;
  unsigned char modaddr, mcpd, id, chan, gain, thresh;
  unsigned short cells[3];

  // clear configured MCPD list:
  for(unsigned char c = 0; c < MCPDS; c++)
  	confMcpd[c] = false;

  if ( f.open(IO_ReadOnly) ) {    // file opened successfully
    if(!ask)
      pstring.sprintf("Reading standard configfile " + configfilename);
    else{
      pstring.sprintf("Reading configfile " + configfilename);
    }
    protocol(pstring, 1);

    QTextStream t( &f );        // use a text stream

    s = t.readLine();
    while(!s.isNull()){
		// comment line
		if((s.find("//") >= 0 && s.find("//") < 10) ||
		   (s.find(";") >= 0 && s.find(";") < 10))
		   	;
		else{
		// mesydaq
		if(s.find("[MESYDAQ]") >= 0){
			section = 1;
		}
		// MCPD-8
		if(s.find("[MCPD-8]") >= 0){
			section = 2;
		}
		// MPSD-8
		if(s.find("[MPSD-8]") >= 0){
			section = 3;
		}

		// mesydaq properties
		if(section == 1 && s.contains("configPath =")){
			s = s.mid(s.find("=")+1);
			s.stripWhiteSpace();
			configPath = s;
		}
		if(section == 1 && s.contains("histogramPath =")){
			s = s.mid(s.find("=")+1);
			s.stripWhiteSpace();
			histPath = s;
		}
		if(section == 1 && s.contains("listfilePath =")){
			s = s.mid(s.find("=")+1);
			s.stripWhiteSpace();
			listPath = s;
		}
		if(section == 1 && s.contains("debugLevel =")){
			s = s.mid(s.find("=")+1);
			s.stripWhiteSpace();
			if(s.contains("All") || s.contains("3"))
				debugLevel = 3;
			if(s.contains("Details") || s.contains("2"))
				debugLevel = 2;
			if(s.contains("Standard") || s.contains("1"))
				debugLevel = 1;
			if(s.contains("Error") || s.contains("0"))
				debugLevel = 0;
			mainWin->debugLevelBox->setCurrentItem(debugLevel);
		}
		// counter assignment
		if(section == 1 && s.contains("monitor1")){
			s = s.mid(s.find("=")+1);
			while(s.find(" ") == 0)
				s = s.mid(1);
			s2 = s.left(s.find(" "));
			cells[0] = s2.toUShort();
			s2 = s.mid(s.find(" "));
			while(s2.find(" ") == 0)
				s2 = s2.mid(1);
			cells[1] = s2.toUShort();
			meas->assignCounter(0, cells[0], cells[1]);
		}

		if(section == 1 && s.contains("monitor2")){
			s = s.mid(s.find("=")+1);
			while(s.find(" ") == 0)
				s = s.mid(1);
			s2 = s.left(s.find(" "));
			cells[0] = s2.toUShort();
			s2 = s.mid(s.find(" "));
			while(s2.find(" ") == 0)
				s2 = s2.mid(1);
			cells[1] = s2.toUShort();
			meas->assignCounter(1, cells[0], cells[1]);
		}


		// MCPD-8 properties
		if(section == 2 && s.contains("id =")){
			s = s.mid(s.find("=")+1);
			s.stripWhiteSpace();
			modaddr = s.toUShort();
			confMcpd[modaddr] = true;
			myMcpd[modaddr]->setConfigured(true);
			pstring.sprintf("found config data for mcpd #%d", modaddr);
			protocol(pstring, 2);
		}
		if(section == 2 && s.contains("ipAddress =")){
			s2 = s.mid(s.find("ipAddress =")+12);
			s2.stripWhiteSpace();
//			qDebug("ipAddress"+s2);
//			qDebug("modaddr: %d", modaddr);
			myMcpd[modaddr]->setIpAddress(s2);
			netDev[0]->setAddress(modaddr, s2);
		}
		if(section == 2 && s.contains("udpPort =")){
		}
		if(section == 2 && s.contains("master =")){
			if(s.contains("1"))
				myMcpd[modaddr]->setMaster(true);
			else
				myMcpd[modaddr]->setMaster(false);
		}
		if(section == 2 && s.contains("terminate =")){
			if(s.contains("1"))
				myMcpd[modaddr]->setTermination(true);
			else
				myMcpd[modaddr]->setTermination(false);
		}

		if(section == 2 && s.contains("counterCell")){
			s2 = s.mid(s.find("counterCell")+11, 1);
			cells[0] = s2.toUShort();
			s = s.mid(s.find("=")+1);
			while(s.find(" ") == 0)
				s = s.mid(1);
			s2 = s.left(s.find(" "));
			cells[1] = s2.toUShort();
			s2 = s.mid(s.find(" "));
			while(s2.find(" ") == 0)
				s2 = s2.mid(1);
			cells[2] = s2.toUShort();
			myMcpd[modaddr]->setCounterCell(cells);
		}
		if(section == 2 && s.contains("auxTimer")){
			s2 = s.mid(s.find("auxTimer")+8, 1);
			chan = s2.toUShort();
			s = s.mid(s.find("=")+1);
			while(s.find(" ") == 0)
				s = s.mid(1);
			gain = s.toUShort();
			myMcpd[modaddr]->setAuxTimer((unsigned short)chan, (unsigned short)gain);
		}
		if(section == 2 && s.contains("paramSource")){
			s2 = s.mid(s.find("paramSource")+11, 1);
			chan = s2.toUShort();
			s = s.mid(s.find("=")+1);
			while(s.find(" ") == 0)
				s = s.mid(1);
			gain = s.toUShort();
			myMcpd[modaddr]->setParamSource((unsigned short)chan, (unsigned short)gain);
		}

		// MPSD-8 properties
		if(section == 3 && s.contains("id =")){
			s = s.mid(s.find("=")+1);
			s.stripWhiteSpace();
			modaddr = s.toUShort();
			mcpd = (unsigned char)(modaddr / 8);
			id = (unsigned char)(modaddr - mcpd*8);
			pstring.sprintf("found config data for mpsd #%d", modaddr);
			protocol(pstring, 2);
		}
		if(section == 3 && s.contains("gain")){
			s2 = s.mid(s.find("gain")+4, 1);
			chan = s2.toUShort();
			s = s.mid(s.find("=")+1);
			s.stripWhiteSpace();
			gain = s.toUShort();
//			qDebug("modaddr: %d, chan: %d, gain: %d", modaddr, chan, gain);
//			if(myMpsd[modaddr]->getMpsdId() > 0)
			myMpsd[modaddr]->setGain(chan, gain, 1);
//			else
		}
		if(section == 3 && s.contains("threshold =")){
			s2 = s.mid(s.find("threshold =")+11);
			s2.stripWhiteSpace();
			thresh = s2.toUShort();
//			qDebug("modaddr: %d, thresh: %d", modaddr, thresh);
//			if(myMpsd[modaddr]->getMpsdId() > 0)
				myMpsd[modaddr]->setThreshpoti(thresh, 1);
		}
		} // end else comment line
	    // read next line
	    s = t.readLine();
	}

	f.close();
	mainWin->dispFiledata();
	mainWin->dispCounterAssign();
	return true;
	}
  	else{
		pstring.sprintf("ERROR: opening configfile '");
		pstring.append(name);
		pstring.append("' failed");
		protocol(pstring, 0);
		return false;
  }
}


/*!
    \fn mesydaq2::commTimeout()
 */
void mesydaq2::commTimeout()
{
	pstring.sprintf("Timeout while waiting for cmd answer from MCPD-ID: %d", commId);
	protocol(pstring, 0);
	myMcpd[commId]->timeout();
}


/*!
    \fn mesydaq2::centralDispatch()
 */
void mesydaq2::centralDispatch()
{
    if(cInt->caressTaskPending && (!cInt->asyncTaskPending))
    	cInt->caressTask();

	dispatch[0]++;
	if(dispatch[0] == 8){
		dispatch[0] = 0;
		meas->calcRates();
	}

	// graphics update
	dispatch[1]++;
	if(dispatch[1] == 100){
		dispTime();
		dispatch[1] = 0;
	}

	// commTimeout
	dispatch[2]++;
	if(cmdActive == true && dispatch[2] > 51){
		commTimeout();
	}

	// pulser test
	dispatch[3]++;
	if(testRunning == true && dispatch[3] == 11){
		pulserTest();
		dispatch[3] = 0;
	}

}


/*!
    \fn mesydaq2::initMpsd(unsigned char id)
 */
void mesydaq2::initMpsd(unsigned char mcpd, unsigned char id)
{
	unsigned char start = 0;
	unsigned char stop = 0;
	unsigned char num = 8 * mcpd + id;
	bool common = false;

	commandBuffer[0] = mcpd;

	// gains:
	commandBuffer[1] = SETGAIN;
	commandBuffer[2] = id;
	if(myMpsd[num]->comGain()){
		// only channel 8 = common
		start = 8;
		stop = 9;
		common = true;
	}
	else{
		// iterate through all channels
		start = 0;
		stop = 8;
		common = false;
	}
	for(unsigned char c = start; c < stop; c++){
		commandBuffer[3] = c;
		commandBuffer[4] = myMpsd[num]->getGainpoti(c, 1);
		sendCommand(commandBuffer);
	}

	// threshold:
	commandBuffer[1] = SETTHRESH;
	commandBuffer[3] = myMpsd[num]->getThreshpoti(1);
	sendCommand(commandBuffer);

	// pulser
	commandBuffer[1] = SETPULSER;
	commandBuffer[2] = id;
	commandBuffer[3] = 0;
	commandBuffer[4] = 2;
	commandBuffer[5] = 50;
	commandBuffer[6] = 0;
	sendCommand(commandBuffer);

	// mode
	commandBuffer[1] = SETMODE;
	commandBuffer[3] = 0;
	sendCommand(commandBuffer);

	// now set tx capabilities, if id == 105
	if(myMpsd[num]->getMpsdId() == 105){
		myMpsd[num]->setInternalreg(1, 4, 1);
		commandBuffer[1] = WRITEPERIREG;
		commandBuffer[2] = id;
		commandBuffer[3] = 1;	// write register 1
		commandBuffer[4] = 4;
		sendCommand(commandBuffer);
	}

	pstring.sprintf("initialized mpsd-8 on bus %d of mcpd %d", id, myMpsd[id]->getMcpdId());
	protocol(pstring, 1);
}


/*!
    \fn mesydaq2::initMcpd(unsigned char id)
 */
void mesydaq2::initMcpd(unsigned char id)
{
    unsigned char c;

    if(!myMcpd[id]->isOnline())
    	return;
    // set master / slave and termination
	myMcpd[id]->fillTiming(commandBuffer);
	sendCommand(commandBuffer);

    // set counter cells
    for(c=0; c < 8; c++){
		myMcpd[id]->fillCounterCell(c, commandBuffer);
		sendCommand(commandBuffer);
	}

	// set auxTimers
    for(c=0; c < 4; c++){
		myMcpd[id]->fillAuxTimer(c, commandBuffer);
		sendCommand(commandBuffer);
	}

	// set parameter sources
    for(c=0; c < 4; c++){
		myMcpd[id]->fillParamSource(c, commandBuffer);
		sendCommand(commandBuffer);
	}

    // set tx capability to TAP
	commandBuffer[0] = id;
   	commandBuffer[1] = WRITEREGISTER;
	commandBuffer[2] = 1;
	commandBuffer[3] = 103;
    // set tx capability to TAP
	commandBuffer[4] = 4;
    // set tx capability to P
//	commandBuffer[4] = 1;
	sendCommand(commandBuffer);
	pstring.sprintf("initialized MCPD ID %d", id);
	protocol(pstring, 1);
}


/*!
    \fn mesydaq2::allPulserOff()
 */
void mesydaq2::allPulserOff()
{
    // send pulser off to all connected MPSD

	commandBuffer[0] = 0;
   	commandBuffer[1] = SETPULSER;
	commandBuffer[3] = 0;
	commandBuffer[4] = 2;
	commandBuffer[5] = 40;
	commandBuffer[6] = 0;

    for(unsigned int i = 0; i < MCPDS; i++){
    	if(confMcpd[i] && myMcpd[i]->isOnline()){
			for(unsigned int j = 0; j < 8; j++){
				if(myMpsd[j]->getMpsdId()){
					commandBuffer[0] = i;
					commandBuffer[2] = j;
					myMpsd[j]->setPulser(0, 0, 2, 0, 1);
					sendCommand(commandBuffer);
				}
			}
		}
	}
}


/*!
    \fn mesydaq2::setTimingwidth(unsigned char width)
 */
void mesydaq2::setTimingwidth(unsigned char width)
{
    if(width < 48)
    	timingwidth = width;
    else
    	timingwidth = 48;

   	for(unsigned i=0; i < MCPDS; i++)
   		hist[i]->setWidth(timingwidth);
}


/*!
    \fn mesydaq2::readPeriReg(unsigned short id, unsigned short mod, unsigned short reg)
 */
unsigned short mesydaq2::readPeriReg(unsigned short id, unsigned short mod, unsigned short reg)
{
   	commandBuffer[0] = id;
	commandBuffer[1] = READPERIREG;
	commandBuffer[2] = mod;
	commandBuffer[3] = reg;
	sendCommand(commandBuffer);
}


/*!
    \fn mesydaq2::writePeriReg(unsigned short id, unsigned short mod, unsigned short reg, unsigned short val)
 */
void mesydaq2::writePeriReg(unsigned short id, unsigned short mod, unsigned short reg, unsigned short val)
{
   	commandBuffer[0] = id;
	commandBuffer[1] = WRITEPERIREG;
	commandBuffer[2] = mod;
	commandBuffer[3] = reg;
	commandBuffer[4] = val;
	sendCommand(commandBuffer);
}






/*!
    \fn mesydaq2::checkListfilename(void)
 */
bool mesydaq2::checkListfilename(void)
{
	// name already defined?
	// no - try ot get one...
	if(listfilename.isEmpty()){
		if(mainWin->listFilename->text().isEmpty()){

		}
	}
	datfile.setName(listfilename);
	return true;
}


/*!
    \fn mesydaq2::getListpath()
 */
QString mesydaq2::getListfilepath()
{
    return listPath;
}


/*!
    \fn mesydaq2::getListfilename()
 */
bool mesydaq2::getListfilename()
{
	ovwList = false;
	QString name = QFileDialog::getSaveFileName(listPath, "mesydaq data files (*.mdat);;all files (*.*);;really all files (*)", this, "Save as...");
  	if(!name.isEmpty()){
    	int i = name.find(".mdat");
		if(i == -1)
		name.append(".mdat");
		if(QFile::exists(name) && ovwList == false){
			int answer = QMessageBox::warning(
						this, "Listfile Exists -- Overwrite File",
						QString("Overwrite existing listfile?"),
						"&Yes", "&Cancel", QString::null, 1, 1 );
			if(answer == 1){
				name.sprintf("");
				return false;
			}
			else
				ovwList = true;
		}
 	   	mainWin->listFilename->setText(name);
    	listfilename = name;
  		return true;
  	}
	else{
		listfilename.sprintf("");
		return false;
	}
}


/*!
    \fn mesydaq2::getHistfilename(void)
 */
QString mesydaq2::getHistfilename(void)
{
    return histfilename;
}


/*!
    \fn mesydaq2::getHistfilepath(void)
 */
QString mesydaq2::getHistfilepath(void)
{
    return histPath;
}


/*!
    \fn mesydaq2::getConfigfilename(void)
 */
QString mesydaq2::getConfigfilename(void)
{
    return configfilename;
}


/*!
    \fn mesydaq2::getConfigfilepath(void)
 */
QString mesydaq2::getConfigfilepath(void)
{
    return configPath;
}


/*!
    \fn mesydaq2::setHistfilename(QString name)
 */
void mesydaq2::setHistfilename(QString name)
{
    histfilename = name;
}


/*!
    \fn mesydaq2::setConfigfilename(QString name)
 */
void mesydaq2::setConfigfilename(QString name)
{
    if(name.length()>0)
    	configfilename = name;
    else
    	configfilename = "mesycfg.mcfg";
    pstring.sprintf("config set to: ");
    pstring.append(configfilename);
    protocol(pstring, 2);
}


/*!
    \fn mesydaq2::setListfilepath(QString path)
 */
void mesydaq2::setListfilepath(QString path)
{
    listPath = path;
}


/*!
    \fn mesydaq2::setHistfilepath(QString path)
 */
void mesydaq2::setHistfilepath(QString path)
{
    histPath = path;
}


/*!
    \fn mesydaq2::setConfigfilepath(QString path)
 */
void mesydaq2::setConfigfilepath(QString path)
{
    configPath = path;
}


/*!
    \fn mesydaq2::writeHistograms()
 */
void mesydaq2::writeHistograms()
{
   QFile f;
   int k;

   histfilename = QFileDialog::getSaveFileName(histPath, "mesydaq histogram files (*.mtxt);;all files (*.*)", this, "Write Histogram...");
   if(histfilename.isEmpty())
      return;

   k = histfilename.find(".mtxt");
   if(k == -1)
      histfilename.append(".mtxt");

   if(QFile::exists(histfilename)){
      int answer = QMessageBox::warning(
                 this, "Histogram File Exists -- Overwrite File",
                 QString("Overwrite existing histogram file?"),
                 "&Yes", "&No", QString::null, 1, 1 );
      if(answer){
        histfilename.sprintf(" ");
      }
   }

  QDateTime dateTime;
  dateTime = QDateTime::currentDateTime();

  f.setName(histfilename);
	if ( f.open(IO_WriteOnly) ) {    // file opened successfully
		QTextStream t( &f );        // use a text stream
		QString s;
		// Title
		t << "mesydaq Histogram File    ";
		t << dateTime.toString("dd.MM.yy  ")<< dateTime.toString("hh:mm:ss");
		t << '\r' << '\n';


	    for(unsigned char c=0;c<MCPDS;c++){
    		hist[c]->writeHistogram(&f);
    	}
		f.close();
	}
}


/*!
    \fn mesydaq2::setCountlimit(unsigned char cNum, unsigned long lim)
 */
void mesydaq2::setCountlimit(unsigned char cNum, unsigned long lim)
{
	switch(cNum){
		case M1CT:
    		dc->setLimit(MON1ID, lim);
    	break;
		case M2CT:
    		dc->setLimit(MON2ID, lim);
    	break;
		case EVCT:
    		dc->setLimit(EVID, lim);
    	break;
    	default:
    	break;
    }
}


/*!
    \fn mesydaq2::copyData(unsigned int line, unsigned long * data)
 */
void mesydaq2::copyData(unsigned int start, unsigned int len, unsigned long * data)
{
    unsigned int i;
    // intermediate buffer for partial lines
    unsigned long intermediate[960];
    unsigned int numLines = 0;
    unsigned int suffix = 0;
    unsigned int startline = 0;
    unsigned int offset = 0;
    unsigned int offsline = 0;
    unsigned int prefix = 0;

    // first: find start line:
    startline = start / 960;
    // check for offset within line:
    offset = start - (startline * 960);

    // ok - get first partial line if offset
    if(offset){
	   	if(len > 960 - offset)
	   		prefix = 960 - offset;
	   	else
	   		prefix = len;
	    hist[0]->copyLine(startline, intermediate);
		for(i = offset; i < offset+prefix; i++)
			data[i-offset] = intermediate[i];
		offsline = 1;
	}
	numLines = (len-prefix) / 960;
	// now copy numLines complete lines into data buffer
	for(i=0;i<numLines;i++)
		hist[0]->copyLine(startline+i+offsline, &data[offset+i*960]);

	suffix = len - prefix  - 960 * numLines;
	// and process possible suffix:
	if(suffix){
		hist[0]->copyLine(startline+numLines+offsline, intermediate);
		for(i = 0; i < suffix; i++)
			data[len-suffix+i] = intermediate[i];
	}
}


/*!
    \fn mesydaq2::isDaq(void)
 */
unsigned char mesydaq2::isDaq(void)
{
	return daq;
}


/*!
    \fn mesydaq2::openCaressListfile(void)
 */
void mesydaq2::openCaressListfile(void)
{
//	cInt->completeCaressFileheader();

	listfilename = listPath;
	listfilename.append('/');
	if(cInt->caressDatadir.length() > 0){
		listfilename.append(cInt->caressDatadir);
		listfilename.append('/');
	}
	listfilename.append(cInt->caressFilename);
	mainWin->listFilename->setText(listfilename);

	// try to find directory - create if not existing:
	QString listfiledir = listPath;
	listfiledir.append('/');
	listfiledir.append(cInt->caressDatadir);
	qDebug(listfiledir);
	if(checkDirectory(listfiledir)){
		// o.k. - now try to use it:
		datfile.setName(listfilename);
		if(datfile.open(IO_WriteOnly)){
			listfileOpen = true;
			textStream.setDevice(&datfile);
			datStream.setDevice(&datfile);
			textStream << cInt->carFileH;
			pstring.sprintf("opened caress listmodefile: ");
			pstring.append(listfilename);
			protocol(pstring,2);
		}
		else{
			pstring.sprintf("error opening listmode file: ");
			pstring.append(listfilename);
			protocol(pstring,1);
/*			// now try to open fallback file:
			if(openFallbackListfile()){
				pstring.sprintf("successfully opened fallback listmode file: ");
				pstring.append(listfilename);
				protocol(pstring,1);
			}
			else{
				pstring.sprintf("error opening fallback listmode file: ");
				pstring.append(listfilename);
				protocol(pstring,1);
			}
*/		}
	}
}


/*!
    \fn mesydaq2::changeCaressListfile()
 */
void mesydaq2::changeCaressListfile()
{
    datfile.close();
    listfileOpen = false;
    cInt->completeCaressFileheader();
    openCaressListfile();
}


/*!
    \fn mesydaq2::checkDirectory(QString dir)
 */
bool mesydaq2::checkDirectory(QString dir)
{
    // takes a given directory, checks existance, tries to create
    // if not existing
    QString directory("");

    QDir checkDir(dir);

    int pos1 = 1, pos2 = 0, len = 0;

    if(checkDir.exists()){
    	pstring.sprintf("Directory ");
    	pstring.append(dir);
    	pstring.append(" exists. ->o.k.");
    	protocol(pstring, 3);
    	return true;
    }

    len = dir.length();
    while(pos1){
    	pos2 = dir.find('/', pos1, true);
		// check if '/' in pathname
		// get directory name
		directory.append('/');
		if(pos2 > 0)
			directory.append(dir.mid(pos1, pos2-pos1));
		else
			directory.append(dir.right(len-pos1));
		checkDir.setPath(directory);
		// check existance
		if(!checkDir.exists()){
			// try to create
			if(!checkDir.mkdir(directory, true)){
				pstring.sprintf("ERROR: directory ");
				pstring.append(directory);
				pstring.append(" can not be created!");
				protocol(pstring, 0);
				return false;
			}
			pstring.sprintf("directory ");
			pstring.append(directory);
			pstring.append(" created.");
			protocol(pstring, 1);
		}
		// search for more text:
		pos1 = 1 + pos2;
	}
	return true;
}

// command shortcuts for simple operations:
/*!
    \fn mesydaq2::start(void)
 */
void mesydaq2::start(void)
{
   	pstring.sprintf("remote start");
   	protocol(pstring, 1);
   	commandBuffer[0] = 0;
	commandBuffer[1] = START;
	sendCommand(commandBuffer);
	pstring.sprintf("Stop");
	mainWin->startStopButton->setOn(true);
	mainWin->startStopButton->setText(pstring);
	mainWin->updateCaress();
}

/*!
    \fn mesydaq2::continue(void)
 */
void mesydaq2::cont(void)
{
    /// @todo implement me
}


/*!
    \fn mesydaq2::reset(void)
 */
void mesydaq2::reset(void)
{
    /// @todo implement me
}


/*!
    \fn mesydaq2::startAll(void)
 */
void mesydaq2::startAll(void)
{
   	unsigned char c, m;
//   	qDebug("start all");
	commandBuffer[1] = START;
   	// start slaves, identify master
   	for(c=0; c < 8; c++){
   		if(confMcpd[c] && myMcpd[c]->isOnline() && !myMcpd[c]->isMaster()){
   			pstring.sprintf("start slave %d", c);
   			protocol(pstring, 2);
   			commandBuffer[0] = c;
			commandBuffer[2] = 0; // don't open listmodefile here!
			sendCommand(commandBuffer);
		}
		if(myMcpd[c]->isMaster())
			m = c;
	}
	// start master
	pstring.sprintf("start master %d", m);
	protocol(pstring, 2);
	commandBuffer[0] = m;
	commandBuffer[2] = 1; // open listmodefile here!
	sendCommand(commandBuffer);
}


/*!
    \fn mesydaq2::stopAll(void)
 */
void mesydaq2::stopAll(void)
{
   	unsigned char c, m;

	commandBuffer[1] = STOP;
   	// identify and stop master
   	for(c=0; c < 8; c++){
   		if(confMcpd[c] && myMcpd[c]->isMaster()){
			m = c;
			commandBuffer[0] = c;
			sendCommand(commandBuffer);
		}
	}
   	// stop slaves
   	for(c=0; c < 8; c++){
   		if(confMcpd[c] && (c != m)){
//   			qDebug("stop slave %d", c);
   			commandBuffer[0] = c;
			sendCommand(commandBuffer);
		}
	}
}


/*!
    \fn mesydaq2::buildListfileheader(void)
 */
void mesydaq2::buildListfileheader(void)
{
    QDateTime datetime;
    QString str;
    unsigned int hlength;

    listfileHeader.sprintf("##############################################################################\n");
    listfileHeader.append("# ");
    listfileHeader.append(listfilename);
    listfileHeader.append("\n");
    listfileHeader.append("# date ");
    listfileHeader.append(datetime.currentDateTime().toString("yyyy-MM-dd"));
    listfileHeader.append("\n");
    listfileHeader.append("#\n");
    listfileHeader.append("# (c) ");
    listfileHeader.append(datetime.currentDateTime().toString("yyyy"));
    listfileHeader.append(", HZB\n");
    listfileHeader.append("#\n");
    listfileHeader.append("# time of flight measurement at HZB instrument v15 (EXED)\n");
    listfileHeader.append("#\n");
    listfileHeader.append("# comment: ");
    listfileHeader.append(mainWin->listfileComment->text());
    listfileHeader.append("\n");
    listfileHeader.append("#\n");
    listfileHeader.append("##############################################################################\n");
	listfileHeader.append("[MSY_] # mesydaq data\n");
	listfileHeader.append("File_Name = ");
	listfileHeader.append(listfilename);
	listfileHeader.append("\n");
	listfileHeader.append("Frequency = 1E+07\n");

    str.sprintf("Start_Time = %d\n", (unsigned long) time(NULL));
	listfileHeader.append(str);
	listfileHeader.append("# offset (bytes) where binary tof data begins\n");
	listfileHeader.append("Data = ");
	// text length plus trailing '\n'
	hlength = listfileHeader.length() + 1;
	if(hlength < 97)
		hlength += 2;
	if(hlength > 96 && hlength < 997)
		hlength += 3;
	if(hlength > 995 && hlength < 9996)
		hlength += 4;
	if(hlength > 9994 && hlength < 99995)
		hlength += 5;
	if(hlength > 99993 && hlength < 999994)
		hlength += 6;
	// should be enough here...
	// convert into string:
	str.sprintf("%d",hlength);
	listfileHeader.append(str);
	listfileHeader.append('\n');
//	qDebug(listfileHeader);
}


/*!
    \fn mesydaq2::setMcpdAddress(unsigned char id, QString address)
 */
void mesydaq2::setMcpdAddress(unsigned char id, QString address)
{
	netDev[0]->setAddress(id, address);
}

/*!
    \fn mesydaq2::getMcpdVersion(unsigned char id)
 */
void mesydaq2::getMcpdVersion(unsigned char id)
{
		commandBuffer[0] = id;
		commandBuffer[1] = STOP;
		sendCommand(commandBuffer);

		commandBuffer[0] = id;
		commandBuffer[1] = GETVER;
		sendCommand(commandBuffer);
}

/*!
    \fn mesydaq2::getDebugLevel(void)
 */
unsigned char mesydaq2::getDebugLevel(void)
{
    return debugLevel;
}

/*!
    \fn mesydaq2::setDebugLevel(unsigned char level)
 */
void mesydaq2::setDebugLevel(unsigned char level)
{
    debugLevel = level;
}


/*!
    \fn mesydaq2::searchMcpd(unsigned char id)
 */
void mesydaq2::searchMcpd(unsigned char id)
{
    getMcpdVersion(id);
    mainWin->displayMcpdSlot();
}


/*!
    \fn mesydaq2::openFallbackListfile(void)
 */
bool mesydaq2::openFallbackListfile(void)
{
	return true;
}


/*!
    \fn mesydaq2::findInterfaces(void)
 */
void mesydaq2::findInterfaces(void)
{
    QString str, str2;
    struct ifconf ifc;
    struct ifreq* ifr;
    struct ifreq ifrcopy;
    struct sockaddr_in* sa;
    int sockfd, i;
    char buf[1000];
    char * ptr;

    numIf = 0;

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
//    qDebug("sockfd for search: %d", sockfd);
    ifc.ifc_len = 1000;
    ifc.ifc_buf = buf;

    if(ioctl(sockfd, SIOCGIFCONF, &ifc) < 0){
    	qDebug("no info retrieved");
    	return;
    }

    for(i=0, ptr = buf; ptr < buf+ifc.ifc_len;i++){
    	ifr = (struct ifreq *) ptr;
    	sa = (struct sockaddr_in*)&ifr->ifr_addr;
    	str.sprintf("%d: %s, %s", i, ifr->ifr_name, inet_ntoa(sa->sin_addr));
    	qDebug(str);
//    	qDebug("%s", inet_ntoa(sa->sin_addr));
    	ifrcopy = *ifr;
    	// get flags
    	if(ioctl(sockfd, SIOCGIFFLAGS, &ifrcopy) < 0)
    		; //qDebug("no flags retrieved");
    	else{
    		if((ifrcopy.ifr_flags & IFF_UP) && !(ifrcopy.ifr_flags & IFF_LOOPBACK)){
    			qDebug("Interface UP and no Loopback");
 				ifrs[numIf] = ifrcopy;
 				numIf++;
 			}
    		if((ifrcopy.ifr_flags & IFF_UP) && (ifrcopy.ifr_flags & IFF_LOOPBACK)){
    			qDebug("Interface UP and LOOPBACK");
    			// do not use for MCPD-8 communication!
			}
		}
    	ptr = ptr + sizeof(struct ifreq);
    }
}


/*!
    \fn mesydaq2::initSystem(void)
 */
void mesydaq2::initSystem(void)
{
    // initialize some variables
	initValues();
	// initilize network interface and sockets
	initNetwork();
	// initialize device objects
	initDevices();
	// initialize and start timers as necessary
	initTimers();
	// load standard config file without asking for filename
//	qDebug("configfilename: "+configfilename);
	if(loadSetup(false)){
		pstring.sprintf("loaded standard config file successfully");
		protocol(pstring, 1);
	}
	else{
		pstring.sprintf("ERROR loading standard config file mesycfg.mcfg!");
		protocol(pstring, 0);
	}
	// initialize connected hardware modules according to config file
	initHardware();

	mainWin->displayMcpdSlot();
	mainWin->displayMpsdSlot();
	mainWin->dispFiledata();
	mainWin->debugLevelBox->setCurrentItem(debugLevel);

//	qDebug("running on qt %s", qVersion());

}


/*!
    \fn mesydaq2::update(void)
 */
void mesydaq2::update(void)
{
    mainWin->update();
}


/*!
    \fn mesydaq2::updateCaress(void)
 */
void mesydaq2::updateCaress(void)
{
    mainWin->updateCaress();
}


/*!
    \fn mesydaq2::updatePresets(void)
 */
void mesydaq2::updatePresets(void)
{
    mainWin->updatePresets();
}


/*!
    \fn mesydaq2::startPulsertest(void)
 */
void mesydaq2::startPulsertest(void)
{
	testMod = 0;
	while(!myMpsd[testMod]->getMpsdId()){
		qDebug("mod: %d", testMod);
		testMod ++;
		if(testMod == 8 * MCPDS)
			break;
	}
	if(testMod == 8 * MCPDS){
		qDebug("not started!");
		return;
	}
//	qDebug("starting with mod: %d", testMod);

	testChan = 0;
	testPos = 0;
	testAmpl = 0;
//	testTimer->start(500, false);
	testJustStarted = true;
	dispatch[3] = 0;
	testRunning = true;
	testStopping = false;
//	qDebug("starting position: cpu%d, mod%d, chan%d, pos%d, ampl%d", testCpu, testMod, testChan, testPos, testAmpl);
}


/*!
    \fn mesydaq2::stopPulsertest(void)
 */
void mesydaq2::stopPulsertest(void)
{
//	qDebug("stopPulsertest");
	testStopping = true;
	qDebug("stopping = true");
}


/*!
    \fn mesydaq2::pulserTest()
 */
void mesydaq2::pulserTest()
{
	unsigned char ampval;
    bool ok;

//	testTimer->stop();
	if(testJustStarted){
		testJustStarted = false;
	}
	else{
//		qDebug("switching off: cpu%d, mod%d, chan%d, pos%d, ampl%d", testCpu, testMod, testChan, testPos, testAmpl);
		// switch off old pulser position

		commandBuffer[0] = testCpu;
		commandBuffer[1] = SETPULSER;
		commandBuffer[2] = testMod;
		commandBuffer[3] = testChan;
		commandBuffer[4] = testPos;
		commandBuffer[5] = testAmpl;
		commandBuffer[6] = 0;
		sendCommand(commandBuffer);

		if(!testStopping){
			// now increment pulser position:
			// switch to new mpsd-8 device?
			if(testAmpl == 0)
				testAmpl = 1;
			else{
				testAmpl = 0;
				if(testPos < 2)
					testPos++;
				else{
					testPos = 0;
					if(testChan < 7)
						testChan++;
					else{
						testChan = 0;
					// check if current MPSD-8 is connected
					testMod ++;
					if(testMod == 8 * MCPDS)
						testMod = 0;
					// if not connected, look for next
					while(!myMpsd[testMod]->getMpsdId()){
						testMod ++;
						if(testMod == 8 * MCPDS)
							testMod = 0;
					}
					testCpu = (unsigned char) testMod / 8;
					}
				}
			}
//			qDebug("next position: cpu%d, mod%d, chan%d, pos%d, ampl%d", testCpu, testMod, testChan, testPos, testAmpl);
		}
	}
	if(testStopping){
		testRunning = false;
		testStopping = false;
	}
	else{
		// set pulser to current cpu/modchan/pos/ampl
		if(testAmpl == 0)
			ampval = (unsigned char)mainWin->pulsAmp1->text().toInt(&ok);
		else
			ampval = (unsigned char)mainWin->pulsAmp2->text().toInt(&ok);
		// pulser
		commandBuffer[0] = testCpu;
		commandBuffer[1] = SETPULSER;
		commandBuffer[2] = testMod;
		commandBuffer[3] = testChan;
		commandBuffer[4] = testPos;
		commandBuffer[5] = ampval;
		commandBuffer[6] = 1;
		sendCommand(commandBuffer);
//		testTimer->start(500, false);

	}
}
