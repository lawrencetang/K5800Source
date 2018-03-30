#ifndef NADIALOG_H
#define NADIALOG_H

#include <QDialog>

namespace Ui {
class NaDialog;
}

class NaDialog : public QDialog
{
    Q_OBJECT

public:
    explicit NaDialog(QWidget *parent = 0);
    ~NaDialog();

    inline QString paramStr() {
        return m_paramStr;
    }

    inline QString watchStr() {
        return m_watchStr;
    }

    void defaultInfo();
    void settinghidedlg();
    //void saveData();
    bool m_showdialogflag;

signals:
    void okBtnClicked();

public slots:
    void showDialog(QString paramStr = "");
    void hideDialog();

private slots:
    void typeChanged(int id);

private:
    Ui::NaDialog *ui;
    QStringList m_typeList;
    QStringList m_coefList;

    QString m_paramStr;
    QString m_watchStr;

    void saveData();//ltg:为了在settingview中调用，改为public
    void initializeDialog(QString paramStr);
    void initializeSystem();
    void initializeWidget();
};

#endif // NADIALOG_H
