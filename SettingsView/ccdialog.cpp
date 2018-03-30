#include "ccdialog.h"
#include "ui_ccdialog.h"

#include <QDir>
#include <QDebug>
#include <QSettings>

CcDialog::CcDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CcDialog) {
    ui->setupUi(this);

    setModal( false );//ltg:模态改为非模态
    initializeSystem();
    initializeWidget();
    ui->cancelPBtn->setVisible(false);//ltj
    ui->okPBtn->setVisible(false);//ltj
    setWindowFlags( windowFlags() & ~Qt::WindowCloseButtonHint & ~Qt::WindowContextHelpButtonHint );//ltj
    m_showdialogflag = false;//ltj
}

CcDialog::~CcDialog() {
    delete ui;
}

/**
 * @brief CcDialog::defaultInfo
 */
void CcDialog::defaultInfo() {
    saveData();
    emit okBtnClicked();
}

/**
 * @brief CcDialog::showDialog
 * @param paramStr
 */
void CcDialog::showDialog(QString paramStr) {
    if (!paramStr.isEmpty()) {
        initializeDialog( paramStr );
    }
    m_showdialogflag = true;//ltj:显示对话框时true该变量
    show();
}

/**
 * @brief CcDialog::hideDialog
 */
void CcDialog::hideDialog() {
    QObject *object = this->sender();
    if (ui->okPBtn == object || ui->typeComboBox == object) {
        saveData();
        emit okBtnClicked();
    }
    hide();
    m_showdialogflag = false;//ltj:隐藏对话框时false该变量
}

/*
 *
 * ltg:使用settingviewdialog关闭对话框时的函数
 *
 */
void CcDialog::settinghidedlg() {
    saveData();//ltg
    emit okBtnClicked();
    hide();
    m_showdialogflag = false;//ltj:隐藏对话框时false该变量
}

/**
 * @brief CcDialog::typeChanged
 * @param id
 */
void CcDialog::typeChanged(int id) {
    if ( id < m_waveList.size()) {
        QString coefStr = m_waveList.at( id );
        ui->waveSpinBox->setValue( coefStr.toDouble() );
        ui->waveSpinBox->setReadOnly( true );
    } else {
        ui->waveSpinBox->setReadOnly( false );
    }
}

/**
 * @brief CcDialog::saveData
 */
void CcDialog::saveData() {
    m_paramStr.clear();
    m_paramStr.append( "type=" + ui->typeComboBox->currentText() );
    m_paramStr.append( "," );
    m_paramStr.append( "wave=" + QString::number( ui->waveSpinBox->value() ) );
    m_paramStr.append( "," );
    m_paramStr.append( "coef=50" );

    m_watchStr.clear();
    m_watchStr.append( "A" + QString::number( ui->waveSpinBox->value() ) );
}

/**
 * @brief CcDialog::initializeDialog
 * @param paramStr
 */
void CcDialog::initializeDialog(QString paramStr) {
    QStringList paramList = paramStr.split( ",",  QString::SkipEmptyParts );
    for (int i = 0; i < paramList.size(); i ++) {

        QString itemStr = paramList.at( i );
        QStringList itemList = itemStr.split( "=",  QString::SkipEmptyParts );

        for (int i = 0; i < itemList.size(); i ++) {
            QString keyStr = itemList.first();
            QString valueStr = itemList.last();
            if (keyStr == "type") {
                int id = ui->typeComboBox->findText( valueStr );
                if (-1 != id) {
                    ui->typeComboBox->setCurrentIndex( id );
                }
            } else if (keyStr == "wave") {
                ui->waveSpinBox->setValue( valueStr.toInt() );
            }
        }
    }
}

/**
 * @brief CcDialog::initializeSystem
 */
void CcDialog::initializeSystem() {

    QString filename = QDir::currentPath() + "/configure/system.ini";
    QSettings *configIniReader = new QSettings( filename, QSettings::IniFormat );

    m_typeList = configIniReader->value( "/Cell Culture/Type" ).toStringList();
    for (int i = 0; i < m_typeList.size(); i ++) {
        ui->typeComboBox->addItem( QIcon( ":/icons/dna.png" ), m_typeList.at( i ) );
    }
    ui->typeComboBox->addItem( QIcon( ":/icons/dna.png" ), tr( "Custom" ) );

    m_waveList = configIniReader->value( "/Cell Culture/Wave" ).toStringList();
    if (!m_waveList.isEmpty()) {
        QString coefStr = m_waveList.first();
        ui->waveSpinBox->setValue( coefStr.toDouble() );
        ui->waveSpinBox->setReadOnly( true );
    }
}

/**
 * @brief CcDialog::initializeWidget
 */
void CcDialog::initializeWidget() {
    connect( ui->typeComboBox, SIGNAL(currentIndexChanged(int)),
             this, SLOT(typeChanged(int)) );

    connect( ui->cancelPBtn, SIGNAL(clicked(bool)), this, SLOT(hideDialog()));
    connect( ui->okPBtn, SIGNAL(clicked(bool)), this, SLOT(hideDialog()));
    //connect( ui->typeComboBox, SIGNAL(currentIndexChanged(QString)), this, SLOT(hideDialog()));//ltj
    connect( ui->typeComboBox, SIGNAL(activated(QString)), this, SLOT(hideDialog()));//ltj
}
