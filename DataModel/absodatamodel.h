#ifndef ABSODATAMODEL_H
#define ABSODATAMODEL_H

#include <QObject>
#include <QMap>
#include <QVector>

class BlankDataModel;
class AbsoDataModel : public QObject
{
    Q_OBJECT
public:
    explicit AbsoDataModel(QObject *parent = 0);

    // 设置,获取光程
    void setOpticalPath(double op);
    double opticalPath();

    // 设置,获取空白数据模型
    void setBlankDataModel(BlankDataModel *dataModel);
    BlankDataModel *blankDataModel();

    // 设置数据
    bool setData(QVector<int> keys, QVector<double> values);
    bool setData(double op, int bwl, double coef, QVector<int> keys, QVector<double> values);

    QString absorbance(QString wlStr);

    // 获取波长,获取吸光度列表
    QVector<double> getWaveLength();
    QVector<double> getAbsorbance();

    // 获取观察值
    QStringList watchValues(QStringList labels);
    QStringList watchValues(QStringList coefs, QStringList labels, QString opStr);

    // 计算核酸浓度函数
    QString calculateNaConc(double coef, double op, int wl = 260);
    QString calculateNaConc(QString coefStr, QString opStr, QString wlStr = "260");

    // 计算蛋白浓度函数
    QString calculatePtConc(double coef, int wl = 280);
    QString calculatePtConc(QString coefStr, QString wlStr = "280");

    inline void clear() {
        m_oData.clear();
    }

    inline bool isEmpty() {
        return m_oData.isEmpty();
    }

private:
    double m_opticalPath;
    int m_bwl;
    int m_smoothingWidth;
    double m_factor;
    double m_coef;
    QMap<int, double> m_oData;
    BlankDataModel *m_pBlankDataModel;

    void avgSlidingFilter(int width, QVector<double> yInput, QVector<double> &yOutput);
    // 获取浓度值
    QString absorbance(int wl);

    // 计算核酸/蛋白纯度函数
    QString calculatePurity(QString label);
};

#endif // ABSODATAMODEL_H
