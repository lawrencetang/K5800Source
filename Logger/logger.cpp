#include "logger.h"

#include <QDir>
#include <QDebug>
#include <QDateTime>
#include <QTextStream>

Logger::Logger(QObject *parent) : QObject(parent) {

}

/**
 * @brief Logger::outputMessage
 * @param modeStr
 * @param message
 */
void Logger::outputMessage(QString modeStr, QString message) {

    QString path = QDir::currentPath() + "/log";
    QDir dir;
    if (!dir.exists( path )) {
        bool result = dir.mkdir( path );
        if (!result) {
            return;
        }
    }

    // 日志文件
    QString dateStr = QDate::currentDate().toString( "yyyy-MM-dd" );
    QString filename = QString( "%1/log%2.txt" ).arg( path ).arg( dateStr );
    QFile file( filename );
    if (!file.open(QIODevice::WriteOnly | QIODevice::Append)) {
        return;
    }

    QString textStr = QString( "[%1]%2:%3" ).arg( QDateTime::currentDateTime().toString( "yy-MM-dd hh:mm:ss" ) ).arg( modeStr ).arg( message );
    QTextStream out( &file );
    out.setCodec("GB2312");
    out << textStr << "\r\n";
    file.close();
}

/**
 * @brief Logger::toHexByteArray
 * @param data
 * @return
 */
QByteArray Logger::toHexByteArray(QByteArray data) {
    QByteArray hexByteArray;
    for (int i = 0; i < data.size(); i ++) {
        unsigned char value = (unsigned char)data.at(i);
        if (value < 0x10) {
            hexByteArray.append("0");
        }
        hexByteArray.append(QByteArray::number(value, 16).toUpper());
        if (i < data.size() - 1) {
            hexByteArray.append(" ");
        }
    }

    return hexByteArray;
}

