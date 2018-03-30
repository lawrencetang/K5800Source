#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDir>
#include <QSize>
#include <QUrl>
#include <QFile>
#include <QTimer>
#include <QDebug>
#include <QSpinBox>
#include <QPrinter>
#include <QProcess>
#include <QTextEdit>
#include <QLineEdit>
#include <QSettings>
#include <QDateTime>
#include <QMessageBox>
#include <QFileDialog>
#include <QPrintDialog>
#include <QElapsedTimer>
#include <QDesktopServices>
#include <QPropertyAnimation>
#include <qwt_plot_renderer.h>
#include <QParallelAnimationGroup>
#include <QSequentialAnimationGroup>

#include "windows.h"
#include "singleapplication.h"
#include "Logger/Logger.h"
#include "ToolsView/toolsview.h"
#include "PlotView/plotview.h"
#include "DataView/dataview.h"
#include "RecordView/recordview.h"
#include "FittingView/fittingview.h"
#include "CameraView/cameraview.h"
#include "OligoCalculator/oligocalculator.h"
#include "SettingsView/settingview.h"
#include "TempControlView/tempcontrolview.h"
#include "CheckView/checkview.h"
#include "Controller/controller.h"
#include "DataModel/settingdatamodel.h"
#include "DataModel/absodatamodel.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow) {
    ui->setupUi(this);

    m_heightCoef = 0.28;//ltg:0.33
    m_isBlank = false;
    m_isMerge = false;
    m_isMeasure = false;
    m_pTimer = new QTimer( this );

    initializeSystem();
    initializeWidget();
    initializeAction();

    showDirAndRecordView();//lt:展示数据视图和记录视图
}

MainWindow::~MainWindow() {
    delete ui;
    if (m_pLogger != NULL) {
        delete m_pLogger;
        m_pLogger = NULL;
    }

    if (m_pCameraView != NULL) {
        delete m_pCameraView;
        m_pCameraView = NULL;
    }
}

/**
 * @brief MainWindow::openDevice
 * @return
 */
QString MainWindow::openDevice() {

    QString errorStr = "Success";
    if (!m_pController->openSpectrograph()) {
        return tr( "Spectrograph open error!" );
    }

    waitting( 100 );
    QString serialNumber = m_pController->getSerialNumber();
    if (m_serialNumber != serialNumber) {
        m_pController->closeSpectrograph();
        return tr( "Spectrograph number error!" );
    }

    if (!m_pController->openSerialPort()) {
        return tr( "SerialPort is busy or not exist!" );
    }
    return errorStr;
}

/**
 * @brief MainWindow::ReceiveMessageFromOtherInstance
 * @param message
 */
void MainWindow::ReceiveMessageFromOtherInstance(QStringList /*message*/) {
    ((SingleApplication *)qApp)->BringWindowToTop(this->winId());//lt:获取MainWindow窗口的id
}

/**
 * @brief MainWindow::focusChanged
 * @param o
 * @param n
 */
void MainWindow::focusChanged(QWidget *o, QWidget *n) {
    if (n != NULL) {
        if (n != m_focusWidget) {
            m_focusWidget = n;
            if (m_focusWidget->objectName().contains( "LineEdit" )) {
                QLineEdit *lineEdit = (QLineEdit *)n;
                if (lineEdit->isReadOnly()) {
                    return;
                }
                QDesktopServices::openUrl(QUrl("osk.exe", QUrl::TolerantMode));

            } else if (m_focusWidget->objectName().contains( "SpinBox" )) {
                QSpinBox *spinBox = (QSpinBox *)n;
                if (spinBox->isReadOnly()) {
                    return;
                }
                QDesktopServices::openUrl(QUrl("osk.exe", QUrl::TolerantMode));
            } else if (m_focusWidget->objectName().contains( "TextEdit" )) {
                QTextEdit *textEdit = (QTextEdit *)n;
                if (textEdit->isReadOnly()) {
                    return;
                }
                QDesktopServices::openUrl(QUrl("osk.exe", QUrl::TolerantMode));
            }
        }
    }
}//ltg?

/**
 * @brief MainWindow::showOption 显示选项
 * @param id 1=显示数据视图, 2=显示记录视图, 3=显示计算器视图, 4=显示相机视图, 5=导出图片, 6=打印图片
 * @param ok true=显示, false=不显示
 */
void MainWindow::showOption(int id, bool ok) {


    switch(id) {
    case 1:
        m_isShowDataView = ok;
        updateView();//lt:缺省值为0
        break;
    case 2:
        m_isShowRecordView = ok;
        updateView();
        break;
    case 3:
        m_isShowMainView = !ok;
        m_isOligoCalculator = ok;
        ui->actionCt->setEnabled( !ok );//lt:温控动作失效
        ui->actionDc->setEnabled( !ok );//lt:设备检测
        ui->actionSt->setEnabled( !ok );//lt:设置动作失效
        ui->actionBk->setEnabled( !ok );//lt:空白动作失效
        ui->actionMs->setEnabled( !ok );//lt:检测动作失效
        updateView();
        break;//lt:选择计算器和摄像工具时
    case 4:
        m_isShowMainView = !ok;
        m_isCameraView = ok;
        ui->actionCt->setEnabled( !ok );
        ui->actionDc->setEnabled( !ok );
        ui->actionSt->setEnabled( !ok );
        ui->actionBk->setEnabled( !ok );
        ui->actionMs->setEnabled( !ok );
        updateView();
        break;
    case 5:
        printsPage();
        m_waitStatus = false;
        break;
    case 6:
        exportPage();
        m_waitStatus = false;
        break;
    case 7:
        QDesktopServices::openUrl( QUrl::fromLocalFile( QFileInfo( m_document ).absoluteFilePath() ) );
        m_waitStatus = false;
        break;
    case 8:
        m_isMerge = ok;
        m_waitStatus = false;
        break;//lt:曲线合并
    default:
        break;
    }
}

/**
 * @brief MainWindow::switchPage 切换页面 //lt:slot函数
 */
void MainWindow::switchPage()  {

    QAction *sender = static_cast<QAction *>(this->sender());//lt:得到调用该槽函数的信号指针
    if (m_pSelectedView == sender) {
        return;//lt:如果发送信号行为是当前对象则返回
    }

    if (m_waitStatus) {
        //QMessageBox::warning( this, tr( "Warning" ), tr( "Please waiting!" ), QMessageBox::Ok );
        return;
    }

    if (m_pDataView != NULL) {
        if (!m_isShowMainView) {
            QMessageBox::warning( this, tr( "Warning" ), tr( "Can not switch page!" ), QMessageBox::Ok );
            return;
        }//lt:如果主示界面不是当前界面则警告（设置界面或计算页面或相机界面时）
        m_pDataView->setCurrentDir( sender->text() );//lt:如果dataview对象存在，则更改dataview控件的内容,通过切换dataview控件调用下面的换页函数
    } else {
        switchPage( sender->text() );//获得发送信号的名称切换页面
    }

}

/**
 * @brief MainWindow::switchPage 切换页面 //lt:槽函数，dataview切换时,通过发送dirchanged信号调用该函数
 * @param text 页面标题
 */
void MainWindow::switchPage(QString text) {

    if (m_waitStatus) {
        //QMessageBox::warning( this, tr( "Warning" ), tr( "Please waiting!" ), QMessageBox::Ok );
        return;
    }
    if (sender() == m_pCheckView) {
        m_pDataView->setCurrentDir( text );
    }//lt:无效？
    if (m_pSelectedView != NULL) {
        if (m_pSelectedView->text() == text) {
            return;
        }//lt:改变m_pSelectedView的值
    }

    int dh = 0;
    if (!ui->statusbar->isHidden()) {
        dh = ui->statusbar->height();
        showCheckView( false );
        ui->actionDc->setEnabled( true );
        if (m_pTempCtrlView != NULL) {
            m_pTempCtrlView->setVisible( false );
        }//lt:温控栏没有隐藏时,dh=状态栏高度值
    }

    m_isFittingView = false;
    QString flagStr;
    if (text == tr( "Nucleic Acid" )) {
        flagStr = "Nucleic Acid";
        m_pSelectedView = ui->actionNa;
    } else if (text == tr(  "Protein" )) {
        flagStr = "Protein";
        m_pSelectedView = ui->actionPt;
    } else if (text == tr( "Cell Culture" )) {
        flagStr = "Cell Culture";
        m_pSelectedView = ui->actionCc;
    } else if (text == tr( "UV-VIS" )) {
        flagStr = "UV-VIS";
        m_pSelectedView = ui->actionUv;
    } else if (text == tr( "Kit Method" )) {
        flagStr = "Kit Method";
        m_isFittingView = true;
        m_pSelectedView = ui->actionKm;
    } else if (text == tr( "Micro Array" )) {
        flagStr = "Micro Array";
        m_pSelectedView = ui->actionMa;
    } else if (text == tr( "Dynamics" )) {
        flagStr = "Dynamics";
        m_pSelectedView = ui->actionDy;
    } else if (text == tr( "Device Check" )) {
        flagStr = "Device Check";
        // 隐藏DataView和RecordView以及ToolView
        m_isShowDataView = false;
        m_pToolsView->hideDirView();
        m_isShowRecordView = false;
        m_pToolsView->hideRecordView();
        m_pToolsView->hideDialog();

        m_pSelectedView = ui->actionDc;
        showCheckView( true );//lt:设备检测信号隐藏上述页面，并设置toolbar上其他行为的状态
    } else {
        return;
    }//lt:设置toolbar上各行为状态

    m_pPlotView->setType( flagStr );
    updatePlotView( flagStr );
    if (NULL != m_pRecordView) {
        m_pRecordView->setRecordDir( text );//lt:设置加载记录文件
    }

    if(NULL != m_pSettingView) {
        m_pSettingView->clear();
    }

    if (NULL != m_pFittingView) {
        m_pFittingView->clear();
    }
    updateRect( dh );//lt:缺省值=0，更新各视图qrect
    m_waitStatus = true;
    startSwitchPage( dh );
    waitting();

    if (text != tr( "Device Check" )) {
        showDirAndRecordView();
    }
}

/**
 * @brief MainWindow::exportPage
 */
void MainWindow::exportPage() {

    QDesktopServices::openUrl(QUrl("osk.exe", QUrl::TolerantMode));
    QString filename = QDateTime::currentDateTime().toString("yyyy-MM-dd hh.mm.ss") + ".png";
    QString filepath = QDir::currentPath() + "/Picture/";//lt:模态对话框名称save picture
    QString fileName = QFileDialog::getSaveFileName(this, "Save Picture",
                                                    filepath + filename, "Png File (*.png)");//lt:保存图片
    if (fileName.isEmpty()) {
        return;
    }
    QwtPlotRenderer renderer;
    renderer.renderDocument( m_pPlotView, fileName, QSizeF( 300, 200 ) );//lt:提供画布到文件
    if (m_pCameraView != NULL) {
        m_pCameraView->upDateImage( fileName );
    }
}

/**
 * @brief MainWindow::printsPage
 */
void MainWindow::printsPage() {
    QPrinter printer( QPrinter::HighResolution );

    QString docName = m_pPlotView->title().text();
    if ( !docName.isEmpty() ) {
        docName.replace ( QRegExp ( QString::fromLatin1 ( "\n" ) ), tr ( " -- " ) );
        printer.setDocName ( docName );
    }

    printer.setCreator( "Bode example" );
    printer.setOrientation( QPrinter::Landscape );

    QPrintDialog dialog( &printer, this );
    if ( dialog.exec() ) {
        QwtPlotRenderer renderer;
        if ( printer.colorMode() == QPrinter::GrayScale ) {
            renderer.setDiscardFlag( QwtPlotRenderer::DiscardBackground );
            renderer.setDiscardFlag( QwtPlotRenderer::DiscardCanvasBackground );
            renderer.setDiscardFlag( QwtPlotRenderer::DiscardCanvasFrame );
            renderer.setLayoutFlag( QwtPlotRenderer::FrameWithScales );
        }
        renderer.renderTo( m_pPlotView, printer );
    } else {
        QMessageBox::warning( this, tr( "Warning" ),
                              tr( "Do not support print!" ), QMessageBox::Ok );
        return;
    }
}

/**
 * @brief MainWindow::setHeightCeof 设置记录窗口的高度系数
 * @param ceof 高度系数
 */
void MainWindow::setHeightCeof(double ceof) {

    // 如果在拟合窗口, 则设置拟合窗口的隐藏和显示.
    if (m_pSelectedView == ui->actionKm) {
        // 抬高记录窗口时隐藏拟合窗口,
        // 降低记录窗口时显示拟合窗口.
        if (m_heightCoef < ceof) {
            m_isFittingView = false;
        } else {
            m_isFittingView = true;
        }
    }
    m_heightCoef = ceof;
    m_waitStatus = true;
    updateView();
    waitting();
}//lt:只有在recordview视图点击上移或下移按钮后才会发出信号调用该函数，上移后系数是0.66，下移后系数是0.33

/**
 * @brief MainWindow::animationFinished 动画结束后删除动画对象
 */
void MainWindow::animationFinished() {
    m_waitStatus = false;
}

/**
 * @brief MainWindow::fileRead 读取文件
 * @param type 窗体类型
 * @param filename 文件名称
 */
void MainWindow::fileRead(QString type, QString filename) {
    QFile file( filename );//lt:第一个参数是comboBox的项目值，第二个参数是每个项目下文件名称
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::warning(this, tr("Warnning"),
                             tr("Open file error!"), QMessageBox::Ok);
        return;
    }//lt:在dataview视图中选择文件双击后发送信号调用该函数

    QString headerStr;
    QString recordStr;

    QVector<double> x;
    QVector<double> y;
    QVector<int> c;
    QVector<QString> fitmeasuredata;


    QStringList textList;
    QTextStream in(&file);
    in.setCodec("GB2312");
    if (!m_isMerge) {
        clearPlotView();
    }//lt:没有选择曲线合并时，清空画布
    while(!in.atEnd()) {
        QString text = in.readLine();//lt:读文本的一行，并把它作为一个字符串返回,没有到文档的最后就一行一行的读
        //qDebug() << text;
        textList = text.split( ",", QString::SkipEmptyParts );//lt:读一行后根据逗号把qstring分为qstringlist
        if (textList.isEmpty()) {
            continue;
        }
        if ("header:" == textList.first()) {
            headerStr = text.replace( "header:,", "" );//lt:替换掉header,把其余的字符存入headerstr
        } else if ("record:" == textList.first()) {
            recordStr = text.replace( "record:,", "" );//lt:替换掉record,把其余字符存入recordstr
            //QMessageBox::warning(0, "warning", recordStr, QMessageBox::Ok );//ltj
        } else if ("data:" == textList.first()) {
            QString xStr;
            QString yStr;
            if (type == tr( "Dynamics" )) {
                xStr = textList.at( 1 );//lt:data行内的第一个数
                QList<double> yValues;
                for (int i = 2; i < textList.size(); i ++) {
                    yStr = textList.at( i );//lt:data行内的第二个数及以后的数,动力学才有两个数以上
                    if (yStr == "NULL") {
                        continue;
                    }
                    yValues.append( yStr.toDouble() );
                }//lt:将数据保存在yValues组中
                if (!yValues.isEmpty()) {
                    if (0 == m_pPlotView->dynamicCurveSize()) {
                        m_pPlotView->addDynamicsCurve( yValues.size() );
                    }
                    m_pPlotView->drawDynamicsCurve( xStr.toDouble(), yValues );
                }
            } else {
                xStr = textList.at( 1 );
                yStr = textList.at( 2 );
                x.append( xStr.toDouble() );
                y.append( yStr.toDouble() );
                if (type == tr( "Kit Method" )) {
                    QString cStr = textList.at( 3 );//lt:只有试剂盒有第三个数
                    c.append( cStr.toInt() );
                }
            }//lt:不是动力学的时候x是data行的第一个数，y是data行的第二个数
        }
        else {
            fitmeasuredata.append( text );

        }//ltj:读拟合测量数据
    }
    file.close();

    m_pRecordView->insertRecord( recordStr );
    if (type == tr( "Kit Method" )) {
        m_pFittingView->import( headerStr, recordStr, x, y, c, fitmeasuredata );
    } else {
        // 绘制曲线
        if (type != tr( "Dynamics" )) {
            QStringList recordList = recordStr.split( ",", QString::SkipEmptyParts );
            if (recordList.isEmpty()) {
                return;
            }
            //QString title = recordList.at( 1 ) + recordList.at( 0 ) + "_" + recordList.at(3) + "\n" + recordList.at( 2 );
            QString title = "";
            if( m_pSelectedView == ui->actionPt) {
                title = " " + QString::number( recordList.at(2).toDouble(), 'f', 2) + " ";
            }
            else if( m_pSelectedView == ui->actionNa) {
                title = " " + QString::number( recordList.at(2).toDouble(), 'f', 1) + " ";
            }
            else if( m_pSelectedView == ui->actionUv) {
                title = " " + QString::number( recordList.at(4).toDouble(), 'f', 3) + " ";
            }
            else {
                title = "  OK  ";
            }
            //ltj:plotview的marker浓度保留位数
            m_pPlotView->drawStaticCurve( title, x, y );
        }
    }
}

/**
 * @brief MainWindow::showSetingViwe
 */
void MainWindow::showSetingViwe() {
    if (!m_isSettingView) {
        if (m_waitStatus) {
            //QMessageBox::warning( this, tr( "Warning" ), tr( "Please waiting!" ), QMessageBox::Ok );
            return;
        }
        //QDesktopServices::openUrl(QUrl("osk.exe", QUrl::TolerantMode)); //lt:m_issettingview初始化false
        m_pToolsView->hideDialog();
        // 隐藏temperatureView
        if (ui->actionCt->isChecked()) {
            ui->actionCt->setChecked( false );
            m_pTempCtrlView->hide();
            ui->statusbar->hide();
            m_pTempCtrlView->stopTemperature();
            m_waitStatus = true;
            updateView( ui->statusbar->height() );
            waitting();
        }//lt:温控打开隐藏温控

        m_isSettingView = true;
        m_isShowMainView = false;
        ui->actionCt->setEnabled( false );
        ui->actionDc->setEnabled( false );
        ui->actionTl->setEnabled( false );
        ui->actionBk->setEnabled( false );
        ui->actionMs->setEnabled( false );
        m_waitStatus = true;
        updateView();
        waitting();
        showSetingDialog();//ltj
    }
}

/**
 * lt:直接展示设置对话框
 */
void MainWindow::showSetingDialog() {
    m_pSettingView->directShowDialog();
}

/**
 * @brief MainWindow::hideSetingView
 */
void MainWindow::hideSetingView(int status) {

    if (m_isSettingView) {

        if (status == 1) {
            if (m_isBlank) {
                if (m_pSettingView->isNeedBlank()) {
                    m_isBlank = false;
                }
                clearPlotView();
            }
        }

        m_isSettingView = false;
        m_isShowMainView = true;

        ui->actionCt->setEnabled( true );
        ui->actionDc->setEnabled( true );
        ui->actionTl->setEnabled( true );
        ui->actionBk->setEnabled( true );
        ui->actionMs->setEnabled( true );
        m_waitStatus = true;
        updateView();
        waitting();
    }
}

/**
 * @brief MainWindow::showTempView
 * @param ok
 */
void MainWindow::showTempView(bool ok) {

    if (m_waitStatus) {
        //QMessageBox::warning( this, tr( "Warning" ), tr( "Please waiting!" ), QMessageBox::Ok );
        if (ok) {
            ui->actionCt->setChecked( false );
        }
        return;
    }

    if (m_pSelectedView == ui->actionDc ) {
        return;
    }

    QAction *sender = static_cast<QAction *>(this->sender());
    ui->statusbar->setVisible( ok );
    if (ok) {

        if (sender == ui->actionCt) {
            ui->actionDc->setEnabled( false );
            m_pTempCtrlView->show();
        }

        m_waitStatus = true;
        updateView();
        waitting();
    } else {

        if (sender == ui->actionCt) {
            ui->actionDc->setEnabled( true );
            m_pTempCtrlView->hide();
            m_pTempCtrlView->stopTemperature();
        }

        m_waitStatus = true;
        updateView(ui->statusbar->height());
        waitting();
    }
}

/**
 * @brief MainWindow::shutDown 关闭退出软件并关机
 */
void MainWindow::shutDown() {
    if (QMessageBox::Yes == QMessageBox::warning( this, tr( "Warning" ),
                                                  tr( "Are you sure to shut down system?" ),
                                                  QMessageBox::Yes|QMessageBox::No ) ) {
        m_pController->shutdownMainBoard();//ltj0206
        bool ok = shutDownSystem();
        if (!ok) {
            QMessageBox::warning( this, tr( "Warning" ),
                                  tr( "System Error, Please restart your device!" ), QMessageBox::Ok );
        }
        //m_pController->shutdownMainBoard();//test
    }
}

/**
 * @brief MainWindow::excuteBlank 执行Blank
 */
void MainWindow::excuteBlank() {

    if (m_waitStatus) {
        QMessageBox::warning( this, tr( "Warning" ), tr( "Please waiting!" ), QMessageBox::Ok );
        return;
    }

    // 加载设置内容
    QList<SettingDataModel *> settingDataModels = m_pSettingView->dataModelList();//lt:加载设置模型，单通道只有一个
    if (settingDataModels.isEmpty()) {
        QMessageBox::warning( this, tr( "Warning" ),
                              tr( "Please setting first!" ), QMessageBox::Ok);
        return;
    }

    if (m_pLogger != NULL) {
        QString text;
        if (!m_pSelectedView) {
            text = m_pSelectedView->text();
        }
        m_pLogger->outputMessage( "o", QString( "Start Blank(%1)" ).arg( text ) );
    }

    // 切换到普通视图
    if (m_pSelectedView == ui->actionKm ||
            m_pSelectedView == ui->actionDy) {
        updatePlotView( "Blank" );
    }

    m_pController->setSettingModel( settingDataModels );//lt:将吸光度数据模型指针赋给设置模型
    QString type = m_pSettingView->selectedType();//lt:选择微量还是比色皿

    // 锁定ui,禁止温控系统
    isUnLockUI( false );
    m_pTempCtrlView->pauseRead( true );
    clearPlotView();
    // 进行Blank
    QString errStr = m_pController->startBlank( type );
    // 释放ui,回复温控系统
    if (m_pSelectedView != ui->actionDc) {
        isUnLockUI( true );
    }
    m_pTempCtrlView->pauseRead( false );
    // 判断Blank是否成功
    if (errStr != "Success") {
        QMessageBox::warning( this, tr( "Warning" ),
                              errStr, QMessageBox::Ok );
        if (m_pLogger != NULL) {
            m_pLogger->outputMessage( "o", QString( "Blank ErrorCode(%1)=%2" ).arg( m_pSelectedView->text() ).arg( errStr ) );
        }
        return;
    }
    m_isBlank = true;
    if (m_pLogger != NULL) {
        m_pLogger->outputMessage( "o", QString( "Blank Success(%1)" ).arg( m_pSelectedView->text() ) );
    }
}

/**
 * @brief MainWindow::excuteMeasure 执行测量
 */
void MainWindow::excuteMeasure() {

    if (m_waitStatus) {
        QMessageBox::warning( this, tr( "Warning" ), tr( "Please waiting!" ), QMessageBox::Ok );
        return;
    }

    if (!m_isBlank) {
        QMessageBox::warning( this, tr( "Warning" ),
                              tr( "Please blank first!" ), QMessageBox::Ok );
        return;
    }

    if (m_pLogger != NULL) {
        m_pLogger->outputMessage( "o", QString( "Start Measure(%1)" ).arg( m_pSelectedView->text() ) );
    }

    if (m_pSelectedView == ui->actionKm) {
        updatePlotView( "Blank" );
    }

    m_isMeasure = true;
    // 锁定ui,禁止温控系统0000000
    isUnLockUI( false );
    m_pTempCtrlView->pauseRead( true );
    if (!m_isMerge) {
        clearPlotView();
    }
    // 动力学预处理
    if (m_pSelectedView == ui->actionDy) {

        SettingDataModel *model = m_pController->getSettingDataModel( 0 );
        if (NULL == model) {
            QMessageBox::warning( this, tr( "Warning" ),
                                  tr( "Model is empty!" ), QMessageBox::Ok );
            m_isMeasure = false;
            return;
        }
        // 切换到动力学检测的视图
        updatePlotView( "Dynamics" );

        int curveCount = 0;
        QStringList watchList = model->watchLabels();
        int size = watchList.size();
        for (int i = 0; i < size; i ++) {
            if (watchList.at( i ) != "NULL") {
                curveCount ++;
            }
        }
        m_pPlotView->addDynamicsCurve( curveCount );
    }
    // 进行measure
    QString type = m_pSettingView->selectedType();//lt:选择微量或者比色皿
    QString errStr = m_pController->startMeasure( type );
    // 释放ui,回复温控系统
    if (m_pSelectedView != ui->actionDc) {
        isUnLockUI( true );
    }
    m_pTempCtrlView->pauseRead( false );
    if (errStr != "Success") {
        QMessageBox::warning( this, tr( "Warning" ),
                              errStr, QMessageBox::Ok );
        if (m_pLogger != NULL) {
            m_pLogger->outputMessage( "o", QString( "Measure ErrorCode(%1)=%2" ).arg( m_pSelectedView->text() ).arg( errStr ) );
        }
        m_isMeasure = false;
        return;
    }
    if (m_pLogger != NULL) {
        m_pLogger->outputMessage( "o", QString( "Measure Success(%1)" ).arg( m_pSelectedView->text() ) );
    }
    m_isMeasure = false;
}

/**
 * @brief MainWindow::excuteAutoMeasure
 */
void MainWindow::excuteAutoMeasure(bool ok) {
    if (ok) {
        if (m_pSelectedView == ui->actionDc) {
            return;
        }

        if (!m_pSettingView->isAutoMeasure()) {
            return;
        }

        if (!m_isMeasure) {
            m_pTimer->singleShot( 500, this, SLOT( excuteMeasure() ));
        }
    }
}

/**
 * @brief MainWindow::measureFinish
 * @param id
 */
void MainWindow::measureFinish(int id) {

    SettingDataModel *sDataModel = m_pController->getSettingDataModel( id );
    QString measureTypeStr = sDataModel->baseValue( "measure" );
    if (measureTypeStr == "Kit Method") {
        m_pFittingView->insert( id, sDataModel );
    } else {
        QString rcdStr;
        QString filename;
        QStringList values;
        sDataModel->result( filename, rcdStr, values );//lt:将record和data等数据导入
        if (measureTypeStr == "Dynamics") {
            rcdStr.append( "," );
            rcdStr.append( QString::number( m_pController->dyTrainTimes() ) );
            filename = QString( "%1.csv" ).arg( QDateTime::currentDateTime().toString( "yyyyMMddhhmmss" ) );
            rcdStr.append( "," );
            rcdStr.append( filename );//lt:以年月日建立data文件名

            values.append( "record:," + rcdStr );
            values.append( m_pController->dyWatchStrList() );
        }
        // 3.添加记录及保存
        m_pRecordView->insertRecord( rcdStr );//lt:写表写record文件

        QString headerStr = "header:,";
        headerStr.append( m_pRecordView->headerLabels() );//lt:从表头读header
        values.insert( 0, headerStr );//lt:将表头数据插入value数据最前面
        //QMessageBox::warning(0, "warning", headerStr, QMessageBox::Ok);//ltj
        // 保存数据
        m_pDataView->saveDataFile( filename, values );//lt:将data文件的数据保存到相关路径的data文件
    }
}

/**
 * @brief MainWindow::clearPlotView 清空曲线视图
 */
void MainWindow::clearPlotView() {
    if (NULL != m_pPlotView) {
        m_pPlotView->clearPointMarker();
        m_pPlotView->clearCurves();
    }
}

/**
 * @brief MainWindow::isUnLockUI 当进行检测相关操作时,首先需要锁定UI,直到操作完成后在解锁
 * @param ok true-解锁, false-锁定
 */
void MainWindow::isUnLockUI(bool ok) {
    // 界面转换窗口8个按键
    ui->actionNa->setEnabled( ok );
    ui->actionPt->setEnabled( ok );
    ui->actionUv->setEnabled( ok );
    ui->actionMa->setEnabled( ok );
    ui->actionKm->setEnabled( ok );
    ui->actionDc->setEnabled( ok );
    bool cuvetteEnable = m_pSettingView->cuvetteEnable();
    if (cuvetteEnable) {
        ui->actionDy->setEnabled( ok );
        ui->actionCc->setEnabled( ok );
    }


    if (m_pSelectedView != ui->actionDc) {
        ui->actionCt->setEnabled( ok );
        ui->actionSt->setEnabled( ok );

        ui->actionBk->setEnabled( ok );
        ui->actionMs->setEnabled( ok );
        ui->actionTl->setEnabled( ok );

        ui->actionSh->setEnabled( ok );
    }
}

/**
 * @brief MainWindow::isUnNeedCheck 当打开设备失败时,直接切到Device Check视图
 * @param ok true-找到设备后回复所有操作, false-未找到设备切换界面
 */
void MainWindow::isUnNeedCheck(bool ok) {

    // 不在主界面先切换到主界面
    if (!m_isShowMainView && !ok) {
        m_isShowMainView = !ok;
        if (m_isSettingView) {
            m_pSettingView->hideDialogs();
        }
        m_isCameraView = ok;
        m_isSettingView = ok;
        m_isOligoCalculator = ok;

        m_waitStatus = true;
        updateView();
        waitting();
    }

    // 隐藏temperatureView
    if (m_pSelectedView != ui->actionDc &&
            ui->statusbar->isVisible() && !ok) {
        ui->actionCt->setChecked( ok );
        ui->actionDc->setEnabled( !ok );
        m_pTempCtrlView->hide();
        ui->statusbar->hide();
        m_pTempCtrlView->stopTemperature();
        m_waitStatus = true;
        updateView( ui->statusbar->height() );
        waitting();
    }

    ui->actionNa->setEnabled( ok );
    ui->actionPt->setEnabled( ok );
    ui->actionKm->setEnabled( ok );
    ui->actionMa->setEnabled( ok );
    ui->actionUv->setEnabled( ok );

    bool cuvetteEnable = m_pSettingView->cuvetteEnable();
    if (cuvetteEnable) {
        ui->actionDy->setEnabled( ok );
        ui->actionCc->setEnabled( ok );
    }

    if (!ok) {
        ui->actionDc->setEnabled( !ok );
        if (m_pDataView != NULL) {
            m_pDataView->setCurrentDir( tr( "Device Check" ) );
        }
        //switchPage( tr( "Device Check" ) );
    }
}

/**
 * @brief MainWindow::showEvent 窗体初始化
 */
void MainWindow::showEvent(QShowEvent *event) {
    if (m_isShowMainView) {
        QPoint tvTopLeft = rect().center() - m_pToolsView->rect().center();
        m_pToolsView->move( tvTopLeft );

        updateRect();
        m_pDataView->setGeometry( m_leftViewRect );
        m_pFittingView->setGeometry( m_rightViewRect );
        m_pPlotView->setGeometry( m_mainViewRect );
        m_pRecordView->setGeometry( m_buttomViewRect );

        if (NULL != m_pCameraView) {
            m_pCameraView->setGeometry( m_ToolViewRect );
        }
        m_pOligoCalc->setGeometry( m_ToolViewRect );
        m_pSettingView->setGeometry( m_ToolViewRect );//lt:更新完毕设置各个widget的尺寸
    }
}//lt:重载事件ltg

/**
 * @brief MainWindow::closeEvent
 * @param event
 */
void MainWindow::closeEvent(QCloseEvent *event) {
    if (m_pLogger != NULL) {
        delete m_pLogger;
        m_pLogger = NULL;
    }

    if (m_pCameraView != NULL) {
        delete m_pCameraView;
        m_pCameraView = NULL;
    }
    QMainWindow::closeEvent( event );
}

/**
 * @brief MainWindow::showDirAndRecordView
 */
void MainWindow::showDirAndRecordView() {
    if (!m_isShowDataView) {
        m_waitStatus = true;
        showOption( 1, true );//lt:展示dataview
        waitting();
        m_pToolsView->showDirView();//lt:toolview中data图标按钮被选中
    }

    if (!m_isShowRecordView) {
        m_waitStatus = true;
        showOption( 2, true );//lt:展示recordview
        waitting();
        m_pToolsView->showRecordView();//lt:toolview中record图标按钮被选中
    }
}

/**
 * @brief MainWindow::waitting
 */
void MainWindow::waitting() {
    QElapsedTimer t;
    t.start();
    while(m_waitStatus) {
        if (t.elapsed() > 10000) {
            m_waitStatus = false;
        }
        QCoreApplication::processEvents();
    }
}

/**
 * @brief MainWindow::waitting
 * @param timeout
 */
void MainWindow::waitting(int timeout) {
    QElapsedTimer t;
    t.start();
    while(t.elapsed() < timeout) {
        QCoreApplication::processEvents();
    }
}

/**
 * @brief MainWindow::showCheckView
 * @param ok
 */
void MainWindow::showCheckView(bool ok) {

    ui->actionTl->setEnabled( !ok );
    ui->actionCt->setEnabled( !ok );
    ui->actionSt->setEnabled( !ok );
    ui->actionBk->setEnabled( !ok );
    ui->actionMs->setEnabled( !ok );

    ui->actionCt->setChecked( ok );
    ui->statusbar->setVisible( ok );
    m_pCheckView->setVisible( ok );
}

/**
 * @brief MainWindow::shutDownSystem 关机函数
 * @return 是否成功
 */
bool MainWindow::shutDownSystem() {
    HANDLE hToken;
    TOKEN_PRIVILEGES tkp;

    if (!OpenProcessToken(GetCurrentProcess(),
                          TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, &hToken)) {
        return false;
    }

    LookupPrivilegeValue( NULL, SE_SHUTDOWN_NAME, &tkp.Privileges[0].Luid );
    tkp.PrivilegeCount = 1;
    tkp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;

    AdjustTokenPrivileges( hToken, false, &tkp, 0, (PTOKEN_PRIVILEGES)NULL, 0 );
    if (GetLastError() != ERROR_SUCCESS) {
        return false;
    }

    if (!ExitWindowsEx( EWX_SHUTDOWN | EWX_FORCE, 0 )) {
        return false;
    }

    return true;
}

/**
 * @brief MainWindow::startSwitchPage 开始切换页面
 */
void MainWindow::startSwitchPage(int dh) {
    if (!m_isShowMainView) {
        return;
    }
    clearPlotView();//lt:清除画布

    m_isBlank = false;
    QRect rect = centralWidget()->geometry();
    rect.setHeight( rect.height() + dh );//lt:+=dh状态栏高度

    int x = 0, y = 0, w = 0, h = 0;
    x = m_leftViewRect.topRight().x();
    y = m_leftViewRect.topRight().y();
    QRect hideRect = QRect( x, y, w, h );
    QPropertyAnimation *hideAni = getShowViewAni( m_pPlotView, m_pPlotView->geometry(), hideRect );//lt:缩放画布

    int rw = 0;
    if (m_isFittingView && m_isShowMainView) {
        rw = rect.width()*0.22;
    }//lt:拟合界面宽度
    int margin = 10;
    // 初始化主视图
    x = m_leftViewRect.topRight().x() + margin;
    y = m_leftViewRect.topRight().y() + margin;
    if (m_isFittingView) {
        w = rect.width() - m_leftViewRect.width() - rw - 2*margin;
    }
    else {
        w = rect.width() - m_leftViewRect.width() - rw - 2*margin - 0;//lt:md-170
    }
    h = rect.height() - m_buttomViewRect.height()- 2*margin;
    QRect showRect = QRect( x, y, w, h );
    QPropertyAnimation *showAni = getShowViewAni( m_pPlotView, hideRect, showRect );//lt:放大画布

    // 初始化右视图
    x = showRect.topRight().x();
    y = showRect.topRight().y();
    w = rw;
    h = showRect.height();
    m_rightViewRect = QRect( x, y, w, h );
    QPropertyAnimation *showRightAni = getShowViewAni( m_pFittingView, m_pFittingView->geometry(), m_rightViewRect );//lt:初始rw=0

    QPropertyAnimation *aLeft = getShowViewAni(m_pDataView, m_pDataView->geometry(), m_leftViewRect);
    QPropertyAnimation *aButtom = getShowViewAni(m_pRecordView, m_pRecordView->geometry(), m_buttomViewRect);

    QParallelAnimationGroup *aGroup = new QParallelAnimationGroup();
    aGroup->addAnimation(showRightAni);
    aGroup->addAnimation(showAni);
    aGroup->addAnimation(aLeft);
    aGroup->addAnimation(aButtom);

    QSequentialAnimationGroup *animationGroup = new QSequentialAnimationGroup();
    animationGroup->addAnimation(hideAni);
    animationGroup->addAnimation(aGroup);
    animationGroup->start();

    connect(animationGroup , SIGNAL(finished()), this, SLOT(animationFinished()) );
}

/**
 * @brief MainWindow::updateView 更新视图
 */
void MainWindow::updateView(int dh) {
    updateRect( dh );
    QPropertyAnimation *aLeft = getShowViewAni(m_pDataView, m_pDataView->geometry(), m_leftViewRect);
    QPropertyAnimation *aRight = getShowViewAni(m_pFittingView, m_pFittingView->geometry(), m_rightViewRect);
    QPropertyAnimation *aMain = getShowViewAni(m_pPlotView, m_pPlotView->geometry(), m_mainViewRect);
    QPropertyAnimation *aButtom = getShowViewAni(m_pRecordView, m_pRecordView->geometry(), m_buttomViewRect);

    int x = m_ToolViewRect.topLeft().x();
    int y = m_ToolViewRect.topLeft().y();
    int w = 0;
    int h = 0;
    QPropertyAnimation *aCamera = NULL;
    if (NULL != m_pCameraView) {
        if (m_isCameraView) {
            aCamera = getShowViewAni(m_pCameraView, m_pCameraView->geometry(), m_ToolViewRect);
        } else {
            aCamera = getShowViewAni(m_pCameraView, m_pCameraView->geometry(), QRect( x, y, w, h ));
        }
    }//lt:相机界面动画,打开相机界面由左上角变大，关闭相机界面缩回左上角

    QPropertyAnimation *aOligoCalc = NULL;
    if (m_isOligoCalculator) {
        aOligoCalc = getShowViewAni(m_pOligoCalc, m_pOligoCalc->geometry(), m_ToolViewRect);
    } else {
        aOligoCalc = getShowViewAni(m_pOligoCalc, m_pOligoCalc->geometry(), QRect( x, y, w, h ));
    }//lt:计算界面动画

    QPropertyAnimation *aSetingView = NULL;
    if (m_isSettingView) {
        aSetingView = getShowViewAni(m_pSettingView, m_pSettingView->geometry(), m_ToolViewRect);
    } else {
        aSetingView = getShowViewAni(m_pSettingView, m_pSettingView->geometry(), QRect( x, y, w, h ));
    }//lt:设置界面动画

    QParallelAnimationGroup *animationGroup = new QParallelAnimationGroup();
    animationGroup->addAnimation(aLeft);
    animationGroup->addAnimation(aRight);
    animationGroup->addAnimation(aMain);
    animationGroup->addAnimation(aButtom);//lt:4个组件的动画同时进行
    if (NULL != aCamera) {
        animationGroup->addAnimation(aCamera);
    }
    animationGroup->addAnimation(aOligoCalc);
    animationGroup->addAnimation(aSetingView);
    animationGroup->start();

    connect(animationGroup , SIGNAL(finished()), this, SLOT(animationFinished()) );//lt:动画未完给m_waitStatus标志
}

/**
 * @brief MainWindow::updateRect 更新视图的大小
 */
void MainWindow::updateRect(int dh) {

    int margin = 10;
    int x = 0, y = 0, w = 0, h = 0;
    QRect rect = centralWidget()->geometry();//lt:返回主窗口中心组件设置几何尺寸
    //QMessageBox::warning(0, "rect", QString::number(rect.x(), 10) + "  " + QString::number(rect.y(), 10) + "  " + QString::number(rect.width(), 10) + "  " + QString::number(rect.height(),10), QMessageBox::Ok);
    rect.setHeight( rect.height() + dh );//lt:中心组件的高度+dh的高度设置为新的中心组件高度

    x = rect.topLeft().x() + margin;
    y = rect.topLeft().y() + margin;//lt:起始位置为中心组件+margin
    w = 0;
    h = 0;
    if (m_isCameraView ||
            m_isOligoCalculator || m_isSettingView) {
        w = rect.width() - 2*margin;
        h = rect.height() - 2*margin;
    }//lt:缺省为false
    m_ToolViewRect = QRect( x, y, w, h );//lt:相机，计算器，设置界面不打开时宽高为0，打开了宽高为中心组件-2margin

    // 初始化左视图
    x = rect.topLeft().x();
    y = rect.topLeft().y();
    w = 0;
    h = rect.height();
    if (m_isShowDataView && m_isShowMainView) {
        w = rect.width()*0.22;
    }
    m_leftViewRect = QRect( x, y, w, h );

    // 初始化底视图
    x = m_leftViewRect.bottomRight().x();
    y = m_leftViewRect.bottomRight().y();
    w = rect.width() - m_leftViewRect.width();
    h = 0;
    if (m_isShowRecordView && m_isShowMainView) {
        h = rect.height()*m_heightCoef;//lt:底视图的高度有几种情况,变化较大
        y -= h;
    }
    m_buttomViewRect = QRect( x, y, w, h );

    int rw = 0;
    if (m_isFittingView && m_isShowMainView) {
        rw = rect.width()*0.22;
    }
    // 初始化主视图
    x = m_leftViewRect.topRight().x() + margin;
    y = m_leftViewRect.topRight().y() + margin;
    w = 0;
    h = 0;
    if (m_isShowMainView) {
        if (m_isFittingView) {
            w = rect.width() - m_leftViewRect.width() - rw - 2*margin;//lt:有拟合界面是主视图宽度要减去拟合界面的宽度及不减170
            h = rect.height() - m_buttomViewRect.height() - 2*margin;
        }
        else {
            w = rect.width() - m_leftViewRect.width() - rw - 2*margin - 0;//lt:md-170
            h = rect.height() - m_buttomViewRect.height() - 2*margin;
        }
    }
    m_mainViewRect = QRect( x, y, w, h );

    // 初始化右视图
    x = m_mainViewRect.topRight().x() + margin;
    y = m_mainViewRect.topRight().y() - margin;
    w = rw;
    h = m_mainViewRect.height() + 2*margin;
    m_rightViewRect = QRect( x, y, w, h );
}

/**
 * @brief MainWindow::getShowViewAni 获取显示视图动画
 * @param widget 视图窗体
 * @param start 初始值
 * @param end 终止值
 * @return 动画
 */
QPropertyAnimation *MainWindow::getShowViewAni(QWidget *widget, QRect start, QRect end) {
    QPropertyAnimation *animation = new QPropertyAnimation(widget, "geometry");
    animation->setDuration( 500 );//lt:时间
    animation->setStartValue( start );//lt:起始点和起始大小
    animation->setEndValue( end );//lt:结束点和结束大小
    return animation;
}

/**
 * @brief MainWindow::updatePlotView 设置PlotView,更具当前选择的窗口对PlotView进行初始化
 * @param text 选择窗口的名称
 */
void MainWindow::updatePlotView(QString text) {

    QString filename = QDir::currentPath() + "/configure/plot.ini";
    QSettings *configIniReader = new QSettings( filename, QSettings::IniFormat );

    QString xAxisText = configIniReader->value( QString("/%1/xAxisText").arg( text ) ).toString();
    QString yAxisText = configIniReader->value( QString("/%1/yAxisText").arg( text ) ).toString();//lt:各行为xy轴名称

    int xAxisMinVaule = configIniReader->value( QString("/%1/xAxisMinVaule").arg( text ) ).toInt();
    int xAxisMaxVaule = configIniReader->value( QString("/%1/xAxisMaxVaule").arg( text ) ).toInt();//lt:各行为x轴值

    int yAxisMinVaule = configIniReader->value( QString("/%1/yAxisMinVaule").arg( text ) ).toInt();
    int yAxisMaxVaule = configIniReader->value( QString("/%1/yAxisMaxVaule").arg( text ) ).toInt();//lt:各行为y轴值

    int scaleCount = configIniReader->value( QString("/%1/scaleCount").arg( text ) ).toInt();//lt:刻度

    if (text == "Device Check") {
        m_pPlotView->setTitle( "Device Check" );
    }
    m_pPlotView->setXAxisText( xAxisText );
    m_pPlotView->setYAxisText( yAxisText );

    m_pPlotView->uninstallPlotZoomer();
    m_pPlotView->setAxisScale( QwtPlot::xTop, xAxisMinVaule, xAxisMaxVaule );
    m_pPlotView->setAxisScale( QwtPlot::xBottom, xAxisMinVaule, xAxisMaxVaule );
    m_pPlotView->setAxisScale( QwtPlot::yLeft, yAxisMinVaule, yAxisMaxVaule );
    m_pPlotView->installPlotZoomer();
    m_pPlotView->addSacleMarker( scaleCount );//lt:在画布设置scale

    delete configIniReader;
    configIniReader = NULL;
}

/**
 * @brief changeAmText
 */
void MainWindow::changeAmText() {
   QString systemIconsPath = QDir::currentPath() + "/images/system/";
   if( m_pSettingView->isAutoMeasure() ) {
       ui->actionAm->setText(tr("AUTO"));
       ui->actionAm->setIcon(QIcon(systemIconsPath + "Auto.png"));
   }
   else {
       ui->actionAm->setText(tr("MANUAL"));
       ui->actionAm->setIcon(QIcon(systemIconsPath + "AutoState.png"));
   }
}


/**
 * @brief MainWindow::initializeSystem
 */
void MainWindow::initializeSystem() {
    QString filename = QDir::currentPath() + "/configure/system.ini";
    QSettings *configIniReader = new QSettings( filename, QSettings::IniFormat );
    configIniReader->setIniCodec( "GB2312" );

    m_temperatureEnable = configIniReader->value( "/System/Temperature Enable" ).toBool();
    m_cameraEnable = configIniReader->value( "/System/Camera Enable" ).toBool();
    QString title = configIniReader->value( "/System/Name" ).toString();
    this->setWindowTitle( title );
    m_document = QDir::currentPath() + configIniReader->value( "/System/Document" ).toString();
    m_serialNumber = configIniReader->value( "/System/Spectrograph ID" ).toString();
    m_channelNumber = configIniReader->value( "/System/Channel Number" ).toInt();

    bool loggerEnable = configIniReader->value( "/System/Logger" ).toBool();
    if (loggerEnable) {
        m_pLogger = new Logger( this );
    } else {
        m_pLogger = NULL;
    }

    delete configIniReader;
    configIniReader = NULL;
}//lt:读取System.ini系统配置文件

/**
 * @brief MainWindow::initializeWidget
 */
void MainWindow::initializeWidget() {

    m_isShowDataView = false;//lt:左视
    m_isShowRecordView = false;
    m_isShowMainView = true;//lt:主视
    m_isFittingView = false;//lt:右视

    m_isCameraView = false;
    m_isOligoCalculator = false;
    m_isSettingView = false;
    m_waitStatus = false;

    m_pPlotView = new PlotView(this);
    // 配置设置窗口
    m_pSettingView = new SettingView( this );
    connect(m_pSettingView, SIGNAL(hideView(int)), this, SLOT(hideSetingView(int)));
    connect(m_pSettingView, SIGNAL(changeTitle(QString)), m_pPlotView, SLOT(setPlotTitle(QString)));

    // 初始化数据视图
    m_pDataView = new DataView( "data", m_pSettingView->cuvetteEnable(), this );
    connect(m_pDataView, SIGNAL(dirChanged(QString)), this, SLOT(switchPage(QString)));
    connect(m_pDataView, SIGNAL(fileReadReady(QString, QString)), this, SLOT(fileRead(QString, QString)));
    connect(m_pDataView, SIGNAL(dirChanged(QString)), m_pSettingView, SLOT(subDirChanged(QString)));

    // 初始化记录视图
    m_pRecordView = new RecordView( "record", this );
    connect(m_pRecordView, SIGNAL(moveCoef(double)), this, SLOT(setHeightCeof(double)));//lt:根据recordview界面上下移按钮确定传递参数
    connect(m_pRecordView, SIGNAL(clearid()), m_pSettingView, SLOT(clearid()));//ltj
    connect(m_pRecordView, SIGNAL(sampleLEchange(QString)), m_pSettingView, SLOT(changeId(QString)));//ltj


    // 初始化拟合曲线视图
    m_pFittingView = new FittingView( this );
    m_pFittingView->installPlotView( m_pPlotView );
    m_pFittingView->installRecordView( m_pRecordView );
    connect( m_pFittingView, SIGNAL( readySaveFile( QString, QStringList ) ),
             m_pDataView, SLOT( saveDataFile( QString, QStringList ) ) );

    // 摄像头工具
    if (m_cameraEnable) {
        m_pCameraView = new CameraView( "picture", this );
    } else {
        m_pCameraView = NULL;
        m_pSettingView->setAutoCheckIamge( m_cameraEnable );
    }
    // 计算器工具
    m_pOligoCalc = new OligoCalculator( this );

    // 初始化工具视图
    m_pToolsView = new ToolsView( this );
    m_pToolsView->setCameraEnable( m_cameraEnable );
    m_pToolsView->hide();

    // 后台控制器
    m_pController = new Controller( this );
    if (m_pLogger != NULL) {
        m_pController->installLogger( m_pLogger );
    }
    connect( m_pController, SIGNAL(staticWave(QVector<double>, QVector<double>)),
             m_pPlotView, SLOT(drawStaticCurve(QVector<double>, QVector<double>)) );
    connect( m_pController, SIGNAL(staticWave(QString, QVector<double>, QVector<double>)),
             m_pPlotView, SLOT(drawStaticCurve(QString, QVector<double>, QVector<double>)) );
    connect( m_pController, SIGNAL(dynamicsWave(double, QList<double>)),
             m_pPlotView, SLOT(drawDynamicsCurve(double,QList<double>)) );
    connect( m_pController, SIGNAL(measureOk(int)), this, SLOT(measureFinish(int)) );
    connect( m_pController, SIGNAL(toMessage(bool)), this, SLOT(excuteAutoMeasure(bool)));
    connect(m_pRecordView, SIGNAL(sendConcValue(QString)), m_pController, SLOT(getConcValue(QString)));//ltj

    m_pCheckView = new CheckView( m_pController, m_temperatureEnable );//lt:初始时m_temper从ini文件获取
    connect(m_pCheckView, SIGNAL(deviceEnable(bool)), this, SLOT(isUnNeedCheck(bool)));
    connect(m_pCheckView, SIGNAL(clearPlot()), this, SLOT(clearPlotView()));
    connect(m_pCheckView, SIGNAL(checking(bool)), this, SLOT(isUnLockUI(bool)));
    connect(m_pCheckView, SIGNAL(saveImage()), this, SLOT(exportPage()));

    if (m_temperatureEnable) {
        m_pTempCtrlView = new TempControlView( m_pController );//lt:如果配置文件中temperature enable值为true
        ui->statusbar->addWidget( m_pTempCtrlView );//lt:在status区增加tempctrlview
        m_pTempCtrlView->hide();
        connect(m_pCheckView, SIGNAL(checking(bool)), m_pTempCtrlView, SLOT(pauseRead(bool)));
    }

    ui->statusbar->addWidget( m_pCheckView );//lt:在status区增加checkview
    m_pCheckView->hide();
    ui->statusbar->hide();

    m_pSelectedView = ui->actionNa;
    m_pSelectedView = NULL;
    connect(m_pToolsView, SIGNAL(triggered(int,bool)),
            this, SLOT(showOption(int,bool))); 
    ui->toolBar->removeAction(ui->actionCt);//ltj,md
    //ui->toolBar->removeAction(ui->actionAm);//ltj,md
}

/**
 * @brief MainWindow::initializeAction
 */
void MainWindow::initializeAction() {
    QString systemIconsPath = QDir::currentPath() + "/images/system/";

    QMap<QString, QString> viewTitles = m_pDataView->getViewTitle();
    // 1
    ui->actionNa->setIcon( QIcon( systemIconsPath + "Nucleic Acid.png" ) );
    ui->actionNa->setText( tr("%1").arg( viewTitles.value( tr( "Nucleic Acid" ) ) ) );
    connect(ui->actionNa, SIGNAL(triggered(bool)), this, SLOT(switchPage()));
    m_pDataView->updateView( ui->actionNa->text() );
    updatePlotView( "Nucleic Acid" );//lt:缺省显示核酸界面

    // 2
    ui->actionPt->setIcon( QIcon( systemIconsPath + "Protein.png" ) );
    ui->actionPt->setText( tr("%1").arg( viewTitles.value( tr( "Protein" ) ) ) );
    connect(ui->actionPt, SIGNAL(triggered(bool)), this, SLOT(switchPage()));

    // 4
    ui->actionUv->setIcon( QIcon( systemIconsPath + "UV-VIS.png" ) );
    ui->actionUv->setText( tr("%1").arg( viewTitles.value( tr( "UV-VIS" ) ) ) );
    connect(ui->actionUv, SIGNAL(triggered(bool)), this, SLOT(switchPage()));
    // 5
    ui->actionMa->setIcon( QIcon( systemIconsPath + "Micro Array.png" ) );
    ui->actionMa->setText( tr("%1").arg( viewTitles.value( tr( "Micro Array" ) ) ) );
    connect(ui->actionMa, SIGNAL(triggered(bool)), this, SLOT(switchPage()));
    // 3
    ui->actionCc->setIcon( QIcon( systemIconsPath + "Cell Culture.png" ) );
    // 6
    ui->actionDy->setIcon( QIcon( systemIconsPath + "Dynamics.png" ) );
    // 7
    ui->actionKm->setIcon(QIcon(systemIconsPath + "Kit Method.png"));
    bool cuvetteEnable = m_pSettingView->cuvetteEnable();
    if (cuvetteEnable && m_channelNumber == 1) {
        ui->actionCc->setText( tr("%1").arg( viewTitles.value( tr( "Cell Culture" ) ) ) );
        ui->actionDy->setText( tr("%1").arg( viewTitles.value( tr( "Dynamics" ) ) ) );
        ui->actionKm->setText( tr("%1").arg( viewTitles.value( tr( "Kit Method" ) ) ) );
        connect(ui->actionCc, SIGNAL(triggered(bool)), this, SLOT(switchPage()));
        connect(ui->actionDy, SIGNAL(triggered(bool)), this, SLOT(switchPage()));
        connect(ui->actionKm, SIGNAL(triggered(bool)), this, SLOT(switchPage()));
    } else {
        ui->actionCc->setVisible( false );
        ui->actionKm->setVisible( false );
        ui->actionDy->setVisible( false );
        ui->toolBar->setIconSize(QSize (105,80));//lt:控制有无比色皿时的图标大小
    }
    ui->actionCc->setEnabled( cuvetteEnable );
    ui->actionDy->setEnabled( cuvetteEnable );
    ui->actionKm->setEnabled( cuvetteEnable );

    // 8
    ui->actionDc->setIcon(QIcon(systemIconsPath + "Device Check.png"));
    connect(ui->actionDc, SIGNAL(triggered(bool)), this, SLOT(switchPage()));

    ui->actionTl->setIcon(QIcon(systemIconsPath + "Tools.png"));
    connect(ui->actionTl, SIGNAL(triggered()), m_pToolsView, SLOT(showDialog()));

    ui->actionCt->setIcon(QIcon(systemIconsPath + "Temperture.png"));
    connect(ui->actionCt, SIGNAL(triggered(bool)), this, SLOT(showTempView(bool)));
    ui->actionCt->setEnabled( m_temperatureEnable );

    ui->actionSt->setIcon(QIcon(systemIconsPath + "Settings.png"));
    connect(ui->actionSt, SIGNAL(triggered()), this, SLOT(showSetingViwe()));

    ui->actionAm->setIcon(QIcon(systemIconsPath + "Auto.png"));//ltj md
    connect(ui->actionAm, SIGNAL(triggered(bool)), m_pSettingView, SLOT(changeAutoMeasure()));//ltj md
    connect(ui->actionAm, SIGNAL(triggered(bool)), this, SLOT(changeAmText()));//ltj md

    ui->actionBk->setIcon(QIcon(systemIconsPath + "Blank.png"));
    connect(ui->actionBk, SIGNAL(triggered(bool)), this, SLOT(excuteBlank()));

    ui->actionMs->setIcon(QIcon(systemIconsPath + "Measure.png"));
    connect(ui->actionMs, SIGNAL(triggered(bool)), this, SLOT(excuteMeasure()));

    ui->actionSh->setIcon(QIcon(systemIconsPath + "Shut.png"));
    connect(ui->actionSh, SIGNAL(triggered(bool)), this, SLOT(shutDown()));
}
