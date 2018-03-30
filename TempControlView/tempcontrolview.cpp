#include "tempcontrolview.h"
#include "ui_tempcontrolview.h"

#include "../Controller/controller.h"
#include "targetsetingdialog.h"
#include <QDebug>
#include <QTimer>
#include <QMessageBox>
#include <QDesktopWidget>

#define READ_TEMPERATURE_INTERVAL  1000 // 读取温度的周期单位(ms)

TempControlView::TempControlView(Controller *controller, QWidget *parent) :
    QFrame(parent),
    ui(new Ui::TempControlView) {
    ui->setupUi(this);
    m_isPauseRead = false;
    m_pController = controller;
    initializeWidget();
}

TempControlView::~TempControlView() {
    delete ui;
    delete m_pTargetSetingDlg;
    m_pTargetSetingDlg = NULL;
}

/**
 * @brief TempControlView::stopTemperature
 */
void TempControlView::stopTemperature() {
    m_pTargetSetingDlg->hide();
    if (ui->starttBtn->text() != tr( "start" )) {
        onStartBtnClicked();
    }
}

/**
 * @brief TempControlView::onStartBtnClicked 确定按钮
 */
void TempControlView::onStartBtnClicked() {

    m_pTimer->stop();
    QString resultStr = m_pController->temperatureStop();
    if (resultStr != "Success") {
        QMessageBox::warning( 0, tr( "Warning" ), resultStr, QMessageBox::Ok);
    }

    if (ui->starttBtn->text() == tr( "start" )) {

        int targetValue = ui->targetLcdNumber->value() * 10;
        QString resultStr = m_pController->temperatureStart( targetValue );
        if (resultStr == "Success") {
            ui->starttBtn->setText( tr( "stop" ) );
            ui->starttBtn->setIcon( QIcon( ":/icons/stop.png" ) );
            ui->setingtBtn->setEnabled( false );

            m_pTimer->start( READ_TEMPERATURE_INTERVAL );
        } else {
            QMessageBox::warning( 0, tr( "Warning" ), resultStr, QMessageBox::Ok);
        }
    } else {

        ui->starttBtn->setText( tr( "start" ) );
        ui->starttBtn->setIcon( QIcon( ":/icons/start.png" ) );
        ui->setingtBtn->setEnabled( true );
    }
}

/**
 * @brief TempControlView::setTargetValue 设置目标温度值,对内接口
 * @param value 目标温度值
 */
void TempControlView::setTargetValue(double value) {
    ui->targetLcdNumber->display( value );
}

/**
 * @brief TempControlView::setCurrentValue 设置当前温度值,对外接口。
 * @param value 当前温度值
 */
void TempControlView::setCurrentValue(double value) {
    QString displayStr = QString::number( value, 'f', 1 );
    ui->currentLcdNumber->display( displayStr );
}

/**
 * @brief TempControlView::readTemperature
 */
void TempControlView::readTemperature() {
    if (!m_isPauseRead) {
        m_pController->temperatureRead();
    }
}

/**
 * @brief TempControlView::pauseRead
 * @param ok
 */
void TempControlView::pauseRead(bool ok) {
    m_isPauseRead = ok;
}

/**
 * @brief TempControlView::initializeWidget 初始化窗体
 */
void TempControlView::initializeWidget() {
    m_pTargetSetingDlg = new TargetSetingDialog();
    m_pTargetSetingDlg->hide();
    m_pTimer = new QTimer( this );

    connect(m_pTimer, SIGNAL(timeout()), this, SLOT(readTemperature()));
    connect(m_pController, SIGNAL(tempValue(double)), this, SLOT(setCurrentValue(double)));

    connect(m_pTargetSetingDlg, SIGNAL(targetChanged(double)),
            this, SLOT(setTargetValue(double)));

    connect(ui->setingtBtn, SIGNAL(clicked(bool)), m_pTargetSetingDlg, SLOT(show()));
    connect(ui->starttBtn, SIGNAL(clicked(bool)), this, SLOT(onStartBtnClicked()));
}
