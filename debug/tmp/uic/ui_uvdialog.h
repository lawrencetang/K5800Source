/********************************************************************************
** Form generated from reading UI file 'uvdialog.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_UVDIALOG_H
#define UI_UVDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_UvDialog
{
public:
    QHBoxLayout *horizontalLayout_6;
    QGroupBox *groupBox_2;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QCheckBox *wl1CheckBox;
    QSpinBox *wl1SpinBox;
    QLabel *label;
    QDoubleSpinBox *cf1DoubleSpinBox;
    QHBoxLayout *horizontalLayout_2;
    QCheckBox *wl2CheckBox;
    QSpinBox *wl2SpinBox;
    QLabel *label_2;
    QDoubleSpinBox *cf2DoubleSpinBox;
    QHBoxLayout *horizontalLayout_3;
    QCheckBox *wl3CheckBox;
    QSpinBox *wl3SpinBox;
    QLabel *label_3;
    QDoubleSpinBox *cf3DoubleSpinBox;
    QHBoxLayout *horizontalLayout_4;
    QCheckBox *wl4CheckBox;
    QSpinBox *wl4SpinBox;
    QLabel *label_4;
    QDoubleSpinBox *cf4DoubleSpinBox;
    QHBoxLayout *horizontalLayout_5;
    QCheckBox *wl5CheckBox;
    QSpinBox *wl5SpinBox;
    QLabel *label_5;
    QDoubleSpinBox *cf5DoubleSpinBox;
    QVBoxLayout *verticalLayout_2;
    QPushButton *cancelPBtn;
    QPushButton *okPBtn;
    QSpacerItem *verticalSpacer;

    void setupUi(QDialog *UvDialog)
    {
        if (UvDialog->objectName().isEmpty())
            UvDialog->setObjectName(QStringLiteral("UvDialog"));
        UvDialog->resize(703, 341);
        UvDialog->setStyleSheet(QString::fromUtf8("QDialog{\n"
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
"}"));
        horizontalLayout_6 = new QHBoxLayout(UvDialog);
        horizontalLayout_6->setObjectName(QStringLiteral("horizontalLayout_6"));
        groupBox_2 = new QGroupBox(UvDialog);
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
        verticalLayout = new QVBoxLayout(groupBox_2);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        wl1CheckBox = new QCheckBox(groupBox_2);
        wl1CheckBox->setObjectName(QStringLiteral("wl1CheckBox"));
        wl1CheckBox->setChecked(true);

        horizontalLayout->addWidget(wl1CheckBox);

        wl1SpinBox = new QSpinBox(groupBox_2);
        wl1SpinBox->setObjectName(QStringLiteral("wl1SpinBox"));
        wl1SpinBox->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        wl1SpinBox->setMinimum(200);
        wl1SpinBox->setMaximum(850);
        wl1SpinBox->setValue(200);

        horizontalLayout->addWidget(wl1SpinBox);

        label = new QLabel(groupBox_2);
        label->setObjectName(QStringLiteral("label"));

        horizontalLayout->addWidget(label);

        cf1DoubleSpinBox = new QDoubleSpinBox(groupBox_2);
        cf1DoubleSpinBox->setObjectName(QStringLiteral("cf1DoubleSpinBox"));
        cf1DoubleSpinBox->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        cf1DoubleSpinBox->setMaximum(1000);
        cf1DoubleSpinBox->setValue(1);

        horizontalLayout->addWidget(cf1DoubleSpinBox);

        horizontalLayout->setStretch(1, 1);
        horizontalLayout->setStretch(3, 1);

        verticalLayout->addLayout(horizontalLayout);

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

        label_2 = new QLabel(groupBox_2);
        label_2->setObjectName(QStringLiteral("label_2"));

        horizontalLayout_2->addWidget(label_2);

        cf2DoubleSpinBox = new QDoubleSpinBox(groupBox_2);
        cf2DoubleSpinBox->setObjectName(QStringLiteral("cf2DoubleSpinBox"));
        cf2DoubleSpinBox->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        cf2DoubleSpinBox->setMaximum(1000);
        cf2DoubleSpinBox->setValue(1);

        horizontalLayout_2->addWidget(cf2DoubleSpinBox);

        horizontalLayout_2->setStretch(1, 1);
        horizontalLayout_2->setStretch(3, 1);

        verticalLayout->addLayout(horizontalLayout_2);

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

        label_3 = new QLabel(groupBox_2);
        label_3->setObjectName(QStringLiteral("label_3"));

        horizontalLayout_3->addWidget(label_3);

        cf3DoubleSpinBox = new QDoubleSpinBox(groupBox_2);
        cf3DoubleSpinBox->setObjectName(QStringLiteral("cf3DoubleSpinBox"));
        cf3DoubleSpinBox->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        cf3DoubleSpinBox->setMaximum(1000);
        cf3DoubleSpinBox->setValue(1);

        horizontalLayout_3->addWidget(cf3DoubleSpinBox);

        horizontalLayout_3->setStretch(1, 1);
        horizontalLayout_3->setStretch(3, 1);

        verticalLayout->addLayout(horizontalLayout_3);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        wl4CheckBox = new QCheckBox(groupBox_2);
        wl4CheckBox->setObjectName(QStringLiteral("wl4CheckBox"));

        horizontalLayout_4->addWidget(wl4CheckBox);

        wl4SpinBox = new QSpinBox(groupBox_2);
        wl4SpinBox->setObjectName(QStringLiteral("wl4SpinBox"));
        wl4SpinBox->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        wl4SpinBox->setMinimum(200);
        wl4SpinBox->setMaximum(850);

        horizontalLayout_4->addWidget(wl4SpinBox);

        label_4 = new QLabel(groupBox_2);
        label_4->setObjectName(QStringLiteral("label_4"));

        horizontalLayout_4->addWidget(label_4);

        cf4DoubleSpinBox = new QDoubleSpinBox(groupBox_2);
        cf4DoubleSpinBox->setObjectName(QStringLiteral("cf4DoubleSpinBox"));
        cf4DoubleSpinBox->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        cf4DoubleSpinBox->setSingleStep(1000);
        cf4DoubleSpinBox->setValue(1);

        horizontalLayout_4->addWidget(cf4DoubleSpinBox);

        horizontalLayout_4->setStretch(1, 1);
        horizontalLayout_4->setStretch(3, 1);

        verticalLayout->addLayout(horizontalLayout_4);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        wl5CheckBox = new QCheckBox(groupBox_2);
        wl5CheckBox->setObjectName(QStringLiteral("wl5CheckBox"));

        horizontalLayout_5->addWidget(wl5CheckBox);

        wl5SpinBox = new QSpinBox(groupBox_2);
        wl5SpinBox->setObjectName(QStringLiteral("wl5SpinBox"));
        wl5SpinBox->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        wl5SpinBox->setMinimum(200);
        wl5SpinBox->setMaximum(850);

        horizontalLayout_5->addWidget(wl5SpinBox);

        label_5 = new QLabel(groupBox_2);
        label_5->setObjectName(QStringLiteral("label_5"));

        horizontalLayout_5->addWidget(label_5);

        cf5DoubleSpinBox = new QDoubleSpinBox(groupBox_2);
        cf5DoubleSpinBox->setObjectName(QStringLiteral("cf5DoubleSpinBox"));
        cf5DoubleSpinBox->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        cf5DoubleSpinBox->setMaximum(1000);
        cf5DoubleSpinBox->setValue(1);

        horizontalLayout_5->addWidget(cf5DoubleSpinBox);

        horizontalLayout_5->setStretch(1, 1);
        horizontalLayout_5->setStretch(3, 1);

        verticalLayout->addLayout(horizontalLayout_5);


        horizontalLayout_6->addWidget(groupBox_2);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(0);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        cancelPBtn = new QPushButton(UvDialog);
        cancelPBtn->setObjectName(QStringLiteral("cancelPBtn"));

        verticalLayout_2->addWidget(cancelPBtn);

        okPBtn = new QPushButton(UvDialog);
        okPBtn->setObjectName(QStringLiteral("okPBtn"));

        verticalLayout_2->addWidget(okPBtn);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_2->addItem(verticalSpacer);


        horizontalLayout_6->addLayout(verticalLayout_2);

        horizontalLayout_6->setStretch(0, 4);
        horizontalLayout_6->setStretch(1, 1);

        retranslateUi(UvDialog);

        QMetaObject::connectSlotsByName(UvDialog);
    } // setupUi

    void retranslateUi(QDialog *UvDialog)
    {
        UvDialog->setWindowTitle(QApplication::translate("UvDialog", "UV-VIS", 0));
        groupBox_2->setTitle(QApplication::translate("UvDialog", "Watch", 0));
        wl1CheckBox->setText(QApplication::translate("UvDialog", "Wave Length1", 0));
        wl1SpinBox->setSuffix(QApplication::translate("UvDialog", " nm", 0));
        label->setText(QApplication::translate("UvDialog", "Coef1", 0));
        wl2CheckBox->setText(QApplication::translate("UvDialog", "Wave Length2", 0));
        wl2SpinBox->setSuffix(QApplication::translate("UvDialog", " nm", 0));
        label_2->setText(QApplication::translate("UvDialog", "Coef2", 0));
        wl3CheckBox->setText(QApplication::translate("UvDialog", "Wave Length3", 0));
        wl3SpinBox->setSuffix(QApplication::translate("UvDialog", " nm", 0));
        label_3->setText(QApplication::translate("UvDialog", "Coef3", 0));
        wl4CheckBox->setText(QApplication::translate("UvDialog", "Wave Length4", 0));
        wl4SpinBox->setSuffix(QApplication::translate("UvDialog", " nm", 0));
        label_4->setText(QApplication::translate("UvDialog", "Coef4", 0));
        wl5CheckBox->setText(QApplication::translate("UvDialog", "Wave Length5", 0));
        wl5SpinBox->setSuffix(QApplication::translate("UvDialog", " nm", 0));
        label_5->setText(QApplication::translate("UvDialog", "Coef5", 0));
        cancelPBtn->setText(QApplication::translate("UvDialog", "Cancel", 0));
        okPBtn->setText(QApplication::translate("UvDialog", "OK", 0));
    } // retranslateUi

};

namespace Ui {
    class UvDialog: public Ui_UvDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_UVDIALOG_H
