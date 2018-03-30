#include "olistscroll.h"

#include <QMouseEvent>
#include <QScrollBar>

OListscroll::OListscroll(QWidget *parent) :
    QListWidget(parent) {
    m_leftButtonPressed = false;
    setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setSelectionMode(QAbstractItemView::ContiguousSelection);
    setFrameShape(QFrame::NoFrame);
}

OListscroll::~OListscroll() {
}

/**
 * @brief OScrollArea::mousePressEvent
 * @param event
 */
void OListscroll::mousePressEvent(QMouseEvent *event) {
    /*
    if (event->button() == Qt::LeftButton) {
        m_leftButtonPressed = true;
        m_originalPoint = event->pos();
        return;
    }
    QAbstractScrollArea::mousePressEvent(event);
    */
    if (event->button() == Qt::LeftButton) {
        m_leftButtonPressed = true;
        m_originalPoint = event->globalPos();
        m_originalPointBackup = m_originalPoint;
    }
    QListView::mousePressEvent(event);
}

/**
 * @brief OScrollArea::mouseMoveEvent
 * @param event
 */
void OListscroll::mouseMoveEvent(QMouseEvent *event) {
    /*
    if (m_leftButtonPressed) {
        int yMoved = event->pos().y() - m_originalPoint.y();
        verticalScrollBar()->setValue(verticalScrollBar()->value() - yMoved);//lt:新值=原始值-移动值
        m_originalPoint = event->pos();
        return;
    }
    QAbstractScrollArea::mouseMoveEvent(event);
    */
    if (m_leftButtonPressed) {
        int yMoved = event->globalPos().y() - m_originalPoint.y();
        verticalScrollBar()->setValue(verticalScrollBar()->value() - yMoved);
        m_originalPoint = event->globalPos();
        return;
    }
    QListView::mouseMoveEvent(event);
}

/**
 * @brief OScrollArea::mouseReleaseEvent
 * @param event
 */
void OListscroll::mouseReleaseEvent(QMouseEvent *event) {
    /*
    m_leftButtonPressed = false;
    QAbstractScrollArea::mouseReleaseEvent(event);
    */
    if (m_leftButtonPressed) {
        m_leftButtonPressed = false;
        int yMoved = event->globalPos().y() - m_originalPointBackup.y();
        if (abs(yMoved) > 10) {
            return;
        }
    }
    QListView::mouseReleaseEvent(event);
}
