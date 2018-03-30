#include "specdatamodel.h"

SpecDataModel::SpecDataModel(double opticalPath, QObject *parent)
    : QObject(parent) {

    m_opticalPath = opticalPath;
    m_data.clear();
}

/**
 * @brief SpecDataModel::setData 设置数据
 * @param keys 波长列表
 * @param values 光强列表
 */
void SpecDataModel::setData(QVector<int> keys,
                            QVector<double> values) {

    m_data.clear();
    for (int i = 0; i < keys.size(); i ++) {
        m_data.insert( keys.at( i ), values.at( i ) );
    }
}//lt:将空白读取光谱的x,y放入光谱数据模型的m_data中,y是光强数据

/**
 * @brief SpecDataModel::waveLength 获取波长列表
 * @return 波长列表
 */
QVector<double> SpecDataModel::waveLength() {
    QList<int> keys = m_data.keys();//lt:以键的升序返回一个包含map所有值得队列
    QVector<double> wLs;
    for (int i = 0; i < keys.size(); i ++) {
        wLs.append( keys.at( i ) );
    }

    return wLs;
}

/**
 * @brief SpecDataModel::lightIntensity 获取光强列表
 * @return 光强列表
 */
QVector<double> SpecDataModel::lightIntensity() {
    QList<double> value = m_data.values();
    QVector<double> lIs;
    for (int i = 0; i < value.size(); i ++) {
        lIs.append( value.at( i ) );
    }

    return lIs;
}
