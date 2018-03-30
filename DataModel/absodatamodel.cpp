#include "absodatamodel.h"
#include "blankdatamodel.h"

#include <QDir>
#include <QDebug>
#include <QSettings>
#include <QMessageBox>

AbsoDataModel::AbsoDataModel(QObject *parent)
    : QObject(parent) {

    m_opticalPath = 0.5;
    m_pBlankDataModel = NULL;
    m_oData.clear();

    QString filename = QDir::currentPath() + "/configure/system.ini";
    QSettings *configIniReader = new QSettings( filename, QSettings::IniFormat );
    m_factor = configIniReader->value( "/System/Factor" ).toDouble();
    if (m_factor <= 0) {
        m_factor = 1;
    }//lt:系数为1

    m_smoothingWidth = configIniReader->value( "/System/Smoothing Width" ).toInt();
    if (m_smoothingWidth <= 0) {
        m_smoothingWidth = 3;
    } else {
        if (m_smoothingWidth%2 == 0) {
            m_smoothingWidth += 1;
        }
    }//lt:平滑宽度为11
    delete configIniReader;
    configIniReader = NULL;
}

/**
 * @brief AbsoDataModel::setOpticalPath 设置光程
 * @param op
 */
void AbsoDataModel::setOpticalPath(double op) {
    m_opticalPath = op;
}//lt:未用

/**
 * @brief AbsoDataModel::opticalPath 获取光程
 * @return
 */
double AbsoDataModel::opticalPath() {
    return m_opticalPath;
}

/**
 * @brief AbsoDataModel::setBlankDataModel 设置BlankDataModel
 * @param dataModel BlankDataModel
 */
void AbsoDataModel::setBlankDataModel(BlankDataModel *dataModel) {
    m_pBlankDataModel = dataModel;
}

/**
 * @brief AbsoDataModel::blankDataModel 获取BlankDataModel
 * @return BlankDataModel
 */
BlankDataModel *AbsoDataModel::blankDataModel() {
    return m_pBlankDataModel;
}

/**
 * @brief AbsoDataModel::setData 设置检测到的数据(转换成吸光度)
 * @param keys 波长值
 * @param values 光强值
 * @return 是否成功, 失败原因：
 *                   1. Blank中与检测的光程不匹配;
 */
bool AbsoDataModel::setData(QVector<int> keys,
                            QVector<double> values) {

    QVector<double> absosValue;
    if (NULL == m_pBlankDataModel) {
        return false;
    } else {
        absosValue = m_pBlankDataModel->absorbance( m_opticalPath, values );//lt:value是光谱读取的y轴值
        if (absosValue.isEmpty()) {
            return false;
        }
    }

    QVector<double> absos;
    avgSlidingFilter( m_smoothingWidth, absosValue, absos );//lt:以每个吸光度数据为准中心平均返回absos,m_smoothingwidth=11

    m_oData.clear();
    int size = absos.size();
    int index = keys.indexOf( m_bwl );//lt:基准波长的波长值的指数
    double zero = 0;
    if (index != -1) {
        if (index != 850) {
            zero = absos.at( index );//lt:基准波长的吸光度值
        }
        else {
            zero = 0;//ltj:在细胞液和全波长下基准波长的吸光度值为0
        }

    }

    for (int i = 0; i < keys.size(); i ++) {
        int k = keys.at( i );
        double v = 0.0;
        if (i < size) {
            v = (absos.at( i ) - zero) * m_factor * m_coef;//lt:进行了系数处理,要减去吸光度(关键)m_factor=1
        }//lt:注意
        m_oData.insert( k, v );
    }

    return true;
}

/**
 * @brief AbsoDataModel::setData 设置检测到的数据(转换成吸光度)
 * @param op 光程
 * @param keys 波长值
 * @param values 光强值
 * @return 是否成功, 失败原因：
 *                   1. Blank中与检测的光程不匹配;
 */
bool AbsoDataModel::setData(double op, int bwl, double coef,
                            QVector<int> keys, QVector<double> values) {
    m_bwl = bwl;
    m_opticalPath = op;
    m_coef = coef;
    bool ok = setData( keys, values );
    return ok;
}

/**
 * @brief AbsoDataModel::absorbance
 * @param wlStr
 * @param bwlStr
 * @return
 */
QString AbsoDataModel::absorbance(QString wlStr) {

    QString resultStr = "NULL";
    if (wlStr != "NULL") {
        wlStr = wlStr.replace( "A", "" );
        int wl = wlStr.toInt();
        resultStr = absorbance( wl );//lt:得到固定波长下的长度
    }

    return resultStr;
}

/**
 * @brief AbsoDataModel::getWaveLength 获取波长列表
 * @return  波长数组
 */
QVector<double> AbsoDataModel::getWaveLength() {
    QList<int> keys = m_oData.keys();
    QVector<double> wLs;
    for (int i = 0; i < keys.size(); i ++) {
        wLs.append( keys.at( i ) );
    }

    return wLs;
}

/**
 * @brief AbsoDataModel::getAbsorbance 获取吸光值列表
 * @param bwl 基准点的波长值,如340
 * @return 吸光值列表
 */
QVector<double> AbsoDataModel::getAbsorbance() {
    QList<double> values = m_oData.values();
    QVector<double> absos;
    for (int i = 0; i < values.size(); i ++) {
        absos.append( values.at( i ) );
    }
    return absos;
}

/**
 * @brief AbsoDataModel::watchValue 获取需要观察的数据
 * @param labels 例如：“280”,“260”，“280/260”...
 * @param bwlStr 基准线的值
 * @return 返回光差值的double形式
 */
QStringList AbsoDataModel::watchValues(QStringList labels) {

    QStringList values;
    for (int i = 0; i < labels.size(); i ++) {
        QString valueStr = labels.at( i );
        if (valueStr.contains( "/" )) {
            values.append( calculatePurity( valueStr ) );//lt:有/做下除法
        } else {
            values.append( absorbance( valueStr ) );
        }
    }

    return values;
}

/**
 * @brief AbsoDataModel::watchValues
 * @param coefs
 * @param labels
 * @param bwlStr
 * @return
 */
QStringList AbsoDataModel::watchValues(QStringList coefs, QStringList labels, QString opStr) {

    QStringList values;
    for (int i = 0; i < labels.size(); i ++) {
        QString valueStr = labels.at( i );
        if (valueStr != "NULL") {
            valueStr = valueStr.replace( "A", "" );
            QString absoStr = absorbance( valueStr );//lt:先观测写的值和后面data各项的原始数据无关
            QString coefStr = coefs.at( i );
            //QMessageBox::warning(0, "opstr", opStr + "  " +absoStr, QMessageBox::Ok);//ltj
            values.append( QString::number( absoStr.toDouble()/* * coefStr.toDouble() * 10 / opStr.toDouble() */) );//ltg待讨论
        } else {
            values.append( "NULL" );
        }
    }//lt:全波长的watchvalue中各参数的值处理

    return values;
}

/**
 * @brief AbsoDataModel::calculateNaConc 计算核酸浓度
 * @param coef 系数
 * @param op 光程
 * @param wl 波长
 * @return 核酸浓度
 */
QString AbsoDataModel::calculateNaConc(double coef, double op, int wl) {

    double abso = absorbance( wl ).toDouble();//lt:获取固定波长下的浓度值？
    QString concStr = "NULL";
    if (0 != op) {
        double conc = abso * coef/* 10 / op*/;
        concStr = QString::number( conc );
    }
    return concStr;
}

/**
 * @brief AbsoDataModel::calculateNaConc 计算核酸浓度
 * @param coefStr 系数字符串
 * @param opStr 光程字符串
 * @return 核酸浓度
 */
QString AbsoDataModel::calculateNaConc(QString coefStr, QString opStr, QString wlStr) {

    int wl = wlStr.replace( "A", "").toInt();//lt:波长没有A
    double coef = coefStr.toDouble();//lt:系数
    double op = opStr.toDouble();//lt:光程

    return calculateNaConc( coef, op, wl );
}

/**
 * @brief AbsoDataModel::calculatePtConc 计算蛋白浓度
 * @param coef 参数
 * @param wl 波长
 * @return 蛋白浓度
 */
QString AbsoDataModel::calculatePtConc(double coef, int wl) {

    double abso = absorbance( wl ).toDouble();
    QString concStr = "NULL";
    if (0 != coef) {
        double conc = abso * 10 / coef;
        concStr = QString::number( conc );
    }
    return concStr;
}

/**
 * @brief AbsoDataModel::calculatePtConc 计算蛋白浓度
 * @param coefStr 参数字符串
 * @param wlStr 波长字符串
 * @return 蛋白浓度
 */
QString AbsoDataModel::calculatePtConc(QString coefStr, QString wlStr) {
    int wl = wlStr.replace( "A", "" ).toInt();
    double coef = coefStr.toDouble();
    return calculatePtConc( coef, wl );
}

/**
 * @brief AbsoDataModel::avgSlidingFilter
 * @param width
 * @param y
 */
void AbsoDataModel::avgSlidingFilter(int width,
                                     QVector<double> yInput, QVector<double> &yOutput) {

    int size = yInput.size();
    if (size == 0 && size < width) {
        yOutput.clear();
        //yOutput.append( yInput );
        yOutput<<( yInput );
        return;
    }
    QVector<double> data;

    /*
    data.append( yInput.mid( 0, width/2 ) );//lt:截取qvector,其实为0，长度是width/2
    data.append( yInput );
    data.append( yInput.mid( size - width/2, width/2) );
    */
    data<<( yInput.mid( 0, width/2 ) );//lt:截取qvector,其实为0，长度是width/2
    data<<( yInput );
    data<<( yInput.mid( size - width/2, width/2) );//lt:放5个在前面，放5个在后面


    yOutput.clear();
    double sum = 0.0;
    for (int i = 0; i < yInput.size(); i ++) {
        sum = 0;
        for (int w = 0; w < width; w ++) {
            sum += data.at( i + w );
        }
        yOutput.append( sum/(double)width );
    }
}

/**
 * @brief AbsoDataModel::absorbance 获取固定波长下的浓度值
 * @param wl 固定波长
 * @return 浓度值
 */
QString AbsoDataModel::absorbance(int wl) {

    QString absoStr = "NULL";
    if (m_oData.contains( wl ) && wl > 0) {
        double abso = m_oData.value( wl );
        absoStr = QString::number( abso );
    }
    return absoStr;
}

/**
 * @brief AbsoDataModel::calculatePurity 计算纯度(A260/A230、A260/A280)
 * @param label  数据字符串形式, 例如A260/A230
 * @return 纯度
 */
QString AbsoDataModel::calculatePurity(QString label) {

    QStringList valueList = label.split( "/",  QString::SkipEmptyParts );
    QString numeratorStr = valueList.at( 0 );
    QString denominatorStr = valueList.at( 1 );

    numeratorStr = numeratorStr.replace( "A", "" );
    denominatorStr = denominatorStr.replace( "A", "" );

    double numeratorConc = absorbance( numeratorStr ).toDouble();
    double denominatorConc = absorbance( denominatorStr ).toDouble();

    QString purityStr = "NULL";
    if (0 != denominatorConc) {
        double purity = numeratorConc/denominatorConc;
        purityStr = QString::number( purity );
    }

    return purityStr;
}


