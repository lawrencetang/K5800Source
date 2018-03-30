#ifndef CHECKVIEW_H
#define CHECKVIEW_H

#include <QFrame>
#include <QSerialPort>

namespace Ui {
class CheckView;
}

class QTimer;
class Controller;
class CheckView : public QFrame
{
    Q_OBJECT

public:
    explicit CheckView(Controller *controller,
                       bool hasTemperatrue = true, QWidget *parent = 0);
    ~CheckView();

    void installController(Controller *controller);
    void setMessage(QString message);

signals:
    void checking(bool ok);
    void clearPlot();
    void deviceEnable(bool ok);
    void saveImage();

public slots:
    void controllerOption();
    void excuteCheck();
    void checkMainboard();
    void checkMicroscale();
    void checkCuttve();
    void checkTemperature();

    void autoCheckError();
    void autoConnection();

    void changeModel(bool ok);

private:
    Ui::CheckView *ui;
    QTimer *m_pAutoCheckErrorTimer;
    QTimer *m_pAutoConnectionTimer;
    Controller *m_pController;

    bool m_cuvetteEnable;
    int m_channelNumber;

    void setViewEnable(bool ok);
    void initializeWidget();
};

#endif // CHECKVIEW_H
