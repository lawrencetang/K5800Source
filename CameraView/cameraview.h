#ifndef CAMERAVIEW_H
#define CAMERAVIEW_H

#include <QFrame>
#include <cv.h>
#include <highgui.h>

namespace Ui {
class CameraView;
}

using namespace cv;
class QListWidgetItem;
class CameraView : public QFrame
{
    Q_OBJECT

public:
    explicit CameraView(QString systemPath, QWidget *parent = 0);
    ~CameraView();

public slots:
    bool autoCheck();
    void upDateImage(QString fileName);

private slots:
    void openCamera();
    void readFrame();

    void showCamera();
    void remove();
    void saveAs();
    void showSelectedImage(QListWidgetItem *item);
    void showPageChanged(int id);

protected:
    virtual void mouseDoubleClickEvent(QMouseEvent *event);

private:
    Ui::CameraView *ui;
    QString m_systemPath;
    bool m_isOpen;

    QTimer *m_pTimer;
    CvCapture *m_pCamera;

    void showMessage(QString text);
    void insert(QPixmap pixmap);
    void capture();
    QImage toImage(IplImage *iplImg);

    void initializeSystem();
    void initalizeWidgets();
};

#endif // CAMERAVIEW_H
