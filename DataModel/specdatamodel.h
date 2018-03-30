#ifndef SPECDATAMODEL_H
#define SPECDATAMODEL_H

#include <QObject>
#include <QMap>
#include <QVector>

class SpecDataModel : public QObject
{
    Q_OBJECT
public:
    explicit SpecDataModel(double opticalPath, QObject *parent = 0);
    double m_opticalPath;

    void setData(QVector<int> keys, QVector<double> values);
    QVector<double> waveLength();
    QVector<double> lightIntensity();

private:
    QMap<int, double> m_data;
};

#endif // SPECDATAMODEL_H
