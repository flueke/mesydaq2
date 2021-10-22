#include <kdialog.h>
#include <klocale.h>
/****************************************************************************
** Form implementation generated from reading ui file '/home/gregor/mesydaq2/src/mesydaq2mainwindow.ui'
**
** Created: Di Feb 10 09:25:53 2009
**
** WARNING! All changes made in this file will be lost!
****************************************************************************/

#include "mesydaq2mainwindow.h"

#include <qvariant.h>
#include <qframe.h>
#include <qlabel.h>
#include <qtabwidget.h>
#include <qbuttongroup.h>
#include <qradiobutton.h>
#include <qcheckbox.h>
#include <qspinbox.h>
#include <qpushbutton.h>
#include <qlineedit.h>
#include <qgroupbox.h>
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

    dataFrame = new QFrame( mainFrame, "dataFrame" );
    dataFrame->setGeometry( QRect( 80, 10, 960, 480 ) );
    dataFrame->setMinimumSize( QSize( 960, 480 ) );
    dataFrame->setFrameShape( QFrame::StyledPanel );
    dataFrame->setFrameShadow( QFrame::Raised );

    textLabel1_5_3 = new QLabel( mainFrame, "textLabel1_5_3" );
    textLabel1_5_3->setGeometry( QRect( 1060, 80, 76, 20 ) );

    textLabel1_5 = new QLabel( mainFrame, "textLabel1_5" );
    textLabel1_5->setGeometry( QRect( 1060, 40, 76, 20 ) );

    meanText = new QLabel( mainFrame, "meanText" );
    meanText->setGeometry( QRect( 1060, 60, 76, 20 ) );

    sigmaText = new QLabel( mainFrame, "sigmaText" );
    sigmaText->setGeometry( QRect( 1060, 100, 76, 20 ) );

    tabWidget5_2 = new QTabWidget( this, "tabWidget5_2" );
    tabWidget5_2->setGeometry( QRect( 10, 541, 261, 260 ) );

    tab = new QWidget( tabWidget5_2, "tab" );

    logGroup = new QButtonGroup( tab, "logGroup" );
    logGroup->setEnabled( FALSE );
    logGroup->setGeometry( QRect( 150, 170, 100, 30 ) );

    lin = new QRadioButton( logGroup, "lin" );
    lin->setGeometry( QRect( 10, 10, 40, 16 ) );
    lin->setChecked( TRUE );

    log = new QRadioButton( logGroup, "log" );
    log->setGeometry( QRect( 50, 10, 40, 16 ) );

    specialBox = new QCheckBox( tab, "specialBox" );
    specialBox->setEnabled( FALSE );
    specialBox->setGeometry( QRect( 20, 180, 71, 21 ) );

    dispAll = new QCheckBox( tab, "dispAll" );
    dispAll->setGeometry( QRect( 20, 10, 100, 20 ) );
    dispAll->setChecked( TRUE );

    dispMcpd = new QSpinBox( tab, "dispMcpd" );
    dispMcpd->setEnabled( FALSE );
    dispMcpd->setGeometry( QRect( 70, 70, 50, 21 ) );
    dispMcpd->setMaxValue( 7 );

    textLabel2 = new QLabel( tab, "textLabel2" );
    textLabel2->setGeometry( QRect( 180, 120, 70, 29 ) );

    clearChan = new QPushButton( tab, "clearChan" );
    clearChan->setGeometry( QRect( 130, 130, 40, 21 ) );

    dispChan = new QSpinBox( tab, "dispChan" );
    dispChan->setEnabled( FALSE );
    dispChan->setGeometry( QRect( 70, 130, 50, 21 ) );
    dispChan->setMaxValue( 15 );

    clearMcpd = new QPushButton( tab, "clearMcpd" );
    clearMcpd->setGeometry( QRect( 130, 70, 40, 21 ) );

    textLabel1_4_2_3_4_2_2_2 = new QLabel( tab, "textLabel1_4_2_3_4_2_2_2" );
    textLabel1_4_2_3_4_2_2_2->setGeometry( QRect( 10, 130, 50, 21 ) );

    dispMpsd = new QSpinBox( tab, "dispMpsd" );
    dispMpsd->setEnabled( FALSE );
    dispMpsd->setGeometry( QRect( 70, 100, 50, 21 ) );
    dispMpsd->setMaxValue( 7 );

    textLabel1_4_2_3_4_2 = new QLabel( tab, "textLabel1_4_2_3_4_2" );
    textLabel1_4_2_3_4_2->setGeometry( QRect( 10, 70, 40, 21 ) );

    textLabel1_4_2_3_4_2_2 = new QLabel( tab, "textLabel1_4_2_3_4_2_2" );
    textLabel1_4_2_3_4_2_2->setGeometry( QRect( 10, 100, 40, 21 ) );

    clearMpsd = new QPushButton( tab, "clearMpsd" );
    clearMpsd->setGeometry( QRect( 130, 100, 40, 21 ) );

    clearAll = new QPushButton( tab, "clearAll" );
    clearAll->setGeometry( QRect( 130, 40, 60, 21 ) );

    buttonGroup10 = new QButtonGroup( tab, "buttonGroup10" );
    buttonGroup10->setGeometry( QRect( 118, 3, 121, 31 ) );

    dispAllAmpl = new QRadioButton( buttonGroup10, "dispAllAmpl" );
    dispAllAmpl->setGeometry( QRect( 60, 10, 50, 16 ) );

    dispAllPos = new QRadioButton( buttonGroup10, "dispAllPos" );
    dispAllPos->setGeometry( QRect( 10, 10, 41, 16 ) );
    dispAllPos->setChecked( TRUE );
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

    groupBox1 = new QGroupBox( this, "groupBox1" );
    groupBox1->setGeometry( QRect( 1050, 550, 131, 250 ) );

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
    allPulsersoffButton->setGeometry( QRect( 20, 210, 90, 21 ) );

    pulserWarning = new QLabel( groupBox1, "pulserWarning" );
    pulserWarning->setGeometry( QRect( 20, 190, 91, 18 ) );
    pulserWarning->setPaletteForegroundColor( QColor( 251, 13, 5 ) );

    tabWidget2 = new QTabWidget( this, "tabWidget2" );
    tabWidget2->setGeometry( QRect( 280, 540, 760, 260 ) );

    tab_3 = new QWidget( tabWidget2, "tab_3" );

    versionLabel = new QLabel( tab_3, "versionLabel" );
    versionLabel->setGeometry( QRect( 50, 20, 170, 21 ) );

    groupBox17 = new QGroupBox( tab_3, "groupBox17" );
    groupBox17->setGeometry( QRect( 30, 50, 271, 160 ) );

    textLabel1_3_6 = new QLabel( groupBox17, "textLabel1_3_6" );
    textLabel1_3_6->setGeometry( QRect( 10, 20, 56, 21 ) );

    textLabel1_3 = new QLabel( groupBox17, "textLabel1_3" );
    textLabel1_3->setGeometry( QRect( 10, 50, 30, 21 ) );

    textLabel1_3_3 = new QLabel( groupBox17, "textLabel1_3_3" );
    textLabel1_3_3->setGeometry( QRect( 10, 70, 30, 21 ) );

    textLabel1_3_4 = new QLabel( groupBox17, "textLabel1_3_4" );
    textLabel1_3_4->setGeometry( QRect( 10, 90, 30, 21 ) );

    textLabel1_3_5 = new QLabel( groupBox17, "textLabel1_3_5" );
    textLabel1_3_5->setGeometry( QRect( 10, 110, 30, 21 ) );

    param0 = new QLabel( groupBox17, "param0" );
    param0->setGeometry( QRect( 140, 50, 110, 21 ) );

    param1 = new QLabel( groupBox17, "param1" );
    param1->setGeometry( QRect( 140, 70, 110, 21 ) );

    param3 = new QLabel( groupBox17, "param3" );
    param3->setGeometry( QRect( 140, 110, 110, 21 ) );

    paramId = new QSpinBox( groupBox17, "paramId" );
    paramId->setEnabled( FALSE );
    paramId->setGeometry( QRect( 210, 20, 41, 21 ) );
    paramId->setMaxValue( 15 );

    param2 = new QLabel( groupBox17, "param2" );
    param2->setGeometry( QRect( 140, 90, 110, 21 ) );

    hTimeText = new QLabel( groupBox17, "hTimeText" );
    hTimeText->setGeometry( QRect( 70, 130, 180, 20 ) );
    hTimeText->setAlignment( int( QLabel::AlignVCenter | QLabel::AlignRight ) );

    textLabel1_2_3_2 = new QLabel( groupBox17, "textLabel1_2_3_2" );
    textLabel1_2_3_2->setGeometry( QRect( 10, 130, 118, 20 ) );

    tabWidget11 = new QTabWidget( tab_3, "tabWidget11" );
    tabWidget11->setGeometry( QRect( 328, 4, 420, 221 ) );

    tab_4 = new QWidget( tabWidget11, "tab_4" );

    textLabel1_11_2 = new QLabel( tab_4, "textLabel1_11_2" );
    textLabel1_11_2->setGeometry( QRect( 10, 150, 90, 20 ) );

    textLabel1_10_2_2 = new QLabel( tab_4, "textLabel1_10_2_2" );
    textLabel1_10_2_2->setGeometry( QRect( 10, 170, 90, 20 ) );

    monRate2 = new QLabel( tab_4, "monRate2" );
    monRate2->setGeometry( QRect( 290, 170, 80, 20 ) );
    monRate2->setAlignment( int( QLabel::AlignVCenter | QLabel::AlignRight ) );

    monitor2 = new QLabel( tab_4, "monitor2" );
    monitor2->setGeometry( QRect( 290, 150, 80, 20 ) );
    monitor2->setAlignment( int( QLabel::AlignVCenter | QLabel::AlignRight ) );

    mTimeText = new QLabel( tab_4, "mTimeText" );
    mTimeText->setGeometry( QRect( 280, 10, 90, 20 ) );
    mTimeText->setAlignment( int( QLabel::AlignVCenter | QLabel::AlignRight ) );

    totalCounts = new QLabel( tab_4, "totalCounts" );
    totalCounts->setGeometry( QRect( 290, 60, 80, 20 ) );
    totalCounts->setAlignment( int( QLabel::AlignVCenter | QLabel::AlignRight ) );

    eventRate = new QLabel( tab_4, "eventRate" );
    eventRate->setGeometry( QRect( 290, 80, 80, 20 ) );
    eventRate->setAlignment( int( QLabel::AlignVCenter | QLabel::AlignRight ) );

    textLabel1 = new QLabel( tab_4, "textLabel1" );
    textLabel1->setGeometry( QRect( 10, 60, 90, 20 ) );

    textLabel1_10 = new QLabel( tab_4, "textLabel1_10" );
    textLabel1_10->setGeometry( QRect( 10, 80, 90, 20 ) );

    tSecsText = new QLabel( tab_4, "tSecsText" );
    tSecsText->setGeometry( QRect( 280, 30, 90, 20 ) );
    tSecsText->setAlignment( int( QLabel::AlignVCenter | QLabel::AlignRight ) );

    tPresetButton = new QPushButton( tab_4, "tPresetButton" );
    tPresetButton->setGeometry( QRect( 100, 30, 20, 20 ) );
    tPresetButton->setToggleButton( TRUE );

    ePresetButton = new QPushButton( tab_4, "ePresetButton" );
    ePresetButton->setGeometry( QRect( 100, 60, 20, 20 ) );
    ePresetButton->setToggleButton( TRUE );

    m2PresetButton = new QPushButton( tab_4, "m2PresetButton" );
    m2PresetButton->setGeometry( QRect( 100, 150, 20, 20 ) );
    m2PresetButton->setToggleButton( TRUE );

    tPreset = new QSpinBox( tab_4, "tPreset" );
    tPreset->setEnabled( FALSE );
    tPreset->setGeometry( QRect( 120, 30, 121, 21 ) );
    tPreset->setMaxValue( 1000000000 );

    textLabel1_2_3_2_3_2 = new QLabel( tab_4, "textLabel1_2_3_2_3_2" );
    textLabel1_2_3_2_3_2->setGeometry( QRect( 10, 30, 80, 20 ) );

    textLabel1_2_3_2_3 = new QLabel( tab_4, "textLabel1_2_3_2_3" );
    textLabel1_2_3_2_3->setGeometry( QRect( 10, 10, 80, 20 ) );

    evPreset = new QSpinBox( tab_4, "evPreset" );
    evPreset->setEnabled( FALSE );
    evPreset->setGeometry( QRect( 120, 60, 121, 21 ) );
    evPreset->setMaxValue( 1000000000 );

    m2Preset = new QSpinBox( tab_4, "m2Preset" );
    m2Preset->setEnabled( FALSE );
    m2Preset->setGeometry( QRect( 120, 150, 121, 21 ) );
    m2Preset->setMaxValue( 1000000000 );

    monitor1 = new QLabel( tab_4, "monitor1" );
    monitor1->setGeometry( QRect( 290, 110, 80, 20 ) );
    monitor1->setAlignment( int( QLabel::AlignVCenter | QLabel::AlignRight ) );

    textLabel1_11 = new QLabel( tab_4, "textLabel1_11" );
    textLabel1_11->setGeometry( QRect( 10, 110, 90, 20 ) );

    monRate1 = new QLabel( tab_4, "monRate1" );
    monRate1->setGeometry( QRect( 290, 130, 80, 20 ) );
    monRate1->setAlignment( int( QLabel::AlignVCenter | QLabel::AlignRight ) );

    m1PresetButton = new QPushButton( tab_4, "m1PresetButton" );
    m1PresetButton->setGeometry( QRect( 100, 110, 20, 20 ) );
    m1PresetButton->setToggleButton( TRUE );

    m1Preset = new QSpinBox( tab_4, "m1Preset" );
    m1Preset->setEnabled( FALSE );
    m1Preset->setGeometry( QRect( 120, 110, 121, 21 ) );
    m1Preset->setMaxValue( 1000000000 );

    textLabel1_10_2 = new QLabel( tab_4, "textLabel1_10_2" );
    textLabel1_10_2->setGeometry( QRect( 10, 130, 90, 20 ) );

    tResetButton = new QPushButton( tab_4, "tResetButton" );
    tResetButton->setGeometry( QRect( 380, 30, 20, 20 ) );
    tResetButton->setToggleButton( FALSE );

    eResetButton = new QPushButton( tab_4, "eResetButton" );
    eResetButton->setGeometry( QRect( 380, 60, 20, 20 ) );
    eResetButton->setToggleButton( FALSE );

    m1ResetButton = new QPushButton( tab_4, "m1ResetButton" );
    m1ResetButton->setGeometry( QRect( 380, 110, 20, 20 ) );
    m1ResetButton->setToggleButton( FALSE );

    m2RresetButton = new QPushButton( tab_4, "m2RresetButton" );
    m2RresetButton->setGeometry( QRect( 380, 150, 20, 20 ) );
    m2RresetButton->setToggleButton( FALSE );
    tabWidget11->insertTab( tab_4, QString::fromLatin1("") );

    tab_5 = new QWidget( tabWidget11, "tab_5" );

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
    tabWidget11->insertTab( tab_5, QString::fromLatin1("") );

    TabPage = new QWidget( tabWidget11, "TabPage" );

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
    tabWidget11->insertTab( TabPage, QString::fromLatin1("") );
    tabWidget2->insertTab( tab_3, QString::fromLatin1("") );

    tab_6 = new QWidget( tabWidget2, "tab_6" );

    textLabel1_5_2 = new QLabel( tab_6, "textLabel1_5_2" );
    textLabel1_5_2->setGeometry( QRect( 10, 10, 20, 20 ) );

    groupBox30 = new QGroupBox( tab_6, "groupBox30" );
    groupBox30->setGeometry( QRect( 10, 40, 130, 150 ) );

    master = new QCheckBox( groupBox30, "master" );
    master->setGeometry( QRect( 20, 20, 70, 20 ) );
    master->setChecked( TRUE );

    terminate = new QCheckBox( groupBox30, "terminate" );
    terminate->setEnabled( FALSE );
    terminate->setGeometry( QRect( 20, 50, 80, 20 ) );
    terminate->setChecked( TRUE );

    resetTimer = new QPushButton( groupBox30, "resetTimer" );
    resetTimer->setGeometry( QRect( 20, 100, 91, 20 ) );

    mcpdId = new QSpinBox( tab_6, "mcpdId" );
    mcpdId->setEnabled( FALSE );
    mcpdId->setGeometry( QRect( 40, 10, 61, 21 ) );
    mcpdId->setMaxValue( 8 );

    tabWidget5 = new QTabWidget( tab_6, "tabWidget5" );
    tabWidget5->setGeometry( QRect( 150, 10, 600, 210 ) );

    tab_7 = new QWidget( tabWidget5, "tab_7" );

    groupBox9 = new QGroupBox( tab_7, "groupBox9" );
    groupBox9->setGeometry( QRect( 10, 20, 360, 70 ) );

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

    groupBox9_2 = new QGroupBox( tab_7, "groupBox9_2" );
    groupBox9_2->setGeometry( QRect( 10, 100, 250, 70 ) );

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
    groupBox9_2_2->setGeometry( QRect( 280, 100, 270, 70 ) );

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

    groupBox16 = new QGroupBox( tab_7, "groupBox16" );
    groupBox16->setGeometry( QRect( 380, 20, 171, 70 ) );

    statusStream = new QCheckBox( groupBox16, "statusStream" );
    statusStream->setGeometry( QRect( 10, 30, 70, 21 ) );

    setStream = new QPushButton( groupBox16, "setStream" );
    setStream->setGeometry( QRect( 90, 29, 61, 21 ) );
    tabWidget5->insertTab( tab_7, QString::fromLatin1("") );

    tab_8 = new QWidget( tabWidget5, "tab_8" );

    groupBox29 = new QGroupBox( tab_8, "groupBox29" );
    groupBox29->setGeometry( QRect( 10, 10, 110, 60 ) );

    deviceId = new QSpinBox( groupBox29, "deviceId" );
    deviceId->setGeometry( QRect( 10, 20, 41, 21 ) );

    setID = new QPushButton( groupBox29, "setID" );
    setID->setGeometry( QRect( 60, 20, 41, 21 ) );

    groupBox6 = new QGroupBox( tab_8, "groupBox6" );
    groupBox6->setGeometry( QRect( 130, 10, 460, 160 ) );

    textLabel1_3_2 = new QLabel( groupBox6, "textLabel1_3_2" );
    textLabel1_3_2->setGeometry( QRect( 10, 80, 61, 21 ) );

    textLabel1_3_2_2 = new QLabel( groupBox6, "textLabel1_3_2_2" );
    textLabel1_3_2_2->setGeometry( QRect( 10, 50, 61, 21 ) );

    textLabel1_3_2_2_2 = new QLabel( groupBox6, "textLabel1_3_2_2_2" );
    textLabel1_3_2_2_2->setGeometry( QRect( 10, 110, 61, 21 ) );

    dataThisPc = new QCheckBox( groupBox6, "dataThisPc" );
    dataThisPc->setGeometry( QRect( 70, 80, 60, 20 ) );
    dataThisPc->setChecked( TRUE );

    cmdThisPc = new QCheckBox( groupBox6, "cmdThisPc" );
    cmdThisPc->setGeometry( QRect( 70, 110, 60, 20 ) );
    cmdThisPc->setChecked( TRUE );

    modifyIp = new QCheckBox( groupBox6, "modifyIp" );
    modifyIp->setGeometry( QRect( 70, 50, 60, 20 ) );
    modifyIp->setChecked( FALSE );

    mcpdIpAddress0 = new QLineEdit( groupBox6, "mcpdIpAddress0" );
    mcpdIpAddress0->setEnabled( FALSE );
    mcpdIpAddress0->setGeometry( QRect( 140, 50, 30, 20 ) );

    dataIpAddress0 = new QLineEdit( groupBox6, "dataIpAddress0" );
    dataIpAddress0->setEnabled( FALSE );
    dataIpAddress0->setGeometry( QRect( 140, 80, 30, 20 ) );

    dataIpAddress2 = new QLineEdit( groupBox6, "dataIpAddress2" );
    dataIpAddress2->setEnabled( FALSE );
    dataIpAddress2->setGeometry( QRect( 220, 80, 30, 20 ) );

    mcpdIpAddress1 = new QLineEdit( groupBox6, "mcpdIpAddress1" );
    mcpdIpAddress1->setEnabled( FALSE );
    mcpdIpAddress1->setGeometry( QRect( 180, 50, 30, 20 ) );

    dataIpAddress1 = new QLineEdit( groupBox6, "dataIpAddress1" );
    dataIpAddress1->setEnabled( FALSE );
    dataIpAddress1->setGeometry( QRect( 180, 80, 30, 20 ) );

    textLabel1_3_3_2_2 = new QLabel( groupBox6, "textLabel1_3_3_2_2" );
    textLabel1_3_3_2_2->setGeometry( QRect( 160, 20, 61, 21 ) );

    mcpdIpAddress3 = new QLineEdit( groupBox6, "mcpdIpAddress3" );
    mcpdIpAddress3->setEnabled( FALSE );
    mcpdIpAddress3->setGeometry( QRect( 260, 50, 30, 20 ) );

    mcpdIpAddress2 = new QLineEdit( groupBox6, "mcpdIpAddress2" );
    mcpdIpAddress2->setEnabled( FALSE );
    mcpdIpAddress2->setGeometry( QRect( 220, 50, 30, 20 ) );

    cmdIpAddress3 = new QLineEdit( groupBox6, "cmdIpAddress3" );
    cmdIpAddress3->setEnabled( FALSE );
    cmdIpAddress3->setGeometry( QRect( 260, 110, 30, 20 ) );

    dataIpAddress3 = new QLineEdit( groupBox6, "dataIpAddress3" );
    dataIpAddress3->setEnabled( FALSE );
    dataIpAddress3->setGeometry( QRect( 260, 80, 30, 20 ) );

    cmdIpAddress2 = new QLineEdit( groupBox6, "cmdIpAddress2" );
    cmdIpAddress2->setEnabled( FALSE );
    cmdIpAddress2->setGeometry( QRect( 220, 110, 30, 20 ) );

    cmdIpAddress1 = new QLineEdit( groupBox6, "cmdIpAddress1" );
    cmdIpAddress1->setEnabled( FALSE );
    cmdIpAddress1->setGeometry( QRect( 180, 110, 30, 20 ) );

    cmdIpAddress0 = new QLineEdit( groupBox6, "cmdIpAddress0" );
    cmdIpAddress0->setEnabled( FALSE );
    cmdIpAddress0->setGeometry( QRect( 140, 110, 30, 20 ) );

    textLabel1_3_3_2 = new QLabel( groupBox6, "textLabel1_3_3_2" );
    textLabel1_3_3_2->setGeometry( QRect( 310, 20, 50, 21 ) );

    dataUdpPort = new QSpinBox( groupBox6, "dataUdpPort" );
    dataUdpPort->setGeometry( QRect( 300, 80, 60, 21 ) );
    dataUdpPort->setMaxValue( 65536 );
    dataUdpPort->setValue( 0 );

    cmdUdpPort = new QSpinBox( groupBox6, "cmdUdpPort" );
    cmdUdpPort->setGeometry( QRect( 300, 110, 60, 21 ) );
    cmdUdpPort->setMaxValue( 65536 );
    cmdUdpPort->setValue( 0 );

    setIP = new QPushButton( groupBox6, "setIP" );
    setIP->setGeometry( QRect( 370, 80, 80, 30 ) );
    tabWidget5->insertTab( tab_8, QString::fromLatin1("") );
    tabWidget2->insertTab( tab_6, QString::fromLatin1("") );

    TabPage_2 = new QWidget( tabWidget2, "TabPage_2" );

    tabWidget4 = new QTabWidget( TabPage_2, "tabWidget4" );
    tabWidget4->setGeometry( QRect( 9, 4, 720, 220 ) );

    tab_9 = new QWidget( tabWidget4, "tab_9" );

    devid_2 = new QSpinBox( tab_9, "devid_2" );
    devid_2->setEnabled( FALSE );
    devid_2->setGeometry( QRect( 80, 30, 50, 21 ) );
    devid_2->setMaxValue( 255 );

    textLabel1_4_2_4 = new QLabel( tab_9, "textLabel1_4_2_4" );
    textLabel1_4_2_4->setGeometry( QRect( 10, 30, 63, 21 ) );

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

    textLabel1_4_2 = new QLabel( tab_10, "textLabel1_4_2" );
    textLabel1_4_2->setGeometry( QRect( 10, 20, 63, 21 ) );

    modeGroup = new QButtonGroup( tab_10, "modeGroup" );
    modeGroup->setGeometry( QRect( 10, 90, 130, 80 ) );

    pos = new QRadioButton( modeGroup, "pos" );
    pos->setGeometry( QRect( 10, 20, 70, 20 ) );
    pos->setChecked( TRUE );
    modeGroup->insert( pos, 0 );

    amp = new QRadioButton( modeGroup, "amp" );
    amp->setGeometry( QRect( 10, 50, 80, 20 ) );
    modeGroup->insert( amp, 1 );

    groupBox35 = new QGroupBox( tab_10, "groupBox35" );
    groupBox35->setGeometry( QRect( 150, 10, 560, 70 ) );

    textLabel1_4_2_3_4 = new QLabel( groupBox35, "textLabel1_4_2_3_4" );
    textLabel1_4_2_3_4->setGeometry( QRect( 90, 30, 50, 21 ) );

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

    pulsChan = new QSpinBox( groupBox35, "pulsChan" );
    pulsChan->setGeometry( QRect( 140, 30, 40, 21 ) );
    pulsChan->setMaxValue( 7 );

    pulserButton = new QPushButton( groupBox35, "pulserButton" );
    pulserButton->setGeometry( QRect( 17, 24, 61, 31 ) );
    pulserButton->setToggleButton( TRUE );

    module = new QSpinBox( tab_10, "module" );
    module->setGeometry( QRect( 80, 50, 50, 21 ) );
    module->setMaxValue( 255 );

    devid = new QSpinBox( tab_10, "devid" );
    devid->setEnabled( FALSE );
    devid->setGeometry( QRect( 80, 20, 50, 21 ) );
    devid->setMaxValue( 255 );
    tabWidget4->insertTab( tab_10, QString::fromLatin1("") );
    tabWidget2->insertTab( TabPage_2, QString::fromLatin1("") );

    TabPage_3 = new QWidget( tabWidget2, "TabPage_3" );

    groupBox15 = new QGroupBox( TabPage_3, "groupBox15" );
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

    groupBox20 = new QGroupBox( TabPage_3, "groupBox20" );
    groupBox20->setGeometry( QRect( 8, 74, 271, 111 ) );

    timingBox = new QSpinBox( groupBox20, "timingBox" );
    timingBox->setGeometry( QRect( 130, 30, 50, 20 ) );
    timingBox->setMaxValue( 48 );
    timingBox->setMinValue( 1 );

    textLabel1_8 = new QLabel( groupBox20, "textLabel1_8" );
    textLabel1_8->setGeometry( QRect( 20, 30, 79, 29 ) );
    tabWidget2->insertTab( TabPage_3, QString::fromLatin1("") );

    TabPage_4 = new QWidget( tabWidget2, "TabPage_4" );

    groupBox79_2 = new QGroupBox( TabPage_4, "groupBox79_2" );
    groupBox79_2->setGeometry( QRect( 10, 110, 240, 110 ) );

    saveSetupButton = new QPushButton( groupBox79_2, "saveSetupButton" );
    saveSetupButton->setGeometry( QRect( 20, 20, 50, 26 ) );

    restoreSetupButton = new QPushButton( groupBox79_2, "restoreSetupButton" );
    restoreSetupButton->setGeometry( QRect( 90, 20, 50, 26 ) );

    textLabel2_2 = new QLabel( groupBox79_2, "textLabel2_2" );
    textLabel2_2->setGeometry( QRect( 20, 50, 171, 20 ) );

    configfilename = new QLabel( groupBox79_2, "configfilename" );
    configfilename->setGeometry( QRect( 20, 70, 191, 21 ) );

    groupBox35_2 = new QGroupBox( TabPage_4, "groupBox35_2" );
    groupBox35_2->setGeometry( QRect( 260, 110, 431, 110 ) );

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
    groupBox79->setGeometry( QRect( 10, 10, 470, 90 ) );

    acqListfile = new QCheckBox( groupBox79, "acqListfile" );
    acqListfile->setGeometry( QRect( 20, 20, 100, 20 ) );

    replayButton = new QPushButton( groupBox79, "replayButton" );
    replayButton->setGeometry( QRect( 350, 40, 100, 26 ) );

    listFilename = new QLineEdit( groupBox79, "listFilename" );
    listFilename->setGeometry( QRect( 20, 40, 230, 26 ) );

    selectButton = new QPushButton( groupBox79, "selectButton" );
    selectButton->setGeometry( QRect( 260, 40, 50, 26 ) );

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
    tabWidget2->insertTab( TabPage_4, QString::fromLatin1("") );
    languageChange();
    resize( QSize(1280, 950).expandedTo(minimumSizeHint()) );
    clearWState( WState_Polished );

    // signals and slots connections
    connect( acqListfile, SIGNAL( toggled(bool) ), acquireFile, SLOT( setChecked(bool) ) );
    connect( acqListfile, SIGNAL( toggled(bool) ), this, SLOT( acqListfileSlot() ) );
    connect( acquireFile, SIGNAL( toggled(bool) ), acqListfile, SLOT( setChecked(bool) ) );
    connect( allPulsersoffButton, SIGNAL( clicked() ), this, SLOT( allPulserSlot() ) );
    connect( applyDispThreshButton, SIGNAL( clicked() ), this, SLOT( applyThreshSlot() ) );
    connect( cellSource, SIGNAL( activated(int) ), this, SLOT( displayMcpdSlot() ) );
    connect( channel, SIGNAL( valueChanged(int) ), this, SLOT( displayMpsdSlot() ) );
    connect( clearAll, SIGNAL( clicked() ), this, SLOT( clearAllSlot() ) );
    connect( clearChan, SIGNAL( clicked() ), this, SLOT( clearChanSlot() ) );
    connect( clearMcpd, SIGNAL( clicked() ), this, SLOT( clearMcpdSlot() ) );
    connect( clearMpsd, SIGNAL( clicked() ), this, SLOT( clearMpsdSlot() ) );
    connect( cmdThisPc, SIGNAL( toggled(bool) ), cmdIpAddress3, SLOT( setDisabled(bool) ) );
    connect( cmdThisPc, SIGNAL( toggled(bool) ), cmdIpAddress2, SLOT( setDisabled(bool) ) );
    connect( cmdThisPc, SIGNAL( toggled(bool) ), cmdIpAddress1, SLOT( setDisabled(bool) ) );
    connect( cmdThisPc, SIGNAL( toggled(bool) ), cmdIpAddress0, SLOT( setDisabled(bool) ) );
    connect( comgain, SIGNAL( toggled(bool) ), channel, SLOT( setDisabled(bool) ) );
    connect( dataThisPc, SIGNAL( toggled(bool) ), dataIpAddress3, SLOT( setDisabled(bool) ) );
    connect( dataThisPc, SIGNAL( toggled(bool) ), dataIpAddress2, SLOT( setDisabled(bool) ) );
    connect( dataThisPc, SIGNAL( toggled(bool) ), dataIpAddress1, SLOT( setDisabled(bool) ) );
    connect( dataThisPc, SIGNAL( toggled(bool) ), dataIpAddress0, SLOT( setDisabled(bool) ) );
    connect( dispAll, SIGNAL( toggled(bool) ), buttonGroup10, SLOT( setEnabled(bool) ) );
    connect( dispAll, SIGNAL( toggled(bool) ), specialBox, SLOT( setDisabled(bool) ) );
    connect( dispAll, SIGNAL( toggled(bool) ), clearChan, SLOT( setDisabled(bool) ) );
    connect( dispAll, SIGNAL( toggled(bool) ), clearMpsd, SLOT( setDisabled(bool) ) );
    connect( dispAll, SIGNAL( toggled(bool) ), clearMcpd, SLOT( setDisabled(bool) ) );
    connect( dispAll, SIGNAL( toggled(bool) ), dispChan, SLOT( setDisabled(bool) ) );
    connect( dispAll, SIGNAL( toggled(bool) ), dispMpsd, SLOT( setDisabled(bool) ) );
    connect( dispAll, SIGNAL( toggled(bool) ), dispMcpd, SLOT( setDisabled(bool) ) );
    connect( ePresetButton, SIGNAL( toggled(bool) ), this, SLOT( ePresetSlot(bool) ) );
    connect( eResetButton, SIGNAL( clicked() ), this, SLOT( eResetSlot() ) );
    connect( logGroup, SIGNAL( clicked(int) ), this, SLOT( linlogSlot() ) );
    connect( logGroup, SIGNAL( toggled(bool) ), this, SLOT( redrawSlot() ) );
    connect( m1PresetButton, SIGNAL( toggled(bool) ), this, SLOT( m1PresetSlot(bool) ) );
    connect( m1ResetButton, SIGNAL( clicked() ), this, SLOT( m1ResetSlot() ) );
    connect( m2PresetButton, SIGNAL( toggled(bool) ), this, SLOT( m2PresetSlot(bool) ) );
    connect( m2RresetButton, SIGNAL( clicked() ), this, SLOT( m2ResetSlot() ) );
    connect( master, SIGNAL( toggled(bool) ), terminate, SLOT( setChecked(bool) ) );
    connect( master, SIGNAL( toggled(bool) ), resetTimer, SLOT( setEnabled(bool) ) );
    connect( master, SIGNAL( toggled(bool) ), terminate, SLOT( setDisabled(bool) ) );
    connect( master, SIGNAL( toggled(bool) ), this, SLOT( setTimingSlot() ) );
    connect( mcpdId, SIGNAL( valueChanged(int) ), this, SLOT( displayMcpdSlot() ) );
    connect( modeGroup, SIGNAL( clicked(int) ), this, SLOT( setModeSlot(int) ) );
    connect( modifyIp, SIGNAL( toggled(bool) ), mcpdIpAddress3, SLOT( setEnabled(bool) ) );
    connect( modifyIp, SIGNAL( toggled(bool) ), mcpdIpAddress2, SLOT( setEnabled(bool) ) );
    connect( modifyIp, SIGNAL( toggled(bool) ), mcpdIpAddress1, SLOT( setEnabled(bool) ) );
    connect( modifyIp, SIGNAL( toggled(bool) ), mcpdIpAddress0, SLOT( setEnabled(bool) ) );
    connect( module, SIGNAL( valueChanged(int) ), this, SLOT( displayMpsdSlot() ) );
    connect( param, SIGNAL( valueChanged(int) ), this, SLOT( displayMcpdSlot() ) );
    connect( pulsAmp1, SIGNAL( returnPressed() ), this, SLOT( setPulserSlot() ) );
    connect( pulsAmp1, SIGNAL( lostFocus() ), this, SLOT( setPulserSlot() ) );
    connect( pulsAmp2, SIGNAL( returnPressed() ), this, SLOT( setPulserSlot() ) );
    connect( pulsAmp2, SIGNAL( lostFocus() ), this, SLOT( setPulserSlot() ) );
    connect( pulsampRadio1, SIGNAL( toggled(bool) ), this, SLOT( setPulserSlot() ) );
    connect( pulsampRadio1, SIGNAL( toggled(bool) ), pulsAmp1, SLOT( setEnabled(bool) ) );
    connect( pulsampRadio2, SIGNAL( toggled(bool) ), this, SLOT( setPulserSlot() ) );
    connect( pulsampRadio2, SIGNAL( toggled(bool) ), pulsAmp2, SLOT( setEnabled(bool) ) );
    connect( pulsChan, SIGNAL( valueChanged(int) ), this, SLOT( setPulserSlot() ) );
    connect( pulserButton, SIGNAL( toggled(bool) ), this, SLOT( setPulserSlot() ) );
    connect( pulsLeft, SIGNAL( toggled(bool) ), this, SLOT( setPulserSlot() ) );
    connect( pulsMid, SIGNAL( toggled(bool) ), this, SLOT( setPulserSlot() ) );
    connect( pulsRight, SIGNAL( toggled(bool) ), this, SLOT( setPulserSlot() ) );
    connect( readRegisterButton, SIGNAL( clicked() ), this, SLOT( readRegisterSlot() ) );
    connect( replayButton, SIGNAL( clicked() ), this, SLOT( replayListfileSlot() ) );
    connect( resetTimer, SIGNAL( clicked() ), this, SLOT( resetTimerSlot() ) );
    connect( restoreSetupButton, SIGNAL( clicked() ), this, SLOT( restoreSetupSlot() ) );
    connect( saveSetupButton, SIGNAL( clicked() ), this, SLOT( saveConfigSlot() ) );
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
    connect( specialBox, SIGNAL( clicked() ), this, SLOT( redrawSlot() ) );
    connect( startStopButton, SIGNAL( clicked() ), this, SLOT( startStopSlot() ) );
    connect( tabWidget2, SIGNAL( selected(const QString&) ), this, SLOT( displayMcpdSlot() ) );
    connect( tabWidget5, SIGNAL( selected(const QString&) ), this, SLOT( displayMcpdSlot() ) );
    connect( terminate, SIGNAL( toggled(bool) ), this, SLOT( setTimingSlot() ) );
    connect( timer, SIGNAL( valueChanged(int) ), this, SLOT( displayMcpdSlot() ) );
    connect( tPresetButton, SIGNAL( toggled(bool) ), this, SLOT( tPresetSlot(bool) ) );
    connect( tResetButton, SIGNAL( clicked() ), this, SLOT( tResetSlot() ) );
    connect( useThresh, SIGNAL( clicked() ), this, SLOT( applyThreshSlot() ) );
    connect( useThresh, SIGNAL( toggled(bool) ), hiLim, SLOT( setEnabled(bool) ) );
    connect( useThresh, SIGNAL( toggled(bool) ), loLim, SLOT( setEnabled(bool) ) );
    connect( writeHistButton, SIGNAL( clicked() ), this, SLOT( writeHistSlot() ) );
    connect( writeRegisterButton, SIGNAL( clicked() ), this, SLOT( writeRegisterSlot() ) );
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
    logGroup->setTitle( QString::null );
    lin->setText( tr2i18n( "&lin" ) );
    log->setText( tr2i18n( "log" ) );
    specialBox->setText( tr2i18n( "delta-t" ) );
    dispAll->setText( tr2i18n( "Sum spectra" ) );
    dispAll->setAccel( QKeySequence( QString::null ) );
    textLabel2->setText( tr2i18n( "0-7: position\n"
"8-15: energy" ) );
    clearChan->setText( tr2i18n( "clear" ) );
    clearChan->setAccel( QKeySequence( QString::null ) );
    clearMcpd->setText( tr2i18n( "clear" ) );
    clearMcpd->setAccel( QKeySequence( QString::null ) );
    textLabel1_4_2_3_4_2_2_2->setText( tr2i18n( "Channel" ) );
    textLabel1_4_2_3_4_2->setText( tr2i18n( "MCPD" ) );
    textLabel1_4_2_3_4_2_2->setText( tr2i18n( "MPSD" ) );
    clearMpsd->setText( tr2i18n( "clear" ) );
    clearMpsd->setAccel( QKeySequence( QString::null ) );
    clearAll->setText( tr2i18n( "clear all" ) );
    clearAll->setAccel( QKeySequence( QString::null ) );
    buttonGroup10->setTitle( QString::null );
    dispAllAmpl->setText( tr2i18n( "Ampl" ) );
    dispAllAmpl->setAccel( QKeySequence( QString::null ) );
    dispAllPos->setText( tr2i18n( "Pos" ) );
    dispAllPos->setAccel( QKeySequence( QString::null ) );
    tabWidget5_2->changeTab( tab, tr2i18n( "Display" ) );
    useThresh->setText( tr2i18n( "Thresholds" ) );
    loLim->setText( tr2i18n( "0" ) );
    textLabel1_6->setText( tr2i18n( "low" ) );
    textLabel1_6_2->setText( tr2i18n( "hi" ) );
    hiLim->setText( tr2i18n( "1000000000" ) );
    applyDispThreshButton->setText( tr2i18n( "apply" ) );
    tabWidget5_2->changeTab( tab_2, tr2i18n( "Thresholds" ) );
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
    groupBox17->setTitle( tr2i18n( "Parameters" ) );
    textLabel1_3_6->setText( tr2i18n( "MCPD-ID:" ) );
    textLabel1_3->setText( tr2i18n( "P0:" ) );
    textLabel1_3_3->setText( tr2i18n( "P1:" ) );
    textLabel1_3_4->setText( tr2i18n( "P2:" ) );
    textLabel1_3_5->setText( tr2i18n( "P3:" ) );
    param0->setText( tr2i18n( "<p align=\"right\">0</p>" ) );
    param1->setText( tr2i18n( "<p align=\"right\">0</p>" ) );
    param3->setText( tr2i18n( "<p align=\"right\">0</p>" ) );
    param2->setText( tr2i18n( "<p align=\"right\">0</p>" ) );
    hTimeText->setText( tr2i18n( "0" ) );
    textLabel1_2_3_2->setText( tr2i18n( "header time:" ) );
    textLabel1_11_2->setText( tr2i18n( "Monitor 2" ) );
    textLabel1_10_2_2->setText( tr2i18n( "Monitor 2 rate" ) );
    monRate2->setText( tr2i18n( "0" ) );
    monitor2->setText( tr2i18n( "0" ) );
    mTimeText->setText( tr2i18n( "0" ) );
    totalCounts->setText( tr2i18n( "0" ) );
    eventRate->setText( tr2i18n( "0" ) );
    textLabel1->setText( tr2i18n( "Event counter" ) );
    textLabel1_10->setText( tr2i18n( "Event rate" ) );
    tSecsText->setText( tr2i18n( "0" ) );
    tPresetButton->setText( tr2i18n( "P" ) );
    QToolTip::add( tPresetButton, tr2i18n( "activate preset for timer" ) );
    ePresetButton->setText( tr2i18n( "P" ) );
    QToolTip::add( ePresetButton, tr2i18n( "activate preset for event counter" ) );
    m2PresetButton->setText( tr2i18n( "P" ) );
    QToolTip::add( m2PresetButton, tr2i18n( "activate preset for monitor 2" ) );
    QToolTip::add( tPreset, tr2i18n( "preset value for timer" ) );
    textLabel1_2_3_2_3_2->setText( tr2i18n( "Timer [s]:" ) );
    textLabel1_2_3_2_3->setText( tr2i18n( "Timer [h:m:s]:" ) );
    QToolTip::add( evPreset, tr2i18n( "preset value for event counter" ) );
    QToolTip::add( m2Preset, tr2i18n( "preset value for monitor 2" ) );
    monitor1->setText( tr2i18n( "0" ) );
    textLabel1_11->setText( tr2i18n( "Monitor 1" ) );
    monRate1->setText( tr2i18n( "0" ) );
    m1PresetButton->setText( tr2i18n( "P" ) );
    QToolTip::add( m1PresetButton, tr2i18n( "activate preset for monitor 1" ) );
    QToolTip::add( m1Preset, tr2i18n( "preset value for monitor 1" ) );
    textLabel1_10_2->setText( tr2i18n( "Monitor 1 rate" ) );
    tResetButton->setText( tr2i18n( "R" ) );
    QToolTip::add( tResetButton, tr2i18n( "reset timer" ) );
    eResetButton->setText( tr2i18n( "R" ) );
    QToolTip::add( eResetButton, tr2i18n( "reset event counter" ) );
    m1ResetButton->setText( tr2i18n( "R" ) );
    QToolTip::add( m1ResetButton, tr2i18n( "reset monitor 1" ) );
    m2RresetButton->setText( tr2i18n( "R" ) );
    QToolTip::add( m2RresetButton, tr2i18n( "reset monitor 2" ) );
    tabWidget11->changeTab( tab_4, tr2i18n( "meas. data" ) );
    textLabel1_2_3->setText( tr2i18n( "cmd buffers reveived:" ) );
    textLabel1_2->setText( tr2i18n( "cmd buffers transmitted:" ) );
    cmdTx->setText( tr2i18n( "0" ) );
    cmdRx->setText( tr2i18n( "0" ) );
    textLabel1_2_2->setText( tr2i18n( "data buffers received:" ) );
    dataRx->setText( tr2i18n( "0" ) );
    tabWidget11->changeTab( tab_5, tr2i18n( "statistics" ) );
    textLabel1_12->setText( tr2i18n( "height:" ) );
    textLabel1_12_2->setText( tr2i18n( "width:" ) );
    textLabel1_12_2_2->setText( tr2i18n( "run#" ) );
    caressHeight->setText( tr2i18n( "<p align=\"right\">0</p>" ) );
    caressWidth->setText( tr2i18n( "<p align=\"right\">0</p>" ) );
    caressRun->setText( tr2i18n( "<p align=\"right\">0</p>" ) );
    tabWidget11->changeTab( TabPage, tr2i18n( "Caress" ) );
    tabWidget2->changeTab( tab_3, tr2i18n( "S&tatus" ) );
    textLabel1_5_2->setText( tr2i18n( "ID" ) );
    groupBox30->setTitle( tr2i18n( "Master / Termination" ) );
    QToolTip::add( groupBox30, QString::null );
    master->setText( tr2i18n( "Master" ) );
    master->setAccel( QKeySequence( QString::null ) );
    terminate->setText( tr2i18n( "&terminate" ) );
    terminate->setAccel( QKeySequence( tr2i18n( "Alt+T" ) ) );
    resetTimer->setText( tr2i18n( "&Reset Timer" ) );
    resetTimer->setAccel( QKeySequence( tr2i18n( "Alt+R" ) ) );
    QToolTip::add( resetTimer, tr2i18n( "reset master clock" ) );
    QToolTip::add( mcpdId, tr2i18n( "MCPD-ID to address " ) );
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
    groupBox16->setTitle( tr2i18n( "Status Stream" ) );
    statusStream->setText( tr2i18n( "stream" ) );
    QToolTip::add( statusStream, tr2i18n( "send status stream when daq is stopped" ) );
    setStream->setText( tr2i18n( "send" ) );
    tabWidget5->changeTab( tab_7, tr2i18n( "Settings" ) );
    groupBox29->setTitle( tr2i18n( "MCPD-8 ID" ) );
    setID->setText( tr2i18n( "set ID" ) );
    groupBox6->setTitle( tr2i18n( "IP / UDP settings" ) );
    textLabel1_3_2->setText( tr2i18n( "<b>Data pc</b>" ) );
    textLabel1_3_2_2->setText( tr2i18n( "<b>MCPD-8</b>" ) );
    textLabel1_3_2_2_2->setText( tr2i18n( "<b>Cmd pc</b>" ) );
    dataThisPc->setText( tr2i18n( "this pc" ) );
    cmdThisPc->setText( tr2i18n( "this pc" ) );
    modifyIp->setText( tr2i18n( "modify" ) );
    mcpdIpAddress0->setText( tr2i18n( "192" ) );
    dataIpAddress0->setText( tr2i18n( "192" ) );
    dataIpAddress2->setText( tr2i18n( "168" ) );
    mcpdIpAddress1->setText( tr2i18n( "168" ) );
    dataIpAddress1->setText( tr2i18n( "168" ) );
    textLabel1_3_3_2_2->setText( tr2i18n( "ip address" ) );
    mcpdIpAddress3->setText( tr2i18n( "121" ) );
    mcpdIpAddress2->setText( tr2i18n( "168" ) );
    cmdIpAddress3->setText( tr2i18n( "5" ) );
    dataIpAddress3->setText( tr2i18n( "5" ) );
    cmdIpAddress2->setText( tr2i18n( "168" ) );
    cmdIpAddress1->setText( tr2i18n( "168" ) );
    cmdIpAddress0->setText( tr2i18n( "0" ) );
    textLabel1_3_3_2->setText( tr2i18n( "udp port" ) );
    setIP->setText( tr2i18n( "set &comm\n"
"parameters" ) );
    setIP->setAccel( QKeySequence( tr2i18n( "Alt+C" ) ) );
    tabWidget5->changeTab( tab_8, tr2i18n( "Communication / Networ&k" ) );
    tabWidget2->changeTab( tab_6, tr2i18n( "MCPD-&8" ) );
    textLabel1_4_2_4->setText( tr2i18n( "MCPD-8 ID" ) );
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
    textLabel1_4_2->setText( tr2i18n( "MCPD-8 ID" ) );
    modeGroup->setTitle( tr2i18n( "Mode" ) );
    pos->setText( tr2i18n( "Position" ) );
    amp->setText( tr2i18n( "Amplitude" ) );
    groupBox35->setTitle( tr2i18n( "Pulser" ) );
    textLabel1_4_2_3_4->setText( tr2i18n( "Channel" ) );
    buttonGroup4->setTitle( tr2i18n( "Position" ) );
    pulsLeft->setText( tr2i18n( "left" ) );
    pulsMid->setText( tr2i18n( "mid" ) );
    pulsRight->setText( tr2i18n( "right" ) );
    buttonGroup5->setTitle( tr2i18n( "Amplitude [%]" ) );
    pulsAmp2->setText( tr2i18n( "90" ) );
    QToolTip::add( pulsAmp2, tr2i18n( "alternative pulser amplitude" ) );
    pulsampRadio1->setText( QString::null );
    pulsampRadio2->setText( QString::null );
    pulsAmp1->setText( tr2i18n( "50" ) );
    QToolTip::add( pulsAmp1, tr2i18n( "main pulser amplitude" ) );
    QToolTip::add( pulsChan, tr2i18n( "pulser channel" ) );
    pulserButton->setText( tr2i18n( "Pulser" ) );
    QToolTip::add( pulserButton, tr2i18n( "toggle pulser on/off" ) );
    tabWidget4->changeTab( tab_10, tr2i18n( "Settings" ) );
    tabWidget2->changeTab( TabPage_2, tr2i18n( "MPSD-8" ) );
    groupBox15->setTitle( tr2i18n( "Run ID" ) );
    QToolTip::add( runId, tr2i18n( "RUN ID will be transmitted in every data buffer header" ) );
    runIdAuto->setText( tr2i18n( "Auto Incr." ) );
    runIdAuto->setAccel( QKeySequence( QString::null ) );
    QToolTip::add( runIdAuto, tr2i18n( "increment run ID automatically at every start cmd" ) );
    runIdButton->setText( tr2i18n( "set Run ID" ) );
    groupBox20->setTitle( tr2i18n( "Timing Delta Histogram" ) );
    textLabel1_8->setText( tr2i18n( "Binwidth [bits]\n"
"1 bit = 100 ns" ) );
    tabWidget2->changeTab( TabPage_3, tr2i18n( "General" ) );
    groupBox79_2->setTitle( tr2i18n( "Setup" ) );
    saveSetupButton->setText( tr2i18n( "sa&ve" ) );
    saveSetupButton->setAccel( QKeySequence( tr2i18n( "Alt+V" ) ) );
    restoreSetupButton->setText( tr2i18n( "restore" ) );
    restoreSetupButton->setAccel( QKeySequence( QString::null ) );
    textLabel2_2->setText( tr2i18n( "Currently loaded:" ) );
    configfilename->setText( tr2i18n( "Default setup" ) );
    groupBox35_2->setTitle( tr2i18n( "Default paths" ) );
    textLabel1_9_3->setText( tr2i18n( "Config files" ) );
    textLabel1_9_2->setText( tr2i18n( "Histograms" ) );
    textLabel1_9->setText( tr2i18n( "Listmode files" ) );
    selectListpath->setText( tr2i18n( "select" ) );
    selectConfigpath->setText( tr2i18n( "select" ) );
    selectHistpath->setText( tr2i18n( "select" ) );
    groupBox79->setTitle( tr2i18n( "Listmode data acquisition" ) );
    acqListfile->setText( tr2i18n( "ac&quire listfile:" ) );
    acqListfile->setAccel( QKeySequence( tr2i18n( "Alt+Q" ) ) );
    replayButton->setText( tr2i18n( "Repla&y Listfile" ) );
    replayButton->setAccel( QKeySequence( tr2i18n( "Alt+Y" ) ) );
    selectButton->setText( tr2i18n( "select" ) );
    groupBox36->setTitle( tr2i18n( "Histograms" ) );
    textLabel2_2_2->setText( tr2i18n( "Currently loaded:" ) );
    histfilename->setText( tr2i18n( "-" ) );
    writeHistButton->setText( tr2i18n( "Write" ) );
    writeHistButton->setAccel( QKeySequence( QString::null ) );
    LoadhistButton->setText( tr2i18n( "Load" ) );
    LoadhistButton->setAccel( QKeySequence( QString::null ) );
    tabWidget2->changeTab( TabPage_4, tr2i18n( "Fi&les" ) );
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

#include "mesydaq2mainwindow.moc"
