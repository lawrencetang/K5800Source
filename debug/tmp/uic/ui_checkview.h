/********************************************************************************
** Form generated from reading UI file 'checkview.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CHECKVIEW_H
#define UI_CHECKVIEW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QToolButton>

QT_BEGIN_NAMESPACE

class Ui_CheckView
{
public:
    QHBoxLayout *horizontalLayout;
    QToolButton *closetBtn;
    QRadioButton *radioButtonMs;
    QSpinBox *spinBoxChannel;
    QRadioButton *radioButtonCt;
    QToolButton *checktBtn;
    QToolButton *savetBtn;
    QToolButton *maintBtn;
    QToolButton *microtBtn;
    QToolButton *cuvettetBtn;
    QToolButton *temperaturetBtn;
    QLabel *messageLabel;

    void setupUi(QFrame *CheckView)
    {
        if (CheckView->objectName().isEmpty())
            CheckView->setObjectName(QStringLiteral("CheckView"));
        CheckView->resize(1132, 72);
        CheckView->setStyleSheet(QString::fromUtf8("QRadioButton::indicator { \n"
"	width: 48px;\n"
"	height: 48px;\n"
"}\n"
"/*\345\215\225\351\200\211\346\241\206\346\234\252\351\200\211\344\270\255\346\240\267\345\274\217*/\n"
"QRadioButton::indicator::unchecked {\n"
"	image: url(:/icons/uncheck.png);\n"
"}\n"
"/*\345\215\225\351\200\211\346\241\206\351\200\211\344\270\255\346\240\267\345\274\217*/\n"
"QRadioButton::indicator::checked { \n"
"	image: url(:/icons/check.png);\n"
"}\n"
"/*RadioButton\345\222\214checkbox\345\255\227\344\275\223\345\222\214\351\227\264\350\267\235\350\256\276\347\275\256*/\n"
"QRadioButton {\n"
"	spacing: 5px;\n"
"	font: 14pt \"\351\273\221\344\275\223\";\n"
"}\n"
"\n"
"QSpinBox,QDoubleSpinBox {\n"
"	font:14pt \"\351\273\221\344\275\223\";\n"
"	min-height:50px;\n"
"	min-width:150px;\n"
"	border-radius:24;\n"
"	border:2px solid black;\n"
"	background-color:transparent;\n"
"}\n"
"\n"
"/*spinbox \346\212\254\350\265\267\346\240\267\345\274\217*/\n"
"QTimeEdit::up-button,QDoubleSpinBox::up-button,QSpinBox::up-button {subcontrol-origin"
                        ":border;\n"
"    subcontrol-position:right;\n"
"	image: url(:/icons/up_left.png);\n"
"    width: 50px;\n"
"    height: 50px;       \n"
"}\n"
"QTimeEdit::down-button,QDoubleSpinBox::down-button,QSpinBox::down-button {subcontrol-origin:border;\n"
"    subcontrol-position:left;\n"
"	image: url(:/icons/up_right.png);\n"
"    width: 50px;\n"
"    height: 50px;\n"
"}\n"
"\n"
"/*\346\214\211\351\222\256\346\214\211\344\270\213\346\240\267\345\274\217*/\n"
"QTimeEdit::up-button:pressed,QDoubleSpinBox::up-button:pressed,QSpinBox::up-button:pressed{subcontrol-origin:border;\n"
"    subcontrol-position:right;\n"
"    image: url(:/icons/up_left.png);\n"
"    width: 49px;\n"
"    height: 49px;       \n"
"}\n"
"  \n"
"QTimeEdit::down-button:pressed,QDoubleSpinBox::down-button:pressed,QSpinBox::down-button:pressed,QSpinBox::down-button:pressed{\n"
"    subcontrol-position:left;\n"
"    image: url(:/icons/up_right.png);\n"
"    width: 49px;\n"
"    height: 49px;   \n"
"}"));
        CheckView->setFrameShape(QFrame::StyledPanel);
        CheckView->setFrameShadow(QFrame::Raised);
        horizontalLayout = new QHBoxLayout(CheckView);
        horizontalLayout->setSpacing(3);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        closetBtn = new QToolButton(CheckView);
        closetBtn->setObjectName(QStringLiteral("closetBtn"));
        QIcon icon;
        icon.addFile(QStringLiteral(":/icons/disconnect.png"), QSize(), QIcon::Normal, QIcon::Off);
        closetBtn->setIcon(icon);
        closetBtn->setIconSize(QSize(64, 64));
        closetBtn->setAutoRaise(true);

        horizontalLayout->addWidget(closetBtn);

        radioButtonMs = new QRadioButton(CheckView);
        radioButtonMs->setObjectName(QStringLiteral("radioButtonMs"));
        radioButtonMs->setChecked(true);

        horizontalLayout->addWidget(radioButtonMs);

        spinBoxChannel = new QSpinBox(CheckView);
        spinBoxChannel->setObjectName(QStringLiteral("spinBoxChannel"));
        spinBoxChannel->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        spinBoxChannel->setMinimum(1);
        spinBoxChannel->setMaximum(1);
        spinBoxChannel->setValue(1);

        horizontalLayout->addWidget(spinBoxChannel);

        radioButtonCt = new QRadioButton(CheckView);
        radioButtonCt->setObjectName(QStringLiteral("radioButtonCt"));

        horizontalLayout->addWidget(radioButtonCt);

        checktBtn = new QToolButton(CheckView);
        checktBtn->setObjectName(QStringLiteral("checktBtn"));
        QIcon icon1;
        icon1.addFile(QStringLiteral(":/icons/test.png"), QSize(), QIcon::Normal, QIcon::Off);
        checktBtn->setIcon(icon1);
        checktBtn->setIconSize(QSize(64, 64));
        checktBtn->setAutoRaise(true);

        horizontalLayout->addWidget(checktBtn);

        savetBtn = new QToolButton(CheckView);
        savetBtn->setObjectName(QStringLiteral("savetBtn"));
        QIcon icon2;
        icon2.addFile(QStringLiteral(":/icons/save.png"), QSize(), QIcon::Normal, QIcon::Off);
        savetBtn->setIcon(icon2);
        savetBtn->setIconSize(QSize(64, 64));
        savetBtn->setAutoRaise(true);

        horizontalLayout->addWidget(savetBtn);

        maintBtn = new QToolButton(CheckView);
        maintBtn->setObjectName(QStringLiteral("maintBtn"));
        QIcon icon3;
        icon3.addFile(QStringLiteral(":/icons/mainboard.png"), QSize(), QIcon::Normal, QIcon::Off);
        maintBtn->setIcon(icon3);
        maintBtn->setIconSize(QSize(64, 64));
        maintBtn->setAutoRaise(true);

        horizontalLayout->addWidget(maintBtn);

        microtBtn = new QToolButton(CheckView);
        microtBtn->setObjectName(QStringLiteral("microtBtn"));
        QIcon icon4;
        icon4.addFile(QStringLiteral(":/icons/macroscale.png"), QSize(), QIcon::Normal, QIcon::Off);
        microtBtn->setIcon(icon4);
        microtBtn->setIconSize(QSize(64, 64));
        microtBtn->setAutoRaise(true);

        horizontalLayout->addWidget(microtBtn);

        cuvettetBtn = new QToolButton(CheckView);
        cuvettetBtn->setObjectName(QStringLiteral("cuvettetBtn"));
        QIcon icon5;
        icon5.addFile(QStringLiteral(":/icons/cuvette.png"), QSize(), QIcon::Normal, QIcon::Off);
        cuvettetBtn->setIcon(icon5);
        cuvettetBtn->setIconSize(QSize(64, 64));
        cuvettetBtn->setAutoRaise(true);

        horizontalLayout->addWidget(cuvettetBtn);

        temperaturetBtn = new QToolButton(CheckView);
        temperaturetBtn->setObjectName(QStringLiteral("temperaturetBtn"));
        QIcon icon6;
        icon6.addFile(QStringLiteral(":/icons/temperature.png"), QSize(), QIcon::Normal, QIcon::Off);
        temperaturetBtn->setIcon(icon6);
        temperaturetBtn->setIconSize(QSize(64, 64));
        temperaturetBtn->setAutoRaise(true);

        horizontalLayout->addWidget(temperaturetBtn);

        messageLabel = new QLabel(CheckView);
        messageLabel->setObjectName(QStringLiteral("messageLabel"));
        QFont font;
        font.setFamily(QString::fromUtf8("\351\273\221\344\275\223"));
        font.setPointSize(14);
        messageLabel->setFont(font);

        horizontalLayout->addWidget(messageLabel);

        horizontalLayout->setStretch(10, 1);

        retranslateUi(CheckView);

        QMetaObject::connectSlotsByName(CheckView);
    } // setupUi

    void retranslateUi(QFrame *CheckView)
    {
        CheckView->setWindowTitle(QApplication::translate("CheckView", "Frame", 0));
#ifndef QT_NO_TOOLTIP
        closetBtn->setToolTip(QApplication::translate("CheckView", "Close/Connect", 0));
#endif // QT_NO_TOOLTIP
        closetBtn->setText(QApplication::translate("CheckView", "Close", 0));
        radioButtonMs->setText(QApplication::translate("CheckView", "Microscale", 0));
        spinBoxChannel->setSuffix(QApplication::translate("CheckView", " Channel", 0));
        radioButtonCt->setText(QApplication::translate("CheckView", "Cuvette", 0));
#ifndef QT_NO_TOOLTIP
        checktBtn->setToolTip(QApplication::translate("CheckView", "Check", 0));
#endif // QT_NO_TOOLTIP
        checktBtn->setText(QApplication::translate("CheckView", "Check", 0));
#ifndef QT_NO_TOOLTIP
        savetBtn->setToolTip(QApplication::translate("CheckView", "Save Image", 0));
#endif // QT_NO_TOOLTIP
        savetBtn->setText(QApplication::translate("CheckView", "...", 0));
#ifndef QT_NO_TOOLTIP
        maintBtn->setToolTip(QApplication::translate("CheckView", "Main Borad", 0));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        maintBtn->setStatusTip(QString());
#endif // QT_NO_STATUSTIP
        maintBtn->setText(QApplication::translate("CheckView", "Main Borad", 0));
#ifndef QT_NO_TOOLTIP
        microtBtn->setToolTip(QApplication::translate("CheckView", "Check Microscale", 0));
#endif // QT_NO_TOOLTIP
        microtBtn->setText(QApplication::translate("CheckView", "Check Microscale", 0));
#ifndef QT_NO_TOOLTIP
        cuvettetBtn->setToolTip(QApplication::translate("CheckView", "Check Cuvette", 0));
#endif // QT_NO_TOOLTIP
        cuvettetBtn->setText(QApplication::translate("CheckView", "Check Cuvette", 0));
#ifndef QT_NO_TOOLTIP
        temperaturetBtn->setToolTip(QApplication::translate("CheckView", "Temperature", 0));
#endif // QT_NO_TOOLTIP
        temperaturetBtn->setText(QApplication::translate("CheckView", "Temperature", 0));
        messageLabel->setText(QApplication::translate("CheckView", "TextLabel", 0));
    } // retranslateUi

};

namespace Ui {
    class CheckView: public Ui_CheckView {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CHECKVIEW_H
