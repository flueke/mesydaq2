/****************************************************************************
** Form interface generated from reading ui file './mesydaq2mainwindow.ui'
**
** Created:
**
** WARNING! All changes made in this file will be lost!
****************************************************************************/

#ifndef WIDGET2_H
#define WIDGET2_H

#include <qvariant.h>
#include <qwidget.h>

class QVBoxLayout;
class QHBoxLayout;
class QGridLayout;
class QSpacerItem;
class QFrame;
class QLabel;
class QGroupBox;
class QLineEdit;
class QCheckBox;
class QPushButton;
class QTabWidget;
class QButtonGroup;
class QRadioButton;
class QSpinBox;
class QTextEdit;
class QComboBox;

class mesydaq2mainwindow : public QWidget
{
    Q_OBJECT

public:
    mesydaq2mainwindow( QWidget* parent = 0, const char* name = 0, WFlags fl = 0 );
    ~mesydaq2mainwindow();

    QFrame* mainFrame;
    QLabel* textLabel1_5_3;
    QLabel* textLabel1_5;
    QLabel* meanText;
    QLabel* sigmaText;
    QFrame* dataFrame;
    QGroupBox* groupBox1;
    QLineEdit* daqStatusLine;
    QCheckBox* acquireFile;
    QPushButton* startStopButton;
    QPushButton* allPulsersoffButton;
    QLabel* pulserWarning;
    QLabel* versionLabel;
    QTabWidget* tabWidget5_2;
    QWidget* tab;
    QCheckBox* dispAll;
    QButtonGroup* buttonGroup10;
    QRadioButton* dispAllAmpl;
    QRadioButton* dispAllPos;
    QPushButton* clearMcpd;
    QSpinBox* dispMcpd;
    QPushButton* clearChan;
    QPushButton* clearMpsd;
    QLabel* textLabel1_4_2_3_4_2_2;
    QSpinBox* dispMpsd;
    QLabel* textLabel1_4_2_3_4_2;
    QSpinBox* dispChan;
    QLabel* textLabel1_4_2_3_4_2_2_2;
    QLabel* textLabel2;
    QPushButton* clearAll;
    QButtonGroup* logGroup;
    QRadioButton* log;
    QRadioButton* lin;
    QCheckBox* zoomBox;
    QCheckBox* eightFoldBox;
    QLabel* textLabel1_14;
    QSpinBox* zoomStart;
    QWidget* tab_2;
    QCheckBox* useThresh;
    QLineEdit* loLim;
    QLabel* textLabel1_6;
    QLabel* textLabel1_6_2;
    QLineEdit* hiLim;
    QPushButton* applyDispThreshButton;
    QTabWidget* tabWidget2;
    QWidget* tab_3;
    QTabWidget* TabWidget;
    QWidget* tab_4;
    QSpinBox* evPreset;
    QLabel* textLabel1_10_2;
    QPushButton* eResetButton;
    QSpinBox* m1Preset;
    QPushButton* tPresetButton;
    QLabel* monRate2;
    QLabel* textLabel1_2_3_2_3;
    QLabel* monitor2;
    QPushButton* m1PresetButton;
    QLabel* monRate1;
    QLabel* tSecsText;
    QPushButton* ePresetButton;
    QLabel* textLabel1_2_3_2_3_2;
    QPushButton* m2RresetButton;
    QLabel* textLabel1_10_2_2;
    QLabel* mTimeText;
    QLabel* textLabel1_11;
    QLabel* monitor1;
    QLabel* totalCounts;
    QLabel* textLabel1_11_2;
    QLabel* textLabel1_10;
    QLabel* eventRate;
    QSpinBox* m2Preset;
    QSpinBox* tPreset;
    QPushButton* m1ResetButton;
    QPushButton* tResetButton;
    QPushButton* m2PresetButton;
    QLabel* textLabel1;
    QSpinBox* cpuMon1box;
    QSpinBox* cpuMon2box;
    QLabel* textLabel1_15;
    QLabel* textLabel1_15_2;
    QSpinBox* counterMon2box;
    QSpinBox* counterMon1box;
    QWidget* tab_5;
    QLabel* textLabel1_2_3;
    QLabel* textLabel1_2;
    QLabel* cmdTx;
    QLabel* cmdRx;
    QLabel* textLabel1_2_2;
    QLabel* dataRx;
    QWidget* TabPage;
    QLabel* textLabel1_12;
    QLabel* textLabel1_12_2;
    QLabel* textLabel1_12_2_2;
    QLabel* caressHeight;
    QLabel* caressWidth;
    QLabel* caressRun;
    QLabel* textLabel1_13;
    QTextEdit* caressEdit;
    QWidget* tab_6;
    QLabel* textLabel1_5_2;
    QGroupBox* groupBox38;
    QPushButton* searchMcpdButton1;
    QLabel* mcpdStatusText1;
    QLabel* mcpdConfigText1;
    QLabel* mcpdMasterText1;
    QTabWidget* tabWidget5;
    QWidget* tab_7;
    QGroupBox* groupBox9;
    QLabel* textLabel1_7;
    QLabel* textLabel1_7_3;
    QLabel* textLabel1_7_2;
    QPushButton* sendCellButton;
    QComboBox* cellSource;
    QComboBox* cellTrigger;
    QSpinBox* cellCompare;
    QGroupBox* groupBox16;
    QCheckBox* statusStream;
    QPushButton* setStream;
    QGroupBox* groupBox9_2;
    QLabel* textLabel1_7_4;
    QLabel* textLabel1_7_3_2;
    QPushButton* sendAux;
    QSpinBox* timer;
    QLineEdit* compareAux;
    QGroupBox* groupBox9_2_2;
    QLabel* textLabel1_7_4_2_2;
    QLabel* textLabel1_7_4_2;
    QPushButton* sendParam;
    QComboBox* paramSource;
    QSpinBox* param;
    QWidget* tab_8;
    QGroupBox* groupBox30;
    QCheckBox* master;
    QCheckBox* terminate;
    QPushButton* resetTimer;
    QGroupBox* groupBox29;
    QSpinBox* deviceId;
    QPushButton* setID;
    QGroupBox* groupBox6;
    QLabel* textLabel1_3_3_2;
    QLabel* textLabel1_3_3_2_2;
    QLineEdit* mcpdIpAddress2;
    QLineEdit* cmdIpAddress0;
    QLabel* textLabel1_3_2_2_2;
    QLineEdit* dataIpAddress2;
    QLineEdit* dataIpAddress1;
    QLineEdit* dataIpAddress0;
    QLineEdit* mcpdIpAddress1;
    QLineEdit* cmdIpAddress2;
    QLineEdit* mcpdIpAddress3;
    QLineEdit* mcpdIpAddress0;
    QCheckBox* cmdThisPc;
    QSpinBox* cmdUdpPort;
    QLineEdit* cmdIpAddress3;
    QLineEdit* cmdIpAddress1;
    QLabel* textLabel1_3_2_2;
    QSpinBox* dataUdpPort;
    QLabel* textLabel1_3_2;
    QPushButton* setIP;
    QLineEdit* dataIpAddress3;
    QCheckBox* dataThisPc;
    QLabel* textLabel1_3_2_2_2_2;
    QLineEdit* mIpAddress1;
    QLineEdit* mIpAddress2;
    QCheckBox* modifyIp;
    QLineEdit* mIpAddress3;
    QCheckBox* modifyMIp;
    QPushButton* applyMIp;
    QLineEdit* mIpAddress0;
    QWidget* TabPage_2;
    QLabel* textLabel1_3;
    QLabel* textLabel1_3_4;
    QLabel* textLabel1_3_3;
    QLabel* param0;
    QLabel* param1;
    QLabel* textLabel1_2_3_2;
    QLabel* param2;
    QLabel* param3;
    QLabel* hTimeText;
    QLabel* textLabel1_3_5;
    QSpinBox* mcpdId;
    QWidget* TabPage_3;
    QTabWidget* tabWidget4;
    QWidget* tab_9;
    QGroupBox* groupBox17_2;
    QLabel* textLabel1_4;
    QLabel* textLabel1_4_10;
    QLabel* textLabel1_4_9;
    QLabel* textLabel1_4_8;
    QLabel* textLabel1_4_7;
    QLabel* textLabel1_4_6;
    QLabel* textLabel1_4_5;
    QLabel* textLabel1_4_4;
    QLabel* status3;
    QLabel* status2;
    QLabel* status1;
    QLabel* status4;
    QLabel* status5;
    QLabel* status6;
    QLabel* status7;
    QPushButton* scanPeri;
    QLabel* status0;
    QGroupBox* groupBox39;
    QPushButton* readRegisterButton;
    QSpinBox* registerSelect;
    QLineEdit* registerValue;
    QPushButton* writeRegisterButton;
    QLabel* textLabel1_4_2_4;
    QLabel* textLabel1_14_2;
    QLabel* mcpdStatusText2;
    QSpinBox* devid_2;
    QWidget* tab_10;
    QLabel* textLabel1_4_2_2;
    QGroupBox* groupBox13;
    QLabel* textLabel1_4_2_3_2;
    QLabel* textLabel1_4_2_3_3;
    QPushButton* setThreshold;
    QLabel* textLabel1_4_2_3;
    QLineEdit* gain;
    QLabel* textLabel1_4_2_3_3_3;
    QLineEdit* threshold;
    QPushButton* setGain;
    QLabel* textLabel1_4_2_3_3_2;
    QCheckBox* comgain;
    QSpinBox* channel;
    QGroupBox* groupBox35;
    QLabel* textLabel1_4_2_3_4;
    QButtonGroup* buttonGroup5;
    QLineEdit* pulsAmp2;
    QRadioButton* pulsampRadio1;
    QRadioButton* pulsampRadio2;
    QLineEdit* pulsAmp1;
    QPushButton* pulserButton;
    QSpinBox* pulsChan;
    QButtonGroup* buttonGroup4;
    QRadioButton* pulsLeft;
    QRadioButton* pulsMid;
    QRadioButton* pulsRight;
    QButtonGroup* modeGroup;
    QRadioButton* pos;
    QRadioButton* amp;
    QLabel* textLabel1_4_2;
    QLabel* mpsdDeviceText;
    QSpinBox* devid;
    QSpinBox* module;
    QWidget* TabPage_4;
    QGroupBox* groupBox36;
    QLabel* textLabel2_2_2;
    QLabel* histfilename;
    QPushButton* writeHistButton;
    QPushButton* LoadhistButton;
    QGroupBox* groupBox79_2;
    QPushButton* restoreSetupButton;
    QPushButton* saveSetupButton;
    QLabel* configfilename;
    QLabel* textLabel2_2;
    QGroupBox* groupBox35_2;
    QLabel* textLabel1_9_3;
    QLabel* textLabel1_9_2;
    QLabel* textLabel1_9;
    QLineEdit* listfilepath;
    QLineEdit* histfilepath;
    QLineEdit* configfilepath;
    QPushButton* selectListpath;
    QPushButton* selectConfigpath;
    QPushButton* selectHistpath;
    QGroupBox* groupBox79;
    QLabel* textLabel2_2_3;
    QLineEdit* listFilename;
    QPushButton* selectButton;
    QPushButton* replayButton;
    QLineEdit* listfileComment;
    QCheckBox* acqListfile;
    QWidget* TabPage_5;
    QGroupBox* groupBox15;
    QSpinBox* runId;
    QCheckBox* runIdAuto;
    QPushButton* runIdButton;
    QGroupBox* groupBox20;
    QSpinBox* timingBox;
    QLabel* textLabel1_8;
    QWidget* TabPage_6;
    QLabel* textLabel1_2_3_2_3_2_2;
    QPushButton* clearLogButton;
    QComboBox* debugLevelBox;
    QTextEdit* protocolEdit;
    QPushButton* pulsertestButton;

public slots:
    virtual void startStopSlot();
    virtual void sendCellSlot();
    virtual void sendParamSlot();
    virtual void sendAuxSlot();
    virtual void resetTimerSlot();
    virtual void setTimingSlot();
    virtual void setMcpdIdSlot();
    virtual void setIpUdpSlot();
    virtual void setPulserSlot();
    virtual void setGainSlot();
    virtual void setThresholdSlot();
    virtual void allPulserSlot();
    virtual void selectListfileSlot();
    virtual void acqListfileSlot();
    virtual void setStreamSlot();
    virtual void clearAllSlot();
    virtual void clearMcpdSlot();
    virtual void clearMpsdSlot();
    virtual void clearChanSlot();
    virtual void replayListfileSlot();
    virtual void setRunIdSlot();
    virtual void displayMcpdSlot(void);
    virtual void displayMpsdSlot(void);
    virtual void scanPeriSlot();
    virtual void setModeSlot(int);
    virtual void saveSetupSlot();
    virtual void restoreSetupSlot();
    virtual void saveConfigSlot();
    virtual void redrawSlot();
    virtual void applyThreshSlot();
    virtual void linlogSlot();
    virtual void writeRegisterSlot();
    virtual void readRegisterSlot();
    virtual void selectListpathSlot();
    virtual void selectHistpathSlot();
    virtual void selectConfigpathSlot();
    virtual void writeHistSlot();
    virtual void ePresetSlot(bool);
    virtual void tPresetSlot(bool);
    virtual void m1PresetSlot(bool pre);
    virtual void m2PresetSlot(bool);
    virtual void tResetSlot();
    virtual void eResetSlot();
    virtual void m1ResetSlot();
    virtual void m2ResetSlot();
    virtual void applyMIpSlot();
    virtual void debugLevelSlot(int);
    virtual void mcpdSearchSlot();
    virtual void pulsertestSlot(bool);
    virtual void assignCounterSlot();

protected:

protected slots:
    virtual void languageChange();

};

#endif // WIDGET2_H
