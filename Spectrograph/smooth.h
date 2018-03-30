#ifndef SMOOTH_H
#define SMOOTH_H

#include <QVector>

class Smooth
{
public:
    Smooth();

    void LinearSmooth3(QVector<double> s, QVector<double> &listDist);
    void LinearSmooth5(QVector<double> s, QVector<double> &listDist);
    void LinearSmooth7(QVector<double> s, QVector<double> &listDist);

    void QuadraticSmooth5(QVector<double> s, QVector<double> &listDist);
    void QuadraticSmooth7(QVector<double> s, QVector<double> &listDist);

    void CubicSmooth5(QVector<double> s, QVector<double> &listDist);
    void CubicSmooth7(QVector<double> s, QVector<double> &listDist);

private:
    int m_nSmoothOrder;     // 平滑
};

#endif // SMOOTH_H
