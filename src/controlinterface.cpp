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
#include "controlinterface.h"

#include <time.h>
#include <QDebug>

#include "mesydaq2.h"
#include "mdefines.h"
#include "measurement.h"

controlInterface::controlInterface(QObject *parent)
 : QObject(parent)
{
	theApp = (mesydaq2*) parent;
	transferBuffer = new(unsigned long[512*960]);
	caressTaskPending = false;
	caressTaskNum = 0;
	asyncTaskPending = false;
	caressFilefragment = 0;
	caressMaxfilesize = 0;
	caressInitialized = false;
}


controlInterface::~controlInterface()
{
}


/*!
    \fn controlInterface::caressTask()
 */
void controlInterface::caressTask()
{
	unsigned char devMap[5] = {0, M1CT, TCT, M2CT, EVCT};

	QString pstring, str;
	pstring.sprintf("caress: ");

	if(caressDevice == HISTO){
    	pstring.append("histogram ");
	}
	else{
   			str.sprintf("counter %d (mesydaq #%d) ", caressDevice, devMap[caressDevice]);
   			pstring.append(str);
    }

	switch(caressTaskNum){
   		case CAR_INIT:
    		pstring.append("init.");
				if(caressDevice == HISTO){
					theApp->meas->setCarHistSize(caressHeight, caressWidth);
					caressHistoSize = caressHeight * caressWidth;
					theApp->updateCaress();
				}
				else
					theApp->meas->clearCounter(devMap[caressDevice]);
    		theApp->update();
    	break;

    	case CAR_RELEASE:
    		pstring.append("release.");
    	break;

    	case CAR_START:
   			if(caressDevice == caressMaster){
   				// only start on master start!
   				asyncTaskPending = true;
				theApp->updateCaress();
				caressStarttime = (unsigned long) time(NULL);
   				completeCaressFileheader();
   				theApp->meas->setRemote(true);
   				theApp->startAll();
				pstring.append("start master.");
			}
			else
				// just notice, don't start yet...
				pstring.append("start.");
    	break;

    	case CAR_STOP:
   			if(caressDevice == caressMaster){
   				// only if daq not already stopped (e.g. by preset)
   				if(theApp->isDaq() == RUNNING){
					// only stop on master start!
					asyncTaskPending = true;
					theApp->stopAll();
   				}
   				else
   					caressTaskPending = false;

				pstring.append("stop master.");
			}
			else
				// just notice, don't stop yet...
				pstring.append("stop.");
    	break;

    	case CAR_DRIVE:
    		pstring.append("drive ");
    	break;

    	case CAR_LOAD:
			if(caressDevice == HISTO){
				pstring.append("load.");
    			theApp->clearAllHist();
    		}
    		else{
	    		if(caressSubTaskNum == CAR_SLAVE){
	    			pstring.append("load slave");
	    		}
	    		if(caressSubTaskNum == CAR_MASTER){
					theApp->meas->setPreset(devMap[caressDevice], caressPreset, true);
					pstring.append("load master preset: ");
					str.sprintf("%d", caressPreset);
					pstring.append(str);
					theApp->updatePresets();
					caressMaster = caressDevice;
				}
	    		if(caressSubTaskNum == CAR_RESET){
					theApp->meas->clearCounter(devMap[caressDevice]);
					pstring.append("(reset / load)");
					theApp->updatePresets();
				}
    		}
    	break;

    	case CAR_LOADBLOCK:
    		pstring.append("loadblock.");
            qDebug() << "caress header:" << caressHeader;

// for test purposes:
//createTestheader();

    		// extract given information:
    		extractCaressHeader();
    		caressFilefragment = 1;

    	break;

    	case CAR_READ:
    		pstring.append("read.");
    	break;

    	case CAR_READBLOCKP:
    		pstring.append("readblock param.");
    	break;

    	case CAR_READBLOCKM:
    		unsigned long start, stop;
    	    if(caressDevice == HISTO){
    	    	// check first channel
    	    	start = caressStartChannel - 1;
				// check last channel
				stop = caressEndChannel - 1;
				// now copy requested amount of data into transfer buffer
				theApp->copyData(start, stop-start+1, transferBuffer);
    			pstring.append("readblock module start: ");
	    		str.sprintf("%d",caressStartChannel);
    			pstring.append(str);
	    		pstring.append(", stop: ");
    			str.sprintf("%d",caressEndChannel);
    			pstring.append(str);
    		}
    	break;

    	default:
    		pstring.sprintf("ERROR: invalid task number!");
    	break;
    }
    if(caressTaskNum != CAR_READ){
    	theApp->protocol(pstring, 2);
    	theApp->protocolCaress(pstring, 1);
    }
//    if(caressTaskNum != CAR_START && caressTaskNum != CAR_STOP)
    caressTaskPending = false;
}

/*!
    \fn controlInterface::isActive(void)
 */
bool controlInterface::isActive(void)
{
    return caressTaskPending;
}


/*!
    \fn controlInterface::completeCar()
 */
void controlInterface::completeCar()
{
    caressTaskPending = false;
    asyncTaskPending = false;
    caressTaskNum = 0;
}


/*!
    \fn controlInterface::createTestheader(void);
 */
void controlInterface::createTestheader(void)
{
	caressHeader.sprintf("####################################\n");
	caressHeader.append("Run_Number = 1234567890\n");
	caressHeader.append("File_Base_Name = v15_1234567890_S013\n");
	caressHeader.append("Data_Dir = 2009/01\n");
	caressHeader.append("FILE_SIze_MAX = 1M\n");
	caressHeader.append("####################################\n");
}

/*!
    \fn controlInterface::extractCaressHeader()
 */
void controlInterface::extractCaressHeader()
{
#if 0 // Disabled for now as caress won't be used in this version. (flueke)
       		unsigned int strpos, strpos2;
       		QString helpstr, pstr;

       		// run number
    		strpos = caressHeader.find("Run_Number", 0, false);
    		strpos = caressHeader.find("=", strpos + 10, false);
    		strpos2 = caressHeader.find("\n", strpos + 1, false);
			caressRunnumber = caressHeader.mid(strpos+1, strpos2-strpos-1);
			caressRunnumber.remove(" ");
			qDebug("runNumber:");
			qDebug(caressRunnumber);
       		// filebasename
    		strpos = caressHeader.find("File_Base_Name", 0, false);
    		strpos = caressHeader.find("=", strpos + 14, false);
    		strpos2 = caressHeader.find("\n", strpos + 1, false);
			caressBaseFilename = caressHeader.mid(strpos+1, strpos2-strpos-1);
			caressBaseFilename.remove(" ");
			qDebug("fileName:");
			qDebug(caressBaseFilename);
       		// Data_dir
    		strpos = caressHeader.find("Data_Dir", 0, false);
    		strpos = caressHeader.find("=", strpos + 8, false);
    		strpos2 = caressHeader.find("\n", strpos + 1, false);
			caressDatadir = caressHeader.mid(strpos+1, strpos2-strpos-1);
			caressDatadir.remove(" ");
			qDebug("dataDir:");
			qDebug(caressDatadir);
			// max filesize
    		strpos = caressHeader.find("File_Size_Max", 0, false);
    		strpos = caressHeader.find("=", strpos + 8, false);
    		strpos2 = caressHeader.find("\n", strpos + 1, false);
			helpstr = caressHeader.mid(strpos+1, strpos2-strpos-1);
			helpstr.remove(" ");

			// now extract the numerical value:
			unsigned int factor = 1;
			if(helpstr.find("k", 0, true) > 0)
				factor = 1024;
			if(helpstr.find("M", 0, true) > 0)
				factor = 1024 * 1024;
			if(helpstr.find("G", 0, true) > 0)
				factor = 1024 * 1024 * 1024;
			if(factor > 1){
				helpstr.remove("k");
				helpstr.remove("M");
				helpstr.remove("G");
			}
			helpstr.remove(" ");
			bool ok;
			caressMaxfilesize = helpstr.toUInt(&ok, 10) * factor;
			qDebug("max size: %d", caressMaxfilesize);
#endif
}



/*!
    \fn controlInterface::completeCaressFileheader(unsigned long time)
 */
void controlInterface::completeCaressFileheader(void)
{
	// create complete filename
	QString str;
	str.sprintf("%02d", caressFilefragment);
	caressFilefragment++;
	caressFilename = caressBaseFilename;
	caressFilename.append("_P");
	caressFilename.append(str);
	caressFilename.append(".mts");

	// add the starttime information into fileheader
	carFileH = caressHeader;
	carFileH.append("[MSY_] # mesydaq data\n");
	carFileH.append("File_Name = ");
	carFileH.append(caressFilename);
	carFileH.append("\n");
	carFileH.append("Frequency = 1E+07\n");
    str.sprintf("Start_Time = %d\n", caressStarttime);
	carFileH.append(str);
	carFileH.append("# offset (bytes) where binary tof data begins\n");
	carFileH.append("Data = ");
	// text length plus trailing '\n'
	caressHlen = carFileH.length() + 1;
	if(caressHlen < 97)
		caressHlen += 2;
	if(caressHlen > 96 && caressHlen < 997)
		caressHlen += 3;
	if(caressHlen > 995 && caressHlen < 9996)
		caressHlen += 4;
	if(caressHlen > 9994 && caressHlen < 99995)
		caressHlen += 5;
	if(caressHlen > 99993 && caressHlen < 999994)
		caressHlen += 6;
	// should be enough here...
	// convert into string:
	str.sprintf("%d",caressHlen);
	carFileH.append(str);
	carFileH.append('\n');
//	qDebug(carFileH);
}
