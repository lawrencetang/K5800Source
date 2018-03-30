/********************************************************************************
** Form generated from reading UI file 'tempcontrolview.ui'
**
** Created by: Qt User Interface Compiler version 5.4.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TEMPCONTROLVIEW_H
#define UI_TEMPCONTROLVIEW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLCDNumber>
#include <QtWidgets/QLabel>
#include <QtWidgets/QToolButton>

QT_BEGIN_NAMESPACE

class Ui_TempControlView
{
public:
    QHBoxLayout *horizontalLayout;
    QLabel *label1_2;
    QToolButton *setingtBtn;
    QToolButton *starttBtn;
    QLabel *label1;
    QLCDNumber *targetLcdNumber;
    QLabel *label2;
    QLCDNumber *currentLcdNumber;
    QLabel *label3;

    void setupUi(QFrame *TempControlView)
    {
        if (TempControlView->objectName().isEmpty())
            TempControlView->setObjectName(QStringLiteral("TempControlView"));
        TempControlView->resize(1025, 72);
        TempControlView->setStyleSheet(QStringLiteral(""));
        TempControlView->setFrameShape(QFrame::StyledPanel);
        TempControlView->setFrameShadow(QFrame::Raised);
        horizontalLayout = new QHBoxLayout(TempControlView);
        horizontalLayout->setSpacing(3);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        label1_2 = new QLabel(TempControlView);
        label1_2->setObjectName(QStringLiteral("label1_2"));
        QFont font;
        font.setFamily(QString::fromUtf8("\345\276\256\350\275\257\351\233\205\351\273\221"));
        font.setPointSize(14);
        font.setBold(true);
        font.setWeight(75);
        label1_2->setFont(font);

        horizontalLayout->addWidget(label1_2);

        setingtBtn = new QToolButton(TempControlView);
        setingtBtn->setObjectName(QStringLiteral("setingtBtn"));
        QIcon icon;
        icon.addFile(QStringLiteral(":/icons/seting.png"), QSize(), QIcon::Normal, QIcon::Off);
        setingtBtn->setIcon(icon);
        setingtBtn->setIconSize(QSize(64, 64));
        setingtBtn->setAutoRaise(true);

        horizontalLayout->addWidget(setingtBtn);

        starttBtn = new QToolButton(TempControlView);
        starttBtn->setObjectName(QStringLiteral("starttBtn"));
        QIcon icon1;
        icon1.addFile(QStringLiteral(":/icons/start.png"), QSize(), QIcon::Normal, QIcon::Off);
        starttBtn->setIcon(icon1);
        starttBtn->setIconSize(QSize(64, 64));
        starttBtn->setAutoRaise(true);

        horizontalLayout->addWidget(starttBtn);

        label1 = new QLabel(TempControlView);
        label1->setObjectName(QStringLiteral("label1"));
        label1->setFont(font);

        horizontalLayout->addWidget(label1);

        targetLcdNumber = new QLCDNumber(TempControlView);
        targetLcdNumber->setObjectName(QStringLiteral("targetLcdNumber"));
        targetLcdNumber->setMinimumSize(QSize(150, 29));
        targetLcdNumber->setFrameShape(QFrame::StyledPanel);
        targetLcdNumber->setSegmentStyle(QLCDNumber::Flat);
        targetLcdNumber->setProperty("value", QVariant(25));

        horizontalLayout->addWidget(targetLcdNumber);

        label2 = new QLabel(TempControlView);
        label2->setObjectName(QStringLiteral("label2"));
        label2->setFont(font);

        horizontalLayout->addWidget(label2);

        currentLcdNumber = new QLCDNumber(TempControlView);
        currentLcdNumber->setObjectName(QStringLiteral("currentLcdNumber"));
        currentLcdNumber->setMinimumSize(QSize(150, 29));
        currentLcdNumber->setFrameShape(QFrame::StyledPanel);
        currentLcdNumber->setSmallDecimalPoint(false);
        currentLcdNumber->setSegmentStyle(QLCDNumber::Flat);

        horizontalLayout->addWidget(currentLcdNumber);

        label3 = new QLabel(TempControlView);
        label3->setObjectName(QStringLiteral("label3"));
        label3->setFont(font);

        horizontalLayout->addWidget(label3);

        horizontalLayout->setStretch(4, 1);
        horizontalLayout->setStretch(6, 1);

        retranslateUi(TempControlView);

        QMetaObject::connectSlotsByName(TempControlView);
    } // setupUi

    void retranslateUi(QFrame *TempControlView)
    {
        TempControlView->setWindowTitle(QApplication::translate("TempControlView", "Frame", 0));
        label1_2->setText(QApplication::translate("TempControlView", "Temperture\357\274\232", 0));
        setingtBtn->setText(QApplication::translate("TempControlView", "Seting", 0));
        starttBtn->setText(QApplication::translate("TempControlView", "start", 0));
        label1->setText(QApplication::translate("TempControlView", "Target Temperture:", 0));
        label2->setText(QApplication::translate("TempControlView", "\342\204\203/Current Temperture :", 0));
        label3->setText(QApplication::translate("TempControlView", "\342\204\203", 0));
    } // retranslateUi

};

namespace Ui {
    class TempControlView: public Ui_TempControlView {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TEMPCONTROLVIEW_H
