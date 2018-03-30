#ifndef PTDIALOG_H
#define PTDIALOG_H

#include <QDialog>

namespace Ui {
class PtDialog;
}

class PtDialog : public QDialog
{
    Q_OBJECT

public:
    explicit PtDialog(QWidget *parent = 0);
    ~PtDialog();

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
    Ui::PtDialog *ui;
    QStringList m_typeList;
    QStringList m_coefList;
    QString m_paramStr;
    QString m_watchStr;

    void saveData();
    void initializeDialog(QString paramStr);
    void initializeSystem();
    void initializeWidget();
};

#endif // PTDIALOG_H
