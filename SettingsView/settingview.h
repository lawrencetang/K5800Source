#ifndef SETTINGVIEW_H
#define SETTINGVIEW_H

#include <QFrame>

namespace Ui {
class SettingView;
}

class NaDialog;
class PtDialog;
class KmDialog;
class UvDialog;
class DyDialog;
class CcDialog;
class MaDialog;
class SettingDataModel;
class SettingView : public QFrame
{
    Q_OBJECT

public:
    explicit SettingView(QWidget *parent = 0);
    ~SettingView();

    int getChannelNumber();
    void setAutoCheckIamge(bool ok);
    void hideDialogs();
    QString selectedType();
    bool isAutoMeasure();
    inline QList<SettingDataModel *> dataModelList() {
        return m_dataModelList;
    }
    inline bool cuvetteEnable() {
        return m_cuvetteEnable;
    }
    void clear();
    bool isNeedBlank() {
        return m_isNeedBlank;
    }
    void directShowDialog();//ltj
    //void idadd();//ltj
    void setting_waiting(int timeout);//lt:让子弹飞一会
    void settingwavelength();


signals:
    void hideView(int status);
    void changeTitle(QString title);

public slots:
    void subDirChanged(QString subDir);
    void changeAutoMeasure();
    void changeId(QString recordSendvalue);


private slots:
    void add();
    void edit();
    void remove();
    void ok();
    void modify();

    void updateOp(bool ok);
    void changeMeasureWay();

    void displaySettingInfo();
    void clearid();

private:
    Ui::SettingView *ui;
    int m_editRow;
    bool m_modifyStatus;
    bool m_isNeedBlank;

    NaDialog *m_pNaDialog;
    PtDialog *m_pPtDialog;
    KmDialog *m_pKmDialog;
    UvDialog *m_pUvDialog;
    DyDialog *m_pDyDialog;
    CcDialog *m_pCcDialog;
    MaDialog *m_pMaDialog;

    QString m_rootDir;
    QString m_subDir;

    int m_channelNumber;
    bool m_cuvetteEnable;
    QStringList m_headerList;
    QList<SettingDataModel *> m_dataModelList;

    QString baseParamsStr();
    QString dcMotorStr();
    void clearDataList();

    int keyColumn(QString headerStr);
    void createInfo();
    void showDialog(QString paramStr = "", QString watchStr = "");
    void replaceData(QStringList data);
    void insertData(QStringList data);
    void clearModel();
    void clearTable();
    void updateOptical();
    void updateHeaders(QStringList headerLavbels);

    QString getRootDirEnStr();
    QString getSubDirEnstr();

    void initializeSystem();
    void initializeWidget();
};

#endif // SETTINGVIEW_H
