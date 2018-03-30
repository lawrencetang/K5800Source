#ifndef KMDIALOG_H
#define KMDIALOG_H

#include <QDialog>

namespace Ui {
class KmDialog;
}

class KmDialog : public QDialog
{
    Q_OBJECT

public:
    explicit KmDialog(QWidget *parent = 0);
    ~KmDialog();

    inline QString paramStr() {
        return m_paramStr;
    }
    inline QString watchStr() {
        return m_watchStr;
    }

    void defaultInfo();
    void settinghidedlg();
    bool m_showdialogflag;
    int m_fixedwavelength;//ltj:传递给settingview的固定波长参数

signals:
    void okBtnClicked();

public slots:
    void showDialog(QString paramStr = "");
    void hideDialog();

private slots:
    void typeChanged(int id);

private:
    Ui::KmDialog *ui;

    QStringList m_typeList;
    QStringList m_waveList;
    QString m_paramStr;
    QString m_watchStr;

    void saveData();
    void initializeDialog(QString paramStr);
    void initializeSystem();
    void initializeWidget();
};

#endif // KMDIALOG_H
