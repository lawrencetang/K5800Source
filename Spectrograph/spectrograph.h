#ifndef SPECTROGRAPH_H
#define SPECTROGRAPH_H

#include <QObject>
#include <QVector>

class UsbData;
class UsbDriver;
class Spectrograph : public QObject
{
    Q_OBJECT
public:
    explicit Spectrograph(QObject *parent = 0);
    ~Spectrograph();

    void reset();
    bool isOpened();
    void setIntegrationTime(int time);
signals:
    void error(int code, QString message);

public slots:
    bool open();
    void close();
    int measure(QVector<int> &waveLength, QVector<double> &spectrum, int count = 1);
    QString serialNumber();

private:
    UsbDriver *m_pUsbDriver;
    UsbData *m_pUsbData;
    bool m_isOpened;
    int m_integrationTime;
    int m_offset;

    void waitting(int timeout);

    QVector<double> m_xSource;
    QVector<double> m_ySource;
    QVector<double> m_yFilter;


    void avgSlidingFilter(int width, QVector<double> &y);
    void integerProcess(QVector<int> &x, QVector<double> &y);
    void initializeParameter();
    void initializeDevice();
};

#endif // SPECTROGRAPH_H
