#ifndef OTABLESCROLL_H
#define OTABLESCROLL_H

#include <QTableWidget>


class OTablescroll : public QTableWidget
{
    Q_OBJECT

public:
    explicit OTablescroll(QWidget *parent = 0);
    ~OTablescroll();


protected:
    virtual void mousePressEvent(QMouseEvent *event);
    virtual void mouseMoveEvent(QMouseEvent *event);
    virtual void mouseReleaseEvent(QMouseEvent *event);

private:
    bool m_leftButtonPressed;
    QPoint m_originalPoint;
    QPoint m_originalPointBackup;
};

#endif // OTABLESCROLL_H
