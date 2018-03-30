#include "ptdialog.h"
#include "ui_ptdialog.h"

#include <QDir>
#include <QSettings>

PtDialog::PtDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PtDialog) {
    ui->setupUi(this);

    setWindowFlags( Qt::WindowCloseButtonHint );//lt:窗口只有一个关闭按钮
    setModal( false );//ltg:模态改为非模态
    initializeSystem();
    initializeWidget();
    ui->cancelPBtn->setVisible(false);//ltj
    ui->okPBtn->setVisible(false);//ltj
    setWindowFlags( windowFlags() & ~Qt::WindowCloseButtonHint & ~Qt::WindowContextHelpButtonHint );//ltj
    m_showdialogflag = false;
}

PtDialog::~PtDialog() {
    delete ui;
}

void PtDialog::defaultInfo() {
    saveData();
    emit okBtnClicked();
}

/**
 * @brief PtDialog::showDialog
 * @param paramStr
 */
void PtDialog::showDialog(QString paramStr) {
    if (!paramStr.isEmpty()) {
        initializeDialog( paramStr );
    }
    m_showdialogflag = true;//ltj:显示对话框时true该变量
    show();
}

/**
 * @brief PtDialog::hideDialog
 */
void PtDialog::hideDialog() {
    QObject *object = this->sender();
    if (ui->okPBtn == object | ui->typeComboBox == object || ui->unitComboBox == object) {
        saveData();//ltg
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
void PtDialog::settinghidedlg() {
    saveData();//ltg
    emit okBtnClicked();
    hide();
    m_showdialogflag = false;//ltj:隐藏对话框时false该变量
}

/**
 * @brief PtDialog::typeChanged
 * @param id
 */
void PtDialog::typeChanged(int id) {
    if ( id < m_coefList.size()) {
        QString coefStr = m_coefList.at( id );
        ui->coefDoubleSpinBox->setValue( coefStr.toDouble() );
        ui->coefDoubleSpinBox->setReadOnly( true );
    } else {
        ui->coefDoubleSpinBox->setReadOnly( false );
    }
}

/**
 * @brief PtDialog::saveData
 */
void PtDialog::saveData() {

    m_paramStr.clear();
    m_paramStr.append( "type=" + ui->typeComboBox->currentText() );
    m_paramStr.append( "," );
    m_paramStr.append( "wave=" + QString::number( ui->waveSpinBox->value() ) );
    m_paramStr.append( "," );
    m_paramStr.append( "coef=" + QString::number( ui->coefDoubleSpinBox->value() ) );
    m_paramStr.append( "," );
    m_paramStr.append( "unit=" + ui->unitComboBox->currentText() );

    m_watchStr.clear();
    m_watchStr.append( "A260/A280" );
    m_watchStr.append( "," );
    m_watchStr.append( "A260/A230" );
    m_watchStr.append( "," );
    m_watchStr.append( "A260" );
    m_watchStr.append( "," );
    m_watchStr.append( "A230" );
    m_watchStr.append( "," );
    m_watchStr.append( "A280" );
}

/**
 * @brief PtDialog::initializeDialog
 * @param paramStr
 */
void PtDialog::initializeDialog(QString paramStr) {

    QMap<QString, QString> paramMap;
    QStringList paramList = paramStr.split( ",",  QString::SkipEmptyParts );
    for (int i = 0; i < paramList.size(); i ++) {

        QString itemStr = paramList.at( i );
        QStringList itemList = itemStr.split( "=",  QString::SkipEmptyParts );
        if (itemList.isEmpty()) {
            continue;
        }
        paramMap.insert( itemList.first(), itemList.last() );
    }
    // type
    int id = ui->typeComboBox->findText( paramMap.value( "type" ) );
    if (-1 != id) {
        ui->typeComboBox->setCurrentIndex( id );
    }
    // wave,coef
    ui->waveSpinBox->setValue( paramMap.value( "wave" ).toInt() );
    ui->coefDoubleSpinBox->setValue( paramMap.value( "coef" ).toDouble() );
    // unit
    id = ui->unitComboBox->findText( paramMap.value( "unit" ) );
    if (-1 != id) {
        ui->unitComboBox->setCurrentIndex( id );
    }
}

/**
 * @brief PtDialog::initializeSystem
 */
void PtDialog::initializeSystem() {
    QString filename = QDir::currentPath() + "/configure/system.ini";
    QSettings *configIniReader = new QSettings( filename, QSettings::IniFormat );

    m_typeList = configIniReader->value( "/Protein/Type" ).toStringList();
    m_coefList = configIniReader->value( "/Protein/Coef" ).toStringList();
    for (int i = 0; i < m_typeList.size(); i ++) {
        ui->typeComboBox->addItem( QIcon( ":/icons/dna.png" ), m_typeList.at( i ) );
    }
    ui->typeComboBox->addItem( QIcon( ":/icons/dna.png" ), tr( "Custom" ) );
    if (!m_coefList.isEmpty()) {
        QString coefStr = m_coefList.first();
        ui->coefDoubleSpinBox->setValue( coefStr.toDouble() );
        ui->coefDoubleSpinBox->setReadOnly( true );
    }

    QStringList unitList = configIniReader->value( "/Protein/Unit" ).toStringList();
    for (int i = 0; i < unitList.size(); i ++) {
        ui->unitComboBox->addItem( QIcon( ":/icons/uint.png" ), unitList.at( i ) );
    }
    ui->unitComboBox->setCurrentText( "mg/mL" );

    double waveValue = configIniReader->value( "/Protein/Wave" ).toDouble();
    ui->waveSpinBox->setValue( waveValue );
    ui->waveSpinBox->setReadOnly( true );

    delete configIniReader;
    configIniReader = NULL;
}

/**
 * @brief PtDialog::initializeWidget
 */
void PtDialog::initializeWidget() {
    connect( ui->typeComboBox, SIGNAL(currentIndexChanged(int)),
             this, SLOT(typeChanged(int)) );

    connect( ui->cancelPBtn, SIGNAL(clicked(bool)), this, SLOT(hideDialog()));
    connect( ui->okPBtn, SIGNAL(clicked(bool)), this, SLOT(hideDialog()));
    //connect( ui->typeComboBox, SIGNAL(currentIndexChanged(QString)), this, SLOT(hideDialog()));//ltj
    connect( ui->typeComboBox, SIGNAL(activated(QString)), this, SLOT(hideDialog()));//ltj
    //connect( ui->unitComboBox, SIGNAL(currentIndexChanged(QString)), this, SLOT(hideDialog()));//ltj
    connect( ui->unitComboBox, SIGNAL(activated(QString)), this, SLOT(hideDialog()));//ltj
}
