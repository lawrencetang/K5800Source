#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QObject>
#include <QSerialPort>
#include <QStringList>

class Logger;
class DataLayer;
class Spectrograph;
class AbsoDataModel;
class BlankDataModel;
class MsOpDataModel;
class OpticalDataModel;
class SettingDataModel;
class Controller : public QObject
{
    Q_OBJECT
public:
    explicit Controller(QObject *parent = 0);
    ~Controller();

    void installLogger(Logger *logger);

    inline SettingDataModel *getSettingDataModel(int id) {
        if (id < m_sDataList.size()) {
            return m_sDataList.at( id );
        }
        return NULL;
    }

    inline int dyTrainTimes() {
        return m_dyTrainTimes;
    }

    inline QStringList dyWatchStrList() {
        return m_dyWatchStrList;
    }

    QString getSerialNumber();

    // 检测接口
    void setSettingModel(QList<SettingDataModel *> sDataList);
    QString startMicroscaleCheck(int id);
    QString startCuvetteCheck();
    QString checkMainBoard();
    QString shutdownMainBoard();//ltj0206
    QString checkMicroscale();
    QString checkCuvette();
    QString checkTemperature();
    QString startBlank(QString type);
    QString startMeasure(QString type);

    bool checkDevice();
    // 通讯串口接口
    QString findSerialPortName(QString description);
    QString getDescription() {
        return m_spDescription;
    }

    // 温控系统接口
    QString temperatureStart(int targetTemp);
    QString temperatureRead();
    QString temperatureStop();

    QString reset();

signals:
    void measureOk(int id);
    void staticWave(QVector<double> x, QVector<double> y);
    void staticWave(QString title, QVector<double> x, QVector<double> y);
    void dynamicsWave(double x, QList<double> y);
    void tempValue(double value);
    void toMessage(bool ok);


public slots:
    bool openSerialPort();
    void closeSerialPort();
    bool openSpectrograph();
    void closeSpectrograph();
    void getConcValue(QString text);

private:
    QString m_concValue;//ltj:用于接收recordview的浓度值
    // 串口设备以及相关参数
    QSerialPort *m_pSerialPort;
    QString m_spDescription;
    QString m_spName;
    int m_spBoundRate;
    int m_timeout;

    int m_dyTrainTimes;
    QStringList m_dyWatchStrList;

    // 光谱设备
    Spectrograph *m_pSpectrograph;
    QString m_serialNumber;

    int m_msMaxNumber;
    OpticalDataModel *m_pOpticalDataModel;
    QList<AbsoDataModel *> m_aDataList;
    QList<SettingDataModel *> m_sDataList;

    BlankDataModel *m_pBlankDataModel;
    DataLayer *m_pDataLayer;

    // 预判光程
    QList<int> m_stdOpIdList;
    QList<int> m_maxOpIdList;
    QList<int> m_minOpIdList;
    // 上下限值
    double m_msUpperLimit;
    double m_msLowerLimit;

    // 超微量检测
    QString cuvetteBlank();
    QString microscaleBlank();
    QString cuvetteMeasure(SettingDataModel *sDataModel);
    QString microscaleMeasure();

    // 动力学检测
    QString dynamicsMesaure(SettingDataModel *sDataModel);
    void waitting(int timeout);

    // 准备函数
    QString prepareMicroscaleMeasure(bool &isFixed);
    void addMesaureQueue(int id, double value, double upper, double lower);
    void setMesaureQueue(int id, double value, double upper, double lower);

    // 执行check,blank,measure
    QString excuteCheck(QString typeStr, double op);
    QString excuteMicroscaleBlank(double op);
    QString excuteMicroscaleMeasure(double op, QList<int> idList);

    // 电机控制函数
    QString prepareOpticalPath(double op);
    QString prepareOpticalChannel(int id);

    // 读取光谱数据
    void readSpectrograph(QString typeStr, double op, QVector<int> &x, QVector<double> &y);
    void readSpectrograph(QString typeStr, double op, int bwl = 340, AbsoDataModel *absoDataModel = NULL);

    // 初始化函数
    void initializeSystem();
    void initializeDevice();
};

#endif // CONTROLLER_H
