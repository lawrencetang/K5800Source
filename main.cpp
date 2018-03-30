#include "mainwindow.h"
#include <QDir>
#include <QDate>
#include <QFile>
#include <QDebug>
#include <QProcess>
#include <QSettings>
#include <QTranslator>
#include <QMessageBox>
#include <QApplication>
#include <QElapsedTimer>
#include <QSplashScreen>
#include <QDesktopWidget>
#include <QCoreApplication>//ltj

#include "accredit/accredit.h"
#include "singleapplication.h"

void startup(QMainWindow *window);
void installStyle();
bool checkLicense();
bool CheckAccredit(QString fileName);
int main(int argc, char *argv[]) {

    //QApplication a(argc, argv);
    SingleApplication a ( argc, argv, "uniquekey:ole88888888");
    if (a.alreadyExists()) {
        a.sendMessage("allready running!");
        return 0;
    }

    // 获取当前屏幕的分辨率
    QDesktopWidget *desktopWidget = QApplication::desktop();
    // 加载启动画面
    QPixmap startImage(QDir::currentPath() + "/images/startup/startup.png");
    startImage = startImage.scaled( desktopWidget->size() );//lt:将图片大小设置为计算出的屏幕的宽高

    // 显示启动画面
    QSplashScreen splash(startImage);
    splash.resize(startImage.size());
    splash.setDisabled(true);
    splash.show();
    QString fileName = QDir::currentPath() + "/configure/system.ini";
    QSettings *configIniReader = new QSettings( fileName, QSettings::IniFormat );
    QString languageStr = configIniReader->value( "/System/Language" ).toString();
    if (languageStr == "cn") {
        QTranslator *pTranslator = new QTranslator();
        bool ok = pTranslator->load( QDir::currentPath() + "/language/cn.qm" );
        if (ok) {
            //QMessageBox::warning(0, "warning", "translator is ok", QMessageBox::Ok);//ltj
            //QMessageBox::warning(0, "warning", QCoreApplication::applicationDirPath(), QMessageBox::Ok);//ltj
            a.installTranslator( pTranslator );
        }
    }//lt:移动1

    splash.setFont(QFont("黑体", 32, QFont::Bold));
    splash.showMessage(QObject::tr("Initializing system..."),
                       Qt::AlignLeft|Qt::AlignBottom, Qt::white);//lt:1

    MainWindow *w = new MainWindow();
    splash.showMessage(QObject::tr("Initializing Views..."),
                       Qt::AlignLeft|Qt::AlignBottom, Qt::white);//lt:2

//lt:移动1
    bool isFullScreen = configIniReader->value( "/System/Full Screen" ).toBool();
    delete configIniReader;
    configIniReader = NULL;

    fileName = QString( "%1/%2" ).arg( QDir::currentPath() ).arg( "license/license.key" );
    bool ok = CheckAccredit( fileName );
    if (!ok) {
        QMessageBox::warning(0, "Warning", "License illegitmacy!", QMessageBox::Ok);
        return -1;
    }

    splash.showMessage(QObject::tr("Loading devices..."),
                       Qt::AlignLeft|Qt::AlignBottom, Qt::white);//lt:3

    QString errorStr = w->openDevice();
    if ("Success" != errorStr) {
        QMessageBox::warning(0, QObject::tr( "Warnning" ), errorStr, QMessageBox::Ok);
        w->isUnNeedCheck( false );
    }

    splash.finish( w );
    if (isFullScreen) {
        w->showFullScreen();
    } else {
        w->resize( 1280, 800 );
        w->show();
    }//lt:定界面尺寸

    QObject::connect(&a, SIGNAL(focusChanged(QWidget*, QWidget*)), w, SLOT(focusChanged(QWidget*, QWidget*)));
    QObject::connect(&a, SIGNAL(messageAvailable(QStringList)), w, SLOT(ReceiveMessageFromOtherInstance(QStringList)));

    return a.exec();
}

/**
 * @brief waitting
 * @param timeout
 */
void waitting(int timeout) {
    QElapsedTimer t;
    t.start();
    while(t.elapsed() < timeout) {
        QCoreApplication::processEvents();
    }
}

/**
 * @brief startup
 * @param window
 */
void startup(QMainWindow *window) {
    // 获取当前屏幕的分辨率
    QDesktopWidget *desktopWidget = QApplication::desktop();
    // 加载启动画面
    QPixmap startImage(QDir::currentPath() + "/images/startup/startup.png");
    startImage = startImage.scaled( desktopWidget->size() );

    // 显示启动画面
    QSplashScreen splash(startImage);
    splash.resize(startImage.size());
    splash.setDisabled(true);
    splash.show();

    // 显示情动信息
    splash.setFont(QFont("黑体", 32, QFont::Bold));
    splash.showMessage(QObject::tr("Initializing system..."),
                       Qt::AlignLeft|Qt::AlignBottom, Qt::white);
    waitting( 1000 );
    splash.showMessage(QObject::tr("Initializing Views..."),
                       Qt::AlignLeft|Qt::AlignBottom, Qt::white);
    splash.showMessage(QObject::tr("Loading devices..."),
                       Qt::AlignLeft|Qt::AlignBottom, Qt::white);
    waitting( 1000 );
    splash.finish( window );
}

/**
 * @brief installStyle
 */
void installStyle() {

    QFile file(QDir::currentPath() + "/style/style.qss");
    if ( file.open( QIODevice::ReadOnly ) ) {
        QTextStream in(&file);
        in.setCodec( "GB2312" );
        QString style = in.readAll();
        qApp->setStyleSheet( style );
    }

    file.close();
}//lt:加载静态样式文件

/**
 * @brief checkLicense
 * @return
 */
bool checkLicense() {

    QString filename = QString( "%1/%2" ).arg( QDir::currentPath() ).arg( "license/license" );
    QFile file( filename );
    if(!file.open( QIODevice::ReadOnly )) {
        QMessageBox::warning(0, QObject::tr( "Warning" ), QObject::tr( "License lose!" ), QMessageBox::Ok);
        return false;
    }

    QDate issueDate;
    QDate uptoDate;
    while(!file.atEnd()){
        QByteArray license = file.readLine().replace( "\r\n", "" );
        if (!license.startsWith( "?!" ) && !license.startsWith( "#@" ) &&
                !license.endsWith( "$#" ) && !license.endsWith( "&!" )) {
            QMessageBox::warning(0, QObject::tr( "Warning" ), QObject::tr( "Illegal authorization!" ), QMessageBox::Ok);
            return false;
        }

        license = license.replace( "?!", "" );
        license = license.replace( "$#", "" );
        license = license.replace( "#@", "" );
        license = license.replace( "&!", "" );
        QString bufferStr = QString::fromLocal8Bit( QByteArray::fromBase64( license ) );
        QStringList bufferList = bufferStr.split( ":", QString::SkipEmptyParts );
        if (bufferStr.contains( "issue date" )) {
            issueDate = QDate::fromString( bufferList.last(), "yyyy-MM-dd" );
        }
        if (bufferStr.contains( "up to date" )) {
            uptoDate = QDate::fromString( bufferList.last(), "yyyy-MM-dd" );
        }
    }
    file.close();
    QDate currentDate = QDate::currentDate();
    if (currentDate < issueDate && currentDate > uptoDate) {
        QMessageBox::warning(0, QObject::tr( "Warning" ), QObject::tr( "License expire!" ), QMessageBox::Ok);
        return false;
    }

    QString issueDateStr = QString( "issue date:%1" ).arg( currentDate.toString( "yyyy-MM-dd" ) );
    QString upToDateStr = QString( "up to date:%1" ).arg( uptoDate.toString( "yyyy-MM-dd" ) );
    QByteArray issueDateArray = "?!" + issueDateStr.toLocal8Bit().toBase64() + "$#";
    QByteArray upToDateArray = "#@" + upToDateStr.toLocal8Bit().toBase64() + "&!";

    QFile fileOut( filename );
    if (!fileOut.open(QIODevice::WriteOnly|QIODevice::Truncate)) {
        return false;
    }
    fileOut.write( issueDateArray );
    fileOut.write( "\r\n" );
    fileOut.write( upToDateArray );
    fileOut.close();

    return true;
}

///////////////////////////////////////////////////////////////////////
// 授权相关内容
///////////////////////////////////////////////////////////////////////
#define COMPANY_KAIAO               "KaiAo"
#define SOFTNAME_OPTICSCALIBRATION  "BioFuture"
#define ACCREDIT_KEY                "key-ole-abcdefgh"
#define ACCREDIT_REGISTER_FOLDER    "selder4526133943"
#define ACCREDIT_REGISTER_TOTAL     "to"

QByteArray ReadRegisterInfo(QString folder, QString item)
{
    QSettings settings("HKEY_CURRENT_USER\\Software", QSettings::NativeFormat);
    return settings.value(folder + "/" + item).toByteArray();
}

void WriteRegisterInfo(QString folder, QString item, QByteArray byteArray)
{
    QSettings settings("HKEY_CURRENT_USER\\Software", QSettings::NativeFormat);
    settings.setValue(folder + "/" + item, byteArray);
}

void WriteRegisterInfo(QString folder, QString item, const char *content, const int len)
{
    QByteArray byteArray;
    byteArray.clear();
    byteArray.append(content, len);
    WriteRegisterInfo(folder, item, byteArray);
}

bool CheckAccredit(QString fileName)
{
    // 是否从授权文件更新信息到注册表，默认需要更新
    // 不更新的条件：注册的授权版本是最新的，或授权文件无效
    bool bUpdateAccredInfo = true;
    // 是否更新注册表中的启动时间，默认需要更新
    // 不更新的条件：注册表的授权信息无效，且不能从授权文件中更新授权信息
    bool bWriteUpdateTime = true;
    // 授权验证是否通过，默认不通过
    // 通过条件：授权信息有效，或授权信息无效但从授权文件中更新了授权信息
    bool bRegisterValid = false;

    // 判断该授权文件的有效性
    int nAccreditLevel;
    QString strCompany;
    QString strSoftName;
    int nAccreditVersion;
    QDateTime startDate;
    QDateTime endDate;
    QDateTime updateDate;
    int nAccreditFileValid = Accredit::IsAccredited(ACCREDIT_KEY, fileName,
                                                    &nAccreditLevel, strCompany, strSoftName, &nAccreditVersion,
                                                    startDate, endDate, updateDate);//lt:ACCREDIT_KEY=key-ole-abcdefgh,返回-3,-2,-1,0,1,2,3值表示不同含义
    // 授权文件无效，不影响授权有效性判断

    // 如果授权文件中的公司名、软件名和本软件不一致，置授权文件无效
    if (nAccreditFileValid == 0) {
        if ((strCompany != COMPANY_KAIAO) || (strSoftName != SOFTNAME_OPTICSCALIBRATION)) {
            qDebug() << "Accredit file erro: Company or SoftName Info Error";
            nAccreditFileValid = -1;
        }
    }//lt:不存在文件返回-1直接读取注册表内信息
    qDebug() << "Accredit File Info " << ((nAccreditFileValid == 0) ? "Valid" : "Invalid");

    // 读取注册表中的授权信息
    int nAccreditLevelR;
    QString strCompanyR;
    QString strSoftNameR;
    int nAccreditVersionR;
    QDateTime startDateR;
    QDateTime endDateR;
    QDateTime updateDateR;

    QByteArray byteArray = ReadRegisterInfo(ACCREDIT_REGISTER_FOLDER, ACCREDIT_REGISTER_TOTAL);
    int nAccreditRegisterValid = Accredit::IsAccredited(ACCREDIT_KEY, byteArray,
                                                        &nAccreditLevelR, strCompanyR, strSoftNameR, &nAccreditVersionR,
                                                        startDateR, endDateR, updateDateR);//lt:返回-3,-2,-1,0,1,2,3表示不同含义
#if 1
    QString strInfo;
    strInfo = QString("AccreditLevel:%1\r\nCompany:%2\r\nSoftName:%3\r\nAccreditVersion:%4\r\nStartDate:%5\r\nEndDate:%6\r\nUpdateDate:%7").
            arg(nAccreditLevelR, 0, 16).arg(strCompanyR).arg(strSoftNameR).arg(nAccreditVersionR).
            arg(startDateR.toString(TIME_FORMAT)).arg(endDateR.toString(TIME_FORMAT)).arg(updateDateR.toString(TIME_FORMAT));
    qDebug() << "Accredit Register Info = " << strInfo;
#endif

    if (nAccreditRegisterValid < 0) {
        // 如果授权信息无效，不能更新启动时间，如果后续从授权文件中更新了授权信息，则需要更新启动时间
        bWriteUpdateTime = false;
        qDebug() << "Accredit Register Invalid";
    } else {
#if 1
        if (nAccreditRegisterValid == 0) {
            bRegisterValid = true;
            qDebug() << "Accredit Register Valid";
        } else {
            qDebug() << "Accredit Register Lose-Efficacy";
        }
#endif
        // 如果注册表中的公司名或软件名有误，更新授权信息
        if ((strCompanyR != COMPANY_KAIAO) || (strSoftNameR != SOFTNAME_OPTICSCALIBRATION)) {
            qDebug() << "Accredit Register: Company or SoftName Info Error";
            bRegisterValid = false;
        }
        // 如果授权文件的版本 <= 注册表的版本，不更新授权信息
        if (nAccreditVersion <= nAccreditVersionR) {
            qDebug() << "Accredit Info is now newest";
            bUpdateAccredInfo = false;
        }//lt:如果授权文件的加密授权版本高于注册表中的加密授权版本则则写注册表
    }

    // 如果需要更新注册表，并且授权文件有效，则更新注册表中的所有信息
    if (bUpdateAccredInfo && (nAccreditFileValid == 0)) {
        char content[1024];//lt:bUpdateAccredInfo初始化为true，如果有新版本的授权（值比上一次大）文件且文件有效,没有授权文件则不写注册表
        // 考虑到content中可能存在'\0'字符，不直接使用QString(char *)
        int retLen = Accredit::Accredited(ACCREDIT_KEY, nAccreditLevel,
                                          strCompany, strSoftName, nAccreditVersion,
                                          startDate, endDate, updateDate,
                                          content, 1024);
        WriteRegisterInfo(ACCREDIT_REGISTER_FOLDER, ACCREDIT_REGISTER_TOTAL, content, retLen);
        // 把授权文件更新到注册表后，更新变量
        bWriteUpdateTime = true;//lt:开始是注册表内的时间不符
        bRegisterValid = true;

#if 1
        qDebug() << "Update Accred Info from File to Register";
        QString strInfo;
        strInfo = QString("AccreditLevel:%1\r\nCompany:%2\r\nSoftName:%3\r\nAccreditVersion:%4\r\nStartDate:%5\r\nEndDate:%6\r\nUpdateDate:%7").
                arg(nAccreditLevel, 0, 16).arg(strCompany).arg(strSoftName).arg(nAccreditVersion).
                arg(startDate.toString(TIME_FORMAT)).arg(endDate.toString(TIME_FORMAT)).arg(updateDate.toString(TIME_FORMAT));
        qDebug() << "Accredit File Info = " << strInfo;
#endif
    }

    // 更新启动时间：更新时间 = max(上次启动时间, 当前时间)
    // 无论是注册表有效，或者失效，都更新启动时间
    // 如果用户的时间到了有效期外，再修改回有效期，也不能使用 //lt:每次启动把当前时间写入更新时间写入注册表
    qDebug() << "bWriteUpdateTime = " << bWriteUpdateTime;
    if (bWriteUpdateTime) {
        byteArray = ReadRegisterInfo(ACCREDIT_REGISTER_FOLDER, ACCREDIT_REGISTER_TOTAL);//lt:新授权文件写了注册表后还是要再读一次
        nAccreditRegisterValid = Accredit::IsAccredited(ACCREDIT_KEY, byteArray,
                                                            &nAccreditLevelR, strCompanyR, strSoftNameR, &nAccreditVersionR,
                                                            startDateR, endDateR, updateDateR);
        QDateTime currentDateTime = QDateTime::currentDateTime();//lt:bWriteUpdateTime初始化为true
        qDebug() << "register last update date = " << updateDateR.toString(TIME_FORMAT);
        if (currentDateTime.operator >(updateDateR)) {
            char content[1024];//lt:当前时间大于上次启动时间,新授权文件写注册表后当前时间=更新时间
            memset(content, 0, 1024);
            int retLen = Accredit::Accredited(ACCREDIT_KEY,
                                              nAccreditLevelR, strCompanyR, strSoftNameR, nAccreditVersionR,
                                              startDateR, endDateR, QDateTime::currentDateTime(),
                                              content, 1024);//lt:如果当前时间大于更新时间则把当前时间写回注册表当作更新时间
            WriteRegisterInfo(ACCREDIT_REGISTER_FOLDER, ACCREDIT_REGISTER_TOTAL, content, retLen);

#if 1
            qDebug() << "Write update to Register ";
            QString strInfo;
            strInfo = QString("AccreditLevel:%1\r\nCompany:%2\r\nSoftName:%3\r\nAccreditVersion:%4\r\nStartDate:%5\r\nEndDate:%6\r\nUpdateDate:%7").
                    arg(nAccreditLevelR, 0, 16).arg(strCompanyR).arg(strSoftNameR).arg(nAccreditVersionR).
                    arg(startDateR.toString(TIME_FORMAT)).arg(endDateR.toString(TIME_FORMAT)).arg(QDateTime::currentDateTime().toString(TIME_FORMAT));
            qDebug() << "Accredit Register Info = " << strInfo;
#endif
        } else {
            qDebug() << "Last Update date > currentDate, do not write update time";
        }
    }
    return bRegisterValid;
}



