/********************************************************************************
** Form generated from reading UI file 'dydialog.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DYDIALOG_H
#define UI_DYDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_DyDialog
{
public:
    QVBoxLayout *verticalLayout;
    QGroupBox *groupBox;
    QGridLayout *gridLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *wl1Label;
    QSpinBox *wl1SpinBox;
    QHBoxLayout *horizontalLayout_7;
    QCheckBox *tvCheckBox;
    QDoubleSpinBox *tvDoubleSpinBox;
    QHBoxLayout *horizontalLayout_6;
    QLabel *label_2;
    QSpinBox *mtSpinBox;
    QSpacerItem *horizontalSpacer;
    QGroupBox *groupBox_2;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout_2;
    QCheckBox *wl2CheckBox;
    QSpinBox *wl2SpinBox;
    QCheckBox *wl4CheckBox;
    QSpinBox *wl4SpinBox;
    QHBoxLayout *horizontalLayout_3;
    QCheckBox *wl3CheckBox;
    QSpinBox *wl3SpinBox;
    QCheckBox *wl5CheckBox;
    QSpinBox *wl5SpinBox;
    QHBoxLayout *horizontalLayout_8;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *cancelPBtn;
    QPushButton *okPBtn;

    void setupUi(QDialog *DyDialog)
    {
        if (DyDialog->objectName().isEmpty())
            DyDialog->setObjectName(QStringLiteral("DyDialog"));
        DyDialog->resize(664, 380);
        DyDialog->setStyleSheet(QString::fromUtf8("QDialog{\n"
"	background-color: rgb(255, 255, 255);\n"
"}\n"
"\n"
"/*checkbox\345\255\227\344\275\223\345\222\214\351\227\264\350\267\235\350\256\276\347\275\256*/\n"
"QCheckBox{\n"
"	spacing: 10px;\n"
"	font: 12pt \"\351\273\221\344\275\223\";\n"
"}\n"
"\n"
"/*checkbox\346\240\267\345\274\217\350\256\276\347\275\256*/\n"
"QCheckBox::indicator { \n"
"	width: 64px;\n"
"	height: 32px;\n"
"}\n"
"/*\346\234\252\351\200\211\344\270\255*/\n"
"QCheckBox::indicator::unchecked {	\n"
"	image: url(:/icons/uncheck1.png);\n"
"}\n"
"/*\351\200\211\344\270\255*/\n"
"QCheckBox::indicator::checked { \n"
"	image: url(:/icons/check1.png);\n"
"}\n"
"\n"
"QPushButton,QLabel,QLineEdit,QSpinBox,QDoubleSpinBox{\n"
"	min-height:48px;\n"
"	font: 12pt \"\351\273\221\344\275\223\";\n"
"}\n"
"\n"
"QGroupBox{\n"
"	font: Bold 14pt \"\351\273\221\344\275\223\";\n"
"}\n"
"\n"
"/*spinbox \346\212\254\350\265\267\346\240\267\345\274\217*/\n"
"QTimeEdit::up-button,QDoubleSpinBox::up-button,QSpinBox::up-button {subcontrol-origin:border;\n"
"    s"
                        "ubcontrol-position:right;\n"
"	image: url(:/icons/up_left.png);\n"
"	background-color: rgb(255, 255, 255);\n"
"    width: 36px;\n"
"    height: 50px;       \n"
"}\n"
"QTimeEdit::down-button,QDoubleSpinBox::down-button,QSpinBox::down-button {subcontrol-origin:border;\n"
"    subcontrol-position:left;\n"
"	image: url(:/icons/up_right.png);\n"
"	background-color: rgb(255, 255, 255);\n"
"    width: 36px;\n"
"    height: 50px;\n"
"}\n"
"\n"
"/*\346\214\211\351\222\256\346\214\211\344\270\213\346\240\267\345\274\217*/\n"
"QTimeEdit::up-button:pressed,QDoubleSpinBox::up-button:pressed,QSpinBox::up-button:pressed{subcontrol-origin:border;\n"
"    subcontrol-position:right;\n"
"    image: url(:/icons/up_left.png);\n"
"	background-color: rgb(255, 255, 255);\n"
"    width: 35px;\n"
"    height: 49px;       \n"
"}\n"
"  \n"
"QTimeEdit::down-button:pressed,QDoubleSpinBox::down-button:pressed,QSpinBox::down-button:pressed,QSpinBox::down-button:pressed{\n"
"    subcontrol-position:left;\n"
"    image: url(:/icons/up_right.pn"
                        "g);\n"
"	background-color: rgb(255, 255, 255);\n"
"    width: 35px;\n"
"    height: 49px;   \n"
"}\n"
""));
        verticalLayout = new QVBoxLayout(DyDialog);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        groupBox = new QGroupBox(DyDialog);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        gridLayout = new QGridLayout(groupBox);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        wl1Label = new QLabel(groupBox);
        wl1Label->setObjectName(QStringLiteral("wl1Label"));

        horizontalLayout->addWidget(wl1Label);

        wl1SpinBox = new QSpinBox(groupBox);
        wl1SpinBox->setObjectName(QStringLiteral("wl1SpinBox"));
        wl1SpinBox->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        wl1SpinBox->setMinimum(200);
        wl1SpinBox->setMaximum(850);
        wl1SpinBox->setValue(200);

        horizontalLayout->addWidget(wl1SpinBox);

        horizontalLayout->setStretch(1, 1);

        gridLayout->addLayout(horizontalLayout, 0, 0, 1, 1);

        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setObjectName(QStringLiteral("horizontalLayout_7"));
        tvCheckBox = new QCheckBox(groupBox);
        tvCheckBox->setObjectName(QStringLiteral("tvCheckBox"));

        horizontalLayout_7->addWidget(tvCheckBox);

        tvDoubleSpinBox = new QDoubleSpinBox(groupBox);
        tvDoubleSpinBox->setObjectName(QStringLiteral("tvDoubleSpinBox"));
        tvDoubleSpinBox->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        tvDoubleSpinBox->setMaximum(1000);

        horizontalLayout_7->addWidget(tvDoubleSpinBox);

        horizontalLayout_7->setStretch(1, 1);

        gridLayout->addLayout(horizontalLayout_7, 0, 1, 1, 1);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName(QStringLiteral("horizontalLayout_6"));
        label_2 = new QLabel(groupBox);
        label_2->setObjectName(QStringLiteral("label_2"));

        horizontalLayout_6->addWidget(label_2);

        mtSpinBox = new QSpinBox(groupBox);
        mtSpinBox->setObjectName(QStringLiteral("mtSpinBox"));
        mtSpinBox->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        mtSpinBox->setMaximum(1000);
        mtSpinBox->setValue(1);

        horizontalLayout_6->addWidget(mtSpinBox);

        horizontalLayout_6->setStretch(1, 1);

        gridLayout->addLayout(horizontalLayout_6, 1, 0, 1, 1);

        horizontalSpacer = new QSpacerItem(251, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer, 1, 1, 1, 1);


        verticalLayout->addWidget(groupBox);

        groupBox_2 = new QGroupBox(DyDialog);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        groupBox_2->setStyleSheet(QString::fromUtf8("QDialog{\n"
"	background-color: rgb(255, 255, 255);\n"
"}\n"
"\n"
"/*checkbox\345\255\227\344\275\223\345\222\214\351\227\264\350\267\235\350\256\276\347\275\256*/\n"
"QCheckBox{\n"
"	spacing: 10px;\n"
"	font: 12pt \"\351\273\221\344\275\223\";\n"
"}\n"
"\n"
"/*checkbox\346\240\267\345\274\217\350\256\276\347\275\256*/\n"
"QCheckBox::indicator { \n"
"	width: 64px;\n"
"	height: 32px;\n"
"}\n"
"/*\346\234\252\351\200\211\344\270\255*/\n"
"QCheckBox::indicator::unchecked {	\n"
"	image: url(:/icons/uncheck1.png);\n"
"}\n"
"/*\351\200\211\344\270\255*/\n"
"QCheckBox::indicator::checked { \n"
"	image: url(:/icons/check1.png);\n"
"}\n"
"\n"
"QPushButton,QLabel,QLineEdit,QSpinBox{\n"
"	min-height:48px;\n"
"	font: 12pt \"\351\273\221\344\275\223\";\n"
"}\n"
"\n"
"QGroupBox{\n"
"	font: Bold 14pt \"\351\273\221\344\275\223\";\n"
"}\n"
""));
        verticalLayout_2 = new QVBoxLayout(groupBox_2);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        wl2CheckBox = new QCheckBox(groupBox_2);
        wl2CheckBox->setObjectName(QStringLiteral("wl2CheckBox"));

        horizontalLayout_2->addWidget(wl2CheckBox);

        wl2SpinBox = new QSpinBox(groupBox_2);
        wl2SpinBox->setObjectName(QStringLiteral("wl2SpinBox"));
        wl2SpinBox->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        wl2SpinBox->setMinimum(200);
        wl2SpinBox->setMaximum(850);
        wl2SpinBox->setValue(200);

        horizontalLayout_2->addWidget(wl2SpinBox);

        wl4CheckBox = new QCheckBox(groupBox_2);
        wl4CheckBox->setObjectName(QStringLiteral("wl4CheckBox"));

        horizontalLayout_2->addWidget(wl4CheckBox);

        wl4SpinBox = new QSpinBox(groupBox_2);
        wl4SpinBox->setObjectName(QStringLiteral("wl4SpinBox"));
        wl4SpinBox->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        wl4SpinBox->setMinimum(200);
        wl4SpinBox->setMaximum(850);

        horizontalLayout_2->addWidget(wl4SpinBox);


        verticalLayout_2->addLayout(horizontalLayout_2);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        wl3CheckBox = new QCheckBox(groupBox_2);
        wl3CheckBox->setObjectName(QStringLiteral("wl3CheckBox"));

        horizontalLayout_3->addWidget(wl3CheckBox);

        wl3SpinBox = new QSpinBox(groupBox_2);
        wl3SpinBox->setObjectName(QStringLiteral("wl3SpinBox"));
        wl3SpinBox->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        wl3SpinBox->setMinimum(200);
        wl3SpinBox->setMaximum(850);

        horizontalLayout_3->addWidget(wl3SpinBox);

        wl5CheckBox = new QCheckBox(groupBox_2);
        wl5CheckBox->setObjectName(QStringLiteral("wl5CheckBox"));

        horizontalLayout_3->addWidget(wl5CheckBox);

        wl5SpinBox = new QSpinBox(groupBox_2);
        wl5SpinBox->setObjectName(QStringLiteral("wl5SpinBox"));
        wl5SpinBox->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        wl5SpinBox->setMinimum(200);
        wl5SpinBox->setMaximum(850);

        horizontalLayout_3->addWidget(wl5SpinBox);


        verticalLayout_2->addLayout(horizontalLayout_3);


        verticalLayout->addWidget(groupBox_2);

        horizontalLayout_8 = new QHBoxLayout();
        horizontalLayout_8->setSpacing(0);
        horizontalLayout_8->setObjectName(QStringLiteral("horizontalLayout_8"));
        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_8->addItem(horizontalSpacer_2);

        cancelPBtn = new QPushButton(DyDialog);
        cancelPBtn->setObjectName(QStringLiteral("cancelPBtn"));
        cancelPBtn->setMinimumSize(QSize(140, 50));

        horizontalLayout_8->addWidget(cancelPBtn);

        okPBtn = new QPushButton(DyDialog);
        okPBtn->setObjectName(QStringLiteral("okPBtn"));
        okPBtn->setMinimumSize(QSize(140, 50));

        horizontalLayout_8->addWidget(okPBtn);

        horizontalLayout_8->setStretch(0, 1);

        verticalLayout->addLayout(horizontalLayout_8);


        retranslateUi(DyDialog);

        QMetaObject::connectSlotsByName(DyDialog);
    } // setupUi

    void retranslateUi(QDialog *DyDialog)
    {
        DyDialog->setWindowTitle(QApplication::translate("DyDialog", "Dynamics", 0));
        groupBox->setTitle(QApplication::translate("DyDialog", "Target", 0));
        wl1Label->setText(QApplication::translate("DyDialog", "Wave Length1", 0));
        wl1SpinBox->setSuffix(QApplication::translate("DyDialog", " nm", 0));
        tvCheckBox->setText(QApplication::translate("DyDialog", "Target Value", 0));
        label_2->setText(QApplication::translate("DyDialog", "Train Times ", 0));
        groupBox_2->setTitle(QApplication::translate("DyDialog", "Watch", 0));
        wl2CheckBox->setText(QApplication::translate("DyDialog", "Wave Length2", 0));
        wl2SpinBox->setSuffix(QApplication::translate("DyDialog", " nm", 0));
        wl4CheckBox->setText(QApplication::translate("DyDialog", "Wave Length4", 0));
        wl4SpinBox->setSuffix(QApplication::translate("DyDialog", " nm", 0));
        wl3CheckBox->setText(QApplication::translate("DyDialog", "Wave Length3", 0));
        wl3SpinBox->setSuffix(QApplication::translate("DyDialog", " nm", 0));
        wl5CheckBox->setText(QApplication::translate("DyDialog", "Wave Length5", 0));
        wl5SpinBox->setSuffix(QApplication::translate("DyDialog", " nm", 0));
        cancelPBtn->setText(QApplication::translate("DyDialog", "Cancel", 0));
        okPBtn->setText(QApplication::translate("DyDialog", "OK", 0));
    } // retranslateUi

};

namespace Ui {
    class DyDialog: public Ui_DyDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DYDIALOG_H
