#include "blankdatamodel.h"
#include "specdatamodel.h"

#include "math.h"
#include <QDebug>
#include <QVector>

const double m_stdOpticalPath = 10; // 10mm光程

BlankDataModel::BlankDataModel(QObject *parent)
    : QObject(parent) {

}

/**
 * @brief BlankDataModel::absorbance 获取吸光度
 * @param op 光程
 * @param intensity 光强数据
 * @return 吸光度的值
 */
QVector<double> BlankDataModel::absorbance(double op,
                                           QVector<double> intensity) {

    SpecDataModel *specData = NULL;
    for (int i = 0; i < m_data.size(); i ++) {
        SpecDataModel *specDataTemp = m_data.at( i );
        if (specDataTemp->m_opticalPath == op) {
            specData = specDataTemp;//lt:当前模型内的光程数据成员等于传递进入的光程参数，调入该光谱数据模型
            break;
        }
    }

    QVector<double> absos;
    if (NULL != specData) {
        int size = intensity.size();//lt:intensity是光谱仪测出的值
        QVector<double> baseIntensity = specData->lightIntensity();//lt:从光谱数据模型中获取空白光强
        for (int i = 0; i < baseIntensity.size(); i ++) {

            double b = baseIntensity.at( i ) + 10;
            double v = 1;
            if (i < size) {
                v = intensity.at( i ) + 10;
                if (v == 0) {
                    v = 1;
                }
            }
            double diff = 0.0;
            if (0 != v) {
                diff = b/v;
            }
            double abso = 0.0;
            if (0 != diff) {
                abso = m_stdOpticalPath/op * log10( diff );
            }
            absos.append( abso );
        }
    }

    return absos;
}

/**
 * @brief BlankDataModel::blankData
 * @param op
 * @param x
 * @param y
 */
bool BlankDataModel::blankData(double op,
                               QVector<double> &x, QVector<double> &y) {
    SpecDataModel *specData = NULL;
    for (int i = 0; i < m_data.size(); i ++) {
        SpecDataModel *specDataTemp = m_data.at( i );
        if (specDataTemp->m_opticalPath == op) {
            specData = specDataTemp;//lt:当前模型内的光程数据成员等于传递进入的光程参数
            break;
        }
    }

    if (NULL != specData) {
        x.clear();
        y.clear();
        /*
        x.append( specData->waveLength() );
        y.append( specData->lightIntensity() );
        */
        x<<( specData->waveLength() );//lt:以升序从光谱数据模型返回的波长值
        y<<( specData->lightIntensity() );//lt:以升序从光谱数据模型返回的光强值
        return true;
    }

    return false;
}

/**
 * @brief BlankDataModel::append
 * @param data
 */
void BlankDataModel::append(SpecDataModel *data) {
    m_data.append( data );
}

/**
 * @brief BlankDataModel::remove 删除当前光程下的数据
 * @param op 光程
 */
void BlankDataModel::remove(double op) {
    for (int i = 0; i < m_data.size(); i ++) {
        SpecDataModel *specDataTemp = m_data.at( i );//lt:获得光谱数据模型
        if (specDataTemp->m_opticalPath == op) {
            m_data.removeAt( i );//lt:若光谱数据模型中的光程等于传递进入的光程
            //delete specDataTemp;
            //specDataTemp = NULL;
            break;
        }
    }
}

/**
 * @brief BlankDataModel::clear
 */
void BlankDataModel::clear() {
    for (int i = m_data.size() - 1; i >= 0; i --) {
        SpecDataModel *specData = m_data.takeAt( i );
        delete specData;
        specData = NULL;
    }
}


