#include "accredit.h"
#include <QFile>
#include <QDir>
#include <QMessageBox>
#include <QtDebug>

Accredit::Accredit()
{
}

Accredit::~Accredit()
{
}

bool Accredit::IsAccreditLevel(int nAccreditLevel)
{
    int n = nAccreditLevel;
    n &= (~ACCREDIT_LEVEL_STARTTIME);
    n &= (~ACCREDIT_LEVEL_ENDTIME);
    n &= (~ACCREDIT_LEVEL_UPDATEFILE);
    n &= (~ACCREDIT_LEVEL_UPDATEREGISTER);
    n &= (~ACCREDIT_LEVEL_SECOND);
    return (n == 0);
}

bool Accredit::IsAccreditLevelStartTime(int nAccreditLevel)
{
    return (nAccreditLevel & ACCREDIT_LEVEL_STARTTIME) == ACCREDIT_LEVEL_STARTTIME;
}

bool Accredit::IsAccreditLevelEndTime(int nAccreditLevel)
{
    return (nAccreditLevel & ACCREDIT_LEVEL_ENDTIME) == ACCREDIT_LEVEL_ENDTIME;
}

bool Accredit::IsAccreditLevelUpdateFile(int nAccreditLevel)
{
    return (nAccreditLevel & ACCREDIT_LEVEL_UPDATEFILE) == ACCREDIT_LEVEL_UPDATEFILE;
}

bool Accredit::IsAccreditLevelUpdateRegister(int nAccreditLevel)
{
    return (nAccreditLevel & ACCREDIT_LEVEL_UPDATEREGISTER) == ACCREDIT_LEVEL_UPDATEREGISTER;
}

bool Accredit::IsAccreditLevelSecond(int nAccreditLevel)
{
    return (nAccreditLevel & ACCREDIT_LEVEL_SECOND) == ACCREDIT_LEVEL_SECOND;
}

/**
 * @brief Accredit::Accredited
 *          对传入的数据进行加密
 * @param strKey        ：加密用Key
 * @param variant       ：加密前数据
 * @param dataType      ：加密前数据类型，包括DATA_TYPE_INT、DATA_TYPE_DATE、DATA_TYPE_DATETIME
 * @param encodeValue   ：存放加密后的数据
 * @param encodeLen     ：加密后的数据总长度
 * @return              ：加密后的数据长度，传入数据错误返回0
 */
int Accredit::Accredited(QString strKey, QVariant variant, int dataType, char *encodeValue, int encodeLen)
{
    /*
     * 处理key
     */
    unsigned char key[16];
    memset(key, 0, 16);
    memcpy(key, strKey.toLatin1().data(), strKey.size() > 16 ? 16 : strKey.size());

    /*
     * 把传入数据转为char[]
     */
    QString str = "";
    switch (dataType) {
    case DATA_TYPE_INT: {
        bool ok;
        int nAccreditLevel = variant.toInt(&ok);
        if (ok && IsAccreditLevel(nAccreditLevel)) {
            str = QString::number(nAccreditLevel);
        }
        break;
    }
    case DATA_TYPE_DATE: {
        QDate date = variant.toDate();;
        if (date.isValid()) {
            str = date.toString(DATE_FORMAT);
        }
        break;
    }
    case DATA_TYPE_DATETIME: {
        QDateTime datetime = variant.toDateTime();
        if (datetime.isValid()) {
            str = datetime.toString(TIME_FORMAT);
        }
        break;
    }
    case DATA_TYPE_STRING: {
        str = variant.toString();
        break;
    }
    default:
        break;
    }
    if (str.isEmpty()) {
        return 0;
    }
    char mingwen[1024];
    memset(mingwen, 0, 1024);
    memcpy(mingwen, str.toLatin1().data(), str.toLatin1().size());

    /*
     * 加密
     */
    char l_cDist[1024];
    TAesClass *pTAesClass = new TAesClass;
    DWORD retLen = 0;
    pTAesClass->InitializePrivateKey(16, key);
    retLen = pTAesClass->OnAesEncrypt(mingwen, strlen(mingwen), (LPVOID)l_cDist);
    delete pTAesClass;

    /*
     * 返回加密后的结果
     * 加密后的结果中可能存在\0，因此不能用strlen(l_cDist)，需要用OnAesEncrypt的返回值长度
     */
    memset(encodeValue, 0, encodeLen);
    memcpy(encodeValue, l_cDist, retLen);
    return retLen;
}

/**
 * @brief Accredit::Accredited
 *          生成授权信息
 * @param strKey        ：授权Key
 * @param nAccreditLevel：授权级别
 * @param startDate     ：开始日期
 * @param endDate       ：结束日期
 * @param updateDate    ：上次启动日期
 * @param encodeValue   ：返回结果存放位置
 * @param encodeLen     ：返回结果最大长度
 * @return              ：实际授权信息长度
 */
int Accredit::Accredited(QString strKey,
                         int nAccreditLevel, QString strCompany, QString strSoftName, int nAccreditVersion,
                         QDateTime startDate, QDateTime endDate, QDateTime updateDate, char *encodeValue, int encodeLen)
{
    QString str;
    bool bIsTimeFormat = IsAccreditLevelSecond(nAccreditLevel);//lt:通过授权等级判断使用的时间格式
    QString dateFormat = bIsTimeFormat ? TIME_FORMAT : DATE_FORMAT;

    str.append(QString::number(nAccreditLevel)).append("-").
            append(strCompany).append("-").
            append(strSoftName).append("-").
            append(QString::number(nAccreditVersion)).append("-").
            append(startDate.toString(dateFormat)).append("-").
            append(endDate.toString(dateFormat)).append("-").
            append(updateDate.toString(dateFormat));

    return Accredited(strKey, QVariant(str), DATA_TYPE_STRING, encodeValue, encodeLen);
}

/**
 * @brief Accredit::IsAccredited
 *          验证授权信息
 *          此函数对于注册表信息不判断
 * @param strKey    ：key
 * @param byteArray ：密文信息
 * @param variant   ：存放解密后的数据
 * @param dataType  ：解密后的数据类型
 * @return          ：解密是否成功
 */
bool Accredit::IsAccredited(QString strKey, QByteArray byteArray, QVariant &variant, int dataType)
{
    unsigned char key[16];
    memset(key, 0, 16);//lt:清零
    memcpy(key, strKey.toLatin1().data(), strKey.size() > 16 ? 16 : strKey.size());//lt:strKey=key-ole-abcdefgh,单字节编码,拷贝16个字符

    char miwen[1024];
    int miwenLen = byteArray.size();
    if (miwenLen == 0) {
        return false;
    }
    memset(miwen, 0, 1024);
    // 由于密文中可能含有'\0'，因此不用memcpy + byteArray.data()的方式
    for (int i = 0; i < miwenLen; i++) {
        miwen[i] = byteArray.at(i);
    }//lt:拷贝byteArray到miwen,使用memcpy方式若byteArray中有\0则byteArray.size()返回值为\0前的size+1

    // 解密
    char l_cDist[1024];
    TAesClass *pTAesClass = new TAesClass;
    pTAesClass->InitializePrivateKey(16, key);
    pTAesClass->OnAesUncrypt(miwen, miwenLen, (LPVOID)l_cDist);
    delete pTAesClass;

    // 解密后的内容转换
    bool bRet = false;
    variant.clear();
    switch (dataType) {
    case DATA_TYPE_INT: {
        bool isOk;
        int nAccreditLevel = QString(l_cDist).toInt(&isOk);
        if (isOk) {
            variant.setValue(nAccreditLevel);
            bRet = true;
        }
        break;
    }
    case DATA_TYPE_DATE: {
        QDate date = QDate::fromString(QString(l_cDist), DATE_FORMAT);
        if (date.isValid()) {
            variant.setValue(date);
            bRet = true;
        }
        break;
    }
    case DATA_TYPE_DATETIME: {
        QDateTime datetime = QDateTime::fromString(QString(l_cDist), TIME_FORMAT);
        if (datetime.isValid()) {
            variant.setValue(datetime);
            bRet = true;
        }
        break;
    }
    case DATA_TYPE_STRING: {
        variant.setValue(QString(l_cDist));
        bRet = true;
        break;
    }
    default:
        break;
    }
    return bRet;
}


/**
 * @brief Accredit::IsAccredited
 *          验证授权信息
 *          此函数对于注册表信息不判断
 * @param strKey        ：授权Key
 * @param byteArray     ：授权文件或内容
 * @param nAccreditLevel：返回授权级别
 * @param startDate     ：返回授权开始日期
 * @param endDate       ：返回授权结束日期
 * @param updateDate    ：返回最近启动日期
 * @return              ：0：授权有效
 *                      ：< 0：授权文件无效：-1(字段各个数有误)、-2(授权级别不是数字)、-3(开始日期、结束日期、更新日期不是日期格式)
 *                      ：> 0：授权文件失效：1(startDate失效)、2(endDate失效)、3(updateDate失效)
 */
int Accredit::IsAccredited(QString strKey, QByteArray byteArray, int *nAccreditLevel,
                           QString &strCompany, QString &strSoftName, int *nAccreditVersion,
                           QDateTime &startDate, QDateTime &endDate, QDateTime &updateDate)
{
    QVariant variant;
    IsAccredited(strKey, byteArray, variant, DATA_TYPE_STRING);//lt:DATA_TYPE_STRING=0x04

    // 解密后的内容转换
    QStringList strList = variant.toString().split('-');
    if (strList.size() != 7) {
        return -1;
    }//lt:解密信息不是7个

    QString str;
    str = strList.at(0);
    bool ok;
    *nAccreditLevel = str.toInt(&ok);
    if (!ok) {
        return -2;
    }//lt:返回字符串转换成整形值（十进制），成功ok为true

    bool bIsTimeFormat = ((*nAccreditLevel) & ACCREDIT_LEVEL_SECOND) == ACCREDIT_LEVEL_SECOND;//lt:0x80，通过授权级别确定时间格式
    strCompany = strList.at(1);
    strSoftName = strList.at(2);
    str = strList.at(3);
    *nAccreditVersion = str.toInt();
    str = strList.at(4);
    startDate = QDateTime::fromString(QString(str), bIsTimeFormat ? TIME_FORMAT : DATE_FORMAT);
    str = strList.at(5);
    endDate = QDateTime::fromString(QString(str), bIsTimeFormat ? TIME_FORMAT : DATE_FORMAT);
    str = strList.at(6);
    updateDate = QDateTime::fromString(QString(str), bIsTimeFormat ? TIME_FORMAT : DATE_FORMAT);
    if (!startDate.isValid() || !endDate.isValid() || !updateDate.isValid()) {
        return -3;
    }//lt:开始时间，结束时间，更新时间格式是否正确

    QDateTime currentDate = QDateTime::currentDateTime();
    // 根据授权级别，判断是否有效
    //if (((*nAccreditLevel) & ACCREDIT_LEVEL_STARTTIME) == ACCREDIT_LEVEL_STARTTIME) {
        if (currentDate.operator <(startDate)) {
            return 1;
        }
    //}

    //if (((*nAccreditLevel) & ACCREDIT_LEVEL_ENDTIME) == ACCREDIT_LEVEL_ENDTIME) {
        if (currentDate.operator >(endDate)) {
            return 2;
        }
    //}

    //if (((*nAccreditLevel) & ACCREDIT_LEVEL_UPDATEFILE) == ACCREDIT_LEVEL_UPDATEFILE) {
        if (updateDate.operator <(startDate) || updateDate.operator >(endDate)) {
            return 3;
        }
    //}

    return 0;
}

int Accredit::IsAccredited(QString strKey, QString filePath, int *nAccreditLevel,
                           QString &strCompany, QString &strSoftName, int *nAccreditVersion,
                           QDateTime &startDate, QDateTime &endDate, QDateTime &updateDate)
{
    QByteArray byteArray;
    QFile file(filePath);
    if (file.exists() && file.open(QIODevice::ReadOnly)) {
        byteArray = file.readAll();//lt:将密文读到byteArray中
        file.close();
    }//lt:判断文件是否能打开
    if (byteArray.size() == 0) {
        return -1;
    }
    return IsAccredited(strKey, byteArray, nAccreditLevel, strCompany, strSoftName, nAccreditVersion, startDate, endDate, updateDate);
}
