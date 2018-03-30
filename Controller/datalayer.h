#ifndef DATALAYER_H
#define DATALAYER_H

#include <QObject>

#define RESPOND_FRAME_FLAG          0xB0


#define COMMAND_NUMBER_MB_GET       0x70 // 主板状态查寻
#define COMMAND_NUMBER_MB_SHUTDOWN  0x76 //关机命令ltj0206

#define COMMAND_NUMBER_SM_GET       0x80 // 获取步进电机状态
#define COMMAND_NUMBER_SM_START     0x81 // 启动步进电机
#define COMMAND_NUMBER_SM_STOP      0x82 // 停止步进电机
#define COMMAND_NUMBER_SM_READ      0x83 // 读取步进电机角度
#define COMMAND_NUMBER_SM_SET       0x84 // 设置步进电机角度

#define COMMAND_NUMBER_DM_GET       0x90 // 获取电机状态
#define COMMAND_NUMBER_DM_START     0x91 // 启动直流电机
#define COMMAND_NUMBER_DM_STOP      0x92 // 停止直流电机

#define COMMAND_NUMBER_TC_GET       0xA0 // 获取温控状态
#define COMMAND_NUMBER_TC_START     0xA1 // 启动温控系统
#define COMMAND_NUMBER_TC_STOP      0xA2 // 停止温控系统
#define COMMAND_NUMBER_TC_READ      0xA3 // 读取当前温度

#define COMMAND_NUMBER_VS_CLOSE     0x04 // 器皿闭合指令

class Logger;
class QSerialPort;
class DataLayer : public QObject
{
    Q_OBJECT
public:
    explicit DataLayer(QSerialPort *serialPort, int timeout, QObject *parent = 0);
    ~DataLayer();

    inline void installLogger(Logger *logger) {
        m_pLogger = logger;
    }

    bool waitStatus() {
        return m_waitStatus;
    }

    void setWaitStatus(bool status) {
        m_waitStatus = status;
    }

    bool mainboardStatus(int id = 0x01);
    bool shutdownboard(int id);//ltj0206

    bool stepMotorStatus(int id);
    bool stepMotorStart(int id, int angle);
    bool stepMotorStop(int id);

    bool dcMotorStatus(int id = 0x01);
    bool dcMotorStart(int id = 0x01, int level = 1);
    bool dcMotorStop(int id = 0x01);

    bool temperatureCtrlStatus(int id);
    bool temperatureCtrlStart(int id, int targetValue);
    bool temperatureCtrlStop(int id);
    bool temperatureCtrlRead(int id);

    QString getErrorMessage();

signals:
    void vesselClose(bool ok);
    void temperatureValue(double temperature);
    void currentAngle(double angle);

public slots:
    void readFromSerialPort();

private:
    typedef struct _COMMAND_FRAME
    {
        unsigned char m_cHeader[2];     // 帧头
        unsigned char m_cFrameFlag;     // 帧标识
        unsigned char m_cCommand;       // 命令号
        unsigned char m_cDeviceNum;     // 设备编号
        unsigned char m_cOperStatus;    // 操作状态
        unsigned char m_cIsCarry;       // 是否携带
        unsigned char m_cData[4];       // 帧数据
        unsigned char m_cBccValue;      // 校验位
    } CommandFrame;

    Logger *m_pLogger;
    QSerialPort *m_pSerialPort;
    int m_serialPortTimeout;
    bool m_respondStatus;
    bool m_waitStatus;
    QString m_errorMessage;
    unsigned char m_sendCmmd;
    unsigned char m_readCmmd;

    QString toHexstr(QByteArray data);
    void waitRespond(int timeout);
    void setExcuteStatus(unsigned char status);
    QList<QByteArray> readBuffer();
    int carryValue(CommandFrame command);
    void excute(CommandFrame command);
    QByteArray commandBuffer(unsigned char command,
                             unsigned char deviceId, unsigned char hasParams, int params = 0);
};

#endif // DATALAYER_H
