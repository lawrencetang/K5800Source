#include "nadialog.h"
#include "ui_nadialog.h"

#include <QDir>
#include <QSettings>
#include <QDebug>

NaDialog::NaDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NaDialog) {
    ui->setupUi(this);

    setModal( false );//ltg:模态改为非模态
    initializeSystem();
    initializeWidget();
    ui->cancelPBtn->setVisible(false);//ltj
    ui->okPBtn->setVisible(false);//ltj
    setWindowFlags( windowFlags() & ~Qt::WindowCloseButtonHint & ~Qt::WindowContextHelpButtonHint );//ltj
    m_showdialogflag = false;
}

NaDialog::~NaDialog() {
    delete ui;
}

void NaDialog::defaultInfo() {
    saveData();
    emit okBtnClicked();
}

/**
 * @brief NaDialog::showDialog
 * @param paramStr
 */
void NaDialog::showDialog(QString paramStr) {
    if (!paramStr.isEmpty()) {
        initializeDialog( paramStr );
    }
    m_showdialogflag = true;//ltj:显示对话框时true该变量
    show();
}

/**
 * @brief NaDialog::hideDialog
 */
void NaDialog::hideDialog() {
    QObject *object = this->sender();
    if (ui->okPBtn == object || ui->typeComboBox == object || ui->unitComboBox == object) {
        saveData();//ltg
        emit okBtnClicked();
    }//ltg:需要settingview发信号所以将该条件取消
    hide();
    m_showdialogflag = false;//ltj:隐藏对话框时false该变量
}

/*
 *
 * ltg:使用settingviewdialog关闭对话框时的函数
 *
 */
void NaDialog::settinghidedlg() {
    saveData();//ltg
    emit okBtnClicked();
    hide();
    m_showdialogflag = false;//ltj:隐藏对话框时false该变量
}

/**
 * @brief NaDialog::typeChanged
 * @param id
 */
void NaDialog::typeChanged(int id) {
    if ( id < m_coefList.size()) {
        QString coefStr = m_coefList.at( id );
        ui->coefDoubleSpinBox->setValue( coefStr.toDouble() );
        ui->coefDoubleSpinBox->setReadOnly( true );
    } else {
        ui->coefDoubleSpinBox->setReadOnly( false );
    }
}

/**
 * @brief NaDialog::saveData
 */
void NaDialog::saveData() {

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
 * @brief NaDialog::initializeDialog
 * @param paramStr
 */
void NaDialog::initializeDialog(QString paramStr) {

    QMap<QString, QString> paramMap;
    QStringList paramList = paramStr.split( ",",  QString::SkipEmptyParts );
    for (int i = 0; i < paramList.size(); i ++) {

        QString itemStr = paramList.at( i );
        QStringList itemList = itemStr.split( "=",  QString::SkipEmptyParts );
        if (itemList.isEmpty()) {
            continue;
        }
        paramMap.insert( itemList.first(), itemList.last() );//lt:前面是键，后面是值
    }
    // type
    int id = ui->typeComboBox->findText( paramMap.value( "type" ) );//lt:返回在ComboBox控件中包含type键的值的索引值
    if (-1 != id) {
        ui->typeComboBox->setCurrentIndex( id );//lt:设置该索引值的项目为ComboBox当前项目
    }
    // wave,coef
    ui->waveSpinBox->setValue( paramMap.value( "wave" ).toInt() );
    ui->coefDoubleSpinBox->setValue( paramMap.value( "coef" ).toDouble() );
    // unit
    id = ui->unitComboBox->findText( paramMap.value( "unit" ) );
    if (-1 != id) {
        ui->unitComboBox->setCurrentIndex( id );
    }
}//lt:将Method Parameters中的值填入对话框

/**
 * @brief NaDialog::initializeSystem
 */
void NaDialog::initializeSystem() {

    QString filename = QDir::currentPath() + "/configure/system.ini";
    QSettings *configIniReader = new QSettings( filename, QSettings::IniFormat );

    m_typeList = configIniReader->value( "/Nucleic Acid/Type" ).toStringList();
    m_coefList = configIniReader->value( "/Nucleic Acid/Coef" ).toStringList();
    for (int i = 0; i < m_typeList.size(); i ++) {
        ui->typeComboBox->addItem( QIcon( ":/icons/dna.png" ), m_typeList.at( i ) );
    }
    ui->typeComboBox->addItem( QIcon( ":/icons/dna.png" ), tr( "Custom" ) );
    if (!m_coefList.isEmpty()) {
        QString coefStr = m_coefList.first();
        ui->coefDoubleSpinBox->setValue( coefStr.toDouble() );
        ui->coefDoubleSpinBox->setReadOnly( true );
    }

    QStringList unitList = configIniReader->value( "/Nucleic Acid/Unit" ).toStringList();
    for (int i = 0; i < unitList.size(); i ++) {
        ui->unitComboBox->addItem( QIcon( ":/icons/uint.png" ), unitList.at( i ) );
    }

    int waveValue = configIniReader->value( "/Nucleic Acid/Wave" ).toInt();
    ui->waveSpinBox->setValue( waveValue );
    ui->waveSpinBox->setReadOnly( true );

    delete configIniReader;
    configIniReader = NULL;
}

/**
 * @brief NaDialog::initializeWidget
 */
void NaDialog::initializeWidget() {
    connect( ui->typeComboBox, SIGNAL(currentIndexChanged(int)),
             this, SLOT(typeChanged(int)) );

    connect( ui->cancelPBtn, SIGNAL(clicked(bool)), this, SLOT(hideDialog()));
    connect( ui->okPBtn, SIGNAL(clicked(bool)), this, SLOT(hideDialog()));
    //connect( ui->typeComboBox, SIGNAL(currentIndexChanged(QString)), this, SLOT(hideDialog()));//ltj
    connect( ui->typeComboBox, SIGNAL(activated(QString)), this, SLOT(hideDialog()));//ltj
    //connect( ui->unitComboBox, SIGNAL(currentIndexChanged(QString)), this, SLOT(hideDialog()));//ltj
    connect( ui->unitComboBox, SIGNAL(activated(QString)), this, SLOT(hideDialog()));//ltj
}
