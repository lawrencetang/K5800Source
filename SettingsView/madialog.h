#ifndef MADIALOG_H
#define MADIALOG_H

#include <QDialog>

namespace Ui {
class MaDialog;
}

class MaDialog : public QDialog
{
    Q_OBJECT

public:
    explicit MaDialog(QWidget *parent = 0);
    ~MaDialog();

    inline QString paramStr() {
        return m_paramStr;
    }

    inline QString watchStr() {
        return m_watchStr;
    }

    QString measureStr();

    void defaultInfo();

signals:
    void okBtnClicked();

public slots:
    void showDialog(QString paramStr = "", QString watchStr = "");
    void hideDialog();

private slots:
    void addDyeData();
    void typeChanged(int id);
    void measureChanged();

private:
    Ui::MaDialog *ui;

    QStringList m_typeNaList;
    QStringList m_coefNaList;
    QString m_waveNaStr;
    QStringList m_typePtList;
    QStringList m_coefPtList;
    QString m_wavePtStr;

    QStringList m_typeList;
    QStringList m_coefList;

    QString m_paramStr;
    QString m_watchStr;

    QList<QStringList> dyeDataList();
    void initializeDyeTable();

    void saveData();
    void initializeDialog(QString paramStr);
    void initializeTable(QString watchStr);
    void initializeSystem();
    void initializeWidget();
};

#endif // MADIALOG_H
