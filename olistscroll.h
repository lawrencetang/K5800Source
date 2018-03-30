#ifndef OLISTSCROLL_H
#define OLISTSCROLL_H

#include <QListWidget>
#include <QListView>


class OListscroll : public QListWidget
{
    Q_OBJECT

public:
    explicit OListscroll(QWidget *parent = 0);
    ~OListscroll();


protected:
    virtual void mousePressEvent(QMouseEvent *event);
    virtual void mouseMoveEvent(QMouseEvent *event);
    virtual void mouseReleaseEvent(QMouseEvent *event);

private:
    bool m_leftButtonPressed;
    QPoint m_originalPoint;
    QPoint m_originalPointBackup;
};

#endif // OLISTSCROLL_H
