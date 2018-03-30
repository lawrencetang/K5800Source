#include "settingview.h"
#include "ui_settingview.h"

#include <QDir>
#include <QDebug>
#include <QSettings>
#include <QMessageBox>
#include <QDesktopWidget>
#include <QCoreApplication>
#include <QElapsedTimer>

#include "nadialog.h"
#include "ptdialog.h"
#include "kmdialog.h"
#include "dydialog.h"
#include "uvdialog.h"
#include "ccdialog.h"
#include "madialog.h"
#include "../DataModel/settingdatamodel.h"

SettingView::SettingView(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::SettingView) {
    ui->setupUi(this);

    m_modifyStatus = false;
    m_isNeedBlank = false;

    initializeSystem();
    initializeWidget();
}

SettingView::~SettingView() {
    delete ui;
    delete m_pNaDialog;
    delete m_pPtDialog;
    delete m_pKmDialog;
    delete m_pUvDialog;
    delete m_pDyDialog;
    delete m_pCcDialog;
    delete m_pMaDialog;
}

/**
 * @brief SettingView::getChannelNumber
 * @return
 */
int SettingView::getChannelNumber() {
    return m_channelNumber;
}

/**
 * @brief SettingView::setAutoCheckIamge
 * @param ok
 */
void SettingView::setAutoCheckIamge(bool ok) {
    ui->adCbox->setEnabled( ok );
    ui->adCbox->setChecked( ok );
}

/**
 * @brief SettingView::hideDialogs
 */
void SettingView::hideDialogs() {
    m_pNaDialog->hide();
    m_pPtDialog->hide();
    m_pKmDialog->hide();
    m_pUvDialog->hide();
    m_pDyDialog->hide();
    m_pCcDialog->hide();
    m_pMaDialog->hide();
}

/**
 * @brief SettingView::selectedType
 * @return
 */
QString SettingView::selectedType() {
    if (ui->microsaleRBtn->isChecked()) {
        return "Microscale";
    } else {
        return "Cuvette";
    }
}

/**
 * @brief SettingView::isAutoMeasure
 * @return
 */
bool SettingView::isAutoMeasure() {
    return ui->amCBox->isChecked();
}

/**
 * @brief SettingView::clear 清空所有设置信息
 */
void SettingView::clear() {
    clearModel();
    clearTable();
}

/**
 * @brief SettingView::clear 清空所有设置信息
 */
void SettingView::clearid() {
    createInfo();
}

/**
 * @brief SettingView::subDirChanged 设置当前设置界面
 * @param subDir = “Nucleic Acid”, “Protein” ...
 */
void SettingView::subDirChanged(QString subDir) {
    if (subDir == tr( "Dynamics" ) ||
            subDir == tr( "Cell Culture" )) {
        if (!m_cuvetteEnable) {
            return;
        } else {
            ui->cuvetteRBtn->setChecked( true );
            m_subDir = subDir;
            changeMeasureWay();
            ui->microsaleRBtn->setEnabled( false );
        }//lt:如果是动态或细胞液，配置文件中设置了比色皿true则cuvetterbtn被选中并改变测试方法。
    } else {
        if (!m_cuvetteEnable) {
            ui->cuvetteRBtn->setChecked( false );
            ui->cuvetteRBtn->setEnabled( false );
        }

        ui->microsaleRBtn->setEnabled( true );
        ui->microsaleRBtn->setChecked( true );
        m_subDir = subDir;//lt:获取到当前测试项目
        changeMeasureWay();
    }//lt:不是动态或细胞液，如果配置文件中设置比色皿为false则比色皿按钮失能，反之微量按钮选中，并改变方法

    QString title =  m_subDir;
    ui->caseGBox->setTitle( title );//lt:设置tablewedgit的名称,并显示

    if (m_subDir == tr( "Nucleic Acid" )) {
        m_pNaDialog->defaultInfo();//lt:保存相应对话框中信息，并发送其对话框的okbutton信号
    } else if ( m_subDir == tr( "Protein" ) ) {
        m_pPtDialog->defaultInfo();
    } else if ( m_subDir == tr( "UV-VIS" ) ) {
        m_pUvDialog->defaultInfo();
    } else if ( m_subDir == tr( "Dynamics" ) ) {
        m_pDyDialog->defaultInfo();
    } else if ( m_subDir == tr( "Cell Culture" ) ) {
        m_pCcDialog->defaultInfo();
    } else if ( m_subDir == tr( "Micro Array" ) ) {
        m_pMaDialog->defaultInfo();
    } else if ( m_subDir == tr( "Kit Method" ) ) {
        m_pKmDialog->defaultInfo();
    }
    settingwavelength();//ltj
    createInfo();//lt:建立settingview数据模型
}

/**
 * @brief SettingView::add 用户点击添加按钮时的操作
 */
void SettingView::add() {

    // 1. 判断是否超过通道限制
    int rowCount = ui->tableWidget->rowCount();
    int stdValue = ui->unSpinBox->value();
    if (stdValue <= rowCount) {
        QMessageBox::warning(this, tr( "Warning" ),
                             tr( "Out of use channel number!" ), QMessageBox::Ok);
        return;
    }

    if (ui->idLineEdit->text().isEmpty() ||
            ui->nameLineEdit->text().isEmpty()) {

        QMessageBox::warning(this, tr( "Warning" ),
                             tr( "Please input id and name first!" ), QMessageBox::Ok);
        return;
    }

    // 2. 显示设置对话框
    showDialog();
}

/**
 * @brief SettingView::edit 用户点击编辑按钮时的操作
 *
 */
void SettingView::edit() {

    // 1. 读取获取参数列表中的关键字
    QString filename = QDir::currentPath() + "/configure/system.ini";
    QSettings *configIniReader = new QSettings( filename, QSettings::IniFormat );
    QString keyStr1 = configIniReader->value( QString( "/%1/KeyStr1" ).arg( m_subDir ) ).toString();
    QString keyStr2 = configIniReader->value( QString( "/%1/KeyStr2" ).arg( m_subDir ) ).toString();;
    delete configIniReader;
    configIniReader = NULL;

    // 2. 获取用户选择的参数列表中的项目
    QTableWidget *tableWidget = ui->tableWidget;
    QList<QTableWidgetItem *> selectedItems = tableWidget->selectedItems();
    if (selectedItems.isEmpty()) {
        return;
    }
    QTableWidgetItem *item = selectedItems.first();
    int row = tableWidget->row( item );

    // 3. 获取参数
    QString paramStr1;
    int column1 = keyColumn( keyStr1 );
    if (-1 != column1) {
        QTableWidgetItem *paramItem = tableWidget->item( row, column1 );
        paramStr1 = paramItem->text();
    }
    QString paramStr2;
    if (!keyStr2.isEmpty() && "NULL" != keyStr2) {
        int column2 = keyColumn( keyStr2 );
        if (-1 != column2) {
            QTableWidgetItem *paramItem = tableWidget->item( row, column2 );
            paramStr2 = paramItem->text();
        }
    }

    // 4. 显示对话框
    showDialog( paramStr1, paramStr2 );//lt:大部分是Method Parameters的值和NULL值
    m_editRow = row;
}

/**
 * lt:从mainwindow直接展示对话框
 */
void SettingView::directShowDialog() {
    QTableWidget *tableWidget = ui->tableWidget;
    tableWidget->setCurrentItem( tableWidget->item(0,0) );
    edit();
}

/**
 * @brief SettingView::remove 用户点击删除按钮时的操作
 */
void SettingView::remove() {

    QTableWidget *tableWidget = ui->tableWidget;
    QList<QTableWidgetItem *> selectedItems = tableWidget->selectedItems();
    for (int i = 0; i < selectedItems.size(); i ++) {
        QTableWidgetItem *selectedItem = selectedItems.at( i );
        // 1. 获取选中项目的行号
        int row = tableWidget->row( selectedItem );
        if (row < 0) {
            continue;
        }
        // 2. 删除项目
        tableWidget->removeRow( row );
    }
    if (tableWidget->rowCount() == 0) {
        tableWidget->horizontalHeader()->setSectionResizeMode( QHeaderView::Stretch );
    }
}

void SettingView::setting_waiting(int timeout) {
    QElapsedTimer t;
    t.start();
    while(t.elapsed() < timeout) {
        QCoreApplication::processEvents();
    }
}

/**
 * @brief SettingView::cancel 用户点击取确定钮时的操作
 */
void SettingView::ok() {
    /*
     *
     * 模态转非模态添加代码
     *
     */
    if (m_subDir == tr( "Nucleic Acid" ) && m_pNaDialog->m_showdialogflag == true ) {
        m_pNaDialog->settinghidedlg();
        setting_waiting(500);//lt:让子弹飞0.5秒，避免程序多线执行
    }else if ( m_subDir == tr( "Protein" ) && m_pPtDialog->m_showdialogflag == true ) {
        m_pPtDialog->settinghidedlg();
        setting_waiting(500);
    }else if ( m_subDir == tr( "Cell Culture" ) && m_pCcDialog->m_showdialogflag == true ) {
        m_pCcDialog->settinghidedlg();
        setting_waiting(500);
    } else if ( m_subDir == tr( "Kit Method" ) && m_pKmDialog->m_showdialogflag == true ) {
        m_pKmDialog->settinghidedlg();
        setting_waiting(500);
    }//lt:应防止关闭子项对话框后点击ok再次进入这段代码
    //int status = 0;
    //if (ui->okPBtn == sender()) {//ltg
    createInfo();
    int status = 1;

    m_isNeedBlank = false;
    if (m_modifyStatus) {
        m_isNeedBlank = true;
    }
    m_modifyStatus = false;//lt:设置之后如果m_modifystatus为true则需要重新空白s

    QString opStr = QString::number( ui->opComboBox->currentIndex() );//lt:0,1,2,3
    QString rootStr = getRootDirEnStr();
    QString subDirStr = getSubDirEnstr();
    QString filename = QDir::currentPath() + "/configure/setting.ini";
    QSettings *configIniWriter= new QSettings( filename, QSettings::IniFormat );
    configIniWriter->setValue( QString( "%1/%2" ).arg(rootStr).arg(subDirStr), opStr );
    delete configIniWriter;
    configIniWriter = NULL;

    //}
    emit hideView( status );
}

/**
 * @brief SettingView::modify
 */
void SettingView::modify() {
    if( m_subDir == tr( "Nucleic Acid" ) ) {
        m_pNaDialog->settinghidedlg();
    }
    else if( m_subDir == tr( "Protein") ) {
        m_pPtDialog->settinghidedlg();
    }
    else if( m_subDir == tr( "Cell Culture") ) {
        m_pCcDialog->settinghidedlg();
    }
    else if( m_subDir == tr( "Kit Method" ) ) {
        m_pKmDialog->settinghidedlg();
    }//lt:防止showdialog时点击其他控件死机
    clearTable();
    displaySettingInfo();
}

/**
 * @brief SettingView::updateOp
 * @param ok
 */
void SettingView::updateOp(bool ok) {
    if (ok) {
        ui->opComboBox->setCurrentIndex( 0 );
    } else {
        QString rootStr = getRootDirEnStr();
        QString subDirStr = getSubDirEnstr();
        QString filename = QDir::currentPath() + "/configure/setting.ini";
        QSettings *configIniReader= new QSettings( filename, QSettings::IniFormat );
        int index = configIniReader->value( QString( "%1/%2" ).arg(rootStr).arg(subDirStr) ).toInt();
        ui->opComboBox->setCurrentIndex( index );
        delete configIniReader;
        configIniReader = NULL;
    }
    //modify();
}

/**
 * @brief SettingView::changeMeasureWay 获取切换超微量以及比色皿检测时的操作
 */
void SettingView::changeMeasureWay() {
    modify();//ltj:防止比色皿微量切换死机
    clearTable();
    if (ui->microsaleRBtn->isChecked()) {

        ui->stirGBox->setEnabled( false );
        ui->amCBox->setEnabled( true );
        // 设置当前使用的通道数以及最大通道数
        ui->unSpinBox->setMinimum( 1 );
        ui->unSpinBox->setMaximum( m_channelNumber );
        ui->mnSpinBox->setMaximum( m_channelNumber );

        ui->unSpinBox->setValue( 1 );
        ui->mnSpinBox->setValue( m_channelNumber );

        m_rootDir = ui->microsaleRBtn->text();
        updateOptical();
    } else {

        ui->amCBox->setChecked( false );
        ui->amCBox->setEnabled( false );
        ui->stirGBox->setEnabled( true );
        // 设置当前使用的通道数以及最大通道数
        ui->unSpinBox->setMinimum( 1 );
        ui->unSpinBox->setMaximum( 1 );
        ui->mnSpinBox->setMaximum( 1 );

        ui->unSpinBox->setValue( 1 );
        ui->mnSpinBox->setValue( 1 );

        m_rootDir = ui->cuvetteRBtn->text();
        updateOptical();
    }

    if (m_channelNumber == 1) {
        if (sender() == ui->microsaleRBtn || sender() == ui->cuvetteRBtn) {
            modify();
        }
    }
}


/**
 * @brief SettingView::changeAutoMeasure ltj
 */
void SettingView::changeAutoMeasure() {
    if (ui->amCBox->isChecked()) {
        ui->amCBox->setChecked(false);
    }
    else ui->amCBox->setChecked(true);
}


/**
 * @brief SettingView::displaySettingInfo
 */
void SettingView::displaySettingInfo() {

    if (sender() != ui->idLineEdit
            && sender() != ui->nameLineEdit
            && sender() != ui->amCBox && sender() !=ui->adCbox) {
        m_modifyStatus = true;
    }//lt:是其中一个控件发送的信号则跳出

    QString methodStr;
    QString watchStr;//lt:这两个是设置对话框传出的数据
    QString baseStr = baseParamsStr();
    QString stirStr = dcMotorStr();//lt:获得基础参数数据和直流电机搅拌数据

    if (m_subDir == tr( "Nucleic Acid" )) {
        methodStr = m_pNaDialog->paramStr();
        watchStr = m_pNaDialog->watchStr();
    } else if ( m_subDir == tr( "Protein" ) ) {
        methodStr = m_pPtDialog->paramStr();
        watchStr = m_pPtDialog->watchStr();
    } else if ( m_subDir == tr( "UV-VIS" ) ) {
        methodStr = m_pUvDialog->paramStr();
        watchStr = m_pUvDialog->watchStr();
    } else if ( m_subDir == tr( "Dynamics" ) ) {
        methodStr = m_pDyDialog->paramStr();
        watchStr = m_pDyDialog->watchStr();
    } else if ( m_subDir == tr( "Cell Culture" ) ) {
        methodStr = m_pCcDialog->paramStr();
        watchStr = m_pCcDialog->watchStr();
    } else if ( m_subDir == tr( "Micro Array" ) ) {
        methodStr = m_pMaDialog->paramStr();
        watchStr = m_pMaDialog->watchStr();
    } else if ( m_subDir == tr( "Kit Method" ) ) {
        methodStr = m_pKmDialog->paramStr();
        watchStr = m_pKmDialog->watchStr();
    }

    QStringList settingInfo;
    settingInfo.append( baseStr );
    settingInfo.append( methodStr );
    settingInfo.append( watchStr );
    settingInfo.append( stirStr );
    //QMessageBox::warning(0, "baseStr", baseStr, QMessageBox::Ok);//ltj

    if (-1 == m_editRow) {
        insertData( settingInfo );//lt:把配置写tablewidget
    } else {
        replaceData( settingInfo );
        m_editRow = -1;
    }

    QTableWidget *tableWidget = ui->tableWidget;
    if (tableWidget->rowCount() > 0) {
        /*if ( m_subDir == tr( "Cell Culture" ) ||
             m_subDir == tr( "UV-VIS" ) || m_subDir == tr( "Kit Method" )) {
            tableWidget->horizontalHeader()->setSectionResizeMode( QHeaderView::Stretch );
        } else {
            tableWidget->horizontalHeader()->setSectionResizeMode( QHeaderView::ResizeToContents );
        }*///ltg
        tableWidget->horizontalHeader()->setSectionResizeMode( QHeaderView::ResizeToContents );//ltj
    }
    if (m_subDir == tr( "Kit Method") ) {
        ui->blSpinBox->setValue( m_pKmDialog->m_fixedwavelength ); //ltj:写试剂盒的各个测试方法的固定波长
    }//ltj
}//lt:显示设置信息到设置界面内的表

/**
 * @brief SettingView::baseParamsStr
 * @return
 */
QString SettingView::baseParamsStr() {
    QString baseStr;
    baseStr.append( "id=" + ui->idLineEdit->text() );
    baseStr.append( "," );
    baseStr.append( "name=" + ui->nameLineEdit->text() );
    baseStr.append( "," );
    baseStr.append( "baseline=" + QString::number( ui->blSpinBox->value() ) );
    baseStr.append( "," );
    QString opStr = ui->opComboBox->currentText().replace( "mm", "");//ltg
    if (opStr == "Auto") {
        baseStr.append( "optical=" +  opStr );//ltg
    } else {
        baseStr.append( "optical=" +  opStr );//ltg
    }

    QString text;
    if (m_subDir == tr( "Nucleic Acid" )) {
        text = "Nucleic Acid";
    } else if (m_subDir == tr(  "Protein" )) {
        text = "Protein";
    } else if (m_subDir == tr( "Cell Culture" )) {
        text = "Cell Culture";
    } else if (m_subDir == tr( "UV-VIS" )) {
        text = "UV-VIS";
    } else if (m_subDir == tr( "Kit Method" )) {
        text = "Kit Method";
    } else if (m_subDir == tr( "Micro Array" )) {
        text = m_pMaDialog->measureStr();
    } else if (m_subDir == tr( "Dynamics" )) {
        text = "Dynamics";
    } else if (m_subDir == tr( "Device Check" )) {
        text = "Device Check";
    }

    baseStr.append( "," );
    baseStr.append( "measure=" + text );
    return baseStr;
}

/**
 * @brief SettingView::dcMotorStr
 * @return
 */
QString SettingView::dcMotorStr() {
    QString stirStr;
    if (m_rootDir == tr( "Cuvette" )) {
        stirStr.append( "level=" + QString::number( ui->rsSpinBox->value() ) );
        stirStr.append( "," );
        stirStr.append( "kTime=" + QString::number( ui->ktSpinBox->value() * 60 ) );//ltg
        stirStr.append( "," );
        stirStr.append( "rTime=" + QString::number( ui->rtSpinBox->value() * 60 ) );//ltg
        stirStr.append( "," );
        stirStr.append( "iTime=" + QString::number( ui->itSpinBox->value() * 60 ) );//ltg
    } else {
        stirStr = "NULL";
    }
    return stirStr;
}

/**
 * @brief SettingView::clearDataList
 */
void SettingView::clearDataList() {
    m_dataModelList.clear();
    /*while (!m_dataModelList.isEmpty()) {
        SettingDataModel *settingDataModel = m_dataModelList.takeFirst();
        delete settingDataModel;
        settingDataModel = NULL;
    }*/
}

/**
 * @brief SettingView::keyColumn
 * @param headerStr
 * @return
 */
int SettingView::keyColumn(QString headerStr) {
    if (m_headerList.contains( headerStr )) {
        return m_headerList.indexOf( headerStr );
    }
    return -1;
}

/**
 * @brief SettingView::createInfo
 */
void SettingView::createInfo() {
    clearModel();
    int rowCount = ui->tableWidget->rowCount();
    int columnCount = ui->tableWidget->columnCount();

    QString baseStr;
    QString watchStr;
    QString methodStr;
    QString dcMotorStr;
    for (int r = 0; r < rowCount; r ++) {
        for (int c = 0; c < columnCount; c ++) {
            QTableWidgetItem *item = ui->tableWidget->item( r, c );
            QString itemStr = item->text();
            if (itemStr == "NULL" ||
                    itemStr.isEmpty()) {
                continue;
            }

            if (0 == c) {
                baseStr = itemStr;
            } else if (1 == c) {
                methodStr = itemStr;
            } else if (2 == c) {
                watchStr = itemStr;
            } else if (3 == c) {
                dcMotorStr = itemStr;
            }
        }//lt:将tablewidget中的base,method,watch,dcmotor存入相应qsting中传递进入settingdatamodel
        SettingDataModel *settingDataModel = new SettingDataModel( baseStr, methodStr, dcMotorStr, watchStr );
        m_dataModelList.append( settingDataModel );//lt:有几个设置记录放几个设置记录(分行显示)
        if (ui->mnSpinBox->value() == 1) {
            QString typeStr = settingDataModel->methodValue( "type" );
            QString titleStr;
            if (typeStr == "NULL") {
                titleStr = tr( "%1" ).arg( m_subDir );
            } else {
                titleStr = tr( "%1(%2)" ).arg( m_subDir ).arg( typeStr );
            }
            emit changeTitle( titleStr );//lt:改变plotview界面的title文字
        }
    }
}

/**
 * @brief 用于切换界面时设定固定波长//ltj
 */
void SettingView::settingwavelength() {
    if (m_subDir == tr( "Nucleic Acid" ) ) {
        ui->blSpinBox->setValue( 340 );
    } else if ( m_subDir == tr( "Protein" ) ) {
        ui->blSpinBox->setValue( 340 );//ltj,试剂盒更改控件后恢复
    } else if ( m_subDir == tr( "UV-VIS" ) ) {
        ui->blSpinBox->setValue( 850 );//ltj,固定基准波长
    } else if ( m_subDir == tr( "Dynamics" ) ) {
        ui->blSpinBox->setValue( 200 );//ltj,固定基准波长
    } else if ( m_subDir == tr( "Cell Culture" ) ) {
        ui->blSpinBox->setValue( 850 );//ltj,固定基准波长
    } else if ( m_subDir == tr( "Micro Array" ) ) {
        ui->blSpinBox->setValue( 340 );
    } else if ( m_subDir == tr( "Kit Method" ) ) {
        ui->blSpinBox->setValue( 340 );
    }
    //QMessageBox::warning(0, "test", QString::number(ui->blSpinBox->value(), 10), QMessageBox::Ok );
}

/**
 * @brief SettingView::showDialog
 * @param paramStr
 * @param watchStr
 */
void SettingView::showDialog(QString paramStr, QString watchStr) {

    QDesktopWidget *deskdop = QApplication::desktop();
    if (m_subDir == tr( "Nucleic Acid" ) ) {
        ui->blSpinBox->setValue( 340 );//ltj,试剂盒更改控件后恢复,放在showdialog前面，为了不modifblspinbox控件时关闭对话框
        m_pNaDialog->showDialog( paramStr );
        QPoint centerPoint = deskdop->rect().center() - m_pNaDialog->rect().center();
        m_pNaDialog->move( centerPoint );//lt:定位编辑对话框在中心
    } else if ( m_subDir == tr( "Protein" ) ) {
        ui->blSpinBox->setValue( 340 );//ltj,试剂盒更改控件后恢复
        m_pPtDialog->showDialog( paramStr );
        QPoint centerPoint = deskdop->rect().center() - m_pPtDialog->rect().center();
        m_pPtDialog->move( centerPoint );
    } else if ( m_subDir == tr( "UV-VIS" ) ) {
        ui->blSpinBox->setValue( 850 );//ltj,固定基准波长
        m_pUvDialog->showDialog( paramStr );
        QPoint centerPoint = deskdop->rect().center() - m_pUvDialog->rect().center();
        m_pUvDialog->move( centerPoint );
    } else if ( m_subDir == tr( "Dynamics" ) ) {
        ui->blSpinBox->setValue( 200 );//ltj,固定基准波长
        m_pDyDialog->showDialog( paramStr, watchStr );
        QPoint centerPoint = deskdop->rect().center() - m_pDyDialog->rect().center();
        m_pDyDialog->move( centerPoint );
    } else if ( m_subDir == tr( "Cell Culture" ) ) {
        ui->blSpinBox->setValue( 850 );//ltj,固定基准波长
        m_pCcDialog->showDialog( paramStr );
        QPoint centerPoint = deskdop->rect().center() - m_pCcDialog->rect().center();
        m_pCcDialog->move( centerPoint );
    } else if ( m_subDir == tr( "Micro Array" ) ) {
        m_pMaDialog->showDialog( paramStr, watchStr );
        QPoint centerPoint = deskdop->rect().center() - m_pMaDialog->rect().center();
        m_pMaDialog->move( centerPoint );
    } else if ( m_subDir == tr( "Kit Method" ) ) {
        m_pKmDialog->showDialog( paramStr );
        QPoint centerPoint = deskdop->rect().center() - m_pKmDialog->rect().center();
        m_pKmDialog->move( centerPoint );
    }
}

/**
 * @brief SettingView::replaceData
 * @param data
 */
void SettingView::replaceData(QStringList data) {
    QTableWidget *tableWidget = ui->tableWidget;
    int columnCount = tableWidget->columnCount();
    int size = data.size();
    for (int i = 0; i < columnCount; i ++) {
        QTableWidgetItem *item = ui->tableWidget->item( m_editRow, i );
        if (i < size) {
            item->setText( data.at( i ) );
        }
    }
}

/**
 * @brief SettingView::insertData
 * @param data
 */
void SettingView::insertData(QStringList data) {

    QTableWidget *tableWidget = ui->tableWidget;
    // 获取函数和列数
    int columnCount = tableWidget->columnCount();
    int rowCount = tableWidget->rowCount();
    tableWidget->insertRow( rowCount );

    int size = data.size();
    for (int i = 0; i < columnCount; i ++) {
        QString text;
        if (i < size) {
            text = data.at( i );
        } else {
            text = "NULL";
        }
        QTableWidgetItem *item = new QTableWidgetItem( text );

        item->setTextAlignment( Qt::AlignHCenter | Qt::AlignVCenter );
        tableWidget->setItem( rowCount, i, item );
    }
}

/**
 * @brief SettingView::clearModel 清空所有的设置model
 */
void SettingView::clearModel() {
    m_dataModelList.clear();
    /*
    if (!m_dataModelList.isEmpty()) {
        while (m_dataModelList.size()) {
            SettingDataModel *settingDataModel = m_dataModelList.takeFirst();
            delete settingDataModel;
            settingDataModel = NULL;
        }
    }
*/
}

/**
 * @brief SettingView::clearTable 清空table中的数据
 */
void SettingView::clearTable() {

    QTableWidget *tableWidget = ui->tableWidget;
    int rowCount = tableWidget->rowCount();
    //QMessageBox::ning(0,"warning", QString::number(rowCount, 10), QMessageBox::Ok);//ltj
    //int columnCount = tableWidget->columnCount();

    for (int r = rowCount - 1; r >= 0; r --) {
        tableWidget->removeRow(r);
    }
    /*
    for (int r = rowCount - 1; r >= 0; r --) {
        for (int c = columnCount - 1; c >= 0; c --) {
            QTableWidgetItem *item = tableWidget->takeItem(r, c);

            delete item;
            item = NULL;
        }
        tableWidget->removeRow(r);
    }*/
    tableWidget->horizontalHeader()->setSectionResizeMode( QHeaderView::Stretch );
}

/**
 * @brief SettingView::updateOptical
 */
void SettingView::updateOptical() {

    if (m_channelNumber == 1) {
        disconnect(ui->opComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(modify()));
    }
    QString filename = QDir::currentPath() + "/configure/system.ini";
    QSettings *configIniReader = new QSettings( filename, QSettings::IniFormat );

    QString text;
    if (m_rootDir == tr( "Cuvette" )) {
        text = "Cuvette";
    } else {
        text = "Microscale";
    }
    QStringList opticals = configIniReader->value( QString( "/%1/Optical" ).arg( text ) ).toStringList();
    ui->opComboBox->clear();
    if (m_rootDir == tr( "Microscale" )) {
        ui->opComboBox->addItem( QIcon(":/icons/optical.png"), tr ( "Auto" ) );
    }
    /*if (m_subDir == tr( "UV-VIS" ) || m_subDir == tr( "Kid Method" )) {
        for (int i = 0; i < opticals.size(); i ++) {
            if (opticals.at( i ) == "1") {
                QString opstr = opticals.at( i );
                ui->opComboBox->addItem( QIcon(":/icons/optical.png"), opstr + "mm" );//ltg
            }
        }
    } else {
        for (int i = 0; i < opticals.size(); i ++) {
            QString opstr = opticals.at( i );
            ui->opComboBox->addItem( QIcon(":/icons/optical.png"), opstr + "mm" );//ltg
        }
    }*///ltg
    for (int i = 0; i < opticals.size(); i ++) {
        QString opstr = opticals.at( i );
        ui->opComboBox->addItem( QIcon(":/icons/optical.png"), opstr + "mm" );//ltj
    }

    delete configIniReader;
    configIniReader = NULL;

    if (m_channelNumber == 1) {
        connect(ui->opComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(modify()));
    }
}

/**
 * @brief SettingView::updateHeaders
 * @param headerLavbels
 */
void SettingView::updateHeaders(QStringList headerLavbels) {

    QTableWidget *tableWidget = ui->tableWidget;
    tableWidget->setColumnCount( headerLavbels.size() );//lt:计算出表头的项数
    tableWidget->setHorizontalHeaderLabels( headerLavbels );//lt:水平布置表头内容
    tableWidget->horizontalHeader()->setSectionResizeMode( QHeaderView::Stretch );//lt:设置表头文字填充格式

    clearTable();
    int columnCount = headerLavbels.size();
    for (int i = 0; i < columnCount; i ++) {
        QTableWidgetItem *item = tableWidget->horizontalHeaderItem( i );//lt:返回各水平表头项目的内容
        item->setFont( QFont( "微软雅黑", 10, QFont::Bold ) );
        item->setTextColor( Qt::darkBlue );
    }
}

/**
 * @brief SettingView::getRootDirEnStr
 * @return
 */
QString SettingView::getRootDirEnStr() {
    QString text;
    if (m_rootDir == tr( "Cuvette" )) {
        text = "Cuvette";
    } else {
        text = "Microscale";
    }
    return text;
}

/**
 * @brief SettingView::getSubDirEnstr
 * @return
 */
QString SettingView::getSubDirEnstr() {
    QString text;
    if (m_subDir == tr( "Nucleic Acid" )) {
        text = "Nucleic Acid";
    } else if (m_subDir == tr(  "Protein" )) {
        text = "Protein";
    } else if (m_subDir == tr( "Cell Culture" )) {
        text = "Cell Culture";
    } else if (m_subDir == tr( "UV-VIS" )) {
        text = "UV-VIS";
    } else if (m_subDir == tr( "Kit Method" )) {
        text = "Kit Method";
    } else if (m_subDir == tr( "Micro Array" )) {
        text = m_pMaDialog->measureStr();
    } else if (m_subDir == tr( "Dynamics" )) {
        text = "Dynamics";
    } else if (m_subDir == tr( "Device Check" )) {
        text = "Device Check";
    }
    return text;
}

/**
 *lt:id加的方法
 */
/*void SettingView::idadd() {
    bool ok;
    int idlineedit = ui->idLineEdit->text().toInt(&ok,10);
    idlineedit ++ ;
    ui->idLineEdit->setText( QString::number(idlineedit, 10) );
    //QMessageBox::warning(0,"warning", ui->idLineEdit->text(), QMessageBox::Ok);
}*/
/*
 *
 * ltj:控制sample的id
 *
 */
void SettingView::changeId(QString recordSendvalue) {
    m_modifyStatus = true;
    ui->nameLineEdit->setText(recordSendvalue);
    ok();
}

/**
 * @brief SettingView::initializeSystem 加载系统参数
 * 1. 通道数据
 * 2. 是否支持比色皿
 * 3. SettingView的Header
 */
void SettingView::initializeSystem() {

    m_editRow = -1;
    QString filename = QDir::currentPath() + "/configure/system.ini";
    QSettings *configIniReader = new QSettings( filename, QSettings::IniFormat );

    m_channelNumber = configIniReader->value( "/System/Channel Number" ).toInt();//lt:通道号
    m_cuvetteEnable = configIniReader->value( "/System/Cuvette Enable" ).toBool();//lt:是否支持比色皿
    m_headerList = configIniReader->value( "/SettingView/Headers" ).toStringList();//lt:读出表头
    if (m_headerList.isEmpty()) {
        QMessageBox::warning( this, tr( "Warning" ),
                              tr( "Setting view header of table lose!" ), QMessageBox::Ok);
    } else {
        updateHeaders( m_headerList );//lt:写表头
    }

    delete configIniReader;
    configIniReader = NULL;
}

/**
 * @brief SettingView::initializeWidget 初始化画UI
 */
void SettingView::initializeWidget() {

    // 创建设置对话框
    m_pNaDialog = new NaDialog( this );
    m_pNaDialog->hide();
    connect(m_pNaDialog, SIGNAL(okBtnClicked()), this, SLOT(displaySettingInfo()));
    m_pPtDialog = new PtDialog();
    m_pPtDialog->hide();
    connect(m_pPtDialog, SIGNAL(okBtnClicked()), this, SLOT(displaySettingInfo()));
    m_pKmDialog = new KmDialog();
    m_pKmDialog->hide();
    connect(m_pKmDialog, SIGNAL(okBtnClicked()), this, SLOT(displaySettingInfo()));
    m_pUvDialog = new UvDialog();
    m_pUvDialog->hide();
    connect(m_pUvDialog, SIGNAL(okBtnClicked()), this, SLOT(displaySettingInfo()));
    m_pDyDialog = new DyDialog();
    m_pDyDialog->hide();
    connect(m_pDyDialog, SIGNAL(okBtnClicked()), this, SLOT(displaySettingInfo()));
    m_pCcDialog = new CcDialog();
    m_pCcDialog->hide();
    connect(m_pCcDialog, SIGNAL(okBtnClicked()), this, SLOT(displaySettingInfo()));
    m_pMaDialog = new MaDialog();
    m_pMaDialog->hide();
    connect(m_pMaDialog, SIGNAL(okBtnClicked()), this, SLOT(displaySettingInfo()));

    connect(ui->microsaleRBtn, SIGNAL( clicked(bool) ), this, SLOT( changeMeasureWay() ) );
    connect(ui->cuvetteRBtn, SIGNAL( clicked(bool) ), this, SLOT( changeMeasureWay() ) );

    connect(ui->addPBtn, SIGNAL(clicked(bool)), this, SLOT(add()));
    connect(ui->editPBtn, SIGNAL(clicked(bool)), this, SLOT(edit()));
    connect(ui->removePBtn, SIGNAL(clicked(bool)), this, SLOT(remove()));
    connect(ui->okPBtn, SIGNAL(clicked(bool)), this, SLOT(ok()));
    connect(ui->cancelPBtn, SIGNAL(clicked(bool)), this, SLOT(ok()));

    if (m_channelNumber == 1) {
        connect(ui->idLineEdit, SIGNAL(textChanged(QString)), this, SLOT(modify()));
        connect(ui->nameLineEdit, SIGNAL(textChanged(QString)), this, SLOT(modify()));
        connect(ui->blSpinBox, SIGNAL(valueChanged(int)), this, SLOT(modify()));
        connect(ui->opComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(modify()));

        connect(ui->rsSpinBox, SIGNAL(valueChanged(int)), this, SLOT(modify()));
        connect(ui->ktSpinBox, SIGNAL(valueChanged(int)), this, SLOT(modify()));
        connect(ui->rtSpinBox, SIGNAL(valueChanged(int)), this, SLOT(modify()));
        connect(ui->itSpinBox, SIGNAL(valueChanged(int)), this, SLOT(modify()));

        connect(ui->radioButtonDefault, SIGNAL(clicked(bool)), this, SLOT(updateOp(bool)));
    }
    subDirChanged(tr( "Nucleic Acid" ));
}


