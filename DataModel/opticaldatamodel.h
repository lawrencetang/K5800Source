#ifndef OPTICALDATAMODEL_H
#define OPTICALDATAMODEL_H

#include <QMap>
#include <QObject>

class OpticalDataModel : public QObject
{
    Q_OBJECT
public:
    explicit OpticalDataModel(QObject *parent = 0);
    ~OpticalDataModel();

    int msIntegrationTime(double op);
    int msIntegrationTime(QString opStr);
    int msAngle(double op);
    int msAngle(QString opStr);
    int msFrequency(double op);
    int msFrequency(QString opStr);
    double msCoef(double op);
    double msCoef(QString opStr);

    int ctIntegrationTime(double op);
    int ctIntegrationTime(QString opStr);
    int ctFrequency(double op);
    int ctFrequency(QString opStr);
    double ctCoef(double op);
    double ctCoef(QString opStr);

    double msStdOp();
    double msMaxOp();
    double msMinOp();

    double ctOp();

    QString msFixOp(QString key);

private:
    void initializeSystem();

    QMap<QString, QString> m_oTimeMap_MS;
    QMap<QString, QString> m_oTimeMap_CT;
    QMap<QString, QString> m_oFrequency_MS;
    QMap<QString, QString> m_oFrequency_CT;
    QMap<QString, QString> m_oAngleMap_MS;
    QMap<QString, QString> m_oCoefMap_MS;
    QMap<QString, QString> m_oCoefMap_CT;
    QMap<QString, QString> m_nFixOpMap_MS;

};

#endif // OPTICALDATAMODEL_H
