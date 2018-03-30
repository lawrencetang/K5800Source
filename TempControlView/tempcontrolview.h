#ifndef TEMPCONTROLVIEW_H
#define TEMPCONTROLVIEW_H

#include <QFrame>

namespace Ui {
class TempControlView;
}

class QTimer;
class Controller;
class TargetSetingDialog;
class TempControlView : public QFrame
{
    Q_OBJECT

public:
    explicit TempControlView(Controller *controller, QWidget *parent = 0);
    ~TempControlView();

    void stopTemperature();

public slots:
    void onStartBtnClicked();
    void setTargetValue(double value);
    void setCurrentValue(double value);
    void readTemperature();

    void pauseRead(bool ok);

private:
    Ui::TempControlView *ui;
    bool m_isShow;
    Controller *m_pController;
    QTimer *m_pTimer;
    bool m_isPauseRead;

    TargetSetingDialog *m_pTargetSetingDlg;
    void initializeWidget();
};

#endif // TEMPCONTROLVIEW_H
