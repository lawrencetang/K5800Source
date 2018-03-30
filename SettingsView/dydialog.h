#ifndef DYDIALOG_H
#define DYDIALOG_H

#include <QDialog>

namespace Ui {
class DyDialog;
}

class DyDialog : public QDialog
{
    Q_OBJECT

public:
    explicit DyDialog(QWidget *parent = 0);
    ~DyDialog();

    inline QString paramStr() {
        return m_paramStr;
    }

    inline QString watchStr() {
        return m_watchStr;
    }

    void defaultInfo();

signals:
    void okBtnClicked();

public slots:
    void showDialog(QString paramStr = "", QString watchStr = "");
    void hideDialog();

private slots:
    void wathLabelEnable(bool ok);

private:
    Ui::DyDialog *ui;
    QString m_paramStr;
    QString m_watchStr;

    void saveData();
    void initializeDialog(QString paramStr);
    void initializeWatchs(QString watchStr);

    void initializeSystem();
    void initializeWidget();
};

#endif // DYDIALOG_H
