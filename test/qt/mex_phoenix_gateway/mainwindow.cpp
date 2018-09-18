#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QtDebug>
#include <stddef.h>

#include "ap_bsp.h"
#include "ap.h"
#include "ap_eeprom.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->pushButtonRun->setEnabled(false);
    ui->pushButtonRun->setText("Start");
    running = false;
    runCount = 0;

    runTimer = new QTimer(this);
    connect(runTimer, SIGNAL(timeout()), this, SLOT(run()));

#if 0
    qDebug("0x%04X:  UNUSED_VAR2                ",  EE_MIRROR_VAR_ADDRESS(UNUSED_VAR2             ));
    qDebug("0x%04X:  ee_ThrottleCalRetracted    ",  EE_MIRROR_VAR_ADDRESS(ee_ThrottleCalRetracted ));
    qDebug("0x%04X:  ee_ThrottleCalExtended     ",  EE_MIRROR_VAR_ADDRESS(ee_ThrottleCalExtended  ));
    qDebug("0x%04X:  UNUSED_VAR3                ",  EE_MIRROR_VAR_ADDRESS(UNUSED_VAR3             ));
    qDebug("0x%04X:  ee_ThrottleCalState        ",  EE_MIRROR_VAR_ADDRESS(ee_ThrottleCalState     ));
    qDebug("0x%04X:  var2Checksum               ",  EE_MIRROR_VAR_ADDRESS(var2Checksum            ));

    qDebug("0x%04X:  userInfo                   ",  EE_MIRROR_VAR_ADDRESS(userInfo                ));
    qDebug("0x%04X:  doNotUse_0                 ",  EE_MIRROR_VAR_ADDRESS(doNotUse_0              ));
    qDebug("0x%04X:  queueServiceIntervals      ",  EE_MIRROR_VAR_ADDRESS(queueServiceIntervals   ));
    qDebug("0x%04X:  vitals                     ",  EE_MIRROR_VAR_ADDRESS(vitals                  ));
    qDebug("0x%04X:  queueUserLog               ",  EE_MIRROR_VAR_ADDRESS(queueUserLog            ));
    qDebug("0x%04X:  queueSwUpdate              ",  EE_MIRROR_VAR_ADDRESS(queueSwUpdate           ));
    qDebug("0x%04X:  NOT_USED                   ",  EE_MIRROR_VAR_ADDRESS(NOT_USED                ));
    qDebug("0x%04X:  password                   ",  EE_MIRROR_VAR_ADDRESS(password                ));
    qDebug("0x%04X:  UNUSED                     ",  EE_MIRROR_VAR_ADDRESS(UNUSED                  ));
    qDebug("0x%04X:  event                      ",  EE_MIRROR_VAR_ADDRESS(event                   ));
    qDebug("0x%04X:  queue                      ",  EE_MIRROR_VAR_ADDRESS(queue                   ));
    qDebug("0x%04X:  doNotUse_1                 ",  EE_MIRROR_VAR_ADDRESS(doNotUse_1              ));
    qDebug("0x%04X:  queueService               ",  EE_MIRROR_VAR_ADDRESS(queueService            ));
    qDebug("0x%04X:  UNUSED_EVENTS              ",  EE_MIRROR_VAR_ADDRESS(UNUSED_EVENTS           ));

    qDebug("0x%04X:  serviceClockResetTime      ",  EE_MIRROR_VAR_ADDRESS(serviceClockResetTime   ));
    qDebug("0x%04X:  serviceClockLength         ",  EE_MIRROR_VAR_ADDRESS(serviceClockLength      ));
    qDebug("0x%04X:  consoleTest                ",  EE_MIRROR_VAR_ADDRESS(consoleTest             ));
    qDebug("0x%04X:  serviceClockExpired        ",  EE_MIRROR_VAR_ADDRESS(serviceClockExpired     ));
    qDebug("0x%04X:  jobClock                   ",  EE_MIRROR_VAR_ADDRESS(jobClock                ));
    qDebug("0x%04X:  ee_AuxConfig               ",  EE_MIRROR_VAR_ADDRESS(ee_AuxConfig            ));
    qDebug("0x%04X:  oldAppVersion              ",  EE_MIRROR_VAR_ADDRESS(oldAppVersion           ));
    qDebug("0x%04X:  oldCDVersion               ",  EE_MIRROR_VAR_ADDRESS(oldCDVersion            ));
    qDebug("0x%04X:  serviceClockType           ",  EE_MIRROR_VAR_ADDRESS(serviceClockType        ));
    qDebug("0x%04X:  ee_Version                 ",  EE_MIRROR_VAR_ADDRESS(ee_Version              ));
    qDebug("0x%04X:  EngData                    ",  EE_MIRROR_VAR_ADDRESS(EngData                 ));
    qDebug("0x%04X:  machineIdleTime            ",  EE_MIRROR_VAR_ADDRESS(machineIdleTime         ));
    qDebug("0x%04X:  machineFuelConsumption     ",  EE_MIRROR_VAR_ADDRESS(machineFuelConsumption  ));
    qDebug("0x%04X:  ee_AutoIdleEnabled         ",  EE_MIRROR_VAR_ADDRESS(ee_AutoIdleEnabled      ));
    qDebug("0x%04X:  sparevar1                  ",  EE_MIRROR_VAR_ADDRESS(sparevar1               ));
    qDebug("0x%04X:  ee_autoIdleTime            ",  EE_MIRROR_VAR_ADDRESS(ee_autoIdleTime         ));
    qDebug("0x%04X:  jobClockLHP                ",  EE_MIRROR_VAR_ADDRESS(jobClockLHP             ));
    qDebug("0x%04X:  deluxe_G5                  ",  EE_MIRROR_VAR_ADDRESS(deluxe_G5               ));
    qDebug("0x%04X:  keypad                     ",  EE_MIRROR_VAR_ADDRESS(keypad                  ));
    qDebug("0x%04X:  RFIDKey                    ",  EE_MIRROR_VAR_ADDRESS(RFIDKey                 ));
    qDebug("0x%04X:  passwordLock               ",  EE_MIRROR_VAR_ADDRESS(passwordLock            ));
    qDebug("0x%04X:  jobClockLock               ",  EE_MIRROR_VAR_ADDRESS(jobClockLock            ));
    qDebug("0x%04X:  serviceClockLock           ",  EE_MIRROR_VAR_ADDRESS(serviceClockLock        ));
    qDebug("0x%04X:  sparevar2                  ",  EE_MIRROR_VAR_ADDRESS(sparevar2               ));
    qDebug("0x%04X:  ee_EcoMode                 ",  EE_MIRROR_VAR_ADDRESS(ee_EcoMode              ));
    qDebug("0x%04X:  ee_HydResponse             ",  EE_MIRROR_VAR_ADDRESS(ee_HydResponse          ));
    qDebug("0x%04X:  sparevar3                  ",  EE_MIRROR_VAR_ADDRESS(sparevar3               ));
    qDebug("0x%04X:  recoveryMode               ",  EE_MIRROR_VAR_ADDRESS(recoveryMode            ));
    qDebug("0x%04X:  varChecksum                ",  EE_MIRROR_VAR_ADDRESS(varChecksum             ));

    qDebug("\n0x%04X:  sizeof(eeMirrorRec)", sizeof(eeMirrorRec));
#endif
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButtonInit_clicked(void)
{
    bsp_init();
    ap_init();
    ui->pushButtonInit->setEnabled(false);
    ui->pushButtonRun->setEnabled(true);
    ui->lineEdit->setText(QString::number(runCount));
}

void MainWindow::on_pushButtonRun_clicked(void)
{
    if (!running)
    {
        runTimer->start(0);
        ui->pushButtonRun->setText("Stop");
        running = true;
    }
    else
    {
        runTimer->stop();
        ui->pushButtonRun->setText("Start");
        running = false;
    }
}

void MainWindow::run(void)
{
    bsp_run();
    ap_run();
    eeServiceEEPROM();
    eeServiceEEPROM();
    eeServiceEEPROM();
    eeServiceEEPROM();
    eeServiceEEPROM();
    runCount++;
    ui->lineEdit->setText(QString::number(runCount));
}
