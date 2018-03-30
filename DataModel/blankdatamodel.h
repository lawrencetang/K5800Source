#ifndef BLANKDATAMODEL_H
#define BLANKDATAMODEL_H

#include <QObject>

class SpecDataModel;
class BlankDataModel : public QObject
{
    Q_OBJECT
public:
    explicit BlankDataModel(QObject *parent = 0);
    QVector<double> absorbance(double op, QVector<double> intensity);

    bool blankData(double op, QVector<double> &x, QVector<double> &y);
    void append(SpecDataModel *data);
    void remove(double op);
    void clear();

private:
    QList<SpecDataModel *> m_data;
};

#endif // BLANKDATAMODEL_H
