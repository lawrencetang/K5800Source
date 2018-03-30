#include "settingdatamodel.h"
#include "absodatamodel.h"
#include <QDebug>
#include <QDateTime>
#include <QMessageBox>
#include <QDir>//ltj
#include <QSettings>//ltj

QMap<QString, QString> resolve(QString sourceStr) {

    QMap<QString, QString> resultMap;
    QStringList paramList = sourceStr.split( ",", QString::SkipEmptyParts );
    QString keyStr;
    QString valueStr;
    resultMap.clear();
    for (int i = 0; i < paramList.size(); i ++) {
        QString itemStr = paramList.at( i );
        QStringList itemList = itemStr.split( "=", QString::SkipEmptyParts );
        if (itemList.isEmpty()) {
            continue;
        }
        keyStr = itemList.first();
        valueStr = itemList.last();

        resultMap.insert( keyStr, valueStr );
    }

    return resultMap;
}//lt:把字符串按照，和=分开存在resultmap中返回

DcMotorSetting::DcMotorSetting(QString paramStr) {
    m_dcMotorMap = resolve( paramStr );
}

MethodSetting::MethodSetting(QString paramStr) {
    m_methodMap = resolve( paramStr );
}

SettingDataModel::SettingDataModel(QString baseStr, QString methodStr,
                                   QString dcMotorStr, QString watchStr) {

    m_pAbsoDataModel = NULL;
    m_pMethodSetting = new MethodSetting( methodStr );//lt:参数传递进去就解开到qmap中
    m_pDcMotorSetting = new DcMotorSetting( dcMotorStr );//lt:参数传递进去就解开到qmap中
    m_baseMap = resolve( baseStr );//lt:参数传递进去就解开到qmap中
    m_watchLabels.clear();
    watchStr = watchStr.replace( "A", "" );//lt:把watchvalue值传入watchstr中用空代替A
    m_unitStrList.clear();
    m_unitStrList << "ng/uL" << "mg/mL" << "ug/mL" << "ng/mL" << "g/L" << "mg/L";
    QStringList watchList = watchStr.split( ",", QString::SkipEmptyParts );
    for (int i = 0; i < watchList.size(); i ++) {
        m_watchLabels.append( watchList.at( i ) );
    }//lt:解开watchvalue
}

SettingDataModel::~SettingDataModel() {
    if (NULL != m_pMethodSetting) {
        delete m_pMethodSetting;
        m_pMethodSetting = NULL;
    }

    if (NULL != m_pDcMotorSetting) {
        delete m_pDcMotorSetting;
        m_pDcMotorSetting = NULL;
    }
}

/**
 * @brief SettingDataModel::isAutoSelectOp
 * @return
 */
bool SettingDataModel::isAutoSelectOp() {
    if (baseValue( "optical" ) == "Auto") {
        return true;
    }
    return false;
}

/**
 * @brief SettingDataModel::data 获取检测到的数据
 * @param x 输出波长列表
 * @param y 输出吸光度列表
 */
void SettingDataModel::data(QVector<double> &x, QVector<double> &y) {
    x.clear();
    y.clear();
    if (NULL != m_pAbsoDataModel) {
        /*
        x.append( m_pAbsoDataModel->getWaveLength() );
        y.append( m_pAbsoDataModel->getAbsorbance() );
        */
        x<<( m_pAbsoDataModel->getWaveLength() );
        y<<( m_pAbsoDataModel->getAbsorbance() );
    }
}

/**
 * @brief SettingDataModel::baseValue
 * @param key
 * @return
 */
QString SettingDataModel::baseValue(QString key) {
    if (m_baseMap.contains( key )) {
        return m_baseMap.value( key );
    }
    return "NULL";
}//lt:根据传递进入的key参数查baseparameters中的值返回

/**
 * @brief SettingDataModel::methodValue
 * @param key
 * @return
 */
QString SettingDataModel::methodValue(QString key) {
    return m_pMethodSetting->value( key );
}//lt:根据传递进入的key参数查methodparameters中的值返回

/**
 * @brief SettingDataModel::dcMotorValue
 * @param key
 * @return
 */
QString SettingDataModel::dcMotorValue(QString key) {
    return m_pDcMotorSetting->value( key );
}//lt:根据传递进入的key参数查dcmotorparameters中的值返回

/**
 * @brief SettingDataModel::record
 */
void SettingDataModel::result(QString &fileName, QString &rcdStr, QStringList &values) {

    rcdStr.clear();
    //SettingView* m_pSettingView = new SettingView();
    //m_pSettingView->idadd();
    //QMessageBox::warning(0,"basevalue", baseValue("id"), QMessageBox::Ok);//ltj
    rcdStr = QString( "%1,%2" ).arg( baseValue( "id" ) ).arg( baseValue( "name" ) );
    int idadd = m_baseMap.value("id").toInt();
    idadd ++ ;
    m_baseMap["id"] = QString::number(idadd);

    QString measureStr = baseValue( "measure" );
    if (measureStr == "Nucleic Acid") {

        QString wlStr = methodValue( "wave" );
        QString opStr = QString::number( m_pAbsoDataModel->opticalPath() );//lt:初始0.5,执行空白时装载数据模型
        //QMessageBox::warning(0, "opstr", opStr, QMessageBox::Ok);//ltj

        QString coefStr = methodValue( "coef" );
        QString concStr = m_pAbsoDataModel->calculateNaConc( coefStr, opStr, wlStr );//lt:根据前面代码在method中提取的波长，光程，系数的参数值进行计算
        QString unitStr = methodValue( "unit" );

        QString pcStr = transformUnit( "ng/uL", unitStr );//lt:将unitStr和ng/uL单位比较的得出的换算系数
        double value = concStr.toDouble()*pcStr.toDouble();//lt:将ng/uL下的浓度值进行换算
        if (value < 0) {
            value = 0;
        }
        concStr = QString::number( value );

        rcdStr.append( "," );
        rcdStr.append( concStr );
        rcdStr.append( "," );
        rcdStr.append( unitStr );

        QStringList watchList = m_pAbsoDataModel->watchValues( m_watchLabels );
        for (int i = 0; i < watchList.size(); i ++) {
            rcdStr.append( "," );
            rcdStr.append( watchList.at( i ) );
        }//lt:把除法结果依次列出

        rcdStr.append( "," );
        rcdStr.append( methodValue( "type" ) );
        rcdStr.append( "," );
        rcdStr.append( coefStr );
        rcdStr.append( "," );
        rcdStr.append( measureStr );

    } else if (measureStr == "Protein") {

        QString wlStr = methodValue( "wave" );
        QString coefStr = methodValue( "coef" );
        QString concStr = m_pAbsoDataModel->calculatePtConc( coefStr, wlStr );
        QString unitStr = methodValue( "unit" );

        QString pcStr = transformUnit( "mg/mL", unitStr );
        double value = concStr.toDouble()*pcStr.toDouble();
        if (value < 0) {
            value = 0;
        }
        concStr = QString::number( value );

        rcdStr.append( "," );
        rcdStr.append( concStr );
        rcdStr.append( "," );
        rcdStr.append( unitStr );

        QStringList watchList = m_pAbsoDataModel->watchValues( m_watchLabels );
        for (int i = 0; i < watchList.size(); i ++) {
            rcdStr.append( "," );
            rcdStr.append( watchList.at( i ) );
        }

        rcdStr.append( "," );
        rcdStr.append( methodValue( "type" ) );
        rcdStr.append( "," );
        rcdStr.append( coefStr );
        rcdStr.append( "," );
        rcdStr.append( measureStr );

    } else if (measureStr == "Cell Culture") {

        QString wlStr = methodValue( "wave" );
        QString typeStr = methodValue( "type" );

        rcdStr.append( "," );
        rcdStr.append( typeStr );
        rcdStr.append( "," );
        rcdStr.append( wlStr );

        QStringList watchList = m_pAbsoDataModel->watchValues( m_watchLabels );
        QString filename = QDir::currentPath() + "/configure/system.ini";
        QSettings *configIniReader = new QSettings( filename, QSettings::IniFormat );
        double ccMul = configIniReader->value("/System/Cc Multiple").toDouble();
        for (int i = 0; i < watchList.size(); i ++) {
            QString displayValue =  QString::number( watchList.at(i).toDouble() * ccMul );
            rcdStr.append( "," );
            rcdStr.append( displayValue );//ltnote:注意:这个地方还没改，要加倍乘值//ltg
        }//lt:细胞液无需除法
        delete configIniReader;
        configIniReader = NULL;//ltj

        rcdStr.append( "," );
        rcdStr.append( measureStr );//lt:measure值写进去

    } else if (measureStr == "UV-VIS") {

        QStringList coefList;
        coefList.append( methodValue( "Coef1" ) );
        coefList.append( methodValue( "Coef2" ) );
        coefList.append( methodValue( "Coef3" ) );
        coefList.append( methodValue( "Coef4" ) );
        coefList.append( methodValue( "Coef5" ) );

        QString opStr = QString::number( m_pAbsoDataModel->opticalPath() );
        QStringList watchList = m_pAbsoDataModel->watchValues( coefList, m_watchLabels, opStr );
        for (int i = 0; i < m_watchLabels.size(); i ++) {

            rcdStr.append( "," );
            rcdStr.append( coefList.at( i ) );

            rcdStr.append( "," );
            rcdStr.append( m_watchLabels.at( i ) );

            rcdStr.append( "," );
            rcdStr.append( watchList.at( i ) );
        }

        rcdStr.append( "," );
        rcdStr.append( measureStr );

    } else if (measureStr == "Dynamics") {
        QStringList watchList = m_pAbsoDataModel->watchValues( m_watchLabels );
        for (int i = 0; i < watchList.size(); i ++) {
            rcdStr.append( "," );
            rcdStr.append( watchList.at( i ) );
        }

        rcdStr.append( "," );
        rcdStr.append( methodValue( "target" ) );
        rcdStr.append( "," );
        rcdStr.append( methodValue( "times" ) );
        rcdStr.append( "," );
        rcdStr.append( measureStr );
    }

    values.clear();
    if (measureStr != "Dynamics") {

        fileName.clear();
        fileName = QString( "%1.csv" ).arg( QDateTime::currentDateTime().toString("yyyyMMddhhmmss") );
        rcdStr.append( "," );
        rcdStr.append( fileName );

        QVector<double> x;
        QVector<double> y;
        data( x, y );

        QString dataStr;
        QStringList dataList;
        for (int i = 0; i < x.size(); i ++) {
            if (measureStr == "Cell Culture") {
                QString filename = QDir::currentPath() + "/configure/system.ini";
                QSettings *configIniReader = new QSettings(filename, QSettings::IniFormat);
                double ccMul = configIniReader->value("/System/Cc Multiple").toDouble();
                dataStr = QString( "data:,%1,%2" ).arg( x.at( i ) ).arg( y.at( i ) * ccMul );//ltnote
                delete configIniReader;
                configIniReader = NULL;
            }//ltj:细胞液细胞液时读配置文件加倍数
            else {
                dataStr = QString( "data:,%1,%2" ).arg( x.at( i ) ).arg( y.at( i ) );
            }//ltg
            dataList.append( dataStr );
        }

        QString recordStr = "record:,";
        recordStr.append( rcdStr );
        values.append( recordStr );
        values.append( dataList );
    }
    /*//lt:去掉注释
    rcdStr.clear();
    rcdStr.append( baseValue( "id" ) );
    rcdStr.append( "," );
    rcdStr.append( baseValue( "name" ) );
    rcdStr.append( "," );
    QString measureStr = baseValue( "measure" );
    rcdStr.append( measureStr );
    QString bwlSr = baseValue( "baseline" );
    if (measureStr == "Nucleic Acid" || measureStr == "Protein" ||
            measureStr == "Cell Culture") {

        if (measureStr == "Nucleic Acid") {
            QString wlStr = methodValue( "wave" );
            QString opStr = QString::number( m_pAbsoDataModel->opticalPath() );
            QString coefStr = methodValue( "coef" );
            QString concStr = m_pAbsoDataModel->calculateNaConc( coefStr, opStr, wlStr );
            QString coef = transformUnit( "ng/uL", methodValue( "unit" ) );
            double conc = concStr.toDouble() * coef.toDouble();
            if (conc < 0) {
                conc = 0;
            }
            concStr = QString::number( conc );
            rcdStr.append( "," );
            rcdStr.append( concStr );
        } else if (measureStr == "Protein") {
            QString wlStr = methodValue( "wave" );
            QString coefStr = methodValue( "coef" );
            QString concStr = m_pAbsoDataModel->calculatePtConc( coefStr, wlStr );
            QString coef = transformUnit( "mg/mL", methodValue( "unit" ) );
            double conc = concStr.toDouble() * coef.toDouble();
            if (conc < 0) {
                conc = 0;
            }
            concStr = QString::number( conc );
            rcdStr.append( "," );
            rcdStr.append( concStr );
        }

        rcdStr.append( "," );
        rcdStr.append( methodValue( "type" ) );

        if (measureStr == "Cell Culture") {
            rcdStr.append( "," );
            rcdStr.append( methodValue( "wave" ) );
        } else {
            rcdStr.append( "," );
            rcdStr.append( methodValue( "coef" ) );

            rcdStr.append( "," );
            rcdStr.append( methodValue( "unit" ) );
        }
    }
    if (measureStr == "Dynamics") {
        rcdStr.append( "," );
        rcdStr.append( methodValue( "target" ) );
        rcdStr.append( "," );
        rcdStr.append( methodValue( "times" ) );
    }

    QStringList coefList;
    QStringList watchList;
    if (measureStr == "UV-VIS") {

        coefList.append( methodValue( "Coef1" ) );
        coefList.append( methodValue( "Coef2" ) );
        coefList.append( methodValue( "Coef3" ) );
        coefList.append( methodValue( "Coef4" ) );
        coefList.append( methodValue( "Coef5" ) );

        QString opStr = QString::number( m_pAbsoDataModel->opticalPath() );
        watchList = m_pAbsoDataModel->watchValues( coefList, m_watchLabels, opStr );
        for (int i = 0; i < m_watchLabels.size(); i ++) {

            rcdStr.append( "," );
            QString coefStr = coefList.at( i );
            rcdStr.append( coefStr );

            rcdStr.append( "," );
            QString labelStr = m_watchLabels.at( i );
            rcdStr.append( labelStr );

            rcdStr.append( "," );
            QString watchStr = watchList.at( i );
            rcdStr.append( watchStr );
        }
    } else {
        watchList = m_pAbsoDataModel->watchValues( m_watchLabels );
        for (int i = 0; i < watchList.size(); i ++) {
            QString watchStr = watchList.at( i );
            rcdStr.append( "," );
            rcdStr.append( watchStr );
        }
    }

    values.clear();
    if (measureStr != "Dynamics") {

        fileName.clear();
        fileName = QString( "%1.csv" ).arg( QDateTime::currentDateTime().toString("yyyyMMddhhmmss") );
        rcdStr.append( "," );
        rcdStr.append( fileName );

        QVector<double> x;
        QVector<double> y;
        data( x, y );

        QString dataStr;
        QStringList dataList;
        for (int i = 0; i < x.size(); i ++) {
            dataStr = QString( "data:,%1,%2" ).arg( x.at( i ) ).arg( y.at( i ) );
            dataList.append( dataStr );
        }

        QString recordStr = "record:,";
        recordStr.append( rcdStr );
        values.append( recordStr );
        values.append( dataList );
    }
    //lt:去注释*/
}

/**
 * @brief SettingDataModel::transformUnit
 * @param unit1
 * @param unit2
 * @return
 */
QString SettingDataModel::transformUnit(QString unit1, QString unit2) {

    int coef1 = transformCoef( unit1 );
    if (0 == coef1) {
        return "NULL";
    }

    int coef2 = transformCoef( unit2 );
    if (0 == coef2) {
        return "NULL";
    }

    double proption = (double)coef1/(double)coef2;
    return QString::number( proption );
}

/**
 * @brief FittingView::transformCoef 获取转换系数
 * @param unit 单位
 * @return 系数
 */
int SettingDataModel::transformCoef(QString unit) {
    int coef = 0;
    switch( m_unitStrList.indexOf( unit ) ) {
    case 0:
    case 2:
    case 5:
        coef = 1000;
        break;
    case 1:
    case 4:
        coef = 1;
        break;
    case 3:
        coef = 1000000;
        break;
    default:
        break;
    }

    return coef;
}
