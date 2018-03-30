#ifndef LOGGER_H
#define LOGGER_H

#include <QObject>

class Logger : public QObject
{
    Q_OBJECT
public:
    explicit Logger(QObject *parent = 0);

    void outputMessage(QString modeStr, QString message);

signals:

public slots:

private:
    QByteArray toHexByteArray(QByteArray data);
};

#endif // LOGGER_H
