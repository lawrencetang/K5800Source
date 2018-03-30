#include "dataview.h"
#include "ui_dataview.h"

#include <QDir>
#include <QFile>
#include <QDebug>
#include <QFileInfo>
#include <QDateTime>
#include <QTextStream>
#include <QFileDialog>
#include <QMessageBox>
#include <QDesktopServices>
#include <QMouseEvent>
#include <QScrollBar>
#include <QRect>
#include "olistscroll.h"

DataView::DataView(QString systemPath, bool supportCuvette, QWidget *parent) :
    QFrame(parent),
    ui(new Ui::DataView) {
    // 初始化UI
    ui->setupUi(this);
    // 初始化系统路径
    m_systemPath = QDir::currentPath() + "/" + systemPath;//lt:初始化时是data文件夹
    m_supportCuvette = supportCuvette;

    initializeSystem();
    initializeWidget();
}

DataView::~DataView() {
    delete ui;
}

QMap<QString, QString> DataView::getViewTitle() {
    return m_viewTitle;
}

/**
 * 函数名称: setCurrentDir
 * 函数用途: 设置当前目录
 * 输入参数:
 *          dir = 目录id
 * 输出参数:
 *          无
 */
void DataView::setCurrentDir(QString name) {

    if (m_dirMap.contains( name )) {
        int id = m_dirMap.value( name );//lt:根据name作为key值返回该qmap的value值qmap[qstring, int]
        ui->comboBox->setCurrentIndex( id );//lt:将该id设为当前项目的index
    }
}

/**
 * 函数名称: showDataFile
 * 函数用途: 显示目录下的所有数据文件
 * 输入参数:
 *          dir = 目录名称
 * 输出参数:
 *          无
 */
void DataView::showDataFile(QString dirname) {
    if (dirname.isEmpty()) {
        return;
    }//lt:软件为英文时测量的只能在英文目录内查找，中文时测量的只能在中文目录中查找

    // 检查目录是否存在
    QString path = m_systemPath + "/" + dirname;
    QDir dir(path);
    if (!dir.exists()) {
        QMessageBox::warning(this, tr("Warnning"),
                             tr("Dir not exist!"), QMessageBox::Ok);
        return;
    }
    // 清空listWidget
    m_poscorllArea->clear();

    // 加载该目录下所有以.csv结尾的所有文件
    dir.setFilter(QDir::Files);
    QFileInfoList list = dir.entryInfoList();
    for (int i = 0; i < list.size(); i ++) {

        QFileInfo fileinfo = list.at(i);
        if (fileinfo.fileName().endsWith( ".csv" )) {

            QListWidgetItem *item = NULL;
            item = new QListWidgetItem( QIcon( ":/icons/file.png" ), fileinfo.fileName() );
            /*
            if (i == 0) {
                item->setBackgroundColor( Qt::gray );
            }
            */
            item->setFont( QFont( "黑体", 12 ) );
            item->setSizeHint( QSize(128, 64) );
            m_poscorllArea->insertItem( 0, item );
        }
    }

    int count = m_poscorllArea->count();
    for (int r = 0; r < count; r ++) {
        QListWidgetItem *item = m_poscorllArea->item( r );
        if (0 == r ) {
            item->setBackgroundColor( Qt::white );
        } else {
            item->setBackgroundColor( Qt::white );
        }
    }
}

/**
 * @brief DataView::updateView
 * @param dirname
 */
void DataView::updateView(QString dirname) {
    showDataFile( dirname );
    emit dirChanged(dirname);
}

/**
 * 函数名称: selectedItem
 * 函数用途: 删除数据文件//lt:（选择）
 * 输入参数:
 *          无
 * 输出参数:
 *          无
 */
void DataView::itemSelected(QListWidgetItem *item) {
    QString type = ui->comboBox->currentText();//lt:根据comboBox的项目值
    //QMessageBox::warning(0, "warning", type, QMessageBox::Ok);//ltj
    QString filename = m_systemPath + "/" + type + "/" + item->text();//lt:item是comboBox每项内的子项目的值

    emit fileReadReady( type, filename );
}

/**
 * 函数名称: saveDataFile
 * 函数用途: 保存文件
 * 输入参数:
 *          data = 数据
 * 输出参数:
 *          无
 */
void DataView::saveDataFile(QStringList data) {

    QString filename = QDateTime::currentDateTime().toString("yyyy-MM-dd hh.mm.ss") + ".csv";
    saveDataFile( filename, data );
}

/**
 * 函数名称: saveDataFile
 * 函数用途: 保存文件
 * 输入参数:
 *          filename = 文件名称(不含路径)
 *          data = 数据
 * 输出参数:
 *          无
 */
void DataView::saveDataFile(QString filename, QStringList data) {
    QString filepath = m_systemPath + "/" + ui->comboBox->currentText() + "/";
    filename = filepath + filename;

    QFile file(filename);
    if (!file.open( QIODevice::WriteOnly|QIODevice::Append )) {  //lt:因为拟合需要保存测量结果将Truncate模式改为append模式
        QMessageBox::warning(this, tr("Warnning"),
                             tr("Save data error!"), QMessageBox::Ok);
        return;
    }

    QTextStream out(&file);
    out.setCodec("GB2312");
    for (int i = 0; i < data.size(); i ++) {

        out << data.at(i);
        if (i != data.size() - 1) {
            out << "\n";
        }//lt:表中的每一行就是qstringlist中的一个qstring
    }
    file.close();
    QFileInfo fileInfo( filename );
    //showDataFile( ui->comboBox->currentText() );
    insert( fileInfo.fileName() );
}

/**
 * 函数名称: deleteDataFile
 * 函数用途: 删除数据文件
 * 输入参数:
 *          无
 * 输出参数:
 *          无
 */
void DataView::remove() {
    if (QMessageBox::Ok == QMessageBox::warning(this, tr("Warnning"),
                                                    tr("Do you want select all files?"),
                                                    QMessageBox::Ok|QMessageBox::Cancel)) {
        m_poscorllArea->selectAll();
    }

    if (QMessageBox::Cancel == QMessageBox::warning(this, tr("Warnning"),
                                                    tr("Do you want to delete file?"),
                                                    QMessageBox::Ok|QMessageBox::Cancel)) {
        return;
    }
    // 获取选中的item
    QListWidget *t_pListWidget = m_poscorllArea;
    QList<QListWidgetItem *> selectedItems = t_pListWidget->selectedItems();

    // 获取目录路径
    QString filepath = m_systemPath + "/" + ui->comboBox->currentText() + "/";
    for (int i = 0; i < selectedItems.size(); i ++) {
        // 删除文件
        QListWidgetItem *item = selectedItems.at(i);
        QString filename = filepath + item->text();

        // 删除item
        int row = t_pListWidget->row( item );
        t_pListWidget->takeItem( row );

        delete item;
        item = NULL;

        bool ok = QFile::remove(filename);
        if (!ok) {
//            QMessageBox::warning(this, tr("Warnning"),
//                                 tr("Delete file error!"), QMessageBox::Ok);
            continue;
        }
    }
}

/**
 * 函数名称: moveTo
 * 函数用途: 复制文件到其他目录
 * 输入参数:
 *          无
 * 输出参数:
 *          无
 */
void DataView::moveTo() {

    // 获取选中的item
    QListWidget *t_pListWidget = m_poscorllArea;
    QList<QListWidgetItem *> selectedItems = t_pListWidget->selectedItems();
    if (selectedItems.isEmpty()) {
        return;
    }

    QDesktopServices::openUrl( QUrl( "osk.exe", QUrl::TolerantMode ) );
    for (int i = 0; i < selectedItems.size(); i ++) {
        QString newName = QFileDialog::getSaveFileName(this, tr("Move File"),
                                                       QDir::currentPath(), tr("File (*.csv)"));
        if (newName.isEmpty()) {
            return;
        }

        // 获取目录路径
        QString filepath = m_systemPath + "/" + ui->comboBox->currentText() + "/";

        // 复制文件到指定目录下
        QListWidgetItem *item = selectedItems.at(i);
        QString filename = filepath + item->text();
        bool ok = QFile::copy(filename, newName);
        if (!ok) {
            QMessageBox::warning(this, tr("Warnning"),
                                 tr("Copy file error!"), QMessageBox::Ok);
            continue;
        }
    }
}

/**
 * @brief DataView::insert
 * @param filename
 */
void DataView::insert(QString filename) {
    if (filename.isEmpty()) {
        return;
    }

    // 清空背景
    int count = m_poscorllArea->count();
    for (int r = 0; r < count; r ++) {
        QListWidgetItem *item = m_poscorllArea->item( r );
        item->setBackgroundColor( Qt::white );
    }

    //
    QListWidgetItem *item = new QListWidgetItem( /*QIcon( ":/icons/file.png" ),*/ filename );
    item->setBackground( QBrush( Qt::gray ) );
    item->setFont( QFont( "黑体", 12 ) );
    item->setSizeHint( QSize(128, 64) );
    m_poscorllArea->insertItem( 0, item );
}

/**
 * 函数名称: initializeSystem
 * 函数用途: 初始化文件系统
 * 输入参数:
 *          无
 * 输出参数:
 *          无
 */
void DataView::initializeSystem() {

    QString path = m_systemPath;
    // 检查系统文件目录是否存在,如果不存在则创建系统文件目录//lt:data目录
    QDir dir(path);
    if(!dir.exists()) {
        bool ok = dir.mkdir(path);
        if (!ok) {
            QMessageBox::warning(this, tr("Warnning"),
                                 tr("Create dir error!"), QMessageBox::Ok);
            return;
        }
    }

    // 检查数据目录是否存在,否则创建相应的目录
    ui->comboBox->clear();
    QStringList dirNameList;
    if (m_supportCuvette) {
        // 核酸检测、蛋白检测、全波长检测、细胞检测、微阵列检测、标准曲线、动力学检测
        dirNameList << tr("Nucleic Acid") << tr("Protein") << tr("UV-VIS") << tr("Cell Culture")
                    << tr("Micro Array") << tr("Kit Method") << tr("Dynamics") << tr("Device Check");
    } else {
        // 核酸检测、蛋白检测、全波长检测、细胞检测、微阵列检测、标准曲线、动力学检测
        dirNameList << tr("Nucleic Acid") << tr("Protein") << tr("UV-VIS") << tr("Cell Culture")
                    << tr("Micro Array") << tr("Kit Method") << tr("Device Check");
    }


    m_dirMap.clear();
    m_viewTitle.clear();
    for (int i = 0; i < dirNameList.size(); i ++) {
        QString dirPath = path + "/" + dirNameList.at(i);
        dir.setPath( dirPath );//lt:进入子目录，不存在下面的代码来建立
        if (!dir.exists()) {
            bool ok = dir.mkdir( dirPath );
            if (!ok) {
                continue;
            }
        }
        // 将文目录名称放入comboBox中
        QString name = dirNameList.at(i);
        ui->comboBox->addItem( QIcon( ":/icons/folder" ), name );//lt:自动加索引
        m_dirMap.insert( name, i );//lt:人为加索引，切换页面时，通过该qmap的name值作为键，找到和combobox索引相同的值i，通过该值设置控件的index来切换控件
        m_viewTitle.insert( name, name );
    }
}

/**
 * 函数名称: initializeWidget
 * 函数用途: 初始化窗体控件
 * 输入参数:
 *          无
 * 输出参数:
 *          无
 */
void DataView::initializeWidget() {

    m_poscorllArea = new OListscroll(this);
    m_poscorllArea->setGeometry(QRect(1,72,278,570));
    ui->comboBox->setGeometry(QRect(1,1,280,70));
    m_pdvlayout = new QVBoxLayout;
    m_pdvlayout->addWidget(ui->comboBox);
    m_pdvlayout->addWidget(m_poscorllArea);
    m_pdvlayout->addLayout(ui->horizontalLayout);

    connect(ui->comboBox, SIGNAL(currentIndexChanged( QString )),
            this, SLOT(updateView( QString )));

    connect(m_poscorllArea, SIGNAL(itemDoubleClicked(QListWidgetItem*)),
            this, SLOT(itemSelected( QListWidgetItem* )));

    connect(ui->deleteBtn, SIGNAL(clicked( bool )), this, SLOT(remove()));
    connect(ui->moveToBtn, SIGNAL(clicked( bool )), this, SLOT(moveTo()));
}
