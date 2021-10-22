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
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <mesydaq2mainwindow.h>
#include "mesydaq2.h"
#include "histogram.h"
#include <qpainter.h>


/**
	@author Gregor Montermann <g.montermann@mesytec.com>
*/
class mainWindow : public mesydaq2mainwindow
{
Q_OBJECT
public:
    mainWindow(QWidget* parent = 0, const char* name = 0, WFlags fl = 0 );

    ~mainWindow();
    void update(void);
    QString buildTimestring(unsigned long timeval, bool nano);
    void drawDataGrid(void);
    void setData(unsigned long * data, unsigned int len, unsigned long int max);
    void drawData(void);
    void draw(void);
    void processDispData();
    void drawOpData();
    void dispFiledata(void);
    unsigned char getDispId(void);
    void updatePresets(void);
    void updateCaress(void);
    void splitAddress(QString addrStr, unsigned char * addrByte) ;
    void drawXAxis(void);
    void drawYAxis(void);
    void setDispMode(bool mult, unsigned char num);
    void dispCounterAssign(void);
public slots:
    virtual void sendAuxSlot();
    virtual void sendParamSlot();
    virtual void sendCellSlot();
    virtual void startStopSlot();
    virtual void setTimingSlot();
    virtual void resetTimerSlot();
    virtual void clearChanSlot();
    virtual void clearMpsdSlot();
    virtual void clearMcpdSlot();
    virtual void clearAllSlot();
    virtual void setStreamSlot();
    virtual void replayListfileSlot();
    virtual void setRunIdSlot();
    virtual void displayMpsdSlot(void);
    virtual void displayMcpdSlot(void);
    virtual void setModeSlot(int);
    virtual void scanPeriSlot();
    virtual void restoreSetupSlot();
    virtual void linlogSlot();
    virtual void applyThreshSlot();
    virtual void saveSetupSlot();
    virtual void redrawSlot();
    virtual void readRegisterSlot();
    virtual void writeRegisterSlot();
    virtual void selectConfigpathSlot();
    virtual void selectHistpathSlot();
    virtual void selectListpathSlot();
    virtual void writeHistSlot();
    virtual void m2PresetSlot(bool pr);
    virtual void m1PresetSlot(bool pr);
    virtual void tPresetSlot(bool pr);
    virtual void ePresetSlot(bool pr);
    virtual void m2ResetSlot();
    virtual void m1ResetSlot();
    virtual void eResetSlot();
    virtual void tResetSlot();
    virtual void applyMIpSlot();
    virtual void debugLevelSlot(int level);
    virtual void mcpdSearchSlot();
    virtual void pulsertestSlot(bool on);
    virtual void assignCounterSlot();
protected:
    unsigned short cmdBuffer[20];
    virtual void acqListfileSlot();
    virtual void selectListfileSlot();
    virtual void allPulserSlot();
    virtual void setThresholdSlot();
    virtual void setGainSlot();
    virtual void setPulserSlot();
    virtual void setIpUdpSlot();
    virtual void setMcpdIdSlot();
    unsigned short * pBuffer;
    mesydaq2 * theApp;
    QString pstring;
    
    unsigned long int * pDispBuffer;
    unsigned long int dispMax;
    float dispRange;
    unsigned long int dispLen;
    unsigned short height;
    unsigned short histHeight;
    unsigned short histOffset;
    unsigned short yStart;
    unsigned short width;
    unsigned short xstep;
    float ystep;
    unsigned long int dispLoThresh;
    unsigned long int dispHiThresh;
    unsigned char scale;
    bool  dispLog;
    bool dispThresh;
    unsigned char dispId;
    unsigned int dispChannelCounts;
	bool multi;
	unsigned char dispNum;
    bool dontSend;
};

#endif
