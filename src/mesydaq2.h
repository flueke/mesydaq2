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


#ifndef _MESYDAQ2_H_
#define _MESYDAQ2_H_

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <qmainwindow.h>

#include <networkdevice.h>
#include <qfile.h>
#include <qdatastream.h>
#include <qtextstream.h>
#include <qstring.h>
#include <qtimer.h>
#include <qlabel.h>

#include <qapp.h>

#include <mdefines.h>
#include <net/if.h>

/**
 * @short Application Main Window
 * @author Gregor Montermann <g.montermann@mesytec.com>
 * @version 0.8
 */


class mesydaq2Widget;
class mainWindow;
class histogram;
class dataCruncher;
class mcpd8;
class mpsd8;
class measurement;
class controlInterface;

class mesydaq2 : public QMainWindow
{
    Q_OBJECT
public:
    /**
     * Default Constructor
     */
    mesydaq2();

    /**
     * Default Destructor
     */
    virtual ~mesydaq2();
    void initNetwork(void);
    int setSocket(unsigned char netDevice);
	int sendCommand(unsigned short * buffer);
    void initValues();
    int writeRegister(unsigned int id, unsigned int addr, unsigned int val);
    unsigned short calcChksum(PMDP_PACKET buffer);
    void setListfilename(QString name);
    void acqListfile(bool yesno);
    bool startDaq(void);
    void stopDaq(void);
    void startedDaq(void);
    void stoppedDaq(void);
    void protocol(QString str, unsigned char level = 1);
    void protocolCaress(QString str, unsigned char level = 1);
    void initDevices(void);
    void initTimers(void);
    void clearChanHist(unsigned long chan);
    void clearAllHist(void);
    void writeListfileHeader(void);
    void writeClosingSignature(void);
    void writeBlockSeparator(void);
    void writeHeaderSeparator(void);
    void readListfile(QString readfilename);
    void draw(void);
    void scanPeriph(unsigned short id);
    void dispMpsd(void);
    void initHardware(void);
    bool loadSetup(bool ask);
    bool saveSetup(void);
    void initMpsd(unsigned char mcpd, unsigned char id);
    void initMcpd(unsigned char id);
    void allPulserOff();
    void setTimingwidth(unsigned char width);
    void writePeriReg(unsigned short id, unsigned short mod, unsigned short reg, unsigned short val);
    unsigned short readPeriReg(unsigned short id, unsigned short mod, unsigned short reg);
    bool checkListfilename(void);
    QString getListfilepath();
    bool getListfilename();
    QString getHistfilename(void);
    QString getHistfilepath(void);
    void setConfigfilepath(QString path);
    void setHistfilepath(QString path);
    void setListfilepath(QString path);
    void setConfigfilename(QString name);
    void setHistfilename(QString name);
    QString getConfigfilepath(void);
    QString getConfigfilename(void);
    void writeHistograms();
    void reset(void);
    void cont(void);
    void start(void);
    void setCountlimit(unsigned char cNum, unsigned long lim);
    void copyData(unsigned int line, unsigned int len, unsigned long * data);
    unsigned char isDaq(void);
    void openCaressListfile(void);
    void changeCaressListfile();
    bool checkDirectory(QString dir);
    void stopAll(void);
    void startAll(void);
    void buildListfileheader(void);
    void setMcpdAddress(unsigned char id, QString address);
    void getMcpdVersion(unsigned char id);
    unsigned char getDebugLevel(void);
    void setDebugLevel(unsigned char level);
    void searchMcpd(unsigned char id);
    bool openFallbackListfile(void);
    void findInterfaces(void);
    void initSystem(void);
    void update(void);
    void updatePresets(void);
    void updateCaress(void);
    void stopPulsertest(void);
    void startPulsertest(void);

    histogram * hist[MCPDS+1];

	unsigned long int dataRxd;
	unsigned long int cmdRxd;
	unsigned long int cmdTxd;
    unsigned long headertime;
    unsigned long timeMsecs;
    unsigned short ht[3];
    unsigned int status;
    unsigned int oldStatus;
    unsigned long int dispBuf[1024];
    bool listIds;


    mcpd8 * myMcpd[MCPDS];
	mpsd8 * myMpsd[8*MCPDS];
    networkDevice * netDev[8];
    measurement* meas;
    controlInterface * cInt;
    mainWindow * mainWin;
    dataCruncher * dc;

protected:
    PMDP_PACKET cmdBuf;
	PMDP_PACKET recBuf;
	PDATA_PACKET pDataBuf;
	unsigned int txCmdBufNum;
	unsigned int rxCmdBufNum;
	unsigned int dataBufNum;
    bool cmdActive;
    unsigned char daq;
    QString pstring;
    QTimer * dispTimer;
    QTimer * commTimer;
    QTimer * theTimer;
    QTimer * testTimer;
    unsigned long statuscounter[0];
    unsigned short sep0;
    unsigned short sep5;
    unsigned short sepA;
    unsigned short sepF;
    QString progVersion;
   	unsigned char cmdLen[50];
    QString setupfile;
    unsigned char commId;
    unsigned short commandBuffer[20];

    bool acquireListfile;
    QString listfilename;
    QString configfilename;
    QString histfilename;
    QFile datfile;
    QDataStream datStream;
    QTextStream textStream;
    QString listPath;
    QString histPath;
    QString configPath;
    bool ovwList;
    unsigned char timingwidth;
    unsigned int lastBufnum;
    unsigned int lostBuffers;
    unsigned int dispatch[10];
    unsigned long bytesWritten;
    bool listfileOpen;
    bool confMcpd[MCPDS];
    QString listfileHeader;
    unsigned char debugLevel;
    struct ifreq ifrs[MCPDS];
    unsigned char numIf;
    unsigned char testCpu;
    unsigned char testMod;
    unsigned char testChan;
    unsigned char testPos;
    unsigned char testAmpl;
    bool testJustStarted;
    bool testStopping;
    bool testRunning;

public slots:
    void dispTime();
    void readBuf(void);
    void pulserTest();
    void centralDispatch();
    void commTimeout();
};



#endif // _MESYDAQ2_H_
