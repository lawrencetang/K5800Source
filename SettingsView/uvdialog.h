#ifndef UVDIALOG_H
#define UVDIALOG_H

#include <QDialog>

namespace Ui {
class UvDialog;
}

class UvDialog : public QDialog
{
    Q_OBJECT

public:
    explicit UvDialog(QWidget *parent = 0);
    ~UvDialog();

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
    void showDialog(QString paramStr = "");
    void hideDialog();

private slots:
    void wathLabelEnable(bool ok);

private:
    Ui::UvDialog *ui;
    QString m_watchStr;
    QString m_paramStr;

    void saveData();
    void initializeDialog(QString paramStr);
    void initializeSystem();
    void initializeWidget();
};

#endif // UVDIALOG_H
