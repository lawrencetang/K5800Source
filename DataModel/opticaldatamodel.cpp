#include "opticaldatamodel.h"

#include <QDir>
#include <QDebug>
#include <QSettings>

OpticalDataModel::OpticalDataModel(QObject *parent)
    : QObject(parent) {

    m_oTimeMap_MS.clear();
    m_oTimeMap_CT.clear();
    m_oAngleMap_MS.clear();

    initializeSystem();
}

OpticalDataModel::~OpticalDataModel() {

}

/**
 * @brief OpticalDataModel::msIntegrationTime 获取对应光程下的积分时间
 * @param op 光程
 * @return 积分时间
 */
int OpticalDataModel::msIntegrationTime(double op) {
    QString opStr = QString::number( op );
    return msIntegrationTime( opStr );
}

/**
 * @brief OpticalDataModel::msIntegrationTime 获取对应光程下的积分时间
 * @param op 光程
 * @return 积分时间
 */
int OpticalDataModel::msIntegrationTime(QString opStr) {
    if (m_oTimeMap_MS.contains( opStr )) {
        return m_oTimeMap_MS.value( opStr ).toInt();
    }
    return 40000;
}

/**
 * @brief OpticalDataModel::msAngle 获取对应光程下的角度
 * @param op 光程
 * @return 角度
 */
int OpticalDataModel::msAngle(double op) {
    QString opStr = QString::number( op );
    return msAngle( opStr );
}

/**
 * @brief OpticalDataModel::msAngle 获取对应光程下的角度
 * @param op 光程
 * @return 角度
 */
int OpticalDataModel::msAngle(QString opStr) {
    if (m_oAngleMap_MS.contains( opStr )) {
        return m_oAngleMap_MS.value( opStr ).toInt();
    }
    return 0;
}

/**
 * @brief OpticalDataModel::msFrequency
 * @param op
 * @return
 */
int OpticalDataModel::msFrequency(double op) {
    QString opStr = QString::number( op );
    return msFrequency( opStr );
}

/**
 * @brief OpticalDataModel::msFrequency
 * @param opStr
 * @return
 */
int OpticalDataModel::msFrequency(QString opStr) {
    if (m_oFrequency_MS.contains( opStr )) {
        return m_oFrequency_MS.value( opStr ).toInt();
    }
    return 0;
}

/**
 * @brief OpticalDataModel::msCoef
 * @param op
 * @return
 */
double OpticalDataModel::msCoef(double op) {
    QString opStr = QString::number( op );
    return msCoef( opStr );
}

/**
 * @brief OpticalDataModel::msCoef
 * @param opStr
 * @return
 */
double OpticalDataModel::msCoef(QString opStr) {
    if (m_oCoefMap_MS.contains( opStr )) {
        return m_oCoefMap_MS.value( opStr ).toDouble();
    }
    return 1;
}

/**
 * @brief OpticalDataModel::ctIntegrationTime 获取对应光程下的积分时间
 * @param op 光程
 * @return 积分时间
 */
int OpticalDataModel::ctIntegrationTime(double op) {
    QString opStr = QString::number( op );
    return ctIntegrationTime( opStr );
}

/**
 * @brief OpticalDataModel::ctIntegrationTime 获取对应光程下的积分时间
 * @param opStr 光程
 * @return 积分时间
 */
int OpticalDataModel::ctIntegrationTime(QString opStr) {
    if (m_oTimeMap_MS.contains( opStr )) {
        return m_oTimeMap_CT.value( opStr ).toInt();
    }
    return 40000;
}

/**
 * @brief OpticalDataModel::ctFrequency
 * @param op
 * @return
 */
int OpticalDataModel::ctFrequency(double op) {
    QString opStr = QString::number( op );
    return ctFrequency( opStr );
}

/**
 * @brief OpticalDataModel::ctFrequency
 * @param opStr
 * @return
 */
int OpticalDataModel::ctFrequency(QString opStr) {
    if (m_oFrequency_CT.contains( opStr )) {
        return m_oFrequency_CT.value( opStr ).toInt();
    }
    return 0;
}

/**
 * @brief OpticalDataModel::ctCoef
 * @param op
 * @return
 */
double OpticalDataModel::ctCoef(double op) {
    QString opStr = QString::number( op );
    return ctCoef( opStr );
}

/**
 * @brief OpticalDataModel::ctCoef
 * @param opStr
 * @return
 */
double OpticalDataModel::ctCoef(QString opStr) {
    if (m_oCoefMap_CT.contains( opStr )) {
        return m_oCoefMap_CT.value( opStr ).toDouble();
    }
    return 1;
}

/**
 * @brief OpticalDataModel::msStdOp 获取标准光程
 * @return 标准光程
 */
double OpticalDataModel::msStdOp() {

    double value = 0;
    double stdValue = 0;

    double maxValue = msMaxOp();
    double minValue = msMinOp();

    QList<QString> keys = m_oTimeMap_MS.keys();//lt:光程/积分时间
    for (int i = 0; i < keys.size(); i ++) {
        value = keys.at( i ).toDouble();
        if (maxValue > value && minValue < value) {
            stdValue = value;
            break;
        }
    }
    return stdValue;
}//lt:最大最小中间的那个

/**
 * @brief MsOpDataModel::msMaxOp 获取最大光程
 * @return 最大光程
 */
double OpticalDataModel::msMaxOp() {

    double value = 0;
    double maxValue = -1;
    QList<QString> keys = m_oTimeMap_MS.keys();
    for (int i = 0; i < keys.size(); i ++) {
        value = keys.at( i ).toDouble();
        if (maxValue < value) {
            maxValue = value;
        }
    }
    return maxValue;
}//lt:最大光程1

/**
 * @brief MsOpDataModel::msMaxOp 获取最小光程
 * @return 最小光程
 */
double OpticalDataModel::msMinOp() {

    double value = 0;
    double minValue = 1000000;
    QList<QString> keys = m_oTimeMap_MS.keys();
    for (int i = 0; i < keys.size(); i ++) {
        value = keys.at( i ).toDouble();
        if (minValue > value) {
            minValue = value;
        }
    }
    return minValue;
}//lt:最小光程0.05

/**
 * @brief OpticalDataModel::ctOp
 * @return
 */
double OpticalDataModel::ctOp() {
    QList<QString> keys = m_oTimeMap_CT.keys();
    return keys.first().toDouble();
}

/**
 * @brief OpticalDataModel::msFixOp
 * @param key
 * @return
 */
QString OpticalDataModel::msFixOp(QString key) {
    if (m_nFixOpMap_MS.contains( key )) {
        return m_nFixOpMap_MS.value( key );
    }
    return "NULL";
}

/**
 * @brief OpticalDataModel::initializeSystem
 */
void OpticalDataModel::initializeSystem() {

    QString filename = QDir::currentPath() + "/configure/system.ini";
    QSettings *configIniReader = new QSettings( filename, QSettings::IniFormat );

    // 微量光程\积分时间\电机转动角度信息
    QStringList msOList = configIniReader->value( "/Microscale/Optical" ).toStringList();//lt:3光程0.5,0.05,1
    QStringList msFList = configIniReader->value( "/Microscale/Frequency" ).toStringList();//lt:3频率10,10,10
    QStringList msTList = configIniReader->value( "/Microscale/Integration Time" ).toStringList();//lt:40000...
    QStringList msAList = configIniReader->value( "/Microscale/Angle" ).toStringList();//lt:0,120,240
    QStringList msCList = configIniReader->value( "/Microscale/Coefs" ).toStringList();//lt:1,1,1

    int tSize = msTList.size();//lt:3积分时间
    int aSize = msAList.size();//lt:3角度
    int fSize = msFList.size();//lt:3频率
    int cSize = msCList.size();//lt:3系数

    QString keyStr;
    QString valueStr;
    m_oTimeMap_MS.clear();
    m_oAngleMap_MS.clear();
    m_oCoefMap_MS.clear();
    for (int i = 0; i < msOList.size(); i ++) {
        keyStr = msOList.at( i );
        if (i < tSize) {
            valueStr = msTList.at( i );
        } else {
            valueStr = "NULL";
        }
        m_oTimeMap_MS.insert( keyStr, valueStr );//lt:光程/积分时间Map

        if (i < aSize) {
            valueStr = msAList.at( i );
        } else {
            valueStr = "NULL";
        }
        m_oAngleMap_MS.insert( keyStr, valueStr );//lt:光程/角度Map

        if (i < fSize) {
            valueStr = msFList.at( i );
        } else {
            valueStr = "NULL";
        }
        m_oFrequency_MS.insert( keyStr, valueStr );//lt:光程/频率Map

        if (i < cSize) {
            valueStr = msCList.at( i );
        } else {
            valueStr = "NULL";
        }
        m_oCoefMap_MS.insert( keyStr, valueStr );//lt:光程/系数Map
    }

    // 微量光程\积分时间\电机转动角度信息
    QStringList ctOList = configIniReader->value( "/Cuvette/Optical" ).toStringList();
    QStringList ctTList = configIniReader->value( "/Cuvette/Integration Time" ).toStringList();
    QStringList ctFList = configIniReader->value( "/Cuvette/Frequency" ).toStringList();
    QStringList ccFList = configIniReader->value( "/Cuvette/Coefs" ).toStringList();

    tSize = ctTList.size();
    fSize = ctFList.size();
    cSize = ccFList.size();

    m_oTimeMap_CT.clear();
    m_oFrequency_CT.clear();
    m_oCoefMap_CT.clear();
    for (int i = 0; i < ctOList.size(); i ++) {
        keyStr = ctOList.at( i );
        if (i < tSize) {
            valueStr = ctTList.at( i );
        } else {
            valueStr = "NULL";
        }
        m_oTimeMap_CT.insert( keyStr, valueStr );

        if (i < fSize) {
            valueStr = ctFList.at( i );
        } else {
            valueStr = "NULL";
        }
        m_oFrequency_CT.insert( keyStr, valueStr );

        if (i < cSize) {
            valueStr = ccFList.at( i );
        } else {
            valueStr = "NULL";
        }
        m_oCoefMap_CT.insert( keyStr, valueStr );
    }

    QStringList keyList = configIniReader->value( tr("/Fix Optical/Keys") ).toStringList();
    QStringList valueList = configIniReader->value( tr("/Fix Optical/Values") ).toStringList();

    int size = valueList.size();
    m_nFixOpMap_MS.clear();
    for (int i = 0; i < keyList.size(); i ++ ) {

        keyStr = keyList.at( i );
        if (i < size) {
            valueStr = valueList.at( i );
        } else {
            valueStr = "NULL";
        }
        m_nFixOpMap_MS.insert( keyStr, valueStr );
    }//lt:拟合光程,V-VIS,Kit Method,对应1,1

    delete configIniReader;
    configIniReader = NULL;
}

