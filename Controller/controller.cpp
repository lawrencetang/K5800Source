#include "controller.h"

#include <QDir>
#include <QDebug>
#include <QSettings>
#include <QElapsedTimer>
#include <QSerialPortInfo>
#include <QCoreApplication>

#include "datalayer.h"
#include "../Logger/Logger.h"
#include "../Spectrograph/spectrograph.h"
#include "../DataModel/absodatamodel.h"
#include "../DataModel/blankdatamodel.h"
#include "../DataModel/specdatamodel.h"
#include "../DataModel/opticaldatamodel.h"
#include "../DataModel/settingdatamodel.h"//lt:改了头文件的路径

#define TEMPERATURE_CONTROLER_ID 0x01  // 温控设备编号
#define DC_MOTOR_ID              0x01  // 直流电机编号
#define STEP_MOTOR_OPTICAL_ID    0x01  // 控制光程的电机编号
#define STEP_MOTOR_CHANNEL_ID    0x02  // 控制光路的电机编号
#define MAIN_BOARD_ID            0x01  // 主板设备编号

#define MIN_OPTICAL_PATH         0x00  // 最小光程
#define MAX_OPTICAL_PATH         0x01  // 最大光程

Controller::Controller(QObject *parent)
    : QObject(parent) {

    m_pSerialPort = NULL;
    m_pSpectrograph = NULL;

    initializeSystem();
    initializeDevice();
}

Controller::~Controller() {
    // 关闭串口设备
    if (NULL != m_pSerialPort) {
        if (m_pSerialPort->isOpen()) {
            m_pSerialPort->close();
        }

        delete m_pSerialPort;
        m_pSerialPort = NULL;
    }
    // 关闭光谱设备
    if (NULL != m_pSpectrograph) {
        if (m_pSpectrograph->isOpened()) {
            m_pSpectrograph->close();
        }

        delete m_pSpectrograph;
        m_pSpectrograph = NULL;
    }

    if (NULL != m_pDataLayer) {
        delete m_pDataLayer;
        m_pDataLayer = NULL;
    }
}

/**
 * @brief Controller::installLogger
 * @param logger
 */
void Controller::installLogger(Logger *logger) {
    if (NULL != m_pDataLayer) {
        m_pDataLayer->installLogger( logger );
    }
}

/**
 * @brief Controller::getSerialNumber
 * @return
 */
QString Controller::getSerialNumber() {
    if (m_pSpectrograph != NULL) {
        if (m_pSpectrograph->isOpened()) {
            return m_pSpectrograph->serialNumber();
        }
    }
    return "";
}

/**
 * @brief Controller::setSettingModel 装在设置数据模型
 * @param sDataList 设置数据模型的List表格
 */
void Controller::setSettingModel(QList<SettingDataModel *> sDataList) {
    m_sDataList.clear();
    m_sDataList.append( sDataList );//lt:单通道为.size()为1

    int size = m_aDataList.size();//lt:size为1
    for (int i = 0; i < m_sDataList.size(); i ++) {
        SettingDataModel *sDataMoedel = m_sDataList.at( i );//lt:提取出传递进来的第一个设置模型
        if (i < size) {
            sDataMoedel->setAbsoModel( m_aDataList.at( i ) );//lt:将吸光度数据模型指针赋给设置模型
        } else {
            sDataMoedel->setAbsoModel( NULL );
        }
    }
}

/**
 * @brief Controller::startMicroscaleCheck 开始检测
 * @return 是否成功
 */
QString Controller::startMicroscaleCheck(int id) {
    if (!m_pSerialPort->isOpen() ||
            !m_pSpectrograph->isOpened()) {
        return tr( "Device is not open!" );
    }

    // 复位通道
    /*for (int i = 0; i < m_msMaxNumber; i ++) {
        QString errStr = prepareOpticalChannel( i );
        if (errStr != "Success") {
            return errStr;
        }
        errStr = excuteCheck( "Microscale", m_pOpticalDataModel->msStdOp() );
        if (errStr != "Success") {
            return errStr;
        }
        errStr = excuteCheck( "Microscale", m_pOpticalDataModel->msMaxOp() );
        if (errStr != "Success") {
            return errStr;
        }
        errStr = excuteCheck( "Microscale", m_pOpticalDataModel->msMinOp() );
        if (errStr != "Success") {
            return errStr;
        }
    }*/
    QString errStr = prepareOpticalChannel( id );//lt:启动步进电机
    if (errStr != "Success") {
        return errStr;
    }
    errStr = excuteCheck( "Microscale", m_pOpticalDataModel->msStdOp() );
    if (errStr != "Success") {
        return errStr;
    }
    errStr = excuteCheck( "Microscale", m_pOpticalDataModel->msMaxOp() );
    if (errStr != "Success") {
        return errStr;
    }
    errStr = excuteCheck( "Microscale", m_pOpticalDataModel->msMinOp() );
    if (errStr != "Success") {
        return errStr;
    }

    errStr = prepareOpticalChannel( 0 );
    if (errStr != "Success") {
        return errStr;
    }

    // 电机复位
    errStr = prepareOpticalPath( m_pOpticalDataModel->msStdOp() );
    if (errStr != "Success") {
        return errStr;
    }

    return "Success";
}

/**
 * @brief Controller::startCuttveCheck
 * @return
 */
QString Controller::startCuvetteCheck() {
    if (!m_pSerialPort->isOpen() ||
            !m_pSpectrograph->isOpened()) {
        return tr( "Device is not open!" );
    }

    QString errStr = excuteCheck( "Cuvette", m_pOpticalDataModel->ctOp() );
    return errStr;
}

/**
 * @brief Controller::checkMainBoard 检测主板是否正常
 * @return 是否成功
 */
QString Controller::checkMainBoard() {
    if (!m_pSerialPort->isOpen()) {
        return tr( "Device is not open!" );
    }
    bool ok = m_pDataLayer->mainboardStatus( MAIN_BOARD_ID );//lt:0x01
    if (!ok) {
        return tr( "Mainborad error!" );
    }
    return "Success";
}

/**
 * @brief Controller::shutdownMainBoard 关机函数ltj0206
 * @return 是否成功
 */
QString Controller::shutdownMainBoard() {
    if (!m_pSerialPort->isOpen()) {
        return tr( "Device is not open!" );
    }
    bool ok = m_pDataLayer->shutdownboard(MAIN_BOARD_ID);//lt:0x01
    if (!ok) {
        return tr( "Mainborad error!" );
    }
    return "Success";
}

/**
 * @brief Controller::checkMicroscale
 * @return
 */
QString Controller::checkMicroscale() {
    if (!m_pSerialPort->isOpen()) {
        return tr( "Device is not open!" );
    }
    bool ok = m_pDataLayer->stepMotorStatus( STEP_MOTOR_OPTICAL_ID );
    if (!ok) {
        return tr( "Step Motor 1 error!" );
    }
    if (8 == m_msMaxNumber) {
        ok = m_pDataLayer->stepMotorStatus( STEP_MOTOR_CHANNEL_ID );
        if (!ok) {
            return tr( "Step Motor 2 error!" );
        }
    }
    return "Success";
}

/**
 * @brief Controller::checkCuvette
 * @return
 */
QString Controller::checkCuvette() {
    if (!m_pSerialPort->isOpen()) {
        return tr( "Device is not open!" );
    }
    bool ok = m_pDataLayer->dcMotorStatus( DC_MOTOR_ID );
    if (!ok) {
        return tr( "Dc Motor error!" );
    }
    return "Success";
}

/**
 * @brief Controller::checkTemperature
 * @return
 */
QString Controller::checkTemperature() {
    if (!m_pSerialPort->isOpen()) {
        return tr( "Device is not open!" );
    }
    bool ok = m_pDataLayer->temperatureCtrlStatus( TEMPERATURE_CONTROLER_ID );
    if (!ok) {
        return tr( "Temperature Controller error!" );
    }
    return "Success";
}

/**
 * @brief Controller::startBlank 开始Blank
 * @param type 是超微量还是比色皿
 * @return 是否成功
 */
QString Controller::startBlank(QString type) {

    if (!m_pSerialPort->isOpen() ||
            !m_pSpectrograph->isOpened()) {
        return tr( "Device is not open!" );
    }

    m_pBlankDataModel->clear();//lt:清楚空白模型里的光谱数据模型
    // 比色皿或超微量
    QString errStr = "Success";
    if (type == "Cuvette") {
        if (m_sDataList.isEmpty()) {
            return tr( "Please setting first!" );
        }
        errStr = cuvetteBlank();
    } else {
        // 复位通道
        errStr = prepareOpticalChannel( 0 );
        if (errStr != "Success") {
            return errStr;
        }
        errStr = microscaleBlank();

    }
    return errStr;
}

/**
 * @brief Controller::startMeasure 开始检测
 * @param type 是超微量还是比色皿
 * @return 是否成功
 */
QString Controller::startMeasure(QString type) {

    if (m_sDataList.isEmpty()) {
        return tr( "Please setting first!" );
    }
    // 校验是否可以开始检测
    if (!m_pSerialPort->isOpen() ||
            !m_pSpectrograph->isOpened()) {
        return tr( "Device is not open!" );
    }//lt:判断串口和光谱是否打开
    // 比色皿或超微量
    QString errStr = "Success";
    if (type == "Cuvette") {
        SettingDataModel *sDataModel = m_sDataList.first();//lt:单通道就是该设置数据模型
        if (sDataModel->baseValue( "measure" ) == "Dynamics") {
            errStr = dynamicsMesaure( sDataModel );
        } else {
            errStr = cuvetteMeasure( sDataModel );
        }
    } else {
        // 复位通道
        QString errStr = prepareOpticalChannel( 0 );
        if (errStr != "Success") {
            return errStr;
        }
        errStr = microscaleMeasure();
        if (errStr != "Success") {
            return errStr;
        }
        // 复位通道
        errStr = prepareOpticalChannel( 0 );
        if (errStr != "Success") {
            return errStr;
        }
    }

    return "Success";
}

/**
 * @brief Controller::checkDevice
 * @return
 */
bool Controller::checkDevice() {
    QString portName = findSerialPortName( m_spDescription );//lt:获取串口名称
    QString serialNumber = m_pSpectrograph->serialNumber();//lt:获取光谱号

    if (portName.isEmpty() || serialNumber == "Not Found" ||
            serialNumber.isEmpty()) {
        return false;
    }

    return true;
}

/**
 * @brief Controller::findSerialPortName 查找串口名称
 * @param description 设备描述
 * @return 串口名称
 */
QString Controller::findSerialPortName(QString description) {
    // 根据设备描述获取串口名称
    QString serialPortName;
    QList<QSerialPortInfo> serialPortInfos = QSerialPortInfo::availablePorts();//lt:返回可用的串口名称
    for (int i = 0; i < serialPortInfos.size(); i ++) {
        QSerialPortInfo serialPortInfo = serialPortInfos.at( i );//lt:把第i个串口信息给serialportinfo
        if (serialPortInfo.description().contains( description ) ) {
            serialPortName = serialPortInfo.portName();//lt:包含该传递的描述返回串口名称
            break;
        }
    }

    return serialPortName;
}

/**
 * @brief Controller::temperatureStart 开启温控系统
 * @param targetTemp 目标温度
 * @return 返回是否成功
 */
QString Controller::temperatureStart(int targetTemp) {
    bool ok = m_pDataLayer->temperatureCtrlStart( TEMPERATURE_CONTROLER_ID, targetTemp );
    if (!ok) {
        return m_pDataLayer->getErrorMessage();
    }
    return "Success";
}

/**
 * @brief Controller::temperatureRead 读取当前温度
 * @return 返回是否成功
 */
QString Controller::temperatureRead() {
    bool ok = m_pDataLayer->temperatureCtrlRead( TEMPERATURE_CONTROLER_ID );
    if (!ok) {
        return m_pDataLayer->getErrorMessage();
    }
    return "Success";
}

/**
 * @brief Controller::temperatureStop 停止温控系统
 * @return 是否成功
 */
QString Controller::temperatureStop() {
    bool ok = m_pDataLayer->temperatureCtrlStop( TEMPERATURE_CONTROLER_ID );
    if (!ok) {
        return m_pDataLayer->getErrorMessage();
    }
    return "Success";
}

/**
 * @brief Controller::reset 复位操作(复位光程和通道)
 * @return 是否成功
 */
QString Controller::reset() {

    // 清空残留设置参数
    m_sDataList.clear();

    // 1.电机行进到标准光程位置
    QString errStr = "Success";
    errStr = prepareOpticalPath( m_pOpticalDataModel->msStdOp() );
    if (errStr != "Success") {
        return errStr;
    }

    // 2.电机行进到第一通道位置
    if (m_msMaxNumber == 8) {
        errStr = prepareOpticalChannel( 0 );
        if (errStr != "Success") {
            return errStr;
        }
    }

    return "Success";
}

/**
 * @brief Controller::openSerialPort 打开串口
 * @return 是否成功
 */
bool Controller::openSerialPort() {

    if (NULL == m_pSerialPort) {
        return false;
    }

    if (m_pSerialPort->isOpen()) {
        m_pSerialPort->close();
    }

    if (m_spName.isEmpty()) {
        m_spName = findSerialPortName( m_spDescription );
    }

    m_pSerialPort->setPortName( m_spName );
    m_pSerialPort->setBaudRate( m_spBoundRate );
    m_pSerialPort->setDataBits( QSerialPort::Data8 );
    m_pSerialPort->setParity( QSerialPort::NoParity );
    m_pSerialPort->setStopBits( QSerialPort::OneStop );
    m_pSerialPort->setFlowControl( QSerialPort::NoFlowControl );

    if (!m_pSerialPort->open(QIODevice::ReadWrite)) {
        return false;
    }

    // 复位通道
    QString errStr = prepareOpticalChannel( 0 );
    if (errStr != "Success") {
        return false;
    }

    // 复位通道
    errStr = prepareOpticalPath( m_pOpticalDataModel->msStdOp() );
    if (errStr != "Success") {
        return false;
    }
    return true;
}

/**
 * @brief Controller::closeSerialPort 关闭串口
 */
void Controller::closeSerialPort() {
    if (NULL != m_pDataLayer) {
        if (m_pDataLayer->waitStatus()) {
            m_pDataLayer->setWaitStatus( false );
        }
    }
    if (NULL != m_pSerialPort) {
        m_pSerialPort->close();
    }
}

/**
 * @brief Controller::openSpectrograph 打开光谱设备
 */
bool Controller::openSpectrograph() {
    if (NULL == m_pSpectrograph) {
        return false;
    }
    return m_pSpectrograph->open();
}

/**
 * @brief Controller::closeSpectrograph 关闭光谱设备
 */
void Controller::closeSpectrograph() {
    if (NULL != m_pSpectrograph) {
        m_pSpectrograph->close();
    }
}

/**
 * @brief Controller::cuvetteBlank 比色皿Blank
 * @return 是否成功
 */
QString Controller::cuvetteBlank() {
    // 读取光谱数据
    SettingDataModel *sDataModel = m_sDataList.first();
    double currentOp = sDataModel->baseValue( "optical" ).toDouble();//lt:比色皿初始值为10
    readSpectrograph( "Cuvette", currentOp );

    // 获取Blank的数据
    QVector<double> x;
    QVector<double> y;
    bool ok = m_pBlankDataModel->blankData( currentOp, x, y );
    if (ok) {

        for(int i = 0; i < x.size(); i ++) {
            //qDebug() << QString::number(y.at(i));//ltj:测试光强数据
            y.replace( i, 0 );//lt:空白时y值全放为0,取消了这句可以显示出实际光强?
        }
        //QString title = QString( "Blank(%1)" ).arg( currentOp );//ltg
        QString title = "  OK  ";
        emit staticWave(title, x, y );
        return "Success";
    } else {
        return tr( "Get Blank data filed!" );
    }
}

/**
 * @brief Controller::microscaleBlank 超微量Blank
 * @return 是否成功
 */
QString Controller::microscaleBlank() {

    QString errStr = "Success";
    double currentOp = m_pOpticalDataModel->msStdOp();
    if (1 == m_msMaxNumber) {

        SettingDataModel *sDataModel = m_sDataList.first();
        bool isAuto = sDataModel->isAutoSelectOp();
        if (isAuto) {
            QString typeStr = sDataModel->baseValue( "measure" );
            if (typeStr == "UV-VIS" ||
                    typeStr == "Kit Method") {
                QString fixOpStr = m_pOpticalDataModel->msFixOp( typeStr );
                if (fixOpStr == "NULL") {
                    return tr( "Fix optical setting lose!" );
                }
                currentOp = fixOpStr.toDouble();
                // 标准光程
                errStr = excuteMicroscaleBlank( currentOp );
                if (errStr != "Success") {
                    return errStr;
                }
            } else {
                // 标准光程
                errStr = excuteMicroscaleBlank( m_pOpticalDataModel->msStdOp() );
                if (errStr != "Success") {
                    return errStr;
                }
                // 最大光程
                errStr = excuteMicroscaleBlank( m_pOpticalDataModel->msMaxOp() );
                if (errStr != "Success") {
                    return errStr;
                }
                // 最小光程
                errStr = excuteMicroscaleBlank( m_pOpticalDataModel->msMinOp() );
                if (errStr != "Success") {
                    return errStr;
                }
                // 复位光程
                errStr = prepareOpticalPath( m_pOpticalDataModel->msStdOp() );
                if (errStr != "Success") {
                    return errStr;
                }
            }
        } else {
            currentOp = sDataModel->baseValue( "optical" ).toDouble();
            // 标准光程
            errStr = excuteMicroscaleBlank( currentOp );
            if (errStr != "Success") {
                return errStr;
            }
        }
    }

    if (8 == m_msMaxNumber) {
        // 标准光程
        errStr = excuteMicroscaleBlank( m_pOpticalDataModel->msStdOp() );
        if (errStr != "Success") {
            return errStr;
        }
        // 最大光程
        errStr = excuteMicroscaleBlank( m_pOpticalDataModel->msMaxOp() );
        if (errStr != "Success") {
            return errStr;
        }
        // 最小光程
        errStr = excuteMicroscaleBlank( m_pOpticalDataModel->msMinOp() );
        if (errStr != "Success") {
            return errStr;
        }
        // 复位光程
        errStr = prepareOpticalPath( m_pOpticalDataModel->msStdOp() );
        if (errStr != "Success") {
            return errStr;
        }
    }
    return errStr;
}

/**
 * @brief Controller::cuvetteMeasure 比色皿检测
 * @return 是否成功
 */
QString Controller::cuvetteMeasure(SettingDataModel *sDataModel) {

    // 直流电机参数
    int kTime = sDataModel->dcMotorValue( "kTime" ).toInt() * 1000;
    int iTime = sDataModel->dcMotorValue( "iTime" ).toInt() * 1000;
    int rTime = sDataModel->dcMotorValue( "rTime" ).toInt() * 1000;
    int level = sDataModel->dcMotorValue( "level" ).toInt();


    // 开始搅拌
    bool ok = true;
    ok = m_pDataLayer->dcMotorStart( DC_MOTOR_ID, level );
    if (!ok) {
        return tr( "Start DC-Motor field!" );
    }
    waitting( kTime );

    // 停止搅拌
    ok = m_pDataLayer->dcMotorStop( DC_MOTOR_ID );
    if (!ok) {
        return tr( "Stop DC-Motor field!" );
    }
    waitting( rTime );

    double currentOp = sDataModel->baseValue( "optical" ).toDouble();
    int bwl = sDataModel->baseValue( "baseline" ).toInt();
    AbsoDataModel *absoDataModel = sDataModel->absoModel();
    readSpectrograph( "Cuvette", currentOp, bwl, absoDataModel );//lt:读数据到absodatamodel，（关键）

    QVector<double> x;
    QVector<double> y;
    /*
    x.append( absoDataModel->getWaveLength() );
    y.append( absoDataModel->getAbsorbance() );
    */
    x<<( absoDataModel->getWaveLength() );//lt:直接从m_odata中取数据
    y<<( absoDataModel->getAbsorbance() );//lt:直接从m_odata中取数据

    if(sDataModel->baseValue( "measure" ) == "Cell Culture" ) {
        QString filename = QDir::currentPath() + "/configure/system.ini";
        QSettings *configIniReader = new QSettings( filename, QSettings::IniFormat );
        double ccMul = configIniReader->value("/System/Cc Multiple").toDouble();
        for(int i = 0; i < y.size(); i++ ) {
            y[i] = y.at(i) * ccMul;
        }
        delete configIniReader;
        configIniReader = NULL;
    }//ltj:细胞液时读配置文件加倍数

    //QString idStr = sDataModel->baseValue( "id" );
    //QString name = sDataModel->baseValue( "name" );
    //QString idStr = "";
    //QString name = "";
    //emit staticWave( name+idStr, x, y );//ltg
    emit measureOk( 0 );//ltg
    waitting( 10 );//ltg:检测完成后先写表，再把表中的浓度数据给m_concvalue再读到plotview中
    //qDebug()<< m_concValue;
    QString title="";
    if( "Nucleic Acid" ==sDataModel->baseValue( "measure" ) || "Protein" == sDataModel->baseValue( "measure" )
            || "UV-VIS" == sDataModel->baseValue( "measure" )) {
        title = " " + m_concValue + " ";//ltj
    }
    else {
        title = "  OK  ";
    }

    emit staticWave( title, x, y );
    waitting( iTime );

    return "Success";
}

/**
 * @brief Controller::microscaleMeasure 超微量检测
 * @return 是否成功
 */
QString Controller::microscaleMeasure() {

    bool isFixed = false;
    QString errStr = prepareMicroscaleMeasure( isFixed );
    if (errStr != "Success") {
        m_sDataList.clear();
        return errStr;
    }

    // 标准光程检测
    double currentOp = m_pOpticalDataModel->msStdOp();
    errStr = excuteMicroscaleMeasure( currentOp, m_stdOpIdList );
    if (errStr != "Success") {
        m_sDataList.clear();
        return errStr;
    }

    // 最大光程检测
    currentOp = m_pOpticalDataModel->msMaxOp();
    errStr = excuteMicroscaleMeasure( currentOp, m_maxOpIdList );
    if (errStr != "Success") {
        m_sDataList.clear();
        return errStr;
    }

    // 最小光程检测
    currentOp = m_pOpticalDataModel->msMinOp();
    errStr = excuteMicroscaleMeasure( currentOp, m_minOpIdList );
    if (errStr != "Success") {
        m_sDataList.clear();
        return errStr;
    }
    // 复位通道
    errStr = prepareOpticalChannel( 0 );
    if (errStr != "Success") {
        return errStr;
    }

    // 非固定光程下复位光程
    if (!isFixed && m_msMaxNumber == 1) {
        // 复位光程
        errStr = prepareOpticalPath( m_pOpticalDataModel->msStdOp() );
        if (errStr != "Success") {
            return errStr;
        }
    }

    return "Success";
}

/**
 * @brief Controller::dynamicsMesaure 动力学检测
 * @param sDataModel 设置数据模型
 * @return 是否成功
 */
QString Controller::dynamicsMesaure(SettingDataModel *sDataModel) {

    // 停止条件
    QString stdValueStr = sDataModel->methodValue( "target" );
    int maxTimes = sDataModel->methodValue( "times" ).toInt();

    // 直流电机参数
    int kTime = sDataModel->dcMotorValue( "kTime" ).toInt() * 1000;
    int iTime = sDataModel->dcMotorValue( "iTime" ).toInt() * 1000;
    int rTime = sDataModel->dcMotorValue( "rTime" ).toInt() * 1000;
    int level = sDataModel->dcMotorValue( "level" ).toInt();

    // 获取观察值
    QString wlStr = sDataModel->methodValue( "wave" );

    int checkTmes = 0;
    double mainValue = 0.0;
    QList<double> watchValues;
    QStringList watchLabels = sDataModel->watchLabels();

    bool condition = true;
    double stdValue = 0.0;
    if (stdValueStr == "NULL") {
        condition = (checkTmes < maxTimes);
    } else {
        stdValue = stdValueStr.toDouble();
        condition = (checkTmes < maxTimes) && (mainValue < stdValue);
    }

    // 计时器
    QElapsedTimer t;
    t.start();
    m_dyWatchStrList.clear();
    while (condition) {

        checkTmes ++;
        // 开始搅拌
        bool ok = true;
        ok = m_pDataLayer->dcMotorStart( DC_MOTOR_ID, level );
        if (!ok) {
            return tr( "Start DC-Motor field!" );
        }
        waitting( kTime );

        // 停止搅拌
        ok = m_pDataLayer->dcMotorStop( DC_MOTOR_ID );
        if (!ok) {
            return tr( "Stop DC-Motor field!" );
        }
        waitting( rTime );

        // 数据检测
        double currentOp = sDataModel->baseValue( "optical" ).toDouble();
        int bwl = sDataModel->baseValue( "baseline" ).toInt();
        AbsoDataModel *absoDataModel = sDataModel->absoModel();
        absoDataModel->clear();
        readSpectrograph( "Cuvette", currentOp, bwl, absoDataModel );

        // 获取主目标值
        mainValue = absoDataModel->absorbance( wlStr ).toDouble();
        // 获取观测值
        watchValues.clear();
        double x = t.elapsed();
        QString watchStr = QString( "data:,%1," ).arg( x );
        for (int i = 0; i < watchLabels.size(); i ++) {
            QString watchLable = watchLabels.at( i );
            if ("NULL" == watchLable) {
                watchStr.append( watchLable );
            } else {
                double y = absoDataModel->absorbance( watchLable ).toDouble();
                watchValues.append( y );
                watchStr.append( QString::number( y ) );
            }
            if (i < watchLabels.size() - 1) {
                watchStr.append( "," );
            }
        }
        m_dyWatchStrList.append( watchStr );
        emit dynamicsWave( x, watchValues );

        // 更新执行条件
        if (stdValueStr == "NULL") {
            condition = (checkTmes < maxTimes);
        } else {
            stdValue = stdValueStr.toDouble();
            condition = (checkTmes < maxTimes) && (mainValue < stdValue);
        }

        // 等待时间
        waitting( iTime );
    }

    m_dyTrainTimes = checkTmes;
    emit measureOk( 0 );
    return "Success";
}

/**
 * @brief Controller::waitting 延时等待
 * @param timeout 超时时间
 */
void Controller::waitting(int timeout) {
    QElapsedTimer t;
    t.start();
    while(t.elapsed() < timeout) {
        QCoreApplication::processEvents();
    }
}

/**
 * @brief Controller::prepareMicroscaleMeasure 超微量检测测量工作的准备
 * @return 返回是否成功
 */
QString Controller::prepareMicroscaleMeasure(bool &isFixed) {

    m_maxOpIdList.clear();
    m_minOpIdList.clear();
    m_stdOpIdList.clear();

    isFixed = false;
    for (int i = 0; i < m_sDataList.size(); i ++) {

        SettingDataModel *sDataModel = m_sDataList.at( i );//lt:有几个设置模型
        // 是否为自动判断光程
        bool isAuto = sDataModel->isAutoSelectOp();
        if (!isAuto) {
            isFixed = true;//lt:不是自动判断光程
            double stdOp = m_pOpticalDataModel->msStdOp();
            double selectedOp = sDataModel->baseValue( "optical" ).toDouble();//lt:查光程的值
            setMesaureQueue( i, selectedOp, stdOp, stdOp);
        } else {
            QString typeStr = sDataModel->baseValue( "measure" );//lt:将设置中的measure的值读出
            // 全波长以及曲线拟合采用固定波长
            if (typeStr == "UV-VIS" ||
                    typeStr == "Kit Method") {

                QString fixOpStr = m_pOpticalDataModel->msFixOp( typeStr );
                if (fixOpStr == "NULL") {
                    return tr( "Fix optical setting lose!" );
                }

                double stdOp = m_pOpticalDataModel->msStdOp();
                double fixOp = fixOpStr.toDouble();
                setMesaureQueue( i, fixOp, stdOp, stdOp );
            } else {
                // 准备标准光程
                double currentOp = m_pOpticalDataModel->msStdOp();//lt:获取标准光程
                QString errStr = prepareOpticalPath( currentOp );//lt:获取对应光程电机的角度，下发命令
                if (errStr != "Success") {
                    return errStr;
                }

                // 切换通道编号
                errStr = prepareOpticalChannel( i );
                if (errStr != "Success") {
                    return errStr;
                }

                // 读取光谱仪数据
                AbsoDataModel *absoDataModel = sDataModel->absoModel();
                int bwl = sDataModel->baseValue( "baseline" ).toInt();//lt:获取设置中的baseline值
                if (absoDataModel == NULL) {
                    return tr( "Data model lose!" );
                }

                absoDataModel->clear();
                readSpectrograph( "Microscale", currentOp, bwl, absoDataModel );

                // 获取标准预判波长下的值
                QString wlStr = sDataModel->methodValue( "wave" );//lt:获取设置中的wave值
                QString coefStr = sDataModel->methodValue( "coef" );
                double aValue = 0;
                if (typeStr == "Protein") {
                    aValue = 10 * absoDataModel->absorbance( wlStr ).toDouble() / coefStr.toDouble();
                } else {
                    aValue = absoDataModel->absorbance( wlStr ).toDouble() * coefStr.toDouble();
                }

                addMesaureQueue( i, aValue, m_msUpperLimit, m_msLowerLimit );
            }
        }
    }

    return "Success";
}

/**
 * @brief Controller::addMesaureQueue 添加检测队列
 * @param id 通道id
 * @param value 判断值
 * @param upper 上限值
 * @param lower 下限值
 */
void Controller::addMesaureQueue(int id, double value,
                                 double upper, double lower) {

    SettingDataModel *sDataModel = m_sDataList.at( id );
    AbsoDataModel *absoDataModel = sDataModel->absoModel();
    if ( value > upper ) {
        m_minOpIdList.append( id );
        absoDataModel->clear();
    } else if ( value < lower) {
        m_maxOpIdList.append( id );
        absoDataModel->clear();
    } else {
        m_stdOpIdList.append( id );
        absoDataModel->clear();
    }
}

/**
 * @brief Controller::setMesaureQueue
 * @param id
 * @param value
 * @param upper
 * @param lower
 */
void Controller::setMesaureQueue(int id, double value,
                                 double upper, double lower) {
    SettingDataModel *sDataModel = m_sDataList.at( id );
    AbsoDataModel *absoDataModel = sDataModel->absoModel();
    if ( value > upper ) {
        m_maxOpIdList.append( id );
        absoDataModel->clear();
    } else if ( value < lower) {
        m_minOpIdList.append( id );
        absoDataModel->clear();
    } else {
        m_stdOpIdList.append( id );
        absoDataModel->clear();
    }
}

/**
 * @brief Controller::excuteCheck 执行检测
 * @param op 光程
 * @return 返回是否成功
 */
QString Controller::excuteCheck(QString typeStr, double op) {
    // 读取光谱数据
    double currentOp = op;
    if (typeStr == "Microscale") {
        QString errStr = prepareOpticalPath( currentOp );
        if (errStr != "Success") {
            return errStr;
        }
    }
    //waitting( 500 );

    QVector<int> intX;
    QVector<double> x;
    QVector<double> y;
    readSpectrograph( typeStr, currentOp, intX, y );
    for (int i = 0; i < intX.size(); i ++) {
        x.append( intX.at( i ) );
    }

    emit staticWave( x, y );
    return "Success";
}

/**
 * @brief Controller::excuteMicroscaleBlank 执行Blank
 * @param op 光程
 * @return 是否成功
 */
QString Controller::excuteMicroscaleBlank(double op) {

    // 读取光谱数据
    double currentOp = op;
    QString errStr = prepareOpticalPath( currentOp );
    if (errStr != "Success") {
        return errStr;
    }
    waitting( 500 );
    readSpectrograph( "Microscale", currentOp );

    // 获取Blank的数据
    QVector<double> x;
    QVector<double> y;
    bool ok = m_pBlankDataModel->blankData( currentOp, x, y );
    if (ok) {
        for (int i = 0; i < x.size(); i ++) {
            y.replace( i, 0 );
        }
        //QString title = QString( "Blank(%1)" ).arg( currentOp );//ltg:该plotmarker显示
        QString title = "  OK  ";
        emit staticWave( title, x, y );
        return "Success";
    } else {
        return tr( "Get Blank data filed!" );
    }
}

/**
 * @brief Controller::excuteMicroscaleMeasure 执行检测操作
 * @param op 光程
 * @param idList 带检测的通道的id列表
 * @return 是否成功
 */
QString Controller::excuteMicroscaleMeasure(double op, QList<int> idList) {

    if (idList.isEmpty()) {
        return "Success";
    }

    double currentOp = op;
    QString errStr = prepareOpticalPath( currentOp );
    if (errStr != "Success") {
        return errStr;
    }
    // waitting( 500 );

    QVector<double> x;
    QVector<double> y;
    int size = idList.size();
    //QString title;
    for (int i = 0; i < size; i ++) {
        // 获取通道的ID
        int id = idList.at( i );
        // 改变检测通道
        errStr = prepareOpticalChannel( id );
        if (errStr != "Success") {
            return errStr;
        }

        // 开始进行检测
        SettingDataModel *sDataModel = m_sDataList.at( id );
        int bwl = sDataModel->baseValue( "baseline" ).toInt();
        AbsoDataModel *absoDataModel = sDataModel->absoModel();
        readSpectrograph( "Microscale", currentOp, bwl, absoDataModel );

        // 获取检测波形
        x.clear();
        y.clear();
        /*
        x.append( absoDataModel->getWaveLength() );
        y.append( absoDataModel->getAbsorbance() );
        */
        x<<( absoDataModel->getWaveLength() );
        y<<( absoDataModel->getAbsorbance() );

        //QString idStr = sDataModel->baseValue( "id" );
        //QString name = sDataModel->baseValue( "name" );
        //title = QString( "%1%2(%3,%4)" ).arg( name ).arg( idStr ).arg( id + 1 ).arg( currentOp );
        emit measureOk( id );//ltg
        waitting( 10 );//ltg:检测完成后先写表，再把表中的浓度数据给m_concvalue再读到plotview中
        //qDebug()<< m_concValue;
        QString title="";
        if( "Nucleic Acid" ==sDataModel->baseValue( "measure" ) || "Protein" == sDataModel->baseValue( "measure" )
                || "UV-VIS" == sDataModel->baseValue( "measure" )) {
            title = " " + m_concValue + " ";//ltj
        }
        else {
            title = "  OK  ";
        }
        emit staticWave( title, x, y );
        //emit measureOk( id );//ltg
        //waitting( 10 );
    }

    return "Success";
}

/**
 * @brief Controller::prepareOpticalPath 准备光路(将电机移动到对应光程的位置)
 * @param op 光程
 * @return 是否成功
 */
QString Controller::prepareOpticalPath(double op) {

    double currentOp = op;
    double currentAg = 10*m_pOpticalDataModel->msAngle( currentOp );//lt:对应光程下电机角度*10
    bool ok = m_pDataLayer->stepMotorStart( STEP_MOTOR_OPTICAL_ID, currentAg );//lt:第二个参数为double
    if (!ok) {
        return tr( "Move step motor fail!" );
    }

    return "Success";
}

/**
 * @brief Controller::prepareOpticalChannel 准备通道(移动至待要检测的通道的位置)
 * @param id 通道id
 * @return 是否成功
 */
QString Controller::prepareOpticalChannel(int id) {

    if (m_msMaxNumber == 8) {
        int angle = id*3600/m_msMaxNumber;//lt:0
        bool ok = m_pDataLayer->stepMotorStart( STEP_MOTOR_CHANNEL_ID, angle );
        if (!ok) {
            return tr( "Change optical channel error!" );
        }
    }

    return "Success";
}

/**
 * @brief Controller::readSpectrograph 读取光谱仪的数据
 * @param op 光程
 * @param x 波长
 * @param y 吸光值
 */
void Controller::readSpectrograph(QString typeStr, double op,
                                  QVector<int> &x, QVector<double> &y) {

    int time = 0;
    int count = 0;
    if (typeStr == "Microscale") {
        time = m_pOpticalDataModel->msIntegrationTime( op );
        count = m_pOpticalDataModel->msFrequency( op );
    } else {
        time = m_pOpticalDataModel->ctIntegrationTime( op );
        count = m_pOpticalDataModel->ctFrequency( op );
    }

    // 根据光程设置积分时间
    m_pSpectrograph->setIntegrationTime( time );
    // 读取对应光程下的数据
    m_pSpectrograph->measure( x, y, count );
}

/**
 * @brief Controller::readSpectrograph 读取光谱仪的数据
 * @param op 光程
 * @param absoDataModel absoDataModel = NULL为blank方式,否则为measure方式//lt:bwl默认340,空白的时候不会使用该值
 */
void Controller::readSpectrograph(QString typeStr, double op, int bwl, AbsoDataModel *absoDataModel) {
    QVector<int> x;
    QVector<double> y;

    int time = 40000;
    int count = 1;
    double coef = 1;
    if (typeStr == "Microscale") {
        time = m_pOpticalDataModel->msIntegrationTime( op );//lt:获取对应光程下的积分时间（有配置文件）
        coef = m_pOpticalDataModel->msCoef( op );//lt:获取对应光程下的系数（有配置文件）
        count = m_pOpticalDataModel->msFrequency( op );//lt:获取对应光程下的频率（有配置文件）
    } else {
        time = m_pOpticalDataModel->ctIntegrationTime( op );
        coef = m_pOpticalDataModel->ctCoef( op );
        count = m_pOpticalDataModel->ctFrequency( op );
    }

    // 根据光程设置积分时间
    m_pSpectrograph->setIntegrationTime( time );//lt:40000us
    // 读取对应光程下的数据
    int size = m_pSpectrograph->measure( x, y, count );//lt:比色皿count=100微量=10,return x,y是经过平均和平滑后的原始数据
    if (0 == size) {
        return;
    }

    if (NULL != absoDataModel) {
        absoDataModel->setData( op, bwl, coef, x, y );//lt:measure时,处理m_odata数据组
    } else {
        SpecDataModel *specDataModel = new SpecDataModel( op );
        specDataModel->setData( x, y );//lt:blank时
        m_pBlankDataModel->remove( op );//lt:建立光谱数据模型时的光程和该传递参数光程相同，故移除该光谱数据模型
        m_pBlankDataModel->append( specDataModel );//lt:再将光谱数据模型加入到空白数据模型中的m_data中
    }
}

/*
 *
 * ltj:得到recordview传送过来的浓度值
 *
 */
void Controller::getConcValue(QString text) {
    m_concValue = text;
    //qDebug() << m_concValue + "get";
}

/**
 * @brief Controller::initializeSystem
 */
void Controller::initializeSystem() {
    QString filename = QDir::currentPath() + "/configure/system.ini";
    QSettings *configIniReader = new QSettings( filename, QSettings::IniFormat );

    // 读取串口名称以及波特率
    m_spDescription = configIniReader->value( "/SerialPort/Description" ).toString();
    m_spBoundRate = configIniReader->value( "/SerialPort/BaudRate" ).toInt();
    m_spName = findSerialPortName( m_spDescription );//lt:查找到了串口名称给m_spname
    m_timeout = configIniReader->value( "/SerialPort/Timeout" ).toInt();//lt:10000
    m_msUpperLimit = configIniReader->value( "/Prejudge/Upper Limit" ).toInt();
    m_msLowerLimit = configIniReader->value( "/Prejudge/Lower Limit" ).toInt();
    m_msMaxNumber = configIniReader->value( "/System/Channel Number" ).toInt();//lt:最大测量通道
    m_pOpticalDataModel = new OpticalDataModel();//lt:将光程和各个参数对应到map中(光学数据模型)

    m_serialNumber = configIniReader->value( "/System/Spectrograph ID" ).toString();//lt:光谱编号

    delete configIniReader;
    configIniReader = NULL;
}

/**
 * @brief Controller::initializeDevice
 */
void Controller::initializeDevice() {
    // 创建串口、光谱仪等设备
    m_pSerialPort = new QSerialPort();
    m_pDataLayer = new DataLayer( m_pSerialPort, m_timeout, this );
    connect( m_pDataLayer, SIGNAL(temperatureValue(double)), this, SIGNAL(tempValue(double)) );//lt:给温度控制界面
    connect( m_pDataLayer, SIGNAL(vesselClose(bool)), this, SIGNAL(toMessage(bool)) );//lt:给mainwindow执行自动检测

    m_pSpectrograph = new Spectrograph();
    m_pBlankDataModel = new BlankDataModel();

    for (int i = 0; i < m_msMaxNumber; i ++) {
        AbsoDataModel *absoDataModel = new AbsoDataModel();//lt:m_msMaxNumber=1
        absoDataModel->setBlankDataModel( m_pBlankDataModel );//lt:将control中建立的空白数据模型给吸光度数据模型中使用
        m_aDataList.append( absoDataModel );//lt:把吸光度数据模型放到list中，单通道只有1个
    }

}

