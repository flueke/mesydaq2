#include <kdialog.h>
#include <klocale.h>
/****************************************************************************
** Form implementation generated from reading ui file './mesydaq2mainwindow.ui'
**
** Created:
**
** WARNING! All changes made in this file will be lost!
****************************************************************************/

#include "mesydaq2mainwindow.h"

#include <qvariant.h>
#include <qframe.h>
#include <qlabel.h>
#include <qgroupbox.h>
#include <qlineedit.h>
#include <qcheckbox.h>
#include <qpushbutton.h>
#include <qtabwidget.h>
#include <qbuttongroup.h>
#include <qradiobutton.h>
#include <qspinbox.h>
#include <qtextedit.h>
#include <qcombobox.h>
#include <qlayout.h>
#include <qtooltip.h>
#include <qwhatsthis.h>

/*
 *  Constructs a mesydaq2mainwindow as a child of 'parent', with the
 *  name 'name' and widget flags set to 'f'.
 */
mesydaq2mainwindow::mesydaq2mainwindow( QWidget* parent, const char* name, WFlags fl )
    : QWidget( parent, name, fl )
{
    if ( !name )
	setName( "widget2" );
    setMinimumSize( QSize( 1280, 950 ) );
    setBaseSize( QSize( 1280, 980 ) );

    mainFrame = new QFrame( this, "mainFrame" );
    mainFrame->setGeometry( QRect( 10, 10, 1150, 520 ) );
    mainFrame->setMinimumSize( QSize( 1150, 520 ) );
    mainFrame->setMaximumSize( QSize( 1150, 520 ) );
    mainFrame->setFrameShape( QFrame::StyledPanel );
    mainFrame->setFrameShadow( QFrame::Raised );

    textLabel1_5_3 = new QLabel( mainFrame, "textLabel1_5_3" );
    textLabel1_5_3->setGeometry( QRect( 1060, 80, 76, 20 ) );

    textLabel1_5 = new QLabel( mainFrame, "textLabel1_5" );
    textLabel1_5->setGeometry( QRect( 1060, 40, 76, 20 ) );

    meanText = new QLabel( mainFrame, "meanText" );
    meanText->setGeometry( QRect( 1060, 60, 76, 20 ) );

    sigmaText = new QLabel( mainFrame, "sigmaText" );
    sigmaText->setGeometry( QRect( 1060, 100, 76, 20 ) );

    dataFrame = new QFrame( mainFrame, "dataFrame" );
    dataFrame->setGeometry( QRect( 80, 10, 961, 480 ) );
    dataFrame->setMinimumSize( QSize( 961, 480 ) );
    dataFrame->setFrameShape( QFrame::StyledPanel );
    dataFrame->setFrameShadow( QFrame::Raised );

    groupBox1 = new QGroupBox( this, "groupBox1" );
    groupBox1->setGeometry( QRect( 1050, 550, 131, 210 ) );

    daqStatusLine = new QLineEdit( groupBox1, "daqStatusLine" );
    daqStatusLine->setEnabled( FALSE );
    daqStatusLine->setGeometry( QRect( 10, 60, 110, 21 ) );
    daqStatusLine->setAlignment( int( QLineEdit::AlignHCenter ) );

    acquireFile = new QCheckBox( groupBox1, "acquireFile" );
    acquireFile->setGeometry( QRect( 20, 100, 101, 30 ) );

    startStopButton = new QPushButton( groupBox1, "startStopButton" );
    startStopButton->setGeometry( QRect( 20, 30, 81, 21 ) );
    startStopButton->setToggleButton( TRUE );

    allPulsersoffButton = new QPushButton( groupBox1, "allPulsersoffButton" );
    allPulsersoffButton->setGeometry( QRect( 20, 170, 90, 21 ) );

    pulserWarning = new QLabel( groupBox1, "pulserWarning" );
    pulserWarning->setGeometry( QRect( 20, 150, 91, 18 ) );
    pulserWarning->setPaletteForegroundColor( QColor( 251, 13, 5 ) );

    versionLabel = new QLabel( this, "versionLabel" );
    versionLabel->setGeometry( QRect( 22, 817, 170, 21 ) );

    tabWidget5_2 = new QTabWidget( this, "tabWidget5_2" );
    tabWidget5_2->setGeometry( QRect( 10, 541, 261, 270 ) );

    tab = new QWidget( tabWidget5_2, "tab" );

    dispAll = new QCheckBox( tab, "dispAll" );
    dispAll->setGeometry( QRect( 20, 10, 100, 20 ) );
    dispAll->setChecked( TRUE );

    buttonGroup10 = new QButtonGroup( tab, "buttonGroup10" );
    buttonGroup10->setGeometry( QRect( 118, 3, 121, 31 ) );

    dispAllAmpl = new QRadioButton( buttonGroup10, "dispAllAmpl" );
    dispAllAmpl->setGeometry( QRect( 60, 10, 50, 16 ) );

    dispAllPos = new QRadioButton( buttonGroup10, "dispAllPos" );
    dispAllPos->setGeometry( QRect( 10, 10, 41, 16 ) );
    dispAllPos->setChecked( TRUE );

    clearMcpd = new QPushButton( tab, "clearMcpd" );
    clearMcpd->setGeometry( QRect( 130, 150, 40, 21 ) );

    dispMcpd = new QSpinBox( tab, "dispMcpd" );
    dispMcpd->setEnabled( FALSE );
    dispMcpd->setGeometry( QRect( 70, 150, 50, 21 ) );
    dispMcpd->setMaxValue( 7 );

    clearChan = new QPushButton( tab, "clearChan" );
    clearChan->setGeometry( QRect( 130, 210, 40, 21 ) );

    clearMpsd = new QPushButton( tab, "clearMpsd" );
    clearMpsd->setGeometry( QRect( 130, 180, 40, 21 ) );

    textLabel1_4_2_3_4_2_2 = new QLabel( tab, "textLabel1_4_2_3_4_2_2" );
    textLabel1_4_2_3_4_2_2->setGeometry( QRect( 10, 180, 40, 21 ) );

    dispMpsd = new QSpinBox( tab, "dispMpsd" );
    dispMpsd->setEnabled( FALSE );
    dispMpsd->setGeometry( QRect( 70, 180, 50, 21 ) );
    dispMpsd->setMaxValue( 7 );

    textLabel1_4_2_3_4_2 = new QLabel( tab, "textLabel1_4_2_3_4_2" );
    textLabel1_4_2_3_4_2->setGeometry( QRect( 10, 150, 40, 21 ) );

    dispChan = new QSpinBox( tab, "dispChan" );
    dispChan->setEnabled( FALSE );
    dispChan->setGeometry( QRect( 70, 210, 50, 21 ) );
    dispChan->setMaxValue( 15 );

    textLabel1_4_2_3_4_2_2_2 = new QLabel( tab, "textLabel1_4_2_3_4_2_2_2" );
    textLabel1_4_2_3_4_2_2_2->setGeometry( QRect( 10, 210, 50, 21 ) );

    textLabel2 = new QLabel( tab, "textLabel2" );
    textLabel2->setGeometry( QRect( 180, 200, 70, 29 ) );

    clearAll = new QPushButton( tab, "clearAll" );
    clearAll->setGeometry( QRect( 130, 120, 60, 21 ) );

    logGroup = new QButtonGroup( tab, "logGroup" );
    logGroup->setEnabled( TRUE );
    logGroup->setGeometry( QRect( 120, 40, 100, 30 ) );

    log = new QRadioButton( logGroup, "log" );
    log->setGeometry( QRect( 50, 10, 40, 16 ) );

    lin = new QRadioButton( logGroup, "lin" );
    lin->setGeometry( QRect( 10, 10, 40, 16 ) );
    lin->setChecked( TRUE );

    zoomBox = new QCheckBox( tab, "zoomBox" );
    zoomBox->setGeometry( QRect( 20, 90, 60, 20 ) );

    eightFoldBox = new QCheckBox( tab, "eightFoldBox" );
    eightFoldBox->setGeometry( QRect( 20, 40, 91, 20 ) );

    textLabel1_14 = new QLabel( tab, "textLabel1_14" );
    textLabel1_14->setGeometry( QRect( 80, 90, 50, 16 ) );

    zoomStart = new QSpinBox( tab, "zoomStart" );
    zoomStart->setGeometry( QRect( 140, 90, 61, 21 ) );
    zoomStart->setMaxValue( 704 );
    tabWidget5_2->insertTab( tab, QString::fromLatin1("") );

    tab_2 = new QWidget( tabWidget5_2, "tab_2" );

    useThresh = new QCheckBox( tab_2, "useThresh" );
    useThresh->setGeometry( QRect( 50, 20, 90, 20 ) );

    loLim = new QLineEdit( tab_2, "loLim" );
    loLim->setEnabled( FALSE );
    loLim->setGeometry( QRect( 70, 50, 81, 21 ) );

    textLabel1_6 = new QLabel( tab_2, "textLabel1_6" );
    textLabel1_6->setGeometry( QRect( 40, 50, 30, 20 ) );

    textLabel1_6_2 = new QLabel( tab_2, "textLabel1_6_2" );
    textLabel1_6_2->setGeometry( QRect( 50, 80, 20, 20 ) );

    hiLim = new QLineEdit( tab_2, "hiLim" );
    hiLim->setEnabled( FALSE );
    hiLim->setGeometry( QRect( 70, 80, 81, 21 ) );

    applyDispThreshButton = new QPushButton( tab_2, "applyDispThreshButton" );
    applyDispThreshButton->setGeometry( QRect( 60, 110, 81, 21 ) );
    tabWidget5_2->insertTab( tab_2, QString::fromLatin1("") );

    tabWidget2 = new QTabWidget( this, "tabWidget2" );
    tabWidget2->setGeometry( QRect( 280, 540, 760, 270 ) );

    tab_3 = new QWidget( tabWidget2, "tab_3" );

    TabWidget = new QTabWidget( tab_3, "TabWidget" );
    TabWidget->setEnabled( TRUE );
    TabWidget->setGeometry( QRect( 10, 20, 740, 230 ) );

    tab_4 = new QWidget( TabWidget, "tab_4" );

    evPreset = new QSpinBox( tab_4, "evPreset" );
    evPreset->setEnabled( FALSE );
    evPreset->setGeometry( QRect( 120, 60, 121, 21 ) );
    evPreset->setMaxValue( 1000000000 );

    textLabel1_10_2 = new QLabel( tab_4, "textLabel1_10_2" );
    textLabel1_10_2->setGeometry( QRect( 10, 130, 90, 20 ) );

    eResetButton = new QPushButton( tab_4, "eResetButton" );
    eResetButton->setGeometry( QRect( 350, 60, 20, 20 ) );
    eResetButton->setToggleButton( FALSE );

    m1Preset = new QSpinBox( tab_4, "m1Preset" );
    m1Preset->setEnabled( FALSE );
    m1Preset->setGeometry( QRect( 120, 110, 121, 21 ) );
    m1Preset->setMaxValue( 1000000000 );

    tPresetButton = new QPushButton( tab_4, "tPresetButton" );
    tPresetButton->setGeometry( QRect( 100, 30, 20, 20 ) );
    tPresetButton->setToggleButton( TRUE );

    monRate2 = new QLabel( tab_4, "monRate2" );
    monRate2->setGeometry( QRect( 260, 170, 80, 20 ) );
    monRate2->setAlignment( int( QLabel::AlignVCenter | QLabel::AlignRight ) );

    textLabel1_2_3_2_3 = new QLabel( tab_4, "textLabel1_2_3_2_3" );
    textLabel1_2_3_2_3->setGeometry( QRect( 10, 10, 80, 20 ) );

    monitor2 = new QLabel( tab_4, "monitor2" );
    monitor2->setGeometry( QRect( 260, 150, 80, 20 ) );
    monitor2->setAlignment( int( QLabel::AlignVCenter | QLabel::AlignRight ) );

    m1PresetButton = new QPushButton( tab_4, "m1PresetButton" );
    m1PresetButton->setGeometry( QRect( 100, 110, 20, 20 ) );
    m1PresetButton->setToggleButton( TRUE );

    monRate1 = new QLabel( tab_4, "monRate1" );
    monRate1->setGeometry( QRect( 260, 130, 80, 20 ) );
    monRate1->setAlignment( int( QLabel::AlignVCenter | QLabel::AlignRight ) );

    tSecsText = new QLabel( tab_4, "tSecsText" );
    tSecsText->setGeometry( QRect( 250, 30, 90, 20 ) );
    tSecsText->setAlignment( int( QLabel::AlignVCenter | QLabel::AlignRight ) );

    ePresetButton = new QPushButton( tab_4, "ePresetButton" );
    ePresetButton->setGeometry( QRect( 100, 60, 20, 20 ) );
    ePresetButton->setToggleButton( TRUE );

    textLabel1_2_3_2_3_2 = new QLabel( tab_4, "textLabel1_2_3_2_3_2" );
    textLabel1_2_3_2_3_2->setGeometry( QRect( 10, 30, 80, 20 ) );

    m2RresetButton = new QPushButton( tab_4, "m2RresetButton" );
    m2RresetButton->setGeometry( QRect( 350, 150, 20, 20 ) );
    m2RresetButton->setToggleButton( FALSE );

    textLabel1_10_2_2 = new QLabel( tab_4, "textLabel1_10_2_2" );
    textLabel1_10_2_2->setGeometry( QRect( 10, 170, 90, 20 ) );

    mTimeText = new QLabel( tab_4, "mTimeText" );
    mTimeText->setGeometry( QRect( 250, 10, 90, 20 ) );
    mTimeText->setAlignment( int( QLabel::AlignVCenter | QLabel::AlignRight ) );

    textLabel1_11 = new QLabel( tab_4, "textLabel1_11" );
    textLabel1_11->setGeometry( QRect( 10, 110, 90, 20 ) );

    monitor1 = new QLabel( tab_4, "monitor1" );
    monitor1->setGeometry( QRect( 260, 110, 80, 20 ) );
    monitor1->setAlignment( int( QLabel::AlignVCenter | QLabel::AlignRight ) );

    totalCounts = new QLabel( tab_4, "totalCounts" );
    totalCounts->setGeometry( QRect( 260, 60, 80, 20 ) );
    totalCounts->setAlignment( int( QLabel::AlignVCenter | QLabel::AlignRight ) );

    textLabel1_11_2 = new QLabel( tab_4, "textLabel1_11_2" );
    textLabel1_11_2->setGeometry( QRect( 10, 150, 90, 20 ) );

    textLabel1_10 = new QLabel( tab_4, "textLabel1_10" );
    textLabel1_10->setGeometry( QRect( 10, 80, 90, 20 ) );

    eventRate = new QLabel( tab_4, "eventRate" );
    eventRate->setGeometry( QRect( 260, 80, 80, 20 ) );
    eventRate->setAlignment( int( QLabel::AlignVCenter | QLabel::AlignRight ) );

    m2Preset = new QSpinBox( tab_4, "m2Preset" );
    m2Preset->setEnabled( FALSE );
    m2Preset->setGeometry( QRect( 120, 150, 121, 21 ) );
    m2Preset->setMaxValue( 1000000000 );

    tPreset = new QSpinBox( tab_4, "tPreset" );
    tPreset->setEnabled( FALSE );
    tPreset->setGeometry( QRect( 120, 30, 121, 21 ) );
    tPreset->setMaxValue( 1000000000 );

    m1ResetButton = new QPushButton( tab_4, "m1ResetButton" );
    m1ResetButton->setGeometry( QRect( 350, 110, 20, 20 ) );
    m1ResetButton->setToggleButton( FALSE );

    tResetButton = new QPushButton( tab_4, "tResetButton" );
    tResetButton->setGeometry( QRect( 350, 30, 20, 20 ) );
    tResetButton->setToggleButton( FALSE );

    m2PresetButton = new QPushButton( tab_4, "m2PresetButton" );
    m2PresetButton->setGeometry( QRect( 100, 150, 20, 20 ) );
    m2PresetButton->setToggleButton( TRUE );

    textLabel1 = new QLabel( tab_4, "textLabel1" );
    textLabel1->setGeometry( QRect( 10, 60, 90, 20 ) );

    cpuMon1box = new QSpinBox( tab_4, "cpuMon1box" );
    cpuMon1box->setGeometry( QRect( 440, 110, 41, 21 ) );
    cpuMon1box->setMaxValue( 7 );

    cpuMon2box = new QSpinBox( tab_4, "cpuMon2box" );
    cpuMon2box->setGeometry( QRect( 440, 150, 41, 21 ) );
    cpuMon2box->setMaxValue( 7 );

    textLabel1_15 = new QLabel( tab_4, "textLabel1_15" );
    textLabel1_15->setGeometry( QRect( 430, 90, 58, 21 ) );

    textLabel1_15_2 = new QLabel( tab_4, "textLabel1_15_2" );
    textLabel1_15_2->setGeometry( QRect( 490, 90, 58, 21 ) );

    counterMon2box = new QSpinBox( tab_4, "counterMon2box" );
    counterMon2box->setGeometry( QRect( 500, 150, 41, 21 ) );
    counterMon2box->setMaxValue( 5 );
    counterMon2box->setValue( 1 );

    counterMon1box = new QSpinBox( tab_4, "counterMon1box" );
    counterMon1box->setGeometry( QRect( 500, 110, 41, 21 ) );
    counterMon1box->setMaxValue( 5 );
    TabWidget->insertTab( tab_4, QString::fromLatin1("") );

    tab_5 = new QWidget( TabWidget, "tab_5" );

    textLabel1_2_3 = new QLabel( tab_5, "textLabel1_2_3" );
    textLabel1_2_3->setGeometry( QRect( 10, 30, 118, 20 ) );

    textLabel1_2 = new QLabel( tab_5, "textLabel1_2" );
    textLabel1_2->setGeometry( QRect( 10, 10, 135, 20 ) );

    cmdTx = new QLabel( tab_5, "cmdTx" );
    cmdTx->setGeometry( QRect( 260, 10, 75, 20 ) );
    cmdTx->setAlignment( int( QLabel::AlignVCenter | QLabel::AlignRight ) );

    cmdRx = new QLabel( tab_5, "cmdRx" );
    cmdRx->setGeometry( QRect( 260, 30, 75, 20 ) );
    cmdRx->setAlignment( int( QLabel::AlignVCenter | QLabel::AlignRight ) );

    textLabel1_2_2 = new QLabel( tab_5, "textLabel1_2_2" );
    textLabel1_2_2->setGeometry( QRect( 10, 50, 135, 20 ) );

    dataRx = new QLabel( tab_5, "dataRx" );
    dataRx->setGeometry( QRect( 260, 50, 75, 20 ) );
    dataRx->setAlignment( int( QLabel::AlignVCenter | QLabel::AlignRight ) );
    TabWidget->insertTab( tab_5, QString::fromLatin1("") );

    TabPage = new QWidget( TabWidget, "TabPage" );

    textLabel1_12 = new QLabel( TabPage, "textLabel1_12" );
    textLabel1_12->setGeometry( QRect( 10, 10, 58, 21 ) );

    textLabel1_12_2 = new QLabel( TabPage, "textLabel1_12_2" );
    textLabel1_12_2->setGeometry( QRect( 10, 30, 58, 21 ) );

    textLabel1_12_2_2 = new QLabel( TabPage, "textLabel1_12_2_2" );
    textLabel1_12_2_2->setGeometry( QRect( 10, 50, 58, 21 ) );

    caressHeight = new QLabel( TabPage, "caressHeight" );
    caressHeight->setGeometry( QRect( 90, 10, 58, 21 ) );

    caressWidth = new QLabel( TabPage, "caressWidth" );
    caressWidth->setGeometry( QRect( 90, 30, 58, 21 ) );

    caressRun = new QLabel( TabPage, "caressRun" );
    caressRun->setGeometry( QRect( 90, 50, 58, 21 ) );

    textLabel1_13 = new QLabel( TabPage, "textLabel1_13" );
    textLabel1_13->setGeometry( QRect( 310, 0, 171, 16 ) );

    caressEdit = new QTextEdit( TabPage, "caressEdit" );
    caressEdit->setEnabled( TRUE );
    caressEdit->setGeometry( QRect( 310, 20, 420, 170 ) );
    caressEdit->setReadOnly( TRUE );
    TabWidget->insertTab( TabPage, QString::fromLatin1("") );
    tabWidget2->insertTab( tab_3, QString::fromLatin1("") );

    tab_6 = new QWidget( tabWidget2, "tab_6" );

    textLabel1_5_2 = new QLabel( tab_6, "textLabel1_5_2" );
    textLabel1_5_2->setGeometry( QRect( 10, 20, 20, 20 ) );

    groupBox38 = new QGroupBox( tab_6, "groupBox38" );
    groupBox38->setGeometry( QRect( 0, 70, 100, 160 ) );

    searchMcpdButton1 = new QPushButton( groupBox38, "searchMcpdButton1" );
    searchMcpdButton1->setGeometry( QRect( 10, 120, 61, 21 ) );

    mcpdStatusText1 = new QLabel( groupBox38, "mcpdStatusText1" );
    mcpdStatusText1->setGeometry( QRect( 10, 60, 61, 16 ) );

    mcpdConfigText1 = new QLabel( groupBox38, "mcpdConfigText1" );
    mcpdConfigText1->setGeometry( QRect( 10, 30, 82, 16 ) );

    mcpdMasterText1 = new QLabel( groupBox38, "mcpdMasterText1" );
    mcpdMasterText1->setGeometry( QRect( 10, 90, 61, 16 ) );

    tabWidget5 = new QTabWidget( tab_6, "tabWidget5" );
    tabWidget5->setGeometry( QRect( 100, 20, 620, 210 ) );

    tab_7 = new QWidget( tabWidget5, "tab_7" );

    groupBox9 = new QGroupBox( tab_7, "groupBox9" );
    groupBox9->setGeometry( QRect( 10, 10, 360, 70 ) );

    textLabel1_7 = new QLabel( groupBox9, "textLabel1_7" );
    textLabel1_7->setGeometry( QRect( 10, 20, 30, 16 ) );

    textLabel1_7_3 = new QLabel( groupBox9, "textLabel1_7_3" );
    textLabel1_7_3->setGeometry( QRect( 110, 20, 41, 16 ) );

    textLabel1_7_2 = new QLabel( groupBox9, "textLabel1_7_2" );
    textLabel1_7_2->setGeometry( QRect( 210, 20, 54, 16 ) );

    sendCellButton = new QPushButton( groupBox9, "sendCellButton" );
    sendCellButton->setGeometry( QRect( 280, 40, 61, 21 ) );

    cellSource = new QComboBox( FALSE, groupBox9, "cellSource" );
    cellSource->setGeometry( QRect( 10, 40, 90, 20 ) );

    cellTrigger = new QComboBox( FALSE, groupBox9, "cellTrigger" );
    cellTrigger->setGeometry( QRect( 110, 40, 90, 20 ) );

    cellCompare = new QSpinBox( groupBox9, "cellCompare" );
    cellCompare->setGeometry( QRect( 210, 40, 50, 20 ) );
    cellCompare->setMaxValue( 22 );

    groupBox16 = new QGroupBox( tab_7, "groupBox16" );
    groupBox16->setGeometry( QRect( 380, 10, 171, 70 ) );

    statusStream = new QCheckBox( groupBox16, "statusStream" );
    statusStream->setGeometry( QRect( 10, 30, 70, 21 ) );

    setStream = new QPushButton( groupBox16, "setStream" );
    setStream->setGeometry( QRect( 90, 29, 61, 21 ) );

    groupBox9_2 = new QGroupBox( tab_7, "groupBox9_2" );
    groupBox9_2->setGeometry( QRect( 10, 90, 250, 70 ) );

    textLabel1_7_4 = new QLabel( groupBox9_2, "textLabel1_7_4" );
    textLabel1_7_4->setGeometry( QRect( 20, 20, 34, 16 ) );

    textLabel1_7_3_2 = new QLabel( groupBox9_2, "textLabel1_7_3_2" );
    textLabel1_7_3_2->setGeometry( QRect( 80, 20, 54, 16 ) );

    sendAux = new QPushButton( groupBox9_2, "sendAux" );
    sendAux->setGeometry( QRect( 180, 40, 61, 21 ) );

    timer = new QSpinBox( groupBox9_2, "timer" );
    timer->setGeometry( QRect( 20, 40, 40, 20 ) );
    timer->setMaxValue( 3 );

    compareAux = new QLineEdit( groupBox9_2, "compareAux" );
    compareAux->setGeometry( QRect( 80, 40, 80, 21 ) );

    groupBox9_2_2 = new QGroupBox( tab_7, "groupBox9_2_2" );
    groupBox9_2_2->setGeometry( QRect( 280, 90, 270, 70 ) );

    textLabel1_7_4_2_2 = new QLabel( groupBox9_2_2, "textLabel1_7_4_2_2" );
    textLabel1_7_4_2_2->setGeometry( QRect( 80, 20, 41, 16 ) );

    textLabel1_7_4_2 = new QLabel( groupBox9_2_2, "textLabel1_7_4_2" );
    textLabel1_7_4_2->setGeometry( QRect( 20, 20, 60, 16 ) );

    sendParam = new QPushButton( groupBox9_2_2, "sendParam" );
    sendParam->setGeometry( QRect( 190, 40, 61, 21 ) );

    paramSource = new QComboBox( FALSE, groupBox9_2_2, "paramSource" );
    paramSource->setGeometry( QRect( 80, 40, 90, 20 ) );

    param = new QSpinBox( groupBox9_2_2, "param" );
    param->setGeometry( QRect( 20, 40, 40, 20 ) );
    param->setMaxValue( 3 );
    tabWidget5->insertTab( tab_7, QString::fromLatin1("") );

    tab_8 = new QWidget( tabWidget5, "tab_8" );

    groupBox30 = new QGroupBox( tab_8, "groupBox30" );
    groupBox30->setGeometry( QRect( 10, 80, 130, 90 ) );

    master = new QCheckBox( groupBox30, "master" );
    master->setGeometry( QRect( 20, 20, 70, 20 ) );
    master->setChecked( TRUE );

    terminate = new QCheckBox( groupBox30, "terminate" );
    terminate->setEnabled( FALSE );
    terminate->setGeometry( QRect( 20, 40, 80, 20 ) );
    terminate->setChecked( TRUE );

    resetTimer = new QPushButton( groupBox30, "resetTimer" );
    resetTimer->setGeometry( QRect( 20, 60, 91, 20 ) );

    groupBox29 = new QGroupBox( tab_8, "groupBox29" );
    groupBox29->setGeometry( QRect( 10, 10, 130, 60 ) );

    deviceId = new QSpinBox( groupBox29, "deviceId" );
    deviceId->setGeometry( QRect( 10, 20, 41, 21 ) );

    setID = new QPushButton( groupBox29, "setID" );
    setID->setGeometry( QRect( 70, 20, 41, 21 ) );

    groupBox6 = new QGroupBox( tab_8, "groupBox6" );
    groupBox6->setGeometry( QRect( 150, 10, 460, 160 ) );

    textLabel1_3_3_2 = new QLabel( groupBox6, "textLabel1_3_3_2" );
    textLabel1_3_3_2->setGeometry( QRect( 310, 10, 50, 21 ) );

    textLabel1_3_3_2_2 = new QLabel( groupBox6, "textLabel1_3_3_2_2" );
    textLabel1_3_3_2_2->setGeometry( QRect( 160, 10, 61, 21 ) );

    mcpdIpAddress2 = new QLineEdit( groupBox6, "mcpdIpAddress2" );
    mcpdIpAddress2->setEnabled( FALSE );
    mcpdIpAddress2->setGeometry( QRect( 220, 40, 30, 20 ) );

    cmdIpAddress0 = new QLineEdit( groupBox6, "cmdIpAddress0" );
    cmdIpAddress0->setEnabled( FALSE );
    cmdIpAddress0->setGeometry( QRect( 140, 100, 30, 20 ) );

    textLabel1_3_2_2_2 = new QLabel( groupBox6, "textLabel1_3_2_2_2" );
    textLabel1_3_2_2_2->setGeometry( QRect( 10, 100, 61, 21 ) );

    dataIpAddress2 = new QLineEdit( groupBox6, "dataIpAddress2" );
    dataIpAddress2->setEnabled( FALSE );
    dataIpAddress2->setGeometry( QRect( 220, 70, 30, 20 ) );

    dataIpAddress1 = new QLineEdit( groupBox6, "dataIpAddress1" );
    dataIpAddress1->setEnabled( FALSE );
    dataIpAddress1->setGeometry( QRect( 180, 70, 30, 20 ) );

    dataIpAddress0 = new QLineEdit( groupBox6, "dataIpAddress0" );
    dataIpAddress0->setEnabled( FALSE );
    dataIpAddress0->setGeometry( QRect( 140, 70, 30, 20 ) );

    mcpdIpAddress1 = new QLineEdit( groupBox6, "mcpdIpAddress1" );
    mcpdIpAddress1->setEnabled( FALSE );
    mcpdIpAddress1->setGeometry( QRect( 180, 40, 30, 20 ) );

    cmdIpAddress2 = new QLineEdit( groupBox6, "cmdIpAddress2" );
    cmdIpAddress2->setEnabled( FALSE );
    cmdIpAddress2->setGeometry( QRect( 220, 100, 30, 20 ) );

    mcpdIpAddress3 = new QLineEdit( groupBox6, "mcpdIpAddress3" );
    mcpdIpAddress3->setEnabled( FALSE );
    mcpdIpAddress3->setGeometry( QRect( 260, 40, 30, 20 ) );

    mcpdIpAddress0 = new QLineEdit( groupBox6, "mcpdIpAddress0" );
    mcpdIpAddress0->setEnabled( FALSE );
    mcpdIpAddress0->setGeometry( QRect( 140, 40, 30, 20 ) );

    cmdThisPc = new QCheckBox( groupBox6, "cmdThisPc" );
    cmdThisPc->setGeometry( QRect( 70, 100, 60, 20 ) );
    cmdThisPc->setChecked( TRUE );

    cmdUdpPort = new QSpinBox( groupBox6, "cmdUdpPort" );
    cmdUdpPort->setGeometry( QRect( 300, 100, 60, 21 ) );
    cmdUdpPort->setMaxValue( 65536 );
    cmdUdpPort->setValue( 0 );

    cmdIpAddress3 = new QLineEdit( groupBox6, "cmdIpAddress3" );
    cmdIpAddress3->setEnabled( FALSE );
    cmdIpAddress3->setGeometry( QRect( 260, 100, 30, 20 ) );

    cmdIpAddress1 = new QLineEdit( groupBox6, "cmdIpAddress1" );
    cmdIpAddress1->setEnabled( FALSE );
    cmdIpAddress1->setGeometry( QRect( 180, 100, 30, 20 ) );

    textLabel1_3_2_2 = new QLabel( groupBox6, "textLabel1_3_2_2" );
    textLabel1_3_2_2->setGeometry( QRect( 10, 40, 61, 21 ) );

    dataUdpPort = new QSpinBox( groupBox6, "dataUdpPort" );
    dataUdpPort->setGeometry( QRect( 300, 70, 60, 21 ) );
    dataUdpPort->setMaxValue( 65536 );
    dataUdpPort->setValue( 0 );

    textLabel1_3_2 = new QLabel( groupBox6, "textLabel1_3_2" );
    textLabel1_3_2->setGeometry( QRect( 10, 70, 61, 21 ) );

    setIP = new QPushButton( groupBox6, "setIP" );
    setIP->setGeometry( QRect( 370, 70, 80, 30 ) );

    dataIpAddress3 = new QLineEdit( groupBox6, "dataIpAddress3" );
    dataIpAddress3->setEnabled( FALSE );
    dataIpAddress3->setGeometry( QRect( 260, 70, 30, 20 ) );

    dataThisPc = new QCheckBox( groupBox6, "dataThisPc" );
    dataThisPc->setGeometry( QRect( 70, 70, 60, 20 ) );
    dataThisPc->setChecked( TRUE );

    textLabel1_3_2_2_2_2 = new QLabel( groupBox6, "textLabel1_3_2_2_2_2" );
    textLabel1_3_2_2_2_2->setGeometry( QRect( 10, 130, 61, 21 ) );

    mIpAddress1 = new QLineEdit( groupBox6, "mIpAddress1" );
    mIpAddress1->setEnabled( FALSE );
    mIpAddress1->setGeometry( QRect( 180, 130, 30, 20 ) );

    mIpAddress2 = new QLineEdit( groupBox6, "mIpAddress2" );
    mIpAddress2->setEnabled( FALSE );
    mIpAddress2->setGeometry( QRect( 220, 130, 30, 20 ) );

    modifyIp = new QCheckBox( groupBox6, "modifyIp" );
    modifyIp->setGeometry( QRect( 70, 40, 60, 20 ) );
    modifyIp->setChecked( FALSE );

    mIpAddress3 = new QLineEdit( groupBox6, "mIpAddress3" );
    mIpAddress3->setEnabled( FALSE );
    mIpAddress3->setGeometry( QRect( 260, 130, 30, 20 ) );

    modifyMIp = new QCheckBox( groupBox6, "modifyMIp" );
    modifyMIp->setGeometry( QRect( 70, 130, 60, 20 ) );
    modifyMIp->setChecked( FALSE );

    applyMIp = new QPushButton( groupBox6, "applyMIp" );
    applyMIp->setEnabled( FALSE );
    applyMIp->setGeometry( QRect( 300, 130, 50, 21 ) );

    mIpAddress0 = new QLineEdit( groupBox6, "mIpAddress0" );
    mIpAddress0->setEnabled( FALSE );
    mIpAddress0->setGeometry( QRect( 140, 130, 30, 20 ) );
    tabWidget5->insertTab( tab_8, QString::fromLatin1("") );

    TabPage_2 = new QWidget( tabWidget5, "TabPage_2" );

    textLabel1_3 = new QLabel( TabPage_2, "textLabel1_3" );
    textLabel1_3->setGeometry( QRect( 20, 70, 30, 21 ) );

    textLabel1_3_4 = new QLabel( TabPage_2, "textLabel1_3_4" );
    textLabel1_3_4->setGeometry( QRect( 20, 110, 30, 21 ) );

    textLabel1_3_3 = new QLabel( TabPage_2, "textLabel1_3_3" );
    textLabel1_3_3->setGeometry( QRect( 20, 90, 30, 21 ) );

    param0 = new QLabel( TabPage_2, "param0" );
    param0->setGeometry( QRect( 150, 70, 110, 21 ) );

    param1 = new QLabel( TabPage_2, "param1" );
    param1->setGeometry( QRect( 150, 90, 110, 21 ) );

    textLabel1_2_3_2 = new QLabel( TabPage_2, "textLabel1_2_3_2" );
    textLabel1_2_3_2->setGeometry( QRect( 20, 150, 118, 20 ) );

    param2 = new QLabel( TabPage_2, "param2" );
    param2->setGeometry( QRect( 150, 110, 110, 21 ) );

    param3 = new QLabel( TabPage_2, "param3" );
    param3->setGeometry( QRect( 150, 130, 110, 21 ) );

    hTimeText = new QLabel( TabPage_2, "hTimeText" );
    hTimeText->setGeometry( QRect( 80, 150, 180, 20 ) );
    hTimeText->setAlignment( int( QLabel::AlignVCenter | QLabel::AlignRight ) );

    textLabel1_3_5 = new QLabel( TabPage_2, "textLabel1_3_5" );
    textLabel1_3_5->setGeometry( QRect( 20, 130, 30, 21 ) );
    tabWidget5->insertTab( TabPage_2, QString::fromLatin1("") );

    mcpdId = new QSpinBox( tab_6, "mcpdId" );
    mcpdId->setEnabled( TRUE );
    mcpdId->setGeometry( QRect( 10, 40, 61, 21 ) );
    mcpdId->setMaxValue( 7 );
    tabWidget2->insertTab( tab_6, QString::fromLatin1("") );

    TabPage_3 = new QWidget( tabWidget2, "TabPage_3" );

    tabWidget4 = new QTabWidget( TabPage_3, "tabWidget4" );
    tabWidget4->setGeometry( QRect( 9, 4, 720, 220 ) );

    tab_9 = new QWidget( tabWidget4, "tab_9" );

    groupBox17_2 = new QGroupBox( tab_9, "groupBox17_2" );
    groupBox17_2->setGeometry( QRect( 170, 20, 440, 61 ) );

    textLabel1_4 = new QLabel( groupBox17_2, "textLabel1_4" );
    textLabel1_4->setGeometry( QRect( 20, 20, 20, 16 ) );

    textLabel1_4_10 = new QLabel( groupBox17_2, "textLabel1_4_10" );
    textLabel1_4_10->setGeometry( QRect( 60, 20, 20, 16 ) );

    textLabel1_4_9 = new QLabel( groupBox17_2, "textLabel1_4_9" );
    textLabel1_4_9->setGeometry( QRect( 100, 20, 20, 16 ) );

    textLabel1_4_8 = new QLabel( groupBox17_2, "textLabel1_4_8" );
    textLabel1_4_8->setGeometry( QRect( 140, 20, 20, 16 ) );

    textLabel1_4_7 = new QLabel( groupBox17_2, "textLabel1_4_7" );
    textLabel1_4_7->setGeometry( QRect( 180, 20, 20, 16 ) );

    textLabel1_4_6 = new QLabel( groupBox17_2, "textLabel1_4_6" );
    textLabel1_4_6->setGeometry( QRect( 220, 20, 20, 16 ) );

    textLabel1_4_5 = new QLabel( groupBox17_2, "textLabel1_4_5" );
    textLabel1_4_5->setGeometry( QRect( 260, 20, 20, 16 ) );

    textLabel1_4_4 = new QLabel( groupBox17_2, "textLabel1_4_4" );
    textLabel1_4_4->setGeometry( QRect( 300, 20, 20, 16 ) );

    status3 = new QLabel( groupBox17_2, "status3" );
    status3->setGeometry( QRect( 140, 40, 40, 16 ) );

    status2 = new QLabel( groupBox17_2, "status2" );
    status2->setGeometry( QRect( 100, 40, 40, 16 ) );

    status1 = new QLabel( groupBox17_2, "status1" );
    status1->setGeometry( QRect( 60, 40, 40, 16 ) );

    status4 = new QLabel( groupBox17_2, "status4" );
    status4->setGeometry( QRect( 180, 40, 40, 16 ) );

    status5 = new QLabel( groupBox17_2, "status5" );
    status5->setGeometry( QRect( 220, 40, 40, 16 ) );

    status6 = new QLabel( groupBox17_2, "status6" );
    status6->setGeometry( QRect( 260, 40, 40, 16 ) );

    status7 = new QLabel( groupBox17_2, "status7" );
    status7->setGeometry( QRect( 300, 40, 40, 16 ) );

    scanPeri = new QPushButton( groupBox17_2, "scanPeri" );
    scanPeri->setGeometry( QRect( 350, 20, 80, 21 ) );

    status0 = new QLabel( groupBox17_2, "status0" );
    status0->setGeometry( QRect( 20, 40, 40, 16 ) );

    groupBox39 = new QGroupBox( tab_9, "groupBox39" );
    groupBox39->setEnabled( FALSE );
    groupBox39->setGeometry( QRect( 27, 115, 330, 50 ) );

    readRegisterButton = new QPushButton( groupBox39, "readRegisterButton" );
    readRegisterButton->setGeometry( QRect( 110, 20, 81, 21 ) );

    registerSelect = new QSpinBox( groupBox39, "registerSelect" );
    registerSelect->setGeometry( QRect( 200, 20, 40, 21 ) );
    registerSelect->setMaxValue( 2 );

    registerValue = new QLineEdit( groupBox39, "registerValue" );
    registerValue->setGeometry( QRect( 250, 20, 71, 20 ) );

    writeRegisterButton = new QPushButton( groupBox39, "writeRegisterButton" );
    writeRegisterButton->setGeometry( QRect( 20, 20, 81, 21 ) );

    textLabel1_4_2_4 = new QLabel( tab_9, "textLabel1_4_2_4" );
    textLabel1_4_2_4->setGeometry( QRect( 10, 30, 63, 21 ) );

    textLabel1_14_2 = new QLabel( tab_9, "textLabel1_14_2" );
    textLabel1_14_2->setGeometry( QRect( 10, 60, 61, 16 ) );

    mcpdStatusText2 = new QLabel( tab_9, "mcpdStatusText2" );
    mcpdStatusText2->setGeometry( QRect( 80, 60, 61, 16 ) );

    devid_2 = new QSpinBox( tab_9, "devid_2" );
    devid_2->setEnabled( TRUE );
    devid_2->setGeometry( QRect( 80, 30, 50, 21 ) );
    devid_2->setMaxValue( 7 );
    tabWidget4->insertTab( tab_9, QString::fromLatin1("") );

    tab_10 = new QWidget( tabWidget4, "tab_10" );

    textLabel1_4_2_2 = new QLabel( tab_10, "textLabel1_4_2_2" );
    textLabel1_4_2_2->setGeometry( QRect( 10, 50, 47, 29 ) );

    groupBox13 = new QGroupBox( tab_10, "groupBox13" );
    groupBox13->setGeometry( QRect( 150, 90, 560, 80 ) );

    textLabel1_4_2_3_2 = new QLabel( groupBox13, "textLabel1_4_2_3_2" );
    textLabel1_4_2_3_2->setGeometry( QRect( 20, 20, 32, 21 ) );

    textLabel1_4_2_3_3 = new QLabel( groupBox13, "textLabel1_4_2_3_3" );
    textLabel1_4_2_3_3->setGeometry( QRect( 20, 50, 58, 21 ) );

    setThreshold = new QPushButton( groupBox13, "setThreshold" );
    setThreshold->setGeometry( QRect( 460, 50, 80, 21 ) );

    textLabel1_4_2_3 = new QLabel( groupBox13, "textLabel1_4_2_3" );
    textLabel1_4_2_3->setGeometry( QRect( 180, 20, 32, 21 ) );

    gain = new QLineEdit( groupBox13, "gain" );
    gain->setGeometry( QRect( 380, 20, 50, 20 ) );
    gain->setCursorPosition( 0 );

    textLabel1_4_2_3_3_3 = new QLabel( groupBox13, "textLabel1_4_2_3_3_3" );
    textLabel1_4_2_3_3_3->setGeometry( QRect( 290, 20, 84, 21 ) );

    threshold = new QLineEdit( groupBox13, "threshold" );
    threshold->setGeometry( QRect( 380, 50, 50, 20 ) );

    setGain = new QPushButton( groupBox13, "setGain" );
    setGain->setGeometry( QRect( 460, 20, 80, 21 ) );

    textLabel1_4_2_3_3_2 = new QLabel( groupBox13, "textLabel1_4_2_3_3_2" );
    textLabel1_4_2_3_3_2->setGeometry( QRect( 290, 50, 80, 21 ) );

    comgain = new QCheckBox( groupBox13, "comgain" );
    comgain->setGeometry( QRect( 90, 20, 80, 20 ) );
    comgain->setChecked( TRUE );

    channel = new QSpinBox( groupBox13, "channel" );
    channel->setEnabled( FALSE );
    channel->setGeometry( QRect( 220, 20, 50, 21 ) );
    channel->setMaxValue( 255 );

    groupBox35 = new QGroupBox( tab_10, "groupBox35" );
    groupBox35->setGeometry( QRect( 150, 10, 560, 70 ) );

    textLabel1_4_2_3_4 = new QLabel( groupBox35, "textLabel1_4_2_3_4" );
    textLabel1_4_2_3_4->setGeometry( QRect( 90, 30, 50, 21 ) );

    buttonGroup5 = new QButtonGroup( groupBox35, "buttonGroup5" );
    buttonGroup5->setGeometry( QRect( 200, 10, 150, 50 ) );

    pulsAmp2 = new QLineEdit( buttonGroup5, "pulsAmp2" );
    pulsAmp2->setEnabled( FALSE );
    pulsAmp2->setGeometry( QRect( 100, 20, 40, 20 ) );
    pulsAmp2->setCursorPosition( 2 );

    pulsampRadio1 = new QRadioButton( buttonGroup5, "pulsampRadio1" );
    pulsampRadio1->setGeometry( QRect( 10, 20, 16, 16 ) );
    pulsampRadio1->setChecked( TRUE );

    pulsampRadio2 = new QRadioButton( buttonGroup5, "pulsampRadio2" );
    pulsampRadio2->setGeometry( QRect( 80, 20, 16, 16 ) );
    pulsampRadio2->setChecked( FALSE );
    buttonGroup5->insert( pulsampRadio2, 1 );

    pulsAmp1 = new QLineEdit( buttonGroup5, "pulsAmp1" );
    pulsAmp1->setGeometry( QRect( 30, 20, 40, 20 ) );
    pulsAmp1->setCursorPosition( 2 );

    pulserButton = new QPushButton( groupBox35, "pulserButton" );
    pulserButton->setGeometry( QRect( 17, 24, 61, 31 ) );
    pulserButton->setToggleButton( TRUE );

    pulsChan = new QSpinBox( groupBox35, "pulsChan" );
    pulsChan->setGeometry( QRect( 140, 30, 40, 21 ) );
    pulsChan->setMaxValue( 7 );

    buttonGroup4 = new QButtonGroup( groupBox35, "buttonGroup4" );
    buttonGroup4->setGeometry( QRect( 360, 10, 181, 51 ) );

    pulsLeft = new QRadioButton( buttonGroup4, "pulsLeft" );
    pulsLeft->setGeometry( QRect( 10, 20, 40, 21 ) );

    pulsMid = new QRadioButton( buttonGroup4, "pulsMid" );
    pulsMid->setGeometry( QRect( 60, 20, 40, 21 ) );
    pulsMid->setChecked( TRUE );
    buttonGroup4->insert( pulsMid, 2 );

    pulsRight = new QRadioButton( buttonGroup4, "pulsRight" );
    pulsRight->setGeometry( QRect( 110, 20, 50, 21 ) );
    buttonGroup4->insert( pulsRight, 1 );

    modeGroup = new QButtonGroup( tab_10, "modeGroup" );
    modeGroup->setGeometry( QRect( 10, 110, 130, 60 ) );

    pos = new QRadioButton( modeGroup, "pos" );
    pos->setGeometry( QRect( 10, 20, 70, 16 ) );
    pos->setChecked( TRUE );
    modeGroup->insert( pos, 0 );

    amp = new QRadioButton( modeGroup, "amp" );
    amp->setGeometry( QRect( 10, 40, 80, 16 ) );
    modeGroup->insert( amp, 1 );

    textLabel1_4_2 = new QLabel( tab_10, "textLabel1_4_2" );
    textLabel1_4_2->setGeometry( QRect( 10, 20, 63, 21 ) );

    mpsdDeviceText = new QLabel( tab_10, "mpsdDeviceText" );
    mpsdDeviceText->setGeometry( QRect( 10, 80, 80, 21 ) );

    devid = new QSpinBox( tab_10, "devid" );
    devid->setEnabled( TRUE );
    devid->setGeometry( QRect( 80, 20, 50, 21 ) );
    devid->setMaxValue( 7 );

    module = new QSpinBox( tab_10, "module" );
    module->setGeometry( QRect( 80, 50, 50, 21 ) );
    module->setMaxValue( 7 );
    tabWidget4->insertTab( tab_10, QString::fromLatin1("") );
    tabWidget2->insertTab( TabPage_3, QString::fromLatin1("") );

    TabPage_4 = new QWidget( tabWidget2, "TabPage_4" );

    groupBox36 = new QGroupBox( TabPage_4, "groupBox36" );
    groupBox36->setGeometry( QRect( 490, 10, 261, 90 ) );

    textLabel2_2_2 = new QLabel( groupBox36, "textLabel2_2_2" );
    textLabel2_2_2->setGeometry( QRect( 20, 50, 171, 16 ) );

    histfilename = new QLabel( groupBox36, "histfilename" );
    histfilename->setGeometry( QRect( 20, 70, 191, 16 ) );

    writeHistButton = new QPushButton( groupBox36, "writeHistButton" );
    writeHistButton->setEnabled( TRUE );
    writeHistButton->setGeometry( QRect( 20, 20, 50, 20 ) );

    LoadhistButton = new QPushButton( groupBox36, "LoadhistButton" );
    LoadhistButton->setEnabled( FALSE );
    LoadhistButton->setGeometry( QRect( 80, 20, 50, 20 ) );

    groupBox79_2 = new QGroupBox( TabPage_4, "groupBox79_2" );
    groupBox79_2->setGeometry( QRect( 10, 120, 240, 110 ) );

    restoreSetupButton = new QPushButton( groupBox79_2, "restoreSetupButton" );
    restoreSetupButton->setGeometry( QRect( 90, 20, 50, 26 ) );

    saveSetupButton = new QPushButton( groupBox79_2, "saveSetupButton" );
    saveSetupButton->setGeometry( QRect( 20, 20, 50, 26 ) );

    configfilename = new QLabel( groupBox79_2, "configfilename" );
    configfilename->setGeometry( QRect( 20, 70, 191, 21 ) );

    textLabel2_2 = new QLabel( groupBox79_2, "textLabel2_2" );
    textLabel2_2->setGeometry( QRect( 20, 50, 171, 20 ) );

    groupBox35_2 = new QGroupBox( TabPage_4, "groupBox35_2" );
    groupBox35_2->setGeometry( QRect( 260, 120, 431, 110 ) );

    textLabel1_9_3 = new QLabel( groupBox35_2, "textLabel1_9_3" );
    textLabel1_9_3->setGeometry( QRect( 10, 80, 70, 20 ) );

    textLabel1_9_2 = new QLabel( groupBox35_2, "textLabel1_9_2" );
    textLabel1_9_2->setGeometry( QRect( 10, 50, 70, 20 ) );

    textLabel1_9 = new QLabel( groupBox35_2, "textLabel1_9" );
    textLabel1_9->setGeometry( QRect( 10, 20, 90, 20 ) );

    listfilepath = new QLineEdit( groupBox35_2, "listfilepath" );
    listfilepath->setGeometry( QRect( 110, 20, 221, 20 ) );

    histfilepath = new QLineEdit( groupBox35_2, "histfilepath" );
    histfilepath->setGeometry( QRect( 110, 50, 221, 20 ) );

    configfilepath = new QLineEdit( groupBox35_2, "configfilepath" );
    configfilepath->setGeometry( QRect( 110, 80, 221, 20 ) );

    selectListpath = new QPushButton( groupBox35_2, "selectListpath" );
    selectListpath->setGeometry( QRect( 360, 20, 50, 20 ) );

    selectConfigpath = new QPushButton( groupBox35_2, "selectConfigpath" );
    selectConfigpath->setGeometry( QRect( 360, 80, 50, 20 ) );

    selectHistpath = new QPushButton( groupBox35_2, "selectHistpath" );
    selectHistpath->setGeometry( QRect( 360, 50, 50, 20 ) );

    groupBox79 = new QGroupBox( TabPage_4, "groupBox79" );
    groupBox79->setGeometry( QRect( 10, 10, 470, 100 ) );

    textLabel2_2_3 = new QLabel( groupBox79, "textLabel2_2_3" );
    textLabel2_2_3->setGeometry( QRect( 20, 50, 60, 20 ) );

    listFilename = new QLineEdit( groupBox79, "listFilename" );
    listFilename->setGeometry( QRect( 120, 20, 230, 26 ) );

    selectButton = new QPushButton( groupBox79, "selectButton" );
    selectButton->setGeometry( QRect( 380, 10, 50, 26 ) );

    replayButton = new QPushButton( groupBox79, "replayButton" );
    replayButton->setGeometry( QRect( 360, 40, 90, 26 ) );

    listfileComment = new QLineEdit( groupBox79, "listfileComment" );
    listfileComment->setGeometry( QRect( 20, 70, 430, 26 ) );

    acqListfile = new QCheckBox( groupBox79, "acqListfile" );
    acqListfile->setGeometry( QRect( 20, 20, 100, 20 ) );
    tabWidget2->insertTab( TabPage_4, QString::fromLatin1("") );

    TabPage_5 = new QWidget( tabWidget2, "TabPage_5" );

    groupBox15 = new QGroupBox( TabPage_5, "groupBox15" );
    groupBox15->setGeometry( QRect( 10, 10, 271, 51 ) );

    runId = new QSpinBox( groupBox15, "runId" );
    runId->setEnabled( FALSE );
    runId->setGeometry( QRect( 10, 20, 101, 21 ) );
    runId->setMaxValue( 65536 );

    runIdAuto = new QCheckBox( groupBox15, "runIdAuto" );
    runIdAuto->setGeometry( QRect( 120, 20, 70, 21 ) );
    runIdAuto->setChecked( TRUE );

    runIdButton = new QPushButton( groupBox15, "runIdButton" );
    runIdButton->setEnabled( FALSE );
    runIdButton->setGeometry( QRect( 200, 20, 61, 21 ) );

    groupBox20 = new QGroupBox( TabPage_5, "groupBox20" );
    groupBox20->setGeometry( QRect( 8, 74, 190, 70 ) );

    timingBox = new QSpinBox( groupBox20, "timingBox" );
    timingBox->setGeometry( QRect( 130, 30, 50, 20 ) );
    timingBox->setMaxValue( 48 );
    timingBox->setMinValue( 1 );

    textLabel1_8 = new QLabel( groupBox20, "textLabel1_8" );
    textLabel1_8->setGeometry( QRect( 20, 30, 79, 29 ) );
    tabWidget2->insertTab( TabPage_5, QString::fromLatin1("") );

    TabPage_6 = new QWidget( tabWidget2, "TabPage_6" );

    textLabel1_2_3_2_3_2_2 = new QLabel( TabPage_6, "textLabel1_2_3_2_3_2_2" );
    textLabel1_2_3_2_3_2_2->setGeometry( QRect( 10, 10, 112, 16 ) );

    clearLogButton = new QPushButton( TabPage_6, "clearLogButton" );
    clearLogButton->setGeometry( QRect( 670, 210, 71, 20 ) );

    debugLevelBox = new QComboBox( FALSE, TabPage_6, "debugLevelBox" );
    debugLevelBox->setGeometry( QRect( 660, 30, 90, 16 ) );

    protocolEdit = new QTextEdit( TabPage_6, "protocolEdit" );
    protocolEdit->setEnabled( TRUE );
    protocolEdit->setGeometry( QRect( 10, 30, 640, 200 ) );
    protocolEdit->setReadOnly( TRUE );
    tabWidget2->insertTab( TabPage_6, QString::fromLatin1("") );

    pulsertestButton = new QPushButton( this, "pulsertestButton" );
    pulsertestButton->setEnabled( TRUE );
    pulsertestButton->setGeometry( QRect( 1070, 780, 90, 21 ) );
    pulsertestButton->setToggleButton( TRUE );
    languageChange();
    resize( QSize(1280, 950).expandedTo(minimumSizeHint()) );
    clearWState( WState_Polished );

    // signals and slots connections
    connect( acqListfile, SIGNAL( toggled(bool) ), this, SLOT( acqListfileSlot() ) );
    connect( acqListfile, SIGNAL( toggled(bool) ), acquireFile, SLOT( setChecked(bool) ) );
    connect( acquireFile, SIGNAL( toggled(bool) ), acqListfile, SLOT( setChecked(bool) ) );
    connect( allPulsersoffButton, SIGNAL( clicked() ), this, SLOT( allPulserSlot() ) );
    connect( applyDispThreshButton, SIGNAL( clicked() ), this, SLOT( applyThreshSlot() ) );
    connect( applyMIp, SIGNAL( clicked() ), this, SLOT( applyMIpSlot() ) );
    connect( cellSource, SIGNAL( activated(int) ), this, SLOT( displayMcpdSlot() ) );
    connect( channel, SIGNAL( valueChanged(int) ), this, SLOT( displayMpsdSlot() ) );
    connect( clearAll, SIGNAL( clicked() ), this, SLOT( clearAllSlot() ) );
    connect( clearChan, SIGNAL( clicked() ), this, SLOT( clearChanSlot() ) );
    connect( clearMcpd, SIGNAL( clicked() ), this, SLOT( clearMcpdSlot() ) );
    connect( clearMpsd, SIGNAL( clicked() ), this, SLOT( clearMpsdSlot() ) );
    connect( cmdThisPc, SIGNAL( toggled(bool) ), cmdIpAddress0, SLOT( setDisabled(bool) ) );
    connect( cmdThisPc, SIGNAL( toggled(bool) ), cmdIpAddress1, SLOT( setDisabled(bool) ) );
    connect( cmdThisPc, SIGNAL( toggled(bool) ), cmdIpAddress2, SLOT( setDisabled(bool) ) );
    connect( cmdThisPc, SIGNAL( toggled(bool) ), cmdIpAddress3, SLOT( setDisabled(bool) ) );
    connect( comgain, SIGNAL( toggled(bool) ), channel, SLOT( setDisabled(bool) ) );
    connect( dataThisPc, SIGNAL( toggled(bool) ), dataIpAddress0, SLOT( setDisabled(bool) ) );
    connect( dataThisPc, SIGNAL( toggled(bool) ), dataIpAddress1, SLOT( setDisabled(bool) ) );
    connect( dataThisPc, SIGNAL( toggled(bool) ), dataIpAddress2, SLOT( setDisabled(bool) ) );
    connect( dataThisPc, SIGNAL( toggled(bool) ), dataIpAddress3, SLOT( setDisabled(bool) ) );
    connect( debugLevelBox, SIGNAL( activated(int) ), this, SLOT( debugLevelSlot(int) ) );
    connect( devid, SIGNAL( valueChanged(int) ), this, SLOT( displayMpsdSlot() ) );
    connect( devid, SIGNAL( valueChanged(int) ), devid_2, SLOT( setValue(int) ) );
    connect( devid_2, SIGNAL( valueChanged(int) ), devid, SLOT( setValue(int) ) );
    connect( devid_2, SIGNAL( valueChanged(int) ), this, SLOT( displayMpsdSlot() ) );
    connect( dispAll, SIGNAL( toggled(bool) ), dispMcpd, SLOT( setDisabled(bool) ) );
    connect( dispAll, SIGNAL( toggled(bool) ), dispMpsd, SLOT( setDisabled(bool) ) );
    connect( dispAll, SIGNAL( toggled(bool) ), dispChan, SLOT( setDisabled(bool) ) );
    connect( dispAll, SIGNAL( toggled(bool) ), clearMcpd, SLOT( setDisabled(bool) ) );
    connect( dispAll, SIGNAL( toggled(bool) ), clearMpsd, SLOT( setDisabled(bool) ) );
    connect( dispAll, SIGNAL( toggled(bool) ), clearChan, SLOT( setDisabled(bool) ) );
    connect( dispAll, SIGNAL( toggled(bool) ), buttonGroup10, SLOT( setEnabled(bool) ) );
    connect( ePresetButton, SIGNAL( toggled(bool) ), this, SLOT( ePresetSlot(bool) ) );
    connect( eResetButton, SIGNAL( clicked() ), this, SLOT( eResetSlot() ) );
    connect( logGroup, SIGNAL( toggled(bool) ), this, SLOT( redrawSlot() ) );
    connect( logGroup, SIGNAL( clicked(int) ), this, SLOT( linlogSlot() ) );
    connect( m1PresetButton, SIGNAL( toggled(bool) ), this, SLOT( m1PresetSlot(bool) ) );
    connect( m1ResetButton, SIGNAL( clicked() ), this, SLOT( m1ResetSlot() ) );
    connect( m2PresetButton, SIGNAL( toggled(bool) ), this, SLOT( m2PresetSlot(bool) ) );
    connect( m2RresetButton, SIGNAL( clicked() ), this, SLOT( m2ResetSlot() ) );
    connect( master, SIGNAL( toggled(bool) ), this, SLOT( setTimingSlot() ) );
    connect( master, SIGNAL( toggled(bool) ), terminate, SLOT( setDisabled(bool) ) );
    connect( master, SIGNAL( toggled(bool) ), resetTimer, SLOT( setEnabled(bool) ) );
    connect( master, SIGNAL( toggled(bool) ), terminate, SLOT( setChecked(bool) ) );
    connect( mcpdId, SIGNAL( valueChanged(int) ), this, SLOT( displayMcpdSlot() ) );
    connect( modeGroup, SIGNAL( clicked(int) ), this, SLOT( setModeSlot(int) ) );
    connect( modifyIp, SIGNAL( toggled(bool) ), mcpdIpAddress0, SLOT( setEnabled(bool) ) );
    connect( modifyIp, SIGNAL( toggled(bool) ), mcpdIpAddress1, SLOT( setEnabled(bool) ) );
    connect( modifyIp, SIGNAL( toggled(bool) ), mcpdIpAddress2, SLOT( setEnabled(bool) ) );
    connect( modifyIp, SIGNAL( toggled(bool) ), mcpdIpAddress3, SLOT( setEnabled(bool) ) );
    connect( modifyMIp, SIGNAL( toggled(bool) ), mIpAddress0, SLOT( setEnabled(bool) ) );
    connect( modifyMIp, SIGNAL( toggled(bool) ), mIpAddress1, SLOT( setEnabled(bool) ) );
    connect( modifyMIp, SIGNAL( toggled(bool) ), mIpAddress2, SLOT( setEnabled(bool) ) );
    connect( modifyMIp, SIGNAL( toggled(bool) ), mIpAddress3, SLOT( setEnabled(bool) ) );
    connect( modifyMIp, SIGNAL( toggled(bool) ), applyMIp, SLOT( setEnabled(bool) ) );
    connect( module, SIGNAL( valueChanged(int) ), this, SLOT( displayMpsdSlot() ) );
    connect( param, SIGNAL( valueChanged(int) ), this, SLOT( displayMcpdSlot() ) );
    connect( pulsAmp1, SIGNAL( lostFocus() ), this, SLOT( setPulserSlot() ) );
    connect( pulsAmp1, SIGNAL( returnPressed() ), this, SLOT( setPulserSlot() ) );
    connect( pulsAmp2, SIGNAL( lostFocus() ), this, SLOT( setPulserSlot() ) );
    connect( pulsAmp2, SIGNAL( returnPressed() ), this, SLOT( setPulserSlot() ) );
    connect( pulsampRadio1, SIGNAL( toggled(bool) ), pulsAmp1, SLOT( setEnabled(bool) ) );
    connect( pulsampRadio1, SIGNAL( toggled(bool) ), this, SLOT( setPulserSlot() ) );
    connect( pulsampRadio2, SIGNAL( toggled(bool) ), pulsAmp2, SLOT( setEnabled(bool) ) );
    connect( pulsampRadio2, SIGNAL( toggled(bool) ), this, SLOT( setPulserSlot() ) );
    connect( pulsChan, SIGNAL( valueChanged(int) ), this, SLOT( setPulserSlot() ) );
    connect( pulserButton, SIGNAL( toggled(bool) ), this, SLOT( setPulserSlot() ) );
    connect( pulsLeft, SIGNAL( toggled(bool) ), this, SLOT( setPulserSlot() ) );
    connect( pulsMid, SIGNAL( toggled(bool) ), this, SLOT( setPulserSlot() ) );
    connect( pulsRight, SIGNAL( toggled(bool) ), this, SLOT( setPulserSlot() ) );
    connect( readRegisterButton, SIGNAL( clicked() ), this, SLOT( readRegisterSlot() ) );
    connect( replayButton, SIGNAL( clicked() ), this, SLOT( replayListfileSlot() ) );
    connect( resetTimer, SIGNAL( clicked() ), this, SLOT( resetTimerSlot() ) );
    connect( restoreSetupButton, SIGNAL( clicked() ), this, SLOT( restoreSetupSlot() ) );
    connect( saveSetupButton, SIGNAL( clicked() ), this, SLOT( saveSetupSlot() ) );
    connect( scanPeri, SIGNAL( clicked() ), this, SLOT( scanPeriSlot() ) );
    connect( selectButton, SIGNAL( clicked() ), this, SLOT( selectListfileSlot() ) );
    connect( selectConfigpath, SIGNAL( clicked() ), this, SLOT( selectConfigpathSlot() ) );
    connect( selectHistpath, SIGNAL( clicked() ), this, SLOT( selectHistpathSlot() ) );
    connect( selectListpath, SIGNAL( clicked() ), this, SLOT( selectListpathSlot() ) );
    connect( sendAux, SIGNAL( clicked() ), this, SLOT( sendAuxSlot() ) );
    connect( sendCellButton, SIGNAL( clicked() ), this, SLOT( sendCellSlot() ) );
    connect( sendParam, SIGNAL( clicked() ), this, SLOT( sendParamSlot() ) );
    connect( setGain, SIGNAL( clicked() ), this, SLOT( setGainSlot() ) );
    connect( setID, SIGNAL( clicked() ), this, SLOT( setMcpdIdSlot() ) );
    connect( setIP, SIGNAL( clicked() ), this, SLOT( setIpUdpSlot() ) );
    connect( setStream, SIGNAL( clicked() ), this, SLOT( setStreamSlot() ) );
    connect( setThreshold, SIGNAL( clicked() ), this, SLOT( setThresholdSlot() ) );
    connect( startStopButton, SIGNAL( clicked() ), this, SLOT( startStopSlot() ) );
    connect( tabWidget2, SIGNAL( selected(const QString&) ), this, SLOT( displayMcpdSlot() ) );
    connect( tabWidget5, SIGNAL( selected(const QString&) ), this, SLOT( displayMcpdSlot() ) );
    connect( terminate, SIGNAL( toggled(bool) ), this, SLOT( setTimingSlot() ) );
    connect( timer, SIGNAL( valueChanged(int) ), this, SLOT( displayMcpdSlot() ) );
    connect( tPresetButton, SIGNAL( toggled(bool) ), this, SLOT( tPresetSlot(bool) ) );
    connect( tResetButton, SIGNAL( clicked() ), this, SLOT( tResetSlot() ) );
    connect( useThresh, SIGNAL( toggled(bool) ), loLim, SLOT( setEnabled(bool) ) );
    connect( useThresh, SIGNAL( toggled(bool) ), hiLim, SLOT( setEnabled(bool) ) );
    connect( useThresh, SIGNAL( clicked() ), this, SLOT( applyThreshSlot() ) );
    connect( writeHistButton, SIGNAL( clicked() ), this, SLOT( writeHistSlot() ) );
    connect( writeRegisterButton, SIGNAL( clicked() ), this, SLOT( writeRegisterSlot() ) );
    connect( clearLogButton, SIGNAL( clicked() ), protocolEdit, SLOT( clear() ) );
    connect( searchMcpdButton1, SIGNAL( clicked() ), this, SLOT( mcpdSearchSlot() ) );
    connect( pulsertestButton, SIGNAL( toggled(bool) ), this, SLOT( pulsertestSlot(bool) ) );
    connect( eightFoldBox, SIGNAL( toggled(bool) ), dispChan, SLOT( setDisabled(bool) ) );
    connect( eightFoldBox, SIGNAL( toggled(bool) ), dispAll, SLOT( setDisabled(bool) ) );
    connect( eightFoldBox, SIGNAL( toggled(bool) ), dispChan, SLOT( setDisabled(bool) ) );
    connect( cpuMon1box, SIGNAL( valueChanged(int) ), this, SLOT( assignCounterSlot() ) );
    connect( counterMon1box, SIGNAL( valueChanged(int) ), this, SLOT( assignCounterSlot() ) );
    connect( cpuMon2box, SIGNAL( valueChanged(int) ), this, SLOT( assignCounterSlot() ) );
    connect( counterMon2box, SIGNAL( valueChanged(int) ), this, SLOT( assignCounterSlot() ) );
}

/*
 *  Destroys the object and frees any allocated resources
 */
mesydaq2mainwindow::~mesydaq2mainwindow()
{
    // no need to delete child widgets, Qt does it all for us
}

/*
 *  Sets the strings of the subwidgets using the current
 *  language.
 */
void mesydaq2mainwindow::languageChange()
{
    setCaption( tr2i18n( "mesydaq2" ) );
    setProperty( "windowTitle", tr2i18n( "Form" ) );
    textLabel1_5_3->setText( tr2i18n( "Sigma:" ) );
    textLabel1_5->setText( tr2i18n( "Sliding Mean:" ) );
    meanText->setText( tr2i18n( "0.0" ) );
    sigmaText->setText( tr2i18n( "0.0" ) );
    groupBox1->setTitle( tr2i18n( "DAQ" ) );
    daqStatusLine->setText( tr2i18n( "idle" ) );
    QToolTip::add( daqStatusLine, tr2i18n( "current DAQ status display" ) );
    acquireFile->setText( tr2i18n( "ac&quire\n"
"Listfile" ) );
    acquireFile->setAccel( QKeySequence( tr2i18n( "Alt+Q" ) ) );
    startStopButton->setText( tr2i18n( "S&tart" ) );
    startStopButton->setAccel( QKeySequence( tr2i18n( "Alt+T" ) ) );
    QToolTip::add( startStopButton, tr2i18n( "start / stop data acquisition" ) );
    allPulsersoffButton->setText( tr2i18n( "All pulsers off" ) );
    pulserWarning->setText( tr2i18n( "<p align=\"center\">Pulser!</p>" ) );
    versionLabel->setText( tr2i18n( "mesydaq 2.1.0   16.10.2008" ) );
    dispAll->setText( tr2i18n( "Sum spectra" ) );
    dispAll->setAccel( QKeySequence( QString::null ) );
    buttonGroup10->setTitle( QString::null );
    dispAllAmpl->setText( tr2i18n( "Ampl" ) );
    dispAllAmpl->setAccel( QKeySequence( QString::null ) );
    dispAllPos->setText( tr2i18n( "Pos" ) );
    dispAllPos->setAccel( QKeySequence( QString::null ) );
    clearMcpd->setText( tr2i18n( "clear" ) );
    clearMcpd->setAccel( QKeySequence( QString::null ) );
    clearChan->setText( tr2i18n( "clear" ) );
    clearChan->setAccel( QKeySequence( QString::null ) );
    clearMpsd->setText( tr2i18n( "clear" ) );
    clearMpsd->setAccel( QKeySequence( QString::null ) );
    textLabel1_4_2_3_4_2_2->setText( tr2i18n( "MPSD" ) );
    textLabel1_4_2_3_4_2->setText( tr2i18n( "MCPD" ) );
    textLabel1_4_2_3_4_2_2_2->setText( tr2i18n( "Channel" ) );
    textLabel2->setText( tr2i18n( "0-7: position\n"
"8-15: energy" ) );
    clearAll->setText( tr2i18n( "clear all" ) );
    clearAll->setAccel( QKeySequence( QString::null ) );
    logGroup->setTitle( QString::null );
    log->setText( tr2i18n( "log" ) );
    lin->setText( tr2i18n( "&lin" ) );
    lin->setAccel( QKeySequence( tr2i18n( "Alt+L" ) ) );
    zoomBox->setText( tr2i18n( "&zoom" ) );
    zoomBox->setAccel( QKeySequence( tr2i18n( "Alt+Z" ) ) );
    eightFoldBox->setText( tr2i18n( "8-fold" ) );
    textLabel1_14->setText( tr2i18n( "from" ) );
    tabWidget5_2->changeTab( tab, tr2i18n( "Display" ) );
    useThresh->setText( tr2i18n( "Thresholds" ) );
    loLim->setText( tr2i18n( "0" ) );
    textLabel1_6->setText( tr2i18n( "low" ) );
    textLabel1_6_2->setText( tr2i18n( "hi" ) );
    hiLim->setText( tr2i18n( "1000000000" ) );
    applyDispThreshButton->setText( tr2i18n( "apply" ) );
    tabWidget5_2->changeTab( tab_2, tr2i18n( "Thresholds" ) );
    QToolTip::add( evPreset, tr2i18n( "preset value for event counter" ) );
    textLabel1_10_2->setText( tr2i18n( "Monitor 1 rate" ) );
    eResetButton->setText( tr2i18n( "&R" ) );
    QToolTip::add( eResetButton, tr2i18n( "reset event counter" ) );
    QToolTip::add( m1Preset, tr2i18n( "preset value for monitor 1" ) );
    tPresetButton->setText( tr2i18n( "P" ) );
    QToolTip::add( tPresetButton, tr2i18n( "activate preset for timer" ) );
    monRate2->setText( tr2i18n( "0" ) );
    textLabel1_2_3_2_3->setText( tr2i18n( "Timer [h:m:s]:" ) );
    monitor2->setText( tr2i18n( "0" ) );
    m1PresetButton->setText( tr2i18n( "P" ) );
    QToolTip::add( m1PresetButton, tr2i18n( "activate preset for monitor 1" ) );
    monRate1->setText( tr2i18n( "0" ) );
    tSecsText->setText( tr2i18n( "0" ) );
    ePresetButton->setText( tr2i18n( "P" ) );
    QToolTip::add( ePresetButton, tr2i18n( "activate preset for event counter" ) );
    textLabel1_2_3_2_3_2->setText( tr2i18n( "Timer [s]:" ) );
    m2RresetButton->setText( tr2i18n( "R" ) );
    QToolTip::add( m2RresetButton, tr2i18n( "reset monitor 2" ) );
    textLabel1_10_2_2->setText( tr2i18n( "Monitor 2 rate" ) );
    mTimeText->setText( tr2i18n( "0" ) );
    textLabel1_11->setText( tr2i18n( "Monitor 1" ) );
    monitor1->setText( tr2i18n( "0" ) );
    totalCounts->setText( tr2i18n( "0" ) );
    textLabel1_11_2->setText( tr2i18n( "Monitor 2" ) );
    textLabel1_10->setText( tr2i18n( "Event rate" ) );
    eventRate->setText( tr2i18n( "0" ) );
    QToolTip::add( m2Preset, tr2i18n( "preset value for monitor 2" ) );
    QToolTip::add( tPreset, tr2i18n( "preset value for timer" ) );
    m1ResetButton->setText( tr2i18n( "R" ) );
    QToolTip::add( m1ResetButton, tr2i18n( "reset monitor 1" ) );
    tResetButton->setText( tr2i18n( "R" ) );
    QToolTip::add( tResetButton, tr2i18n( "reset timer" ) );
    m2PresetButton->setText( tr2i18n( "P" ) );
    QToolTip::add( m2PresetButton, tr2i18n( "activate preset for monitor 2" ) );
    textLabel1->setText( tr2i18n( "Event counter" ) );
    QToolTip::add( cpuMon1box, tr2i18n( "MCPD-ID for Mon1" ) );
    QToolTip::add( cpuMon2box, tr2i18n( "MCPD-ID for Mon2" ) );
    textLabel1_15->setText( tr2i18n( "MCPD-ID" ) );
    textLabel1_15_2->setText( tr2i18n( "Counter#" ) );
    QToolTip::add( counterMon2box, tr2i18n( "counter # for Mon2 (0...3: front, 4,5: back)" ) );
    QToolTip::add( counterMon1box, tr2i18n( "counter # for Mon1  (0...3: front, 4,5: back)" ) );
    TabWidget->changeTab( tab_4, tr2i18n( "meas. data" ) );
    textLabel1_2_3->setText( tr2i18n( "cmd buffers reveived:" ) );
    textLabel1_2->setText( tr2i18n( "cmd buffers transmitted:" ) );
    cmdTx->setText( tr2i18n( "0" ) );
    cmdRx->setText( tr2i18n( "0" ) );
    textLabel1_2_2->setText( tr2i18n( "data buffers received:" ) );
    dataRx->setText( tr2i18n( "0" ) );
    TabWidget->changeTab( tab_5, tr2i18n( "statistics" ) );
    textLabel1_12->setText( tr2i18n( "height:" ) );
    textLabel1_12_2->setText( tr2i18n( "width:" ) );
    textLabel1_12_2_2->setText( tr2i18n( "run#" ) );
    caressHeight->setText( tr2i18n( "<p align=\"right\">0</p>" ) );
    caressWidth->setText( tr2i18n( "<p align=\"right\">0</p>" ) );
    caressRun->setText( tr2i18n( "<p align=\"right\">0</p>" ) );
    textLabel1_13->setText( tr2i18n( "Caress cmd protocol" ) );
    QToolTip::add( caressEdit, tr2i18n( "application and error messages" ) );
    TabWidget->changeTab( TabPage, tr2i18n( "Caress" ) );
    tabWidget2->changeTab( tab_3, tr2i18n( "Meas.Status" ) );
    textLabel1_5_2->setText( tr2i18n( "ID" ) );
    groupBox38->setTitle( tr2i18n( "Status" ) );
    QToolTip::add( groupBox38, tr2i18n( "general status of MCPD-8" ) );
    searchMcpdButton1->setText( tr2i18n( "search" ) );
    QToolTip::add( searchMcpdButton1, tr2i18n( "Try to find on ethernet" ) );
    mcpdStatusText1->setText( tr2i18n( "Offline" ) );
    QToolTip::add( mcpdStatusText1, tr2i18n( "Ethernet Status" ) );
    mcpdConfigText1->setText( tr2i18n( "Not configured" ) );
    QToolTip::add( mcpdConfigText1, tr2i18n( "Configuration File" ) );
    mcpdMasterText1->setText( tr2i18n( "Slave" ) );
    QToolTip::add( mcpdMasterText1, tr2i18n( "Master/Slave" ) );
    groupBox9->setTitle( tr2i18n( "Counter/ ADC-Cell" ) );
    QToolTip::add( groupBox9, QString::null );
    textLabel1_7->setText( tr2i18n( "Cell" ) );
    textLabel1_7_3->setText( tr2i18n( "Trigger" ) );
    textLabel1_7_2->setText( tr2i18n( "Compare" ) );
    sendCellButton->setText( tr2i18n( "Send" ) );
    QToolTip::add( sendCellButton, tr2i18n( "send cell data" ) );
    cellSource->clear();
    cellSource->insertItem( tr2i18n( "mon/chop1" ) );
    cellSource->insertItem( tr2i18n( "mon/chop2" ) );
    cellSource->insertItem( tr2i18n( "mon/chop3" ) );
    cellSource->insertItem( tr2i18n( "mon/chop4" ) );
    cellSource->insertItem( tr2i18n( "digInput1" ) );
    cellSource->insertItem( tr2i18n( "digInput2" ) );
    cellSource->insertItem( tr2i18n( "ADC1" ) );
    cellSource->insertItem( tr2i18n( "ADC2" ) );
    QToolTip::add( cellSource, tr2i18n( "Select counter / ADC cell" ) );
    cellTrigger->clear();
    cellTrigger->insertItem( tr2i18n( "no Trig" ) );
    cellTrigger->insertItem( tr2i18n( "auxTimer1" ) );
    cellTrigger->insertItem( tr2i18n( "auxTimer2" ) );
    cellTrigger->insertItem( tr2i18n( "auxTimer3" ) );
    cellTrigger->insertItem( tr2i18n( "auxTimer4" ) );
    cellTrigger->insertItem( tr2i18n( "digInput1" ) );
    cellTrigger->insertItem( tr2i18n( "digInput2" ) );
    cellTrigger->insertItem( tr2i18n( "compareReg" ) );
    QToolTip::add( cellTrigger, tr2i18n( "Select trigger for cell" ) );
    QToolTip::add( cellCompare, tr2i18n( "Define compare source for cell" ) );
    groupBox16->setTitle( tr2i18n( "Status Stream" ) );
    statusStream->setText( tr2i18n( "stream" ) );
    QToolTip::add( statusStream, tr2i18n( "send status stream when daq is stopped" ) );
    setStream->setText( tr2i18n( "send" ) );
    groupBox9_2->setTitle( tr2i18n( "Aux Timer" ) );
    QToolTip::add( groupBox9_2, QString::null );
    textLabel1_7_4->setText( tr2i18n( "Timer" ) );
    textLabel1_7_3_2->setText( tr2i18n( "Compare" ) );
    sendAux->setText( tr2i18n( "Send" ) );
    QToolTip::add( sendAux, tr2i18n( "send timer setting" ) );
    QToolTip::add( timer, tr2i18n( "select timer number" ) );
    QToolTip::add( compareAux, tr2i18n( "define compare value" ) );
    groupBox9_2_2->setTitle( tr2i18n( "Parameter Source" ) );
    QToolTip::add( groupBox9_2_2, QString::null );
    textLabel1_7_4_2_2->setText( tr2i18n( "Source" ) );
    textLabel1_7_4_2->setText( tr2i18n( "Param." ) );
    sendParam->setText( tr2i18n( "Send" ) );
    QToolTip::add( sendParam, tr2i18n( "send parameter settings for selected parameter" ) );
    paramSource->clear();
    paramSource->insertItem( tr2i18n( "mon/chop1" ) );
    paramSource->insertItem( tr2i18n( "mon/chop2" ) );
    paramSource->insertItem( tr2i18n( "mon/chop3" ) );
    paramSource->insertItem( tr2i18n( "mon/chop4" ) );
    paramSource->insertItem( tr2i18n( "digInput1" ) );
    paramSource->insertItem( tr2i18n( "digInput2" ) );
    paramSource->insertItem( tr2i18n( "ADC1,2, DigIn1,2" ) );
    paramSource->insertItem( tr2i18n( "event counter" ) );
    paramSource->insertItem( tr2i18n( "master clock" ) );
    QToolTip::add( paramSource, tr2i18n( "select parameter source" ) );
    QToolTip::add( param, tr2i18n( "select parameter number" ) );
    tabWidget5->changeTab( tab_7, tr2i18n( "Counters, Timers, Parameters" ) );
    groupBox30->setTitle( tr2i18n( "Master / Termination" ) );
    QToolTip::add( groupBox30, QString::null );
    master->setText( tr2i18n( "Master" ) );
    master->setAccel( QKeySequence( QString::null ) );
    terminate->setText( tr2i18n( "&terminate" ) );
    terminate->setAccel( QKeySequence( tr2i18n( "Alt+T" ) ) );
    resetTimer->setText( tr2i18n( "&Reset Timer" ) );
    resetTimer->setAccel( QKeySequence( tr2i18n( "Alt+R" ) ) );
    QToolTip::add( resetTimer, tr2i18n( "reset master clock" ) );
    groupBox29->setTitle( tr2i18n( "MCPD-8 ID" ) );
    setID->setText( tr2i18n( "set ID" ) );
    groupBox6->setTitle( tr2i18n( "IP / UDP settings" ) );
    textLabel1_3_3_2->setText( tr2i18n( "udp port" ) );
    textLabel1_3_3_2_2->setText( tr2i18n( "ip address" ) );
    mcpdIpAddress2->setText( tr2i18n( "168" ) );
    cmdIpAddress0->setText( tr2i18n( "0" ) );
    textLabel1_3_2_2_2->setText( tr2i18n( "<b>Cmd pc</b>" ) );
    dataIpAddress2->setText( tr2i18n( "168" ) );
    dataIpAddress1->setText( tr2i18n( "168" ) );
    dataIpAddress0->setText( tr2i18n( "192" ) );
    mcpdIpAddress1->setText( tr2i18n( "168" ) );
    cmdIpAddress2->setText( tr2i18n( "168" ) );
    mcpdIpAddress3->setText( tr2i18n( "121" ) );
    mcpdIpAddress0->setText( tr2i18n( "192" ) );
    cmdThisPc->setText( tr2i18n( "this pc" ) );
    cmdIpAddress3->setText( tr2i18n( "5" ) );
    cmdIpAddress1->setText( tr2i18n( "168" ) );
    textLabel1_3_2_2->setText( tr2i18n( "<b>MCPD-8</b>" ) );
    textLabel1_3_2->setText( tr2i18n( "<b>Data pc</b>" ) );
    setIP->setText( tr2i18n( "set &comm\n"
"parameters" ) );
    setIP->setAccel( QKeySequence( tr2i18n( "Alt+C" ) ) );
    dataIpAddress3->setText( tr2i18n( "5" ) );
    dataThisPc->setText( tr2i18n( "this pc" ) );
    textLabel1_3_2_2_2_2->setText( tr2i18n( "<b>mesydaq</b>" ) );
    mIpAddress1->setText( tr2i18n( "168" ) );
    mIpAddress2->setText( tr2i18n( "168" ) );
    modifyIp->setText( tr2i18n( "modify" ) );
    mIpAddress3->setText( tr2i18n( "121" ) );
    modifyMIp->setText( tr2i18n( "modify" ) );
    applyMIp->setText( tr2i18n( "Apply" ) );
    applyMIp->setAccel( QKeySequence( QString::null ) );
    QToolTip::add( applyMIp, tr2i18n( "use this ip address for further communication" ) );
    mIpAddress0->setText( tr2i18n( "192" ) );
    tabWidget5->changeTab( tab_8, tr2i18n( "Address / Comm. Settings" ) );
    textLabel1_3->setText( tr2i18n( "P0:" ) );
    textLabel1_3_4->setText( tr2i18n( "P2:" ) );
    textLabel1_3_3->setText( tr2i18n( "P1:" ) );
    param0->setText( tr2i18n( "<p align=\"right\">0</p>" ) );
    param1->setText( tr2i18n( "<p align=\"right\">0</p>" ) );
    textLabel1_2_3_2->setText( tr2i18n( "header time:" ) );
    param2->setText( tr2i18n( "<p align=\"right\">0</p>" ) );
    param3->setText( tr2i18n( "<p align=\"right\">0</p>" ) );
    hTimeText->setText( tr2i18n( "0" ) );
    textLabel1_3_5->setText( tr2i18n( "P3:" ) );
    tabWidget5->changeTab( TabPage_2, tr2i18n( "Counter Status" ) );
    QToolTip::add( mcpdId, tr2i18n( "MCPD-ID to address " ) );
    tabWidget2->changeTab( tab_6, tr2i18n( "MCPD-&8" ) );
    groupBox17_2->setTitle( tr2i18n( "MPSD-8 status" ) );
    textLabel1_4->setText( tr2i18n( "0:" ) );
    textLabel1_4_10->setText( tr2i18n( "1:" ) );
    textLabel1_4_9->setText( tr2i18n( "2:" ) );
    textLabel1_4_8->setText( tr2i18n( "3:" ) );
    textLabel1_4_7->setText( tr2i18n( "4:" ) );
    textLabel1_4_6->setText( tr2i18n( "5:" ) );
    textLabel1_4_5->setText( tr2i18n( "6:" ) );
    textLabel1_4_4->setText( tr2i18n( "7:" ) );
    status3->setText( tr2i18n( "active" ) );
    status2->setText( tr2i18n( "active" ) );
    status1->setText( tr2i18n( "active" ) );
    status4->setText( tr2i18n( "active" ) );
    status5->setText( tr2i18n( "active" ) );
    status6->setText( tr2i18n( "active" ) );
    status7->setText( tr2i18n( "active" ) );
    scanPeri->setText( tr2i18n( "rescan" ) );
    status0->setText( tr2i18n( "active" ) );
    groupBox39->setTitle( tr2i18n( "Register op" ) );
    readRegisterButton->setText( tr2i18n( "Read" ) );
    writeRegisterButton->setText( tr2i18n( "Write" ) );
    textLabel1_4_2_4->setText( tr2i18n( "MCPD-8 ID" ) );
    textLabel1_14_2->setText( tr2i18n( "Status:" ) );
    mcpdStatusText2->setText( tr2i18n( "offline" ) );
    tabWidget4->changeTab( tab_9, tr2i18n( "Status" ) );
    textLabel1_4_2_2->setText( tr2i18n( "MPSD-8\n"
"(Bus-#)" ) );
    groupBox13->setTitle( tr2i18n( "Amplifiers, Discriminator" ) );
    textLabel1_4_2_3_2->setText( tr2i18n( "Gain" ) );
    textLabel1_4_2_3_3->setText( tr2i18n( "Threshold" ) );
    setThreshold->setText( tr2i18n( "set &threshold" ) );
    textLabel1_4_2_3->setText( tr2i18n( "Chan" ) );
    gain->setText( tr2i18n( "1" ) );
    textLabel1_4_2_3_3_3->setText( tr2i18n( "Gain (0.5-1.88)" ) );
    threshold->setText( tr2i18n( "20" ) );
    setGain->setText( tr2i18n( "set gain" ) );
    textLabel1_4_2_3_3_2->setText( tr2i18n( "Threshold [%]" ) );
    comgain->setText( tr2i18n( "common" ) );
    groupBox35->setTitle( tr2i18n( "Pulser" ) );
    textLabel1_4_2_3_4->setText( tr2i18n( "Channel" ) );
    buttonGroup5->setTitle( tr2i18n( "Amplitude [%]" ) );
    pulsAmp2->setText( tr2i18n( "90" ) );
    QToolTip::add( pulsAmp2, tr2i18n( "alternative pulser amplitude" ) );
    pulsampRadio1->setText( QString::null );
    pulsampRadio2->setText( QString::null );
    pulsAmp1->setText( tr2i18n( "50" ) );
    QToolTip::add( pulsAmp1, tr2i18n( "main pulser amplitude" ) );
    pulserButton->setText( tr2i18n( "Pulser" ) );
    QToolTip::add( pulserButton, tr2i18n( "toggle pulser on/off" ) );
    QToolTip::add( pulsChan, tr2i18n( "pulser channel" ) );
    buttonGroup4->setTitle( tr2i18n( "Position" ) );
    pulsLeft->setText( tr2i18n( "left" ) );
    pulsMid->setText( tr2i18n( "mid" ) );
    pulsRight->setText( tr2i18n( "right" ) );
    modeGroup->setTitle( tr2i18n( "Mode" ) );
    pos->setText( tr2i18n( "Position" ) );
    amp->setText( tr2i18n( "Amplitude" ) );
    textLabel1_4_2->setText( tr2i18n( "MCPD-8 ID" ) );
    mpsdDeviceText->setText( tr2i18n( "(Device-ID: 0)" ) );
    QToolTip::add( mpsdDeviceText, tr2i18n( "Device ID in config file" ) );
    tabWidget4->changeTab( tab_10, tr2i18n( "Settings" ) );
    tabWidget2->changeTab( TabPage_3, tr2i18n( "MPSD-&8" ) );
    groupBox36->setTitle( tr2i18n( "Histograms" ) );
    textLabel2_2_2->setText( tr2i18n( "Currently loaded:" ) );
    histfilename->setText( tr2i18n( "-" ) );
    writeHistButton->setText( tr2i18n( "Write" ) );
    writeHistButton->setAccel( QKeySequence( QString::null ) );
    LoadhistButton->setText( tr2i18n( "Load" ) );
    LoadhistButton->setAccel( QKeySequence( QString::null ) );
    groupBox79_2->setTitle( tr2i18n( "Setup" ) );
    restoreSetupButton->setText( tr2i18n( "&restore" ) );
    restoreSetupButton->setAccel( QKeySequence( tr2i18n( "Alt+R" ) ) );
    saveSetupButton->setText( tr2i18n( "sa&ve" ) );
    saveSetupButton->setAccel( QKeySequence( tr2i18n( "Alt+V" ) ) );
    configfilename->setText( tr2i18n( "Default setup" ) );
    textLabel2_2->setText( tr2i18n( "Currently loaded:" ) );
    groupBox35_2->setTitle( tr2i18n( "Default paths" ) );
    textLabel1_9_3->setText( tr2i18n( "Config files" ) );
    textLabel1_9_2->setText( tr2i18n( "Histograms" ) );
    textLabel1_9->setText( tr2i18n( "Listmode files" ) );
    selectListpath->setText( tr2i18n( "select" ) );
    selectConfigpath->setText( tr2i18n( "select" ) );
    selectHistpath->setText( tr2i18n( "select" ) );
    groupBox79->setTitle( tr2i18n( "Listmode data acquisition" ) );
    textLabel2_2_3->setText( tr2i18n( "Comment:" ) );
    QToolTip::add( textLabel2_2_3, tr2i18n( "comment will be written to listfile header" ) );
    selectButton->setText( tr2i18n( "select" ) );
    replayButton->setText( tr2i18n( "Repla&y Listfile" ) );
    replayButton->setAccel( QKeySequence( tr2i18n( "Alt+Y" ) ) );
    QToolTip::add( listfileComment, tr2i18n( "Comment will be written to listfile header" ) );
    acqListfile->setText( tr2i18n( "ac&quire listfile:" ) );
    acqListfile->setAccel( QKeySequence( tr2i18n( "Alt+Q" ) ) );
    tabWidget2->changeTab( TabPage_4, tr2i18n( "Fi&les" ) );
    groupBox15->setTitle( tr2i18n( "Run ID" ) );
    QToolTip::add( runId, tr2i18n( "RUN ID will be transmitted in every data buffer header" ) );
    runIdAuto->setText( tr2i18n( "Auto Incr." ) );
    runIdAuto->setAccel( QKeySequence( QString::null ) );
    QToolTip::add( runIdAuto, tr2i18n( "increment run ID automatically at every start cmd" ) );
    runIdButton->setText( tr2i18n( "set Run ID" ) );
    groupBox20->setTitle( tr2i18n( "Timing Delta Histogram" ) );
    textLabel1_8->setText( tr2i18n( "Binwidth [bits]\n"
"1 bit = 100 ns" ) );
    tabWidget2->changeTab( TabPage_5, tr2i18n( "Special" ) );
    textLabel1_2_3_2_3_2_2->setText( tr2i18n( "Application protocol:" ) );
    clearLogButton->setText( tr2i18n( "clear Log" ) );
    debugLevelBox->clear();
    debugLevelBox->insertItem( tr2i18n( "Errors" ) );
    debugLevelBox->insertItem( tr2i18n( "Standard" ) );
    debugLevelBox->insertItem( tr2i18n( "Details" ) );
    debugLevelBox->insertItem( tr2i18n( "All" ) );
    QToolTip::add( debugLevelBox, tr2i18n( "change protocol level" ) );
    QToolTip::add( protocolEdit, tr2i18n( "application and error messages" ) );
    tabWidget2->changeTab( TabPage_6, tr2i18n( "Protocol" ) );
    pulsertestButton->setText( tr2i18n( "Pulsertest" ) );
    QToolTip::add( pulsertestButton, tr2i18n( "starts pulsertest of all connected modules" ) );
}

void mesydaq2mainwindow::startStopSlot()
{
    qWarning( "mesydaq2mainwindow::startStopSlot(): Not implemented yet" );
}

void mesydaq2mainwindow::sendCellSlot()
{
    qWarning( "mesydaq2mainwindow::sendCellSlot(): Not implemented yet" );
}

void mesydaq2mainwindow::sendParamSlot()
{
    qWarning( "mesydaq2mainwindow::sendParamSlot(): Not implemented yet" );
}

void mesydaq2mainwindow::sendAuxSlot()
{
    qWarning( "mesydaq2mainwindow::sendAuxSlot(): Not implemented yet" );
}

void mesydaq2mainwindow::resetTimerSlot()
{
    qWarning( "mesydaq2mainwindow::resetTimerSlot(): Not implemented yet" );
}

void mesydaq2mainwindow::setTimingSlot()
{
    qWarning( "mesydaq2mainwindow::setTimingSlot(): Not implemented yet" );
}

void mesydaq2mainwindow::setMcpdIdSlot()
{
    qWarning( "mesydaq2mainwindow::setMcpdIdSlot(): Not implemented yet" );
}

void mesydaq2mainwindow::setIpUdpSlot()
{
    qWarning( "mesydaq2mainwindow::setIpUdpSlot(): Not implemented yet" );
}

void mesydaq2mainwindow::setPulserSlot()
{
    qWarning( "mesydaq2mainwindow::setPulserSlot(): Not implemented yet" );
}

void mesydaq2mainwindow::setGainSlot()
{
    qWarning( "mesydaq2mainwindow::setGainSlot(): Not implemented yet" );
}

void mesydaq2mainwindow::setThresholdSlot()
{
    qWarning( "mesydaq2mainwindow::setThresholdSlot(): Not implemented yet" );
}

void mesydaq2mainwindow::allPulserSlot()
{
    qWarning( "mesydaq2mainwindow::allPulserSlot(): Not implemented yet" );
}

void mesydaq2mainwindow::selectListfileSlot()
{
    qWarning( "mesydaq2mainwindow::selectListfileSlot(): Not implemented yet" );
}

void mesydaq2mainwindow::acqListfileSlot()
{
    qWarning( "mesydaq2mainwindow::acqListfileSlot(): Not implemented yet" );
}

void mesydaq2mainwindow::setStreamSlot()
{
    qWarning( "mesydaq2mainwindow::setStreamSlot(): Not implemented yet" );
}

void mesydaq2mainwindow::clearAllSlot()
{
    qWarning( "mesydaq2mainwindow::clearAllSlot(): Not implemented yet" );
}

void mesydaq2mainwindow::clearMcpdSlot()
{
    qWarning( "mesydaq2mainwindow::clearMcpdSlot(): Not implemented yet" );
}

void mesydaq2mainwindow::clearMpsdSlot()
{
    qWarning( "mesydaq2mainwindow::clearMpsdSlot(): Not implemented yet" );
}

void mesydaq2mainwindow::clearChanSlot()
{
    qWarning( "mesydaq2mainwindow::clearChanSlot(): Not implemented yet" );
}

void mesydaq2mainwindow::replayListfileSlot()
{
    qWarning( "mesydaq2mainwindow::replayListfileSlot(): Not implemented yet" );
}

void mesydaq2mainwindow::setRunIdSlot()
{
    qWarning( "mesydaq2mainwindow::setRunIdSlot(): Not implemented yet" );
}

void mesydaq2mainwindow::displayMcpdSlot()
{
    qWarning( "mesydaq2mainwindow::displayMcpdSlot(): Not implemented yet" );
}

void mesydaq2mainwindow::displayMpsdSlot()
{
    qWarning( "mesydaq2mainwindow::displayMpsdSlot(): Not implemented yet" );
}

void mesydaq2mainwindow::scanPeriSlot()
{
    qWarning( "mesydaq2mainwindow::scanPeriSlot(): Not implemented yet" );
}

void mesydaq2mainwindow::setModeSlot(int)
{
    qWarning( "mesydaq2mainwindow::setModeSlot(int): Not implemented yet" );
}

void mesydaq2mainwindow::saveSetupSlot()
{
    qWarning( "mesydaq2mainwindow::saveSetupSlot(): Not implemented yet" );
}

void mesydaq2mainwindow::restoreSetupSlot()
{
    qWarning( "mesydaq2mainwindow::restoreSetupSlot(): Not implemented yet" );
}

void mesydaq2mainwindow::saveConfigSlot()
{
    qWarning( "mesydaq2mainwindow::saveConfigSlot(): Not implemented yet" );
}

void mesydaq2mainwindow::redrawSlot()
{
    qWarning( "mesydaq2mainwindow::redrawSlot(): Not implemented yet" );
}

void mesydaq2mainwindow::applyThreshSlot()
{
    qWarning( "mesydaq2mainwindow::applyThreshSlot(): Not implemented yet" );
}

void mesydaq2mainwindow::linlogSlot()
{
    qWarning( "mesydaq2mainwindow::linlogSlot(): Not implemented yet" );
}

void mesydaq2mainwindow::writeRegisterSlot()
{
    qWarning( "mesydaq2mainwindow::writeRegisterSlot(): Not implemented yet" );
}

void mesydaq2mainwindow::readRegisterSlot()
{
    qWarning( "mesydaq2mainwindow::readRegisterSlot(): Not implemented yet" );
}

void mesydaq2mainwindow::selectListpathSlot()
{
    qWarning( "mesydaq2mainwindow::selectListpathSlot(): Not implemented yet" );
}

void mesydaq2mainwindow::selectHistpathSlot()
{
    qWarning( "mesydaq2mainwindow::selectHistpathSlot(): Not implemented yet" );
}

void mesydaq2mainwindow::selectConfigpathSlot()
{
    qWarning( "mesydaq2mainwindow::selectConfigpathSlot(): Not implemented yet" );
}

void mesydaq2mainwindow::writeHistSlot()
{
    qWarning( "mesydaq2mainwindow::writeHistSlot(): Not implemented yet" );
}

void mesydaq2mainwindow::ePresetSlot(bool)
{
    qWarning( "mesydaq2mainwindow::ePresetSlot(bool): Not implemented yet" );
}

void mesydaq2mainwindow::tPresetSlot(bool)
{
    qWarning( "mesydaq2mainwindow::tPresetSlot(bool): Not implemented yet" );
}

void mesydaq2mainwindow::m1PresetSlot(bool)
{
    qWarning( "mesydaq2mainwindow::m1PresetSlot(bool): Not implemented yet" );
}

void mesydaq2mainwindow::m2PresetSlot(bool)
{
    qWarning( "mesydaq2mainwindow::m2PresetSlot(bool): Not implemented yet" );
}

void mesydaq2mainwindow::tResetSlot()
{
    qWarning( "mesydaq2mainwindow::tResetSlot(): Not implemented yet" );
}

void mesydaq2mainwindow::eResetSlot()
{
    qWarning( "mesydaq2mainwindow::eResetSlot(): Not implemented yet" );
}

void mesydaq2mainwindow::m1ResetSlot()
{
    qWarning( "mesydaq2mainwindow::m1ResetSlot(): Not implemented yet" );
}

void mesydaq2mainwindow::m2ResetSlot()
{
    qWarning( "mesydaq2mainwindow::m2ResetSlot(): Not implemented yet" );
}

void mesydaq2mainwindow::applyMIpSlot()
{
    qWarning( "mesydaq2mainwindow::applyMIpSlot(): Not implemented yet" );
}

void mesydaq2mainwindow::debugLevelSlot(int)
{
    qWarning( "mesydaq2mainwindow::debugLevelSlot(int): Not implemented yet" );
}

void mesydaq2mainwindow::mcpdSearchSlot()
{
    qWarning( "mesydaq2mainwindow::mcpdSearchSlot(): Not implemented yet" );
}

void mesydaq2mainwindow::pulsertestSlot(bool)
{
    qWarning( "mesydaq2mainwindow::pulsertestSlot(bool): Not implemented yet" );
}

void mesydaq2mainwindow::assignCounterSlot()
{
    qWarning( "mesydaq2mainwindow::assignCounterSlot(): Not implemented yet" );
}

#include "mesydaq2mainwindow.moc"
