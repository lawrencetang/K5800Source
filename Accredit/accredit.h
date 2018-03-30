#ifndef ACCREDIT_H
#define ACCREDIT_H

#include "taesclass.h"
#include <QVariant>
#include <QDate>
#include <QDateTime>



/**
 * 验证开始日期
 */
#define ACCREDIT_LEVEL_STARTTIME        0x01

/**
 * 验证结束日期
 * 必选项
 */
#define ACCREDIT_LEVEL_ENDTIME          0x02

/**
 * 在验证文件中更新使用日期
 */
#define ACCREDIT_LEVEL_UPDATEFILE       0x04

/**
 * 在注册文件中更新使用日期
 */
#define ACCREDIT_LEVEL_UPDATEREGISTER   0x08

/**
 * 使用精确到秒的时间来授权
 */
#define ACCREDIT_LEVEL_SECOND           0x80

#define DATE_FORMAT "yyyy.M.d"
#define TIME_FORMAT "yyyy.M.d hh:mm:ss"

#define DATA_TYPE_INT       0x01
#define DATA_TYPE_DATE      0x02
#define DATA_TYPE_DATETIME  0x03
#define DATA_TYPE_STRING    0x04


class Accredit
{
public:
    Accredit();
    ~Accredit();

    static bool IsAccreditLevel(int nAccreditLevel);
    static bool IsAccreditLevelStartTime(int nAccreditLevel);
    static bool IsAccreditLevelEndTime(int nAccreditLevel);
    static bool IsAccreditLevelUpdateFile(int nAccreditLevel);
    static bool IsAccreditLevelUpdateRegister(int nAccreditLevel);
    static bool IsAccreditLevelSecond(int nAccreditLevel);

    // 加密函数
    static int Accredited(QString strKey, QVariant variant, int dataType, char *encodeValue, int encodeLen);
    static int Accredited(QString strKey, int nAccreditLevel, QString strCompany, QString strSoftName, int nAccreditVersion, QDateTime startDate, QDateTime endDate, QDateTime updateDate, char *encodeValue, int encodeLen);

    // 解密函数
    static bool IsAccredited(QString strKey, QByteArray byteArray, QVariant &variant, int dataType);
    static int IsAccredited(QString strKey, QByteArray byteArray, int *nAccreditLevel, QString &strCompany, QString &strSoftName, int *nAccreditVersion, QDateTime &startDate, QDateTime &endDate, QDateTime &updateDate);
    static int IsAccredited(QString strKey, QString filePath, int *nAccreditLevel, QString &strCompany, QString &strSoftName, int *nAccreditVersion, QDateTime &startDate, QDateTime &endDate, QDateTime &updateDate);

private:
};

#endif // ACCREDIT_H
