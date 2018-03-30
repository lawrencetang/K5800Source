#ifndef CCDIALOG_H
#define CCDIALOG_H

#include <QDialog>

namespace Ui {
class CcDialog;
}

class CcDialog : public QDialog
{
    Q_OBJECT

public:
    explicit CcDialog(QWidget *parent = 0);
    ~CcDialog();

    inline QString paramStr() {
        return m_paramStr;
    }

    inline QString watchStr() {
        return m_watchStr;
    }

    void defaultInfo();
    void settinghidedlg();
    bool m_showdialogflag;

signals:
    void okBtnClicked();

public slots:
    void showDialog(QString paramStr = "");
    void hideDialog();

private slots:
    void typeChanged(int id);

private:
    Ui::CcDialog *ui;
    QStringList m_typeList;
    QStringList m_waveList;
    QString m_paramStr;
    QString m_watchStr;

    void saveData();
    void initializeDialog(QString paramStr);
    void initializeSystem();
    void initializeWidget();
};

#endif // CCDIALOG_H
