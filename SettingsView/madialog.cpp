#include "madialog.h"
#include "ui_madialog.h"

#include <QDir>
#include <QDebug>
#include <QSettings>
#include <QMessageBox>

MaDialog::MaDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MaDialog) {
    ui->setupUi(this);

    setModal( true );
    initializeSystem();
    initializeWidget();
    ui->cancelPBtn->setVisible(false);//ltj
    //ui->okPBtn->setVisible(false);//ltj
    setWindowFlags( windowFlags() & ~Qt::WindowCloseButtonHint & ~Qt::WindowContextHelpButtonHint );//ltj
}

MaDialog::~MaDialog() {
    delete ui;
}

/**
 * @brief MaDialog::measureStr
 * @return
 */
QString MaDialog::measureStr() {

    if (ui->naRBtn->isChecked()) {
        return "Nucleic Acid";
    } else {
        return "Protein";
    }
}

/**
 * @brief MaDialog::defaultInfo
 */
void MaDialog::defaultInfo() {
    saveData();
    emit okBtnClicked();
}

/**
 * @brief MaDialog::showDialog
 * @param paramStr
 */
void MaDialog::showDialog(QString paramStr, QString watchStr) {
    if (!paramStr.isEmpty()) {
        initializeDialog( paramStr );
    }
    if (!watchStr.isEmpty()) {
        initializeTable( watchStr );
    }
    show();
}

/**
 * @brief MaDialog::hideDialog
 */
void MaDialog::hideDialog() {
    QObject *object = this->sender();
    if (ui->okPBtn == object | ui->typeComboBox == object || ui->uintComboBox == object) {
        saveData();//ltg
        emit okBtnClicked();
    }
    hide();
}

/**
 * @brief MaDialog::addDyeData
 */
void MaDialog::addDyeData() {
    if (ui->nameLineEdit->text().isEmpty()) {
        QMessageBox::warning(this, tr( "Warning" ),
                             tr( "Name of dye can not be empty!" ), QMessageBox::Ok);
        return;
    }

    int rowCount = ui->tableWidget->rowCount();
    ui->tableWidget->insertRow( rowCount );

    QStringList data;
    data << ui->nameLineEdit->text() << QString::number( ui->spinBox->value() )
         << QString::number( ui->wlSpinBox->value() ) << "0.00" << "0.00";

    int columnCount = ui->tableWidget->columnCount();
    for (int c = 0; c < columnCount; c ++) {
        QTableWidgetItem *item = new QTableWidgetItem( data.at( c ) );
        if (c == 0) {
            item->setCheckState( Qt::Checked );
        }
        item->setTextAlignment( Qt::AlignHCenter | Qt::AlignVCenter );
        ui->tableWidget->setItem( rowCount, c, item );//lt:设置单元格值
    }
}

/**
 * @brief MaDialog::typeChanged
 * @param id
 */
void MaDialog::typeChanged(int id) {
    if ( id < m_coefList.size()) {
        QString coefStr = m_coefList.at( id );
        ui->ceofDoubleSpinBox->setValue( coefStr.toDouble() );
        ui->ceofDoubleSpinBox->setReadOnly( true );
    } else {
        ui->ceofDoubleSpinBox->setReadOnly( false );
    }
}

/**
 * @brief MaDialog::measureChanged
 */
void MaDialog::measureChanged() {

    m_typeList.clear();
    m_coefList.clear();

    QString waveStr;
    if (ui->naRBtn->isChecked()) {
        m_typeList.append( m_typeNaList );
        m_coefList.append( m_coefNaList );
        waveStr = m_waveNaStr;
        ui->uintComboBox->setCurrentText( "ng/uL" );//lt:导入核酸数据
    } else {
        m_typeList.append( m_typePtList );
        m_coefList.append( m_coefPtList );
        waveStr = m_wavePtStr;
        ui->uintComboBox->setCurrentText( "mg/mL" );
    }//lt:导入蛋白质数据

    int size = ui->typeComboBox->count();
    for (int i =  0; i < size - 1; i ++) {
        ui->typeComboBox->removeItem( 0 );
    }
    for (int i = 0; i < m_typeList.size(); i ++) {
        ui->typeComboBox->insertItem( i, QIcon( ":/icons/dna.png" ), m_typeList.at( i ) );
    }
    ui->typeComboBox->setCurrentIndex( 0 );

    if (!m_coefList.isEmpty()) {
        QString coefStr = m_coefList.first();
        ui->ceofDoubleSpinBox->setValue( coefStr.toDouble() );
        ui->ceofDoubleSpinBox->setReadOnly( true );
    }//lt:设置系数
    ui->waveSpinBox->setValue( waveStr.toInt() );//lt:设置波长
}

/**
 * @brief MaDialog::dyeDataList
 * @return
 */
QList<QStringList> MaDialog::dyeDataList() {

    QList<QStringList> dyeList;
    QStringList dyeItemList;

    dyeItemList << "Cy3" << "150000.00" << "550" << "0.04" << "0.05";
    dyeList.append( dyeItemList );

    dyeItemList.clear();
    dyeItemList << "Cy5" << "250000.00" << "650" << "0.00" << "0.05";
    dyeList.append( dyeItemList );

    dyeItemList.clear();
    dyeItemList << "Alexa Fluor 488" << "710000.00" << "495" << "0.30" << "0.11";
    dyeList.append( dyeItemList );

    dyeItemList.clear();
    dyeItemList << "Alexa Fluor 546" << "104000.00" << "556" << "0.21" << "0.12";
    dyeList.append( dyeItemList );

    dyeItemList.clear();
    dyeItemList << "Alexa Fluor 555" << "150000.00" << "555" << "0.04" << "0.08";
    dyeList.append( dyeItemList );

    dyeItemList.clear();
    dyeItemList << "Alexa Fluor 594" << "73000.00" << "590" << "0.43" << "0.56";
    dyeList.append( dyeItemList );

    dyeItemList.clear();
    dyeItemList << "Alexa Fluor 647" << "239000.00" << "650" << "0.00" << "0.03";
    dyeList.append( dyeItemList );

    dyeItemList.clear();
    dyeItemList << "Alexa Fluor 660" << "132000.00" << "663" << "0.00" << "0.10";
    dyeList.append( dyeItemList );

    dyeItemList.clear();
    dyeItemList << "Cy3.5" << "150000.00" << "581" << "0.08" << "0.24";
    dyeList.append( dyeItemList );

    dyeItemList.clear();
    dyeItemList << "Cy5.5" << "250000.00" << "675" << "0.05" << "0.18";
    dyeList.append( dyeItemList );

    return dyeList;
}

/**
 * @brief MaDialog::initializeDyeTable
 */
void MaDialog::initializeDyeTable() {
    QList<QStringList> dyeList = dyeDataList();

    int columnCount = ui->tableWidget->columnCount();
    for (int i = 0; i < dyeList.size(); i ++) {

        ui->tableWidget->insertRow( i );
        QStringList dyeData = dyeList.at( i );

        int size = dyeData.size();
        for (int c = 0; c < columnCount; c ++) {
            QTableWidgetItem *item = NULL;
            if (c < size) {
                item = new QTableWidgetItem( dyeData.at( c ) );
            } else {
                item = new QTableWidgetItem( "NULL" );
            }
            if (c == 0) {
                item->setCheckState( Qt::Unchecked );
            }
            item->setTextAlignment( Qt::AlignHCenter | Qt::AlignVCenter );
            ui->tableWidget->setItem( i, c, item );//lt:设置单元格的值
        }
    }
    ui->tableWidget->horizontalHeader()->setSectionResizeMode( QHeaderView::Stretch );
}

/**
 * @brief MaDialog::saveData
 */
void MaDialog::saveData() {

    m_paramStr.clear();
    m_paramStr.append( "type=" + ui->typeComboBox->currentText() );
    m_paramStr.append( "," );
    m_paramStr.append( "wave=" + QString::number( ui->waveSpinBox->value() ) );
    m_paramStr.append( "," );
    m_paramStr.append( "coef=" + QString::number( ui->ceofDoubleSpinBox->value() ) );
    m_paramStr.append( "," );
    m_paramStr.append( "unit=" + ui->uintComboBox->currentText() );

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

    int rowCount = ui->tableWidget->rowCount();
    for (int r = 0; r < rowCount; r ++) {
        QTableWidgetItem *item = ui->tableWidget->item( r, 0 );
        m_watchStr.append( "," );
        if (Qt::Checked == item->checkState()) {
            QTableWidgetItem *itemWL = ui->tableWidget->item( r, 2 );
            m_watchStr.append( "A" + itemWL->text() );
        } else {
            m_watchStr.append( "NULL" );
        }
    }
}

/**
 * @brief MaDialog::initializeDialog
 * @param paramStr
 */
void MaDialog::initializeDialog(QString paramStr) {

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
    // 设置检测物质
    if (paramMap.value( "wave" ) == "260") {
        ui->naRBtn->setChecked( true );
    } else {
        ui->ptRBtn->setChecked( true );
    }
    measureChanged();
    // type
    int id = ui->typeComboBox->findText( paramMap.value( "type" ) );
    if (-1 != id) {
        ui->typeComboBox->setCurrentIndex( id );
    }
    // wave,coef
    ui->waveSpinBox->setValue( paramMap.value( "wave" ).toInt() );
    ui->ceofDoubleSpinBox->setValue( paramMap.value( "coef" ).toDouble() );
    // unit
    id = ui->uintComboBox->findText( paramMap.value( "unit" ) );
    if (-1 != id) {
        ui->uintComboBox->setCurrentIndex( id );
    }
}

/**
 * @brief MaDialog::initializeTable
 * @param watchStr
 */
void MaDialog::initializeTable(QString watchStr) {
    watchStr = watchStr.replace( "A", "" );
    QStringList watchList = watchStr.split( ",",  QString::SkipEmptyParts );
    int columnCount = ui->tableWidget->columnCount();
    for (int i = 0; i < watchList.size(); i ++) {
        if (i > columnCount) {
            continue;
        }

        QTableWidgetItem *item = ui->tableWidget->item( i, 0 );
        if ( watchList.at( i ) == "NULL" ) {
            item->setCheckState( Qt::Unchecked );
        } else {
            item->setCheckState( Qt::Checked );
        }
        ui->tableWidget->setItem( i, 0, item);
    }
}

/**
 * @brief MaDialog::initializeSystem
 */
void MaDialog::initializeSystem() {

    QString filename = QDir::currentPath() + "/configure/system.ini";
    QSettings *configIniReader = new QSettings( filename, QSettings::IniFormat );

    m_typePtList = configIniReader->value( "/Protein/Type" ).toStringList();
    m_coefPtList = configIniReader->value( "/Protein/Coef" ).toStringList();
    m_wavePtStr = configIniReader->value( "/Protein/Wave" ).toString();

    m_typeNaList = configIniReader->value( "/Nucleic Acid/Type" ).toStringList();
    m_coefNaList = configIniReader->value( "/Nucleic Acid/Coef" ).toStringList();
    m_waveNaStr = configIniReader->value( "/Nucleic Acid/Wave" ).toString();
    ui->typeComboBox->addItem( QIcon( ":/icons/dna.png" ), tr( "Custom" ) );
    measureChanged();

    QStringList unitList = configIniReader->value( "/Nucleic Acid/Unit" ).toStringList();
    for (int i = 0; i < unitList.size(); i ++) {
        ui->uintComboBox->addItem( QIcon( ":/icons/uint.png" ), unitList.at( i ) );
    }

    int waveValue = configIniReader->value( "/Nucleic Acid/Wave" ).toInt();
    ui->waveSpinBox->setValue( waveValue );
    ui->waveSpinBox->setReadOnly( true );

    delete configIniReader;
    configIniReader = NULL;
}

/**
 * @brief MaDialog::initializeWidget
 */
void MaDialog::initializeWidget() {

    initializeDyeTable();
    connect( ui->typeComboBox, SIGNAL(currentIndexChanged(int)),
             this, SLOT(typeChanged(int)) );
    connect(ui->addTBtn, SIGNAL( clicked(bool) ), this, SLOT( addDyeData() ) );

    connect(ui->naRBtn, SIGNAL( clicked(bool) ), this, SLOT( measureChanged() ) );
    connect(ui->ptRBtn, SIGNAL( clicked(bool) ), this, SLOT( measureChanged() ) );

    connect( ui->cancelPBtn, SIGNAL(clicked(bool)), this, SLOT(hideDialog()));
    connect( ui->okPBtn, SIGNAL(clicked(bool)), this, SLOT(hideDialog()));
    //connect( ui->typeComboBox, SIGNAL(currentIndexChanged(QString)), this, SLOT(hideDialog()));//ltj
    connect( ui->typeComboBox, SIGNAL(activated(QString)), this, SLOT(hideDialog()));//ltj
    //connect( ui->uintComboBox, SIGNAL(currentIndexChanged(QString)), this, SLOT(hideDialog()));//ltj
    connect( ui->uintComboBox, SIGNAL(activated(QString)), this, SLOT(hideDialog()));//ltj
}
