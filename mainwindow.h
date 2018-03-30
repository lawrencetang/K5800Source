#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class QTimer;
class Logger;
class SettingView;
class DataView;
class PlotView;
class RecordView;
class FittingView;
class ToolsView;
class CameraView;
class OligoCalculator;
class QPropertyAnimation;
class TempControlView;
class CheckView;
class Controller;
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    QString openDevice();

public slots:
    void ReceiveMessageFromOtherInstance(QStringList message);
    void focusChanged(QWidget* o, QWidget*n);
    void showOption(int id, bool ok);
    void switchPage();
    void switchPage(QString text);
    void exportPage();
    void printsPage();

    // 动画操作
    void setHeightCeof(double ceof);
    void animationFinished();
    void fileRead(QString type, QString filename);

    // 显示或隐藏设置视图
    void showSetingViwe();
    void hideSetingView(int status);
    void showSetingDialog();//ltj

    // 显示温控系统操作视图
    void showTempView(bool ok);
    void shutDown();

    // 检测相关
    void excuteBlank();
    void excuteMeasure();
    void excuteAutoMeasure(bool ok);
    void measureFinish(int id);

    // 视图操作
    void clearPlotView();
    void isUnLockUI(bool ok);
    void isUnNeedCheck(bool ok);

protected:
    virtual void showEvent(QShowEvent *event);
    virtual void closeEvent(QCloseEvent *event);

private:
    Ui::MainWindow *ui;
    QAction *m_pSelectedView;
    ToolsView *m_pToolsView;
    TempControlView *m_pTempCtrlView;
    CheckView *m_pCheckView;
    Logger *m_pLogger;
    QString m_document;
    bool m_temperatureEnable;
    bool m_cameraEnable;
    bool m_isBlank;
    bool m_isMerge;
    bool m_isMeasure;
    QWidget *m_focusWidget;
    QTimer *m_pTimer;
    QString m_serialNumber;
    int m_channelNumber;
    // 左视图
    bool m_isShowDataView;
    QRect m_leftViewRect;
    DataView *m_pDataView;

    // 主视图
    bool m_isShowMainView;
    QRect m_mainViewRect;
    PlotView *m_pPlotView;

    // 底视图
    double m_heightCoef;
    bool m_isShowRecordView;
    QRect m_buttomViewRect;
    RecordView *m_pRecordView;

    // 右视图
    bool m_isFittingView;
    QRect m_rightViewRect;
    FittingView *m_pFittingView;

    // 工具视图
    QRect m_ToolViewRect;
    // 摄像头
    bool m_isCameraView;
    CameraView *m_pCameraView;
    // 计算器
    bool m_isOligoCalculator;
    OligoCalculator *m_pOligoCalc;
    // 设置窗口
    bool m_isSettingView;
    SettingView *m_pSettingView;

    // 后台控制
    Controller *m_pController;
    bool m_waitStatus;

    void showDirAndRecordView();
    void waitting();
    void waitting(int timeout);

    void showCheckView(bool ok);
    bool shutDownSystem();
    // 切换页面
    void startSwitchPage(int dh = 0);

    void updateView(int dh = 0);
    void updateRect(int dh = 0);
    QPropertyAnimation *getShowViewAni(QWidget *widget, QRect start, QRect end);

    void updatePlotView(QString text);
    void initializeSystem();
    void initializeWidget();
    void initializeAction();

private slots:
    void changeAmText();
};

#endif // MAINWINDOW_H
