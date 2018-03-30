#include "kmdialog.h"
#include "ui_kmdialog.h"

#include <QDir>
#include <QSettings>

KmDialog::KmDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::KmDialog) {
    ui->setupUi(this);
    setModal( false );//ltg:模态改为非模态
    initializeSystem();
    initializeWidget();
    ui->cancelPBtn->setVisible(false);//ltj
    ui->okPBtn->setVisible(false);//ltj
    setWindowFlags( windowFlags() & ~Qt::WindowCloseButtonHint & ~Qt::WindowContextHelpButtonHint );//ltj
    m_showdialogflag = false;
}

KmDialog::~KmDialog() {
    delete ui;
}

/**
 * @brief KmDialog::defaultInfo
 */
void KmDialog::defaultInfo() {
    saveData();
    emit okBtnClicked();
}

/**
 * @brief KmDialog::showDialog
 * @param paramStr
 */
void KmDialog::showDialog(QString paramStr) {
    if (!paramStr.isEmpty()) {
        initializeDialog( paramStr );
    }
    m_showdialogflag = true;//ltj:显示对话框时true该变量
    show();
}

/**
 * @brief KmDialog::hideDialog
 */
void KmDialog::hideDialog() {
    //QObject *object = this->sender();
    //if (ui->okPBtn == object || ui->typeComboBox == object) {
        /*
         * 固定定量试剂盒固定波长参数
         */
        if ( ui->typeComboBox->currentText() == "BCA" || ui->typeComboBox->currentText() == "Bradford" ) {
            m_fixedwavelength = 800;
        }
        if (ui->typeComboBox->currentText() == "Lowry" ) {
            m_fixedwavelength = 400;
        }
        saveData();
        emit okBtnClicked();
    //}
    hide();
    m_showdialogflag = false;//ltj:隐藏对话框时false该变量
}

/*
 *
 * ltg:使用settingviewdialog关闭对话框时的函数
 *
 */
void KmDialog::settinghidedlg() {
    saveData();//ltg
    emit okBtnClicked();
    hide();
    m_showdialogflag = false;//ltj:隐藏对话框时false该变量
}

/**
 * @brief KmDialog::typeChanged
 * @param id
 */
void KmDialog::typeChanged(int id) {
    if ( id < m_waveList.size()) {
        QString coefStr = m_waveList.at( id );
        ui->waveSpinBox->setValue( coefStr.toDouble() );
        ui->waveSpinBox->setReadOnly( true );
    } else {
        ui->waveSpinBox->setReadOnly( false );
    }
}

/**
 * @brief KmDialog::saveData
 */
void KmDialog::saveData() {
    m_paramStr.clear();
    m_paramStr.append( "type=" + ui->typeComboBox->currentText() );
    m_paramStr.append( "," );
    m_paramStr.append( "wave=" + QString::number( ui->waveSpinBox->value() ) );

    m_watchStr.clear();
    m_watchStr.append( "A" + QString::number( ui->waveSpinBox->value() ) );
}

/**
 * @brief KmDialog::initializeDialog
 * @param paramStr
 */
void KmDialog::initializeDialog(QString paramStr) {
    QStringList paramList = paramStr.split( ",",  QString::SkipEmptyParts );
    for (int i = 0; i < paramList.size(); i ++) {

        QString itemStr = paramList.at( i );
        QStringList itemList = itemStr.split( ",",  QString::SkipEmptyParts );

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
 * @brief KmDialog::initializeSystem
 */
void KmDialog::initializeSystem() {
    QString filename = QDir::currentPath() + "/configure/system.ini";
    QSettings *configIniReader = new QSettings( filename, QSettings::IniFormat );

    m_typeList = configIniReader->value( "/Kit Method/Type" ).toStringList();
    for (int i = 0; i < m_typeList.size(); i ++) {
        ui->typeComboBox->addItem( QIcon( ":/icons/dna.png" ), m_typeList.at( i ) );
    }
    ui->typeComboBox->addItem( QIcon( ":/icons/dna.png" ), tr( "Custom" ) );

    m_waveList = configIniReader->value( "/Kit Method/Wave" ).toStringList();
    if (!m_waveList.isEmpty()) {
        QString coefStr = m_waveList.first();
        ui->waveSpinBox->setValue( coefStr.toDouble() );
        ui->waveSpinBox->setReadOnly( true );
    }

    delete configIniReader;
    configIniReader = NULL;
}

/**
 * @brief KmDialog::initializeWidget
 */
void KmDialog::initializeWidget() {
    connect( ui->typeComboBox, SIGNAL(currentIndexChanged(int)),
             this, SLOT(typeChanged(int)) );

    connect( ui->cancelPBtn, SIGNAL(clicked(bool)), this, SLOT(hideDialog()));
    connect( ui->okPBtn, SIGNAL(clicked(bool)), this, SLOT(hideDialog()));
    //connect( ui->typeComboBox, SIGNAL(currentIndexChanged(QString)), this, SLOT(hideDialog()));//ltj
    connect( ui->typeComboBox, SIGNAL(activated(QString)), this, SLOT(hideDialog()));//ltj
}
