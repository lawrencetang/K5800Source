#include "otablescroll.h"

#include <QMouseEvent>
#include <QScrollBar>

OTablescroll::OTablescroll(QWidget *parent) :
    QTableWidget(parent) {
    m_leftButtonPressed = false;
    setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setHorizontalScrollMode(QAbstractItemView::ScrollPerPixel);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setSelectionMode(QAbstractItemView::SingleSelection);
    setFrameShape(QFrame::NoFrame);
}

OTablescroll::~OTablescroll() {
}

/**
 * @brief OScrollArea::mousePressEvent
 * @param event
 */
void OTablescroll::mousePressEvent(QMouseEvent *event) {

    if (event->button() == Qt::LeftButton) {
        m_leftButtonPressed = true;
        m_originalPoint = event->globalPos();
        m_originalPointBackup = m_originalPoint;
    }
    QTableWidget::mousePressEvent(event);
}

/**
 * @brief OScrollArea::mouseMoveEvent
 * @param event
 */
void OTablescroll::mouseMoveEvent(QMouseEvent *event) {

    if (m_leftButtonPressed) {
        int yMoved = event->globalPos().y() - m_originalPoint.y();
        int xMoved = event->globalPos().x() - m_originalPoint.x();
        verticalScrollBar()->setValue(verticalScrollBar()->value() - yMoved);
        horizontalScrollBar()->setValue(horizontalScrollBar()->value() - xMoved);
        m_originalPoint = event->globalPos();
        return;
    }
    QTableWidget::mouseMoveEvent(event);
}

/**
 * @brief OScrollArea::mouseReleaseEvent
 * @param event
 */
void OTablescroll::mouseReleaseEvent(QMouseEvent *event) {

    if (m_leftButtonPressed) {
        m_leftButtonPressed = false;
        int yMoved = event->globalPos().y() - m_originalPointBackup.y();
        int xMoved = event->globalPos().x() - m_originalPointBackup.x();
        if (abs(yMoved) > 10 || abs(xMoved) > 10) {
            return;
        }
    }
    QTableWidget::mouseReleaseEvent(event);
}

