#ifndef SETTINGDATAMODEL_H
#define SETTINGDATAMODEL_H

#include <QObject>
#include <QMap>
#include <QStringList>
//#include "./SettingsView/settingview.h"//ltj

class DcMotorSetting {
public:
    explicit DcMotorSetting(QString paramStr);
    inline QString value(QString key) {
        if (m_dcMotorMap.contains( key )) {
            return m_dcMotorMap.value( key );
        }
        return "NULL";
    }

private:
    QMap<QString, QString> m_dcMotorMap;
};

class MethodSetting {
public:
    explicit MethodSetting(QString paramStr);
    inline QString value(QString key) {
        if (m_methodMap.contains( key )) {
            return m_methodMap.value( key );
        }
        return "NULL";
    }

private:
    QMap<QString, QString> m_methodMap;
};

class Controller;
class AbsoDataModel;
class SettingDataModel : public QObject
{
    Q_OBJECT
public:
    explicit SettingDataModel(QString baseStr, QString methodStr,
                              QString dcMotorStr, QString watchStr);
    ~SettingDataModel();

    bool isAutoSelectOp();
    void data(QVector<double> &x, QVector<double> &y);
    void result(QString &fileName, QString &rcdStr, QStringList &values);

    inline AbsoDataModel *absoModel() {
        return m_pAbsoDataModel;
    }
    inline void setAbsoModel(AbsoDataModel *absoDataModel) {
        m_pAbsoDataModel = absoDataModel;
    }

    inline QStringList watchLabels() {
        return m_watchLabels;
    }


    QString baseValue(QString key);
    QString methodValue(QString key);
    QString dcMotorValue(QString key);

private:
    AbsoDataModel *m_pAbsoDataModel;
    MethodSetting *m_pMethodSetting;
    DcMotorSetting *m_pDcMotorSetting;
    QStringList m_unitStrList;
    //SettingView *m_pSettingView;//ltj

    QMap<QString, QString> m_baseMap;
    QStringList m_watchLabels;

    QString transformUnit(QString unit1, QString unit2);
    int transformCoef(QString unit);

};

#endif // SETTINGDATAMODEL_H
