#include "checkview.h"
#include "ui_checkview.h"
#include "../Controller/controller.h"

#include <QDir>
#include <QDebug>
#include <QTimer>
#include <QSettings>
#include <QMessageBox>

#define AUTO_CHECK_TIMEOUT 100


CheckView::CheckView(Controller *controller,
                     bool hasTemperatrue, QWidget *parent) :
    QFrame(parent),
    ui(new Ui::CheckView) {
    ui->setupUi(this);
    ui->temperaturetBtn->setEnabled( hasTemperatrue );//lt:根据传递的参数设置温度按钮是否可用
    m_pController = controller;
    initializeWidget();
    setViewEnable( false );
    m_pAutoCheckErrorTimer->start( AUTO_CHECK_TIMEOUT );//ltj,debug会报错
    controllerOption();//ltj,debug会报错
}

CheckView::~CheckView() {
    delete ui;
}

/**
 * @brief CheckView::setMessage 设置提示信息
 * @param message 提示信息
 */
void CheckView::setMessage(QString message) {
    ui->messageLabel->setText( message );
    if (message.isEmpty()) {

        ui->closetBtn->setIcon( QIcon( ":/icons/connect.png" ) );
        ui->closetBtn->setText( tr( "disconnect" ) );
        setViewEnable( true );
        m_pAutoCheckErrorTimer->start( AUTO_CHECK_TIMEOUT );//lt:100ms
        m_pAutoConnectionTimer->stop();
    } else {

        ui->closetBtn->setIcon( QIcon( ":/icons/disconnect.png" ) );
        ui->closetBtn->setText( tr( "connect" ) );
        setViewEnable( false );
        m_pAutoCheckErrorTimer->stop();
        m_pAutoConnectionTimer->start( AUTO_CHECK_TIMEOUT );
    }
}//lt:未用?

/**
 * @brief CheckView::controllerOption 操作控制器开关
 */
void CheckView::controllerOption() {

    if (ui->closetBtn->text() == tr( "connect" )) {

        if (NULL == m_pController) {
            return;
        }

        bool ok = false;
        ok = m_pController->openSpectrograph();
        if (!ok) {
            m_pController->closeSerialPort();
            QString message = tr( "Open spectrograph port error!" );
            ui->messageLabel->setText( message );
            return;
        }//lt:打开光谱仪，不能打开返回

        ok = m_pController->openSerialPort();
        if (!ok) {
            QString message = tr( "Open serial port error!" );
            ui->messageLabel->setText( message );
            return;
        }//lt:打开串口，不能打开返回

        ui->closetBtn->setIcon( QIcon( ":/icons/connect.png" ) );
        ui->closetBtn->setText( tr( "disconnect" ) );

        ui->messageLabel->clear();
        emit deviceEnable( true );
        m_pAutoCheckErrorTimer->start( AUTO_CHECK_TIMEOUT );
        m_pAutoConnectionTimer->stop();

        setViewEnable( true );
    } else {

        if (NULL == m_pController) {
            return;
        }

        setViewEnable( false );
        m_pController->closeSerialPort();
        m_pController->closeSpectrograph();

        ui->closetBtn->setIcon( QIcon( ":/icons/disconnect.png" ) );
        ui->closetBtn->setText( tr( "connect" ) );

        ui->messageLabel->setText( tr("Disconnect all device!") );
        emit deviceEnable( false );
        m_pAutoCheckErrorTimer->stop();
        m_pAutoConnectionTimer->start( AUTO_CHECK_TIMEOUT );
    }
}

/**
 * @brief CheckView::excuteCheck 测试函数
 */
void CheckView::excuteCheck() {
    if (NULL == m_pController) {
        QMessageBox::warning( 0, tr( "warning" ),
                              tr( "System error, Please restart!" ), QMessageBox::Ok );
        return;
    }
    emit clearPlot();//lt:清空画布
    setViewEnable( false );
    emit checking( false );//lt:锁定ui界面和

    QString errStr;
    if (ui->radioButtonMs->isChecked()) {
        errStr = m_pController->startMicroscaleCheck( ui->spinBoxChannel->value() - 1 );//lt:计算后值为0
    } else {
        errStr = m_pController->startCuvetteCheck();
    }

    if (errStr != "Success") {
        QMessageBox::warning( 0, tr( "warning" ), errStr, QMessageBox::Ok );
    }

    if (ui->closetBtn->text() != tr( "connect" )) {
        emit checking( true );
        setViewEnable( true );
    }
}

/**
 * @brief CheckView::checkMainboard 检查主板
 */
void CheckView::checkMainboard() {
    if (NULL != m_pController) {
        emit checking( false );
        setViewEnable( false );
        QString errStr = m_pController->checkMainBoard();
        if (errStr != "Success") {
            ui->messageLabel->setText( errStr );
        } else {
            ui->messageLabel->setText( tr( "Main Board is OK" ) );
        }
        if (ui->closetBtn->text() != tr( "connect" )) {
            emit checking( true );
            setViewEnable( true );
        }
    }
}

/**
 * @brief CheckView::checkMicroscale 检查超微量
 */
void CheckView::checkMicroscale() {
    if (NULL != m_pController) {
        emit checking( false );
        setViewEnable( false );
        QString errStr = m_pController->checkMicroscale();
        if (errStr != "Success") {
            ui->messageLabel->setText( errStr );
        } else {
            ui->messageLabel->setText( tr( "Micorscale is OK" ) );
        }
        if (ui->closetBtn->text() != tr( "connect" )) {
            emit checking( true );
            setViewEnable( true );
        }
    }
}

/**
 * @brief CheckView::checkCuttve 检查比色皿
 */
void CheckView::checkCuttve() {
    if (NULL != m_pController) {
        emit checking( false );
        setViewEnable( false );
        QString errStr = m_pController->checkCuvette();
        if (errStr != "Success") {
            ui->messageLabel->setText( errStr );
        } else {
            ui->messageLabel->setText( tr( "Cuvetter is OK" ) );
        }
        if (ui->closetBtn->text() != tr( "connect" )) {
            emit checking( true );
            setViewEnable( true );
        }
    }
}

/**
 * @brief CheckView::checkTemperature 检查温控系统
 */
void CheckView::checkTemperature() {
    if (NULL != m_pController) {
        emit checking( false );
        setViewEnable( false );
        QString errStr = m_pController->checkTemperature();
        if (errStr != "Success") {
            ui->messageLabel->setText( errStr );
        } else {
            ui->messageLabel->setText( tr( "Temperature Controller is OK" ) );
        }
        if (ui->closetBtn->text() != tr( "connect" )) {
            emit checking( true );
            setViewEnable( true );
        }
    }
}

/**
 * @brief CheckView::autoCheckError
 */
void CheckView::autoCheckError() {
    if (NULL == m_pController) {
        return;
    }
    bool ok = m_pController->checkDevice();
    if (!ok) {
        if (ui->closetBtn->text() == tr( "disconnect" )) {
            controllerOption();//lt:检测串口和光谱错误，关闭串口和光谱
        } else {
            m_pAutoCheckErrorTimer->stop();
        }
    }//lt:找到了串口和光谱自动检测错误时间清零，没有找到调用controlloption函数
}

/**
 * @brief CheckView::autoConnection
 */
void CheckView::autoConnection() {
    if (NULL == m_pController) {
        return;
    }
    QString description = m_pController->getDescription();
    QString portName = m_pController->findSerialPortName( description );
    if (!portName.isEmpty()) {
        if (ui->closetBtn->text() == tr( "connect" )) {
            controllerOption();
        } else {
            m_pAutoConnectionTimer->stop();
        }
    }
}

/**
 * @brief CheckView::changeModel
 * @param ok
 */
void CheckView::changeModel(bool ok) {
    if (ok) {
        if (sender() == ui->radioButtonMs) {
            ui->spinBoxChannel->setEnabled(ok);
        } else {
            ui->spinBoxChannel->setEnabled(!ok);
        }
    }
}//lt:超微量模式时spinbox使能，比色皿模式时spinbox失能

/**
 * @brief CheckView::setViewEnable
 * @param ok
 */
void CheckView::setViewEnable(bool ok) {
    ui->maintBtn->setEnabled( ok );
    ui->microtBtn->setEnabled( ok );
    ui->cuvettetBtn->setEnabled( ok );
    ui->checktBtn->setEnabled( ok );
    ui->temperaturetBtn->setEnabled( ok );
}

/**
 * @brief CheckView::initializeWidget
 */
void CheckView::initializeWidget() {

    QString filename = QDir::currentPath() + "/configure/system.ini";
    QSettings *configIniReader = new QSettings( filename, QSettings::IniFormat );

    m_channelNumber = configIniReader->value( "/System/Channel Number" ).toInt();
    m_cuvetteEnable = configIniReader->value( "/System/Cuvette Enable" ).toBool();

    delete configIniReader;
    configIniReader = NULL;

    ui->spinBoxChannel->setMaximum( m_channelNumber );
    ui->radioButtonCt->setEnabled( m_cuvetteEnable );


    m_pAutoCheckErrorTimer = new QTimer( this );
    connect(m_pAutoCheckErrorTimer, SIGNAL(timeout()), this, SLOT(autoCheckError()));//lt:自动检查错误时间
    m_pAutoConnectionTimer = new QTimer( this );
    connect(m_pAutoConnectionTimer, SIGNAL(timeout()), this, SLOT(autoConnection()));//lt:自动连接时间

    connect(ui->closetBtn, SIGNAL(clicked(bool)), this, SLOT(controllerOption()));
    connect(ui->savetBtn, SIGNAL(clicked(bool)), this, SIGNAL(saveImage()));
    connect(ui->maintBtn, SIGNAL(clicked(bool)), this, SLOT(checkMainboard()));
    connect(ui->microtBtn, SIGNAL(clicked(bool)), this, SLOT(checkMicroscale()));
    connect(ui->cuvettetBtn, SIGNAL(clicked(bool)), this, SLOT(checkCuttve()));
    connect(ui->checktBtn, SIGNAL(clicked(bool)), this, SLOT(excuteCheck()));
    connect(ui->temperaturetBtn, SIGNAL(clicked(bool)), this, SLOT(checkTemperature()));

    connect(ui->radioButtonMs, SIGNAL(clicked(bool)), this, SLOT(changeModel(bool)));
    connect(ui->radioButtonCt, SIGNAL(clicked(bool)), this, SLOT(changeModel(bool)));
}
