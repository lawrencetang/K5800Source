#include "datalayer.h"
#include "../Logger/Logger.h"
#include <QDebug>
#include <QSerialPort>
#include <QElapsedTimer>
#include <QCoreApplication>


DataLayer::DataLayer(QSerialPort *serialPort, int timeout, QObject *parent)
    : QObject(parent) {
    m_pLogger = NULL;
    m_pSerialPort = serialPort;
    m_serialPortTimeout = timeout;
    m_sendCmmd = m_readCmmd = 0xFF;
    connect(m_pSerialPort, SIGNAL(readyRead()), this, SLOT(readFromSerialPort()));//lt:readyread是qiodevice的信号
}

DataLayer::~DataLayer() {

}

/**
 * @brief DataLayer::mainboardStatus 主板状态查寻
 * @param id 编号
 * @return 是否成功
 */
bool DataLayer::mainboardStatus(int id) {

    unsigned char commandNumber = COMMAND_NUMBER_MB_GET;//lt:0x70
    unsigned char deviceId = (unsigned char)id;//lt:0x01
    unsigned char isCarry = 0x00;

    if (!m_pSerialPort->isOpen()) {
        m_errorMessage = tr( "SerialPort is closed" );
        return false;
    }
    QByteArray buffer = commandBuffer( commandNumber, deviceId, isCarry );
    int size = m_pSerialPort->write( buffer );//lt:发送数据0xff,0xff,0xc0,0x70,0x01,0x00,0x00,0x00,0x00,0x00,0x00,校验
    if (size == 0) {
        m_errorMessage = tr( "Send data error(mainboardStatus)!" );
        return false;
    }

    waitRespond( m_serialPortTimeout );//lt:超时更新m_errormessage
    return m_respondStatus;//lt:接收到的相应数据，然后判断正确后，这里通过调用prossevent，使用其他线程更新该标志为true
}

/**
 * @brief DataLayer::shutdownboard 关机//ltj0206
 * @param id 编号
 * @return 是否成功
 */
bool DataLayer::shutdownboard(int id) {
    unsigned char commandNumber = COMMAND_NUMBER_MB_SHUTDOWN;//lt:0x76
    unsigned char deviceId = (unsigned char)id;//lt:0x01
    unsigned char isCarry = 0x00;

    if (!m_pSerialPort->isOpen()) {
        m_errorMessage = tr( "SerialPort is closed" );
        return false;
    }
    QByteArray buffer = commandBuffer( commandNumber, deviceId, isCarry );
    int size = m_pSerialPort->write( buffer );//lt:发送数据0xff,0xff,0xc0,0x76,0x01,0x00,0x00,0x00,0x00,0x00,0x00,校验
    if (size == 0) {
        m_errorMessage = tr( "Send data error(shutdownboard)!" );
        return false;
    }

    waitRespond( m_serialPortTimeout );//lt:超时更新m_errormessage
    return m_respondStatus;//lt:接收到的相应数据，然后判断正确后，这里通过调用prossevent，使用其他线程更新该标志为true
}

/**
 * @brief DataLayer::stepMotorStatus 进步电机状态
 * @param id 编号
 * @return 是否成功
 */
bool DataLayer::stepMotorStatus(int id) {

    unsigned char commandNumber = COMMAND_NUMBER_SM_GET;//lt:0x80
    unsigned char deviceId = (unsigned char)id;//lt:光程0x01,光路0x02
    unsigned char isCarry = 0x00;

    if (!m_pSerialPort->isOpen()) {
        m_errorMessage = tr( "SerialPort is closed" );
        return false;
    }
    QByteArray buffer = commandBuffer( commandNumber, deviceId, isCarry );
    int size = m_pSerialPort->write( buffer );
    if (size == 0) {
        m_errorMessage = tr( "Send data error(stepMotorStatus)!" );
        return false;
    }

    waitRespond( m_serialPortTimeout );
    return m_respondStatus;
}

/**
 * @brief DataLayer::stepMotorStart 启动步进电机
 * @param id 编号
 * @param angle 角度
 * @return 是否成功
 */
bool DataLayer::stepMotorStart(int id, int angle) {
    unsigned char commandNumber = COMMAND_NUMBER_SM_START;//lt:0x81,启动步进电机
    unsigned char deviceId = (unsigned char)id;
    unsigned char isCarry = 0x01;

    if (!m_pSerialPort->isOpen()) {
        m_errorMessage = tr( "SerialPort is closed" );
        return false;
    }
    QByteArray buffer = commandBuffer( commandNumber, deviceId, isCarry, angle );//lt:下发指令的角度比真实值扩大10倍
    int size = m_pSerialPort->write( buffer );
    if (size == 0) {
        m_errorMessage = tr( "Send data error(stepMotorStart)!" );
        return false;
    }

    waitRespond( m_serialPortTimeout );
    return m_respondStatus;
}

/**
 * @brief DataLayer::stepMotorStop 停止步进电机
 * @param id 编号
 * @return 是否成功
 */
bool DataLayer::stepMotorStop(int id) {
    unsigned char commandNumber = COMMAND_NUMBER_SM_STOP;
    unsigned char deviceId = (unsigned char)id;
    unsigned char isCarry = 0x00;

    if (!m_pSerialPort->isOpen()) {
        m_errorMessage = tr( "SerialPort is closed" );
        return false;
    }
    QByteArray buffer = commandBuffer( commandNumber, deviceId, isCarry );
    int size = m_pSerialPort->write( buffer );
    if (size == 0) {
        m_errorMessage = tr( "Send data error(stepMotorStop)!" );
        return false;
    }

    waitRespond( m_serialPortTimeout );
    return m_respondStatus;
}

/**
 * @brief DataLayer::dcMotorStatus 直流电机状态
 * @param id 直流电机编号
 * @return 是否成功
 */
bool DataLayer::dcMotorStatus(int id) {

    unsigned char commandNumber = COMMAND_NUMBER_DM_GET;
    unsigned char deviceId = (unsigned char)id;
    unsigned char isCarry = 0x00;

    if (!m_pSerialPort->isOpen()) {
        m_errorMessage = tr( "SerialPort is closed" );
        return false;
    }
    QByteArray buffer = commandBuffer( commandNumber, deviceId, isCarry );
    int size = m_pSerialPort->write( buffer );
    if (size == 0) {
        m_errorMessage = tr( "Send data error(dcMotorStart)!" );
        return false;
    }

    waitRespond( m_serialPortTimeout );
    return m_respondStatus;
}

/**
 * @brief DataLayer::dcMotorStart 启动直流电机
 * @param id 直流电机编号
 * @param level 转动等级
 * @return 是否成功
 */
bool DataLayer::dcMotorStart(int id, int level) {
    unsigned char commandNumber = COMMAND_NUMBER_DM_START;
    unsigned char deviceId = (unsigned char)id;
    unsigned char isCarry = 0x01;

    if (!m_pSerialPort->isOpen()) {
        m_errorMessage = tr( "SerialPort is closed" );
        return false;
    }
    QByteArray buffer = commandBuffer( commandNumber, deviceId, isCarry, level );
    int size = m_pSerialPort->write( buffer );
    if (size == 0) {
        m_errorMessage = tr( "Send data error(dcMotorStart)!" );
        return false;
    }

    waitRespond( m_serialPortTimeout );
    return m_respondStatus;
}

/**
 * @brief DataLayer::dcMotorStop 停止直流电机
 * @param id 直流电机编号
 * @return 是否成功
 */
bool DataLayer::dcMotorStop(int id) {
    unsigned char commandNumber = COMMAND_NUMBER_DM_STOP;
    unsigned char deviceId = (unsigned char)id;
    unsigned char isCarry = 0x00;

    if (!m_pSerialPort->isOpen()) {
        m_errorMessage = tr( "SerialPort is closed" );
        return false;
    }
    QByteArray buffer = commandBuffer( commandNumber, deviceId, isCarry );
    int size = m_pSerialPort->write( buffer );
    if (size == 0) {
        m_errorMessage = tr( "Send data error(dcMotorStop)!" );
        return false;
    }

    waitRespond( m_serialPortTimeout );
    return m_respondStatus;
}

/**
 * @brief DataLayer::temperatureCtrlStatus 温控系统状态
 * @param id 温控系统编号
 * @return 是否成功
 */
bool DataLayer::temperatureCtrlStatus(int id) {

    unsigned char commandNumber = COMMAND_NUMBER_TC_GET;
    unsigned char deviceId = (unsigned char)id;
    unsigned char isCarry = 0x00;

    if (!m_pSerialPort->isOpen()) {
        m_errorMessage = tr( "SerialPort is closed" );
        return false;
    }
    QByteArray buffer = commandBuffer( commandNumber, deviceId, isCarry );
    int size = m_pSerialPort->write( buffer );
    if (size == 0) {
        m_errorMessage = tr( "Send data error(temperatureCtrlStart)!" );
        return false;
    }

    waitRespond( m_serialPortTimeout );
    return m_respondStatus;
}

/**
 * @brief DataLayer::temperatureCtrlStart 启动温控系统
 * @param id 温控系统编号
 * @param targetValue 目标温度
 * @return 是否成功
 */
bool DataLayer::temperatureCtrlStart(int id, int targetValue) {
    unsigned char commandNumber = COMMAND_NUMBER_TC_START;
    unsigned char deviceId = (unsigned char)id;
    unsigned char isCarry = 0x01;

    if (!m_pSerialPort->isOpen()) {
        m_errorMessage = tr( "SerialPort is closed" );
        return false;
    }
    QByteArray buffer = commandBuffer( commandNumber, deviceId, isCarry, targetValue );
    int size = m_pSerialPort->write( buffer );
    if (size == 0) {
        m_errorMessage = tr( "Send data error(temperatureCtrlStart)!" );
        return false;
    }

    waitRespond( m_serialPortTimeout );
    return m_respondStatus;
}

/**
 * @brief DataLayer::temperatureCtrlStop 停止温控系统
 * @param id 温控系统编号
 * @return 是否成功
 */
bool DataLayer::temperatureCtrlStop(int id) {
    unsigned char commandNumber = COMMAND_NUMBER_TC_STOP;
    unsigned char deviceId = (unsigned char)id;
    unsigned char isCarry = 0x00;

    if (!m_pSerialPort->isOpen()) {
        m_errorMessage = tr( "SerialPort is closed" );
        return false;
    }
    QByteArray buffer = commandBuffer( commandNumber, deviceId, isCarry );
    int size = m_pSerialPort->write( buffer );
    if (size == 0) {
        m_errorMessage = tr( "Send data error(temperatureCtrlStop)!" );
        return false;
    }

    waitRespond( m_serialPortTimeout );
    return m_respondStatus;
}

/**
 * @brief DataLayer::temperatureCtrlRead 读取温度
 * @param id 温控系统编号
 * @return 是否成功
 */
bool DataLayer::temperatureCtrlRead(int id) {
    unsigned char commandNumber = COMMAND_NUMBER_TC_READ;
    unsigned char deviceId = (unsigned char)id;
    unsigned char isCarry = 0x00;

    if (!m_pSerialPort->isOpen()) {
        m_errorMessage = tr( "SerialPort is closed" );
        return false;
    }
    QByteArray buffer = commandBuffer( commandNumber, deviceId, isCarry );
    int size = m_pSerialPort->write( buffer );
    if (size == 0) {
        m_errorMessage = tr( "Send data error(temperatureCtrlRead)!" );
        return false;
    }

    return true;
}

/**
 * @brief DataLayer::getErrorMessage
 * @return
 */
QString DataLayer::getErrorMessage() {
    return m_errorMessage;
}

/**
 * @brief DataLayer::readFromSerialPort 从串口读取数据
 */
void DataLayer::readFromSerialPort() {

    QList<QByteArray> frameBufferList = readBuffer();//lt:framebufferlist只能存一组数据?
    if (frameBufferList.isEmpty()) {
        return;
    }

    CommandFrame t_command;
    for (int i = 0; i < frameBufferList.size(); i ++) {
        QByteArray buffer = frameBufferList.at( i );
        memcpy( &t_command, buffer.data(), sizeof( CommandFrame ) );//lt:把buffer中的数据按照commandframe的长度复制到t_command中
        excute( t_command );//lt:判断接收的数据
    }
}

/**
 * @brief DataLayer::toHexstr
 * @param data
 * @return
 */
QString DataLayer::toHexstr(QByteArray data) {
    QString hexStr;
    for (int i = 0; i < data.size(); i ++) {
        unsigned char value = (unsigned char)data.at(i);//lt:解析每个字节,0-255存储
        if (value < 0x10) {
            hexStr.append( "0" );//lt:随后转换时，小于16的数只能被转换为一位的0-F
        }
        hexStr.append( QString::number( value, 16 ).toUpper() );//lt:值转换为16进制,并大写
        if (i < data.size() - 1) {
            hexStr.append(" ");//lt:每一个数据后有一个空格,最后一个数据没有
        }
    }
    return hexStr;
}//lt:用来写日志的数据

/**
 * @brief DataLayer::waitRespond
 * @param timeout
 */
void DataLayer::waitRespond(int timeout) {

    m_errorMessage = "Success";
    m_waitStatus = true;
    m_respondStatus = false;

    QElapsedTimer t;
    t.start();
    while(t.elapsed() < timeout && m_waitStatus) {
        QCoreApplication::processEvents();//lt:进程去处理其他线程
    }
    if (t.elapsed() >= timeout) {
        m_errorMessage = tr( "Device timeout!" );
    }//lt:超时更新m_errormessage
}

/**
 * @brief DataLayer::setExcuteStatus
 * @param status
 */
void DataLayer::setExcuteStatus(unsigned char status) {
    if (status == 0x00) {
        m_errorMessage = tr( "Respond success!" );
        m_respondStatus = true;//lt:操作状态为0x00,状态正常
    } else {
        m_errorMessage = tr( "Respond error!" );
        m_respondStatus = false;
    }
    // 退出等待状态
    m_waitStatus = false;
}

/**
 * @brief DataLayer::readBuffer 读取串口数据
 * @return 返回串口帧列表
 */
QList<QByteArray> DataLayer::readBuffer() {

    QList<QByteArray> frameBufferList;
    int size = m_pSerialPort->bytesAvailable();//lt:返回正在等待被读取的字节数量
    if (size <= 0) {
        return frameBufferList;
    }

    char bccValue = 0x00;
    QByteArray data;//lt:由于机制为一主一从，下行一条命令后主控板回复一条数据，故每次都能收到一组数据
    QByteArray buffer = m_pSerialPort->read( size );//lt:将读全部字节的数据存至buffer
    if (m_pLogger != NULL) {
        m_pLogger->outputMessage( "↑", toHexstr( buffer ) );
    }//lt:写上行命令的日志
    for (int i = 0; i < buffer.size(); i++) {
        unsigned char byte = (unsigned char)buffer.at(i);//lt:取每个字节存至byte
        int dataSize = data.size();//lt:初始时datasize=0，写入数据后变大
        if (0 == dataSize) {
            if (byte == 0xFF) {
                data.append( byte );
            }
        } else if (1 == dataSize) {
            if (byte != 0xFF) {
                data.append(0xFF);
                bccValue ^= byte;
            }
            data.append(byte);
        } else if (2 == dataSize) {
            if (byte != 0xFF) {
                bccValue ^= byte;//lt:开始异或
                data.append(byte);
            }
        } else {
            bccValue ^= byte;
            data.append(byte);
            if (data.size() == sizeof( CommandFrame )) {
                if (0x00 == bccValue) {
                    frameBufferList.append( data );
                }//lt:校验成功，将data放进framebufferlist中

                data.clear();
                bccValue = 0x00;
            }
        }
    }
    return frameBufferList;
}

int DataLayer::carryValue(DataLayer::CommandFrame command) {
    int data = -1;
    if (command.m_cIsCarry == 0x01) {
        data = ( command.m_cData[0] << 24 ) +
               ( command.m_cData[1] << 16 ) +
               ( command.m_cData[2] << 8 ) +
               ( command.m_cData[3] );
    }

    return data;
}

/**
 * @brief DataLayer::excute
 * @param command
 */
void DataLayer::excute(DataLayer::CommandFrame command) {

    if (RESPOND_FRAME_FLAG != command.m_cFrameFlag) {
        m_errorMessage = tr( "Frame flag error!" );//lt:如果帧标识不等于0xB0报错
        return;
    }

    m_readCmmd = command.m_cCommand;
    if (m_sendCmmd == m_readCmmd) {
        m_waitStatus = false;
    }//lt:读的命令号和发送命令号相同，更新等待状态

    switch(command.m_cCommand) {
    case COMMAND_NUMBER_SM_START://lt:0x81
    case COMMAND_NUMBER_SM_STOP://lt:0x82
    case COMMAND_NUMBER_SM_SET://lt:0x84
    case COMMAND_NUMBER_DM_START://lt:0x91
    case COMMAND_NUMBER_DM_STOP://lt:0x92
    case COMMAND_NUMBER_TC_START://lt:0xa1
    case COMMAND_NUMBER_TC_STOP://lt:0xa2
        setExcuteStatus( command.m_cOperStatus );//lt:操作状态
        break;//lt:SM:步进电机，DM:直流电机，TC:温控
    case COMMAND_NUMBER_MB_GET:
        if (command.m_cData[0] == 0x00 &&
                command.m_cData[1] == 0x00 &&
                command.m_cData[2] == 0x00 &&
                command.m_cData[3] == 0x00) {
            m_errorMessage = tr( "Main Board Ok!" );
            m_respondStatus = true;
        } else {
            m_errorMessage = tr( "Main Board Error!" );
            m_respondStatus = false;
        }
        break;
    case COMMAND_NUMBER_MB_SHUTDOWN:
        if (command.m_cData[0] == 0x00 &&
                command.m_cData[1] == 0x00 &&
                command.m_cData[2] == 0x00 &&
                command.m_cData[3] == 0x00) {
            m_errorMessage = tr( "ShutDown Ok!" );
            m_respondStatus = true;
        } else {
            m_errorMessage = tr( "ShutDown Error!" );
            m_respondStatus = false;
        }
        break;//ltj0206
    case COMMAND_NUMBER_SM_GET:
        if (command.m_cOperStatus == 0x00) {
            m_errorMessage = tr( "Step Motor Ok!" );
            m_respondStatus = true;//lt:操作状态为0x00,状态正常
        } else {
            m_errorMessage = tr( "Step Motor Error!" );
            m_respondStatus = false;
        }
        break;
    case COMMAND_NUMBER_SM_READ:
        break;//lt:读步进电机角度
    case COMMAND_NUMBER_DM_GET:
        if (command.m_cOperStatus == 0x00) {
            m_errorMessage = tr( "DC Motor Ok!" );
            m_respondStatus = true;//lt:操作状态为0x00,状态正常
        } else {
            m_errorMessage = tr( "DC Motor Error!" );
            m_respondStatus = false;
        }
        break;
    case COMMAND_NUMBER_TC_GET:
        if (command.m_cOperStatus == 0x00) {
            m_errorMessage = tr( "Temperature Controller Ok!" );
            m_respondStatus = true;//lt:操作状态为0x00,状态正常
        } else {
            m_errorMessage = tr( "Temperature Controller Error!" );
            m_respondStatus = false;
        }
        break;
    case COMMAND_NUMBER_TC_READ:
        if (0x00 == command.m_cOperStatus) {
            double value = (double)carryValue( command )/10;
            emit temperatureValue( value );//lt:发送当前温度值信号
            m_respondStatus = true;//lt:操作状态为0x00,状态正常
        } else {
            m_errorMessage = tr( "Read Temperature Error!" );
            m_respondStatus = false;
        }
        break;
    case COMMAND_NUMBER_VS_CLOSE://0x04
        m_waitStatus = false;
        if (0x01 == command.m_cData[3]) {
            emit vesselClose( true );//lt:发送检测臂闭合信号
            m_respondStatus = true;//lt:操作状态为0x00,状态正常
        } else {
            emit vesselClose( false );
            m_respondStatus = false;
        }
        break;
    }
}

/**
 * @brief DataLayer::commandBuffer 获取命令缓冲
 * @param command 命令号
 * @param deviceId 设备ID
 * @param hasParams 是否携带参数
 * @param params 参数
 * @return 帧数据
 */
QByteArray DataLayer::commandBuffer(unsigned char command,
                                    unsigned char deviceId, unsigned char hasParams, int params) {
    QByteArray buffer;
    buffer.append( 0xC0 );
    buffer.append( (char)command );
    buffer.append( (char)deviceId );
    buffer.append( (char)0x00 );
    buffer.append( (char)hasParams );//lt:0x00或0x01
    if (0x01 == hasParams) {
        buffer.append( (char)(params >> 24 & 0xFF) );
        buffer.append( (char)(params >> 16 & 0xFF) );
        buffer.append( (char)(params >> 8 & 0xFF) );
        buffer.append( (char)(params & 0xFF) );//lt:params为整型32位,编译器先将0xFF提升32位再进行与运算
    } else {
        buffer.append( (char)0x00 );
        buffer.append( (char)0x00 );
        buffer.append( (char)0x00 );
        buffer.append( (char)0x00 );
    }//lt:命令不带第四个传递参数则默认为else

    char bccValue = 0x00;
    for (int i = 0; i < buffer.size(); i ++) {
        bccValue ^= buffer.at( i );
    }//lt:计算生成异或校验

    buffer.append( bccValue );
    buffer.insert( 0, 0xFF );
    buffer.insert( 0, 0xFF );//lt:插入帧头

    m_sendCmmd = (unsigned char)command;//lt:命令为下行命令
    if (m_pLogger != NULL) {
        m_pLogger->outputMessage( "↓", toHexstr( buffer ) );
    }//lt:写下行命令的日志

    return buffer;
}

