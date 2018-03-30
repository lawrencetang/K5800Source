#include "recordview.h"
#include "ui_recordview.h"

#include <QDir>
#include <QFile>
#include <QDebug>
#include <QSettings>
#include <QFileDialog>
#include <QTextStream>
#include <QMessageBox>
#include <QDesktopServices>
#include "otablescroll.h"

RecordView::RecordView(QString path, QWidget *parent) :
    QFrame(parent),
    ui(new Ui::RecordView) {
    ui->setupUi(this);
    m_systemPath = QDir::currentPath() + "/" + path;
    initializeSystem();
    initializeWidget();
    setRecordDir( tr( "Nucleic Acid" ) );
}

RecordView::~RecordView() {
    delete ui;
}

/**
 * 函数名称: headerLabels
 * 函数用途: 获取水平表头的字符串List
 * 输入参数:
 *          无
 * 输出参数:
 *          无
 */
QString RecordView::headerLabels() {

    QString labelsStr;
    QTableWidget *pTableWidget = m_poscorllArea;

    int columnCount = pTableWidget->columnCount();
    for (int c = 0; c < columnCount; c ++) {
        QTableWidgetItem *item = pTableWidget->horizontalHeaderItem( c );
        labelsStr.append( item->text() );
        if (c < columnCount - 1) {
            labelsStr.append( "," );
        }
    }

    return labelsStr;
}

/**
 * 函数名称: setRecordDir
 * 函数用途: 设置加载记录文件的目录
 * 输入参数:
 *          无
 * 输出参数:
 *          无
 */
void RecordView::setRecordDir(QString dir) {

    QString filename = m_systemPath + "/" + dir + "/" + "record.csv";
    m_currentDir = dir;
    readRecord( filename );
}

/**
 * @brief RecordView::insertRecord
 * @param recordStr
 */
void RecordView::insertRecord(QString recordStr) {

    QStringList record = recordStr.split( ",", QString::SkipEmptyParts );
    QTableWidget *pTableWidget = m_poscorllArea;
    if (record.isEmpty() ||
            updateRecord( record )) {
        return;
    }//lt:不空为false，有新纪录false,若更新了以前的记录，直接在updaterecord函数中更新后退出
    int columnCount = pTableWidget->columnCount();
    int measureColumn = 0;
    for( int c = 0; c < columnCount; c++ ) {
        QTableWidgetItem *item = pTableWidget->horizontalHeaderItem(c);
        if( item->text() == "Measure" && record.at(c)== "Protein" ) {
            measureColumn = c;
            break;
        }
    }
    for( int c = 0; c < columnCount; c++ ) {
        QTableWidgetItem *item = pTableWidget->horizontalHeaderItem(c);
        if( item->text() == "Conc" ) {
            if(measureColumn != 0) {
                if( record.at( measureColumn ) == "Protein" ) {
                    record.replaceInStrings(record.at(c), QString::number( record.at(c).toDouble(), 'f', 2));
                    emit sendConcValue( record.at(c) );
                }
            }
            else {
                record.replaceInStrings(record.at(c), QString::number( record.at(c).toDouble(), 'f', 1));
                emit sendConcValue( record.at(c) );
                //qDebug() << record.at(c);
            }
        }
        if( item->text().contains("A")) {
            record.replaceInStrings(record.at(c), QString::number( record.at(c).toDouble(), 'f', 3));
        }
        if( item->text().contains("Watch")) {
            record.replaceInStrings(record.at(c), QString::number( record.at(c).toDouble(), 'f', 3));
        }
        if( item->text().contains("Watch1") || item->text().contains("Watch2") || item->text().contains("Watch3")
                 || item->text().contains("Watch4") || item->text().contains("Watch5")) {
            record.replaceInStrings(record.at(c), QString::number( record.at(c).toDouble(), 'f', 0));
        }
        if( item->text().contains("Value")) {
            record.replaceInStrings(record.at(c), QString::number( record.at(c).toDouble(), 'f', 3));
            if (item->text().contains("Value1")) {
                emit sendConcValue( record.at(c) );
            }
        }
    }//ltj 浓度保留两位小数,其他计算结果保留4位小数


    int row = 0;
    insert( record, row );
    m_poscorllArea->setCurrentCell( row, 0 );//lt:选中第row行,第0列
    QString saveStr = QString( "record:,%1" ).arg( recordStr );
    saveRecord( saveStr );//lt:将新的纪录写入record文件，该记录也来自于data文件
}

/**
 * @brief RecordView::save
 */
void RecordView::save() {
    QDesktopServices::openUrl(QUrl("osk.exe", QUrl::TolerantMode));
    QString newName = QFileDialog::getSaveFileName(this, tr("Move File"),
                                                   QDir::currentPath(), tr("File (*.csv)"));
    if (newName.isEmpty()) {
        return;
    }

    // 获取目录路径
    QString filename = m_systemPath + "/" + m_currentDir + "/" + "record.csv";
    bool ok = QFile::copy(filename, newName);
    if (!ok) {
        QMessageBox::warning(this, tr("Warnning"),
                             tr("Copy file error!"), QMessageBox::Ok);
    }
}

/**
 * 函数名称: move
 * 函数用途: 拉高或拉低当前窗口
 * 输入参数:
 *          无
 * 输出参数:
 *          无
 */
void RecordView::move() {

    if (ui->moveUpBtn->text() == tr( "Move Up" )) {

        m_poscorllArea->setGeometry(QRect(1,1,1035,284));
        ui->moveUpBtn->setText( tr( "Move Down" ) );
        emit moveCoef( 0.50 );
    } else {

        m_poscorllArea->setGeometry(QRect(1,1,1035,142));
        ui->moveUpBtn->setText( tr( "Move Up" ) );
        emit moveCoef( 0.33 );
    }
}

/**
 * 函数名称: hideRow
 * 函数用途: 隐藏或还原表的行
 * 输入参数:
 *          无
 * 输出参数:
 *          无
 */
void RecordView::hideRow() {

    if (ui->hideRowBtn->text() == tr( "Hide Row" )) {

        QList<QTableWidgetItem *> items = m_poscorllArea->selectedItems();
        if (items.isEmpty()) {
            QMessageBox::information(this, tr("Infomation"),
                                     tr("Please select row in table!"), QMessageBox::Ok);
            return;
        }
        int minRow = m_poscorllArea->row( items.first() );
        int maxRow = m_poscorllArea->row( items.last() );

        for (int i = minRow; i <= maxRow; i ++) {
            m_poscorllArea->hideRow(i);
        }
        ui->hideRowBtn->setText( tr( "Show Row" ) );
    } else {

        int rowCount = m_poscorllArea->rowCount();
        for (int i = 0; i < rowCount; i ++) {
            if (m_poscorllArea->isRowHidden( i )) {
                m_poscorllArea->showRow( i );
            }
        }
        ui->hideRowBtn->setText( tr( "Hide Row" ) );
    }
}

/**
 * 函数名称: hideColumn
 * 函数用途: 隐藏或还原表的列
 * 输入参数:
 *          无
 * 输出参数:
 *          无
 */
void RecordView::hideColumn() {

    if (ui->hideColumnBtn->text() == tr( "Hide Column" )) {

        QList<QTableWidgetItem *> items = m_poscorllArea->selectedItems();
        if (items.isEmpty()) {
            QMessageBox::information(this, tr("Infomation"),
                                     tr("Please select column in table!"), QMessageBox::Ok);
            return;
        }
        int minColumn = m_poscorllArea->column( items.first() );
        int maxColumn = m_poscorllArea->column( items.last() );

        for (int i = minColumn; i <= maxColumn; i ++) {
            m_poscorllArea->hideColumn(i);
        }
        ui->hideColumnBtn->setText( tr( "Show Column" ) );
    } else {

        ui->hideColumnBtn->setText( tr( "Hide Column" ) );
        int columnCount = m_poscorllArea->columnCount();
        for (int i = 0; i < columnCount; i ++) {
            if ( m_poscorllArea->isColumnHidden( i ) ) {
                m_poscorllArea->showColumn( i );
            }
        }
    }
}

/**
 * 函数名称: clear
 * 函数用途: 清空记录以及文件
 * 输入参数:
 *          无
 * 输出参数:
 *          无
 */
void RecordView::clear() {
    removeAll();
    if (QMessageBox::Ok == QMessageBox::information(this, tr("Infomation"),
                                                    tr("Clear record file?"),
                                                    QMessageBox::Ok | QMessageBox::Cancel)) {
        clearRecord();
    }
    emit clearid();
}

/**
 * 函数名称: saveRecord
 * 函数用途: 保存检测记录
 * 输入参数:
 *          filename = 文件名称
 *          data = 检测记录的Str形式
 * 输出参数:
 *          无
 */
void RecordView::saveRecord(QString recordStr) {

    QString filename = m_systemPath + "/" + m_currentDir + "/" + "record.csv";
    QFile fileR( filename );
    if ( !fileR.open(QIODevice::ReadOnly) ) {
        QMessageBox::warning(this, tr("Warnning"),
                             tr("Open record file error!"), QMessageBox::Ok);
        return;
    }
    QTextStream in( &fileR );
    QStringList contents;
    while (!in.atEnd()) {
        contents.append( in.readLine() );
    }
    fileR.close();//lt:读入record前面行的记录
    contents.insert( 1, recordStr );//lt:在list的第一个位置后面插入

    QFile fileW( filename );
    if ( !fileW.open( QIODevice::WriteOnly |
                     QIODevice::Text | QIODevice::Truncate ) ) {
        QMessageBox::warning(this, tr("Warnning"),
                             tr("Open record file error!"), QMessageBox::Ok);
        return;
    }

    QTextStream out( &fileW );
    out.setCodec("GB2312");
    for (int i = 0; i < contents.size(); i ++) {
        out << contents.at( i ) << "\n";//lt:插在record文件的第二行
    }
    fileW.close();
}

/**
 * 函数名称: setHeaderLabels
 * 函数用途: 设置水平表头的信息
 * 输入参数:
 *          headerStr = 表头信息
 * 输出参数:
 *          无
 */
void RecordView::setHeaderLabels(QString headerStr) {

    QStringList headerList = headerStr.split( ",", QString::SkipEmptyParts );
    if (headerList.isEmpty()) {
        return;
    }
    QTableWidget *t_pTableWidget = m_poscorllArea;
    removeAll();
    t_pTableWidget->setColumnCount( headerList.size() );
    t_pTableWidget->setHorizontalHeaderLabels( headerList );
    //t_pTableWidget->horizontalHeader()->setDefaultSectionSize(150);
    t_pTableWidget->horizontalHeader()->setFont( QFont( "微软雅黑", 12, QFont::Bold ) );

    /*
    if (m_currentDir == tr( "Cell Culture" )) {
        t_pTableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    } else {
        t_pTableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    }
    */
    /*
     * ltj:设定表格宽度
     */
    t_pTableWidget->setColumnWidth( 0, 80 );
    t_pTableWidget->setColumnWidth( 1, 100 );
    if (m_currentDir == tr( "Nucleic Acid" ) || m_currentDir == tr( "Protein" ) || m_currentDir == tr ("Micro Array")) {
        //t_pTableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Interactive);
        t_pTableWidget->setColumnWidth( 2, 100 );
        t_pTableWidget->setColumnWidth( 3, 100 );
        t_pTableWidget->setColumnWidth( 4, 130 );
        t_pTableWidget->setColumnWidth( 5, 130 );
        t_pTableWidget->setColumnWidth( 6, 100 );
    }
    else if (m_currentDir == tr( "Cell Culture" )) {
        //t_pTableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Interactive);
        t_pTableWidget->setColumnWidth( 2, 155 );
        t_pTableWidget->setColumnWidth( 3, 155 );
        t_pTableWidget->setColumnWidth( 4, 155 );
        t_pTableWidget->setColumnWidth( 5, 155 );
        t_pTableWidget->setColumnWidth( 6, 155 );
    }
    else {
        t_pTableWidget->setColumnWidth( 2, 100 );
        t_pTableWidget->setColumnWidth( 3, 100 );
        t_pTableWidget->setColumnWidth( 4, 100 );
        t_pTableWidget->setColumnWidth( 5, 100 );
        t_pTableWidget->setColumnWidth( 6, 100 );
    }

    /*
    if (m_currentDir == tr( "Cell Culture" )) {
        t_pTableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    }//lt:table的属性会保留前面设置的属性
    */



    int columnCount = headerList.size();
    for (int i = 0; i < columnCount; i ++) {
        QTableWidgetItem *item = t_pTableWidget->horizontalHeaderItem( i );
        item->setTextColor( Qt::darkBlue );
    }
}

/**
 * 函数名称: removeAll
 * 函数用途: 清空表格
 * 输入参数:
 *          pTableWidget = 表
 * 输出参数:
 *          无
 */
void RecordView::removeAll() {

    QTableWidget *pTableWidget = m_poscorllArea;
    int rowCount = pTableWidget->rowCount();
    for (int r = rowCount - 1; r >= 0; r --) {
        pTableWidget->removeRow( r );
    }
    /*
    int columnCount = pTableWidget->columnCount();
    for (int r = rowCount - 1; r >= 0; r --) {
        for (int c = columnCount - 1; c >= 0; c --) {
            QTableWidgetItem *item = pTableWidget->takeItem(r, c);

            delete item;
            item = NULL;
        }
        pTableWidget->removeRow( r );
    }*/
}

/**
 * @brief RecordView::insert
 * @param record
 * @param row
 */
void RecordView::insert(QStringList record, int row) {

    QTableWidget *t_pTableWidget = m_poscorllArea;
    int rowCount = t_pTableWidget->rowCount();
    int columnCount = t_pTableWidget->columnCount();//lt:得到tablewidget的行列
    for (int r = 0; r < rowCount; r ++) {
        for (int c = 0; c < columnCount; c ++) {
            QTableWidgetItem *item = t_pTableWidget->item( r, c );
            item->setFont( QFont( "微软雅黑", 9, QFont::Bold ) );
            item->setTextColor( Qt::darkRed );
            item->setBackground( Qt::white );
        }
    }//lt:无效

    int size = record.size();
    t_pTableWidget->insertRow( row );//lt:插入一个空行在row行处
    QString textStr;
    for (int c = 0; c < columnCount; c ++) {

        if (c < size) {
            textStr = record.at( c );
        } else {
            textStr = "NULL";
        }

        QTableWidgetItem *item = new QTableWidgetItem( textStr );//lt:将字符值给每个单元格
        item->setTextAlignment( Qt::AlignHCenter | Qt::AlignVCenter );
        if (row == 0) {
            item->setFont( QFont( "微软雅黑", 12, QFont::Bold ) );
            item->setTextColor( Qt::yellow );
            item->setBackgroundColor( Qt::darkBlue );
        } else {
            item->setFont( QFont( "微软雅黑", 9, QFont::Bold ) );
            item->setTextColor( Qt::darkRed );
        }
        t_pTableWidget->setItem( row, c, item );//lt:设置该行和每一个单元格的格式和值
    }//lt:第0行强调

    if (row > 0) {
        for (int c = 0; c < columnCount; c ++) {
            QTableWidgetItem *item = t_pTableWidget->item( 0, c );
            item->setFont( QFont( "微软雅黑", 12, QFont::Bold ) );
            item->setTextColor(Qt::yellow);
            item->setBackgroundColor( Qt::darkBlue );
        }
    }//lt:无效?

    /*
    if (m_currentDir == tr( "Cell Culture" ) &&
            m_currentDir == tr( "Kit Method" ) ) {
        t_pTableWidget->resizeColumnsToContents();
    }
    *///ltg
}

/**
 * 函数名称: updateRecord
 * 函数用途: 更新table中记录的信息
 * 输入参数:
 *          data = 记录数据
 * 输出参数:
 *          无
 */
bool RecordView::updateRecord(QStringList data) {

    QTableWidget *t_pTableWidget = m_poscorllArea;

    // 查找是否存在相同文件名的记录
    QString fileName = data.last();
    QList<QTableWidgetItem *> items = t_pTableWidget->findItems( fileName, Qt::MatchFixedString );//lt:返回匹配的item项，符合条件的存在队列里
    if (items.isEmpty()) {
        return false;
    }

    // 存在相同ID的记录, 更新记录
    // 还原其他行的背景色
    int columnCount = t_pTableWidget->columnCount();
    int measureColumn = 0;
    for( int c = 0; c < columnCount; c++ ) {
        QTableWidgetItem *item = t_pTableWidget->horizontalHeaderItem(c);
        if( item->text() == "Measure" && data.at(c)== "Protein" ) {
            measureColumn = c;
            break;
        }
    }
    for( int c = 0; c < columnCount; c++ ) {
        QTableWidgetItem *item = t_pTableWidget->horizontalHeaderItem(c);
        if( item->text() == "Conc" ) {
            if(measureColumn != 0) {
                if( data.at( measureColumn ) == "Protein" ) {
                    data.replaceInStrings(data.at(c), QString::number( data.at(c).toDouble(), 'f', 2));
                }
            }
            else {
                data.replaceInStrings(data.at(c), QString::number( data.at(c).toDouble(), 'f', 1));
            }
        }
        if( item->text().contains("A")) {
            data.replaceInStrings(data.at(c), QString::number( data.at(c).toDouble(), 'f', 3));
        }
        if( item->text().contains("Watch")) {
            data.replaceInStrings(data.at(c), QString::number( data.at(c).toDouble(), 'f', 3));
        }
        if( item->text().contains("Watch1") || item->text().contains("Watch2") || item->text().contains("Watch3")
                 || item->text().contains("Watch4") || item->text().contains("Watch5")) {
            data.replaceInStrings(data.at(c), QString::number( data.at(c).toDouble(), 'f', 0));
        }
        if( item->text().contains("Value")) {
            data.replaceInStrings(data.at(c), QString::number( data.at(c).toDouble(), 'f', 3));
        }
    }//ltj 浓度保留两位小数,其他计算结果保留4位小数

    int rowCount = t_pTableWidget->rowCount();
    for (int r = 0; r < rowCount; r ++) {
        for (int c = 0; c < columnCount; c ++) {
            QTableWidgetItem *item = t_pTableWidget->item( r, c );
            item->setFont( QFont( "微软雅黑", 9, QFont::Bold ) );
            item->setTextColor( Qt::darkRed );
            item->setBackground( Qt::white );
        }
    }
    // 更新当前的记录
    int size = data.size();
    for (int i = 0; i < items.size(); i ++) {
        QTableWidgetItem *selectItem = items.at( i );//lt:每次最多一个
        int row = t_pTableWidget->row( selectItem );//lt:获得出该item的行
        for (int c = 0; c < columnCount; c ++) {
            QTableWidgetItem *item = t_pTableWidget->item( row, c );
            if (c == 0) {
                t_pTableWidget->setCurrentItem( item );
            }//lt:第0列选择为当前item
            if (c < size) {
                item->setText( data.at( c ) );
            } else {
                item->setText( "NULL" );
            }//lt:写值到item中
            item->setFont( QFont( "微软雅黑", 12, QFont::Bold ) );
            item->setTextColor( Qt::yellow );
            item->setBackgroundColor( Qt::darkBlue );
        }//lt:将该行强调
    }

    return true;
}

/**
 * 函数名称: updateRecord
 * 函数用途: 更新table中记录的信息
 * 输入参数:
 *          data = 记录数据
 * 输出参数:
 *          无
 */
bool RecordView::updateRecord(QMap<QString, QString> data) {

    QTableWidget *t_pTableWidget = m_poscorllArea;

    // 查找是否存在相同ID的记录
    QString id = data.value( "ID" );
    QList<QTableWidgetItem *> items = t_pTableWidget->findItems( id, Qt::MatchFixedString );
    if (items.isEmpty()) {
        return false;
    }

    // 存在相同ID的记录, 更新记录
    // 还原其他行的背景色
    int columnCount = t_pTableWidget->columnCount();
    int rowCount = t_pTableWidget->rowCount();
    for (int r = 0; r < rowCount; r ++) {
        for (int c = 0; c < columnCount; c ++) {
            QTableWidgetItem *item = t_pTableWidget->item( r, c );
            item->setBackground( Qt::white );
        }
    }
    // 更新当前的记录
    for (int i = 0; i < items.size(); i ++) {
        int row = t_pTableWidget->row( items.at( i ) );
        for (int c = 0; c < columnCount; c ++) {
            QTableWidgetItem *header = t_pTableWidget->horizontalHeaderItem( c );
            QString headerStr = header->text();

            QTableWidgetItem *item = t_pTableWidget->item( row, c );
            if (data.contains( headerStr )) {
                item->setText( data.value( headerStr ) );;
            } else {
                item->setText( "NULL" );
            }
            item->setBackgroundColor( Qt::darkBlue );
        }
    }

    return true;
}

/**
 * 函数名称: readRecord
 * 函数用途: 加载记录文件中的信息
 * 输入参数:
 *          filename = 文件名称
 * 输出参数:
 *          无
 */
void RecordView::readRecord(QString filename) {

    QFile file( filename );
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::warning(this, tr("Warnning"),
                             tr("Open record file error!"), QMessageBox::Ok);
        return;
    }
    QString headerStr;
    QString recordStr;

    QStringList textList;
    QTextStream in(&file);
    in.setCodec("GB2312");
    while(!in.atEnd()) {
        QString text = in.readLine();//lt:读每一行
        textList = text.split( ",", QString::SkipEmptyParts );
        if (textList.isEmpty()) {
            continue;
        }
        if ("header:" == textList.first()) {
            headerStr = text.replace( "header:,", "" );
            setHeaderLabels( headerStr );//lt:初始构造recordview对象时就写好表头
        } else if ("record:" == textList.first()) {
            recordStr = text.replace( "record:,", "" );
            QTableWidget *pTableWidget = m_poscorllArea;
            QStringList record = recordStr.split( ",", QString::SkipEmptyParts );
            if (record.isEmpty() ||
                    updateRecord( record )) {
                return;
            }
            int columnCount = pTableWidget->columnCount();
            int measureColumn = 0;
            for( int c = 0; c < columnCount; c++ ) {
                QTableWidgetItem *item = pTableWidget->horizontalHeaderItem(c);
                if( item->text() == "Measure" && record.at(c)== "Protein" ) {
                    measureColumn = c;
                    break;
                }
            }
            for( int c = 0; c < columnCount; c++ ) {
                QTableWidgetItem *item = pTableWidget->horizontalHeaderItem(c);
                if( item->text() == "Conc" ) {
                    if(measureColumn != 0) {
                        if( record.at( measureColumn ) == "Protein" ) {
                            record.replaceInStrings(record.at(c), QString::number( record.at(c).toDouble(), 'f', 2));
                        }
                    }
                    else {
                        record.replaceInStrings(record.at(c), QString::number( record.at(c).toDouble(), 'f', 1));
                    }
                }
                if( item->text().contains("A")) {
                    record.replaceInStrings(record.at(c), QString::number( record.at(c).toDouble(), 'f', 3));
                }
                if( item->text().contains("Watch")) {
                    record.replaceInStrings(record.at(c), QString::number( record.at(c).toDouble(), 'f', 3));
                }
                if( item->text().contains("Watch1") || item->text().contains("Watch2") || item->text().contains("Watch3")
                         || item->text().contains("Watch4") || item->text().contains("Watch5")) {
                    record.replaceInStrings(record.at(c), QString::number( record.at(c).toDouble(), 'f', 0));
                }
                if( item->text().contains("Value")) {
                    record.replaceInStrings(record.at(c), QString::number( record.at(c).toDouble(), 'f', 3));
                }
            }//ltj 浓度保留两位小数,其他计算结果保留4位小数
            //QMessageBox::warning(0, "warning", "++", QMessageBox::Ok );//ltj
            insert( record, m_poscorllArea->rowCount() );//lt:新纪录总是在record文件的最前面行，所以插入时table表还没有行，在0行
        }//lt:如果是老记录则updaterecord，新纪录则updaterecord返回false再insert,老记录也是一次读进来，row值每次加1
    }
    file.close();
}

/**
 * @brief RecordView::createRecordFile 创建记录文件
 * @param path 路径
 * @param flagStr 记录文件标识(对应到Setting-configure.ini)
 */
void RecordView::createRecordFile(QString path, QString flagStr) {

    QFile file( path + "/record.csv");
    if (!file.exists()) {

        QString filename = QDir::currentPath() + "/configure/system.ini";
        QSettings *configIniReader = new QSettings( filename, QSettings::IniFormat );
        QStringList headerList = configIniReader->value( QString("/recordView/%1").arg( flagStr ) ).toStringList();
        QString headerStr = "header:,";
        int size = headerList.size();
        for (int i = 0; i < size; i ++) {
            headerStr.append( headerList.at( i ) );
            if (i < size - 1) {
                headerStr.append( "," );
            }
        }
        delete configIniReader;
        configIniReader = NULL;
        //QMessageBox::warning(0, "warning", headerStr, QMessageBox::Ok);//ltj

        if ( !file.open( QIODevice::WriteOnly|
                         QIODevice::Text|QIODevice::Truncate ) ) {
            return;
        }
        QTextStream out( &file );
        out.setCodec("GB2312");
        out << headerStr << "\n";
        file.close();
    }//lt:第一次创建的时候一定要有config配置文件
}

/**
 * 函数名称: clearRecord
 * 函数用途: 清空记录文件
 * 输入参数:
 *          无
 * 输出参数:
 *          无
 */
void RecordView::clearRecord() {

    QString filename = m_systemPath + "/" + m_currentDir + "/" + "record.csv";
    QFile file( filename );
    if (!file.open(QIODevice::WriteOnly | QIODevice::Truncate)) {
        QMessageBox::warning(this, tr("Warnning"),
                             tr("Open record file error!"), QMessageBox::Ok);
        return;
    }

    QString headerStr = "header:,";
    int columnCount = m_poscorllArea->columnCount();
    for (int i = 0; i < columnCount; i ++) {
        QTableWidgetItem *item = m_poscorllArea->horizontalHeaderItem( i );
        headerStr.append( item->text() );
        if (i < columnCount) {
            headerStr.append( "," );
        }
    }

    QTextStream out( &file );
    out.setCodec("GB2312");
    out << headerStr << "\n";
    file.close();
}

/**
 * 函数名称: initializeSystem
 * 函数用途: 初始化文件系统
 * 输入参数:
 *          无
 * 输出参数:
 *          无
 */
void RecordView::initializeSystem() {

    QString path = m_systemPath;
    // 检查系统文件目录是否存在,如果不存在则创建系统文件目录
    QDir dir(path);
    if(!dir.exists()) {
        bool ok = dir.mkdir( path );
        if (!ok) {
            QMessageBox::warning(this, tr( "Warnning" ),
                                 tr( "Create dir error!" ), QMessageBox::Ok);
            return;
        }
    }

    // 检查数据目录是否存在,否则创建相应的目录
    QStringList dirNameList;
    // 核酸检测、蛋白检测、全波长检测、细胞检测、微阵列检测
    dirNameList << tr( "Nucleic Acid" ) << tr( "Protein" ) << tr( "UV-VIS" )
                << tr( "Cell Culture" ) << tr( "Micro Array" ) << tr( "Kit Method" ) << tr( "Dynamics" ) << tr( "Device Check" );

    for (int i = 0; i < dirNameList.size(); i ++) {

        QString dirPath = path + "/" + dirNameList.at( i );
        dir.setPath( dirPath );
        if (!dir.exists()) {
            bool ok = dir.mkdir( dirPath );
            if (!ok) {
                continue;
            }
        }
        QString text = dirNameList.at( i );
        if (text == tr( "Nucleic Acid" )) {
            text = "Nucleic Acid";//lt:把中文还为英文
        } else if (text == tr(  "Protein" )) {
            text = "Protein";
        } else if (text == tr( "Cell Culture" )) {
            text = "Cell Culture";
        } else if (text == tr( "UV-VIS" )) {
            text = "UV-VIS";
        } else if (text == tr( "Kit Method" )) {
            text = "Kit Method";
        } else if (text == tr( "Micro Array" )) {
            text = "Micro Array";
        } else if (text == tr( "Dynamics" )) {
            text = "Dynamics";
        } else if (text == tr( "Device Check" )) {
            text = "Device Check";
        } else {
            continue;
        }
        createRecordFile( dirPath, text );//lt:创建record文档
    }
}

/**
 * 函数名称: initializeWidget
 * 函数用途: 初始化窗体
 * 输入参数:
 *          无
 * 输出参数:
 *          无
 */
void RecordView::initializeWidget() {

    m_poscorllArea = new OTablescroll(this);
    m_poscorllArea->setGeometry(QRect(1,1,1035,142));
    m_pdvlayout = new QVBoxLayout;
    m_pdvlayout->addWidget(m_poscorllArea);
    m_pdvlayout->addLayout(ui->horizontalLayout);

    connect(ui->saveAsBtn, SIGNAL(clicked(bool)), this, SLOT(save()));
    connect(ui->moveUpBtn, SIGNAL(clicked(bool)), this, SLOT(move()));
    connect(ui->hideRowBtn, SIGNAL(clicked(bool)), this, SLOT(hideRow()));
    connect(ui->hideColumnBtn, SIGNAL(clicked(bool)), this, SLOT(hideColumn()));
    connect(ui->clearBtn, SIGNAL(clicked(bool)), this, SLOT(clear()));
    connect(ui->sampleLineEdit, SIGNAL(textChanged(QString)), this, SIGNAL(sampleLEchange(QString)));
}


