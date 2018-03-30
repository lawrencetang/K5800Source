/********************************************************************************
** Form generated from reading UI file 'kmdialog.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_KMDIALOG_H
#define UI_KMDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_KmDialog
{
public:
    QHBoxLayout *horizontalLayout_6;
    QGroupBox *groupBox;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *typeLabel;
    QComboBox *typeComboBox;
    QHBoxLayout *horizontalLayout_5;
    QLabel *waveLabel;
    QSpinBox *waveSpinBox;
    QVBoxLayout *verticalLayout_2;
    QPushButton *cancelPBtn;
    QPushButton *okPBtn;
    QSpacerItem *verticalSpacer;

    void setupUi(QDialog *KmDialog)
    {
        if (KmDialog->objectName().isEmpty())
            KmDialog->setObjectName(QStringLiteral("KmDialog"));
        KmDialog->resize(465, 172);
        KmDialog->setStyleSheet(QString::fromUtf8("QLabel,QSpinBox,QDoubleSpinBox,QPushButton,QLineEdit,QComboBox{\n"
"	min-height:48px;\n"
"	font: 12pt \"\351\273\221\344\275\223\";\n"
"}\n"
"\n"
"QGroupBox{\n"
"	font: Bold 14pt \"\351\273\221\344\275\223\";\n"
"}\n"
"\n"
"QDialog{\n"
"	background-color: rgb(255, 255, 255);\n"
"}\n"
"\n"
"/*spinbox \346\212\254\350\265\267\346\240\267\345\274\217*/\n"
"QTimeEdit::up-button,QDoubleSpinBox::up-button,QSpinBox::up-button {subcontrol-origin:border;\n"
"    subcontrol-position:right;\n"
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
"QTimeEdit::up-button:pressed,QDoubleSpinBox:"
                        ":up-button:pressed,QSpinBox::up-button:pressed{subcontrol-origin:border;\n"
"    subcontrol-position:right;\n"
"    image: url(:/icons/up_left.png);\n"
"	background-color: rgb(255, 255, 255);\n"
"    width: 35px;\n"
"    height: 49px;       \n"
"}\n"
"  \n"
"QTimeEdit::down-button:pressed,QDoubleSpinBox::down-button:pressed,QSpinBox::down-button:pressed,QSpinBox::down-button:pressed{\n"
"    subcontrol-position:left;\n"
"    image: url(:/icons/up_right.png);\n"
"	background-color: rgb(255, 255, 255);\n"
"    width: 35px;\n"
"    height: 49px;   \n"
"}"));
        horizontalLayout_6 = new QHBoxLayout(KmDialog);
        horizontalLayout_6->setObjectName(QStringLiteral("horizontalLayout_6"));
        groupBox = new QGroupBox(KmDialog);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        verticalLayout = new QVBoxLayout(groupBox);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        typeLabel = new QLabel(groupBox);
        typeLabel->setObjectName(QStringLiteral("typeLabel"));

        horizontalLayout->addWidget(typeLabel);

        typeComboBox = new QComboBox(groupBox);
        typeComboBox->setObjectName(QStringLiteral("typeComboBox"));
        typeComboBox->setIconSize(QSize(48, 48));

        horizontalLayout->addWidget(typeComboBox);

        horizontalLayout->setStretch(1, 1);

        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        waveLabel = new QLabel(groupBox);
        waveLabel->setObjectName(QStringLiteral("waveLabel"));

        horizontalLayout_5->addWidget(waveLabel);

        waveSpinBox = new QSpinBox(groupBox);
        waveSpinBox->setObjectName(QStringLiteral("waveSpinBox"));
        waveSpinBox->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        waveSpinBox->setMinimum(200);
        waveSpinBox->setMaximum(850);

        horizontalLayout_5->addWidget(waveSpinBox);

        horizontalLayout_5->setStretch(1, 1);

        verticalLayout->addLayout(horizontalLayout_5);


        horizontalLayout_6->addWidget(groupBox);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(0);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        cancelPBtn = new QPushButton(KmDialog);
        cancelPBtn->setObjectName(QStringLiteral("cancelPBtn"));

        verticalLayout_2->addWidget(cancelPBtn);

        okPBtn = new QPushButton(KmDialog);
        okPBtn->setObjectName(QStringLiteral("okPBtn"));

        verticalLayout_2->addWidget(okPBtn);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_2->addItem(verticalSpacer);


        horizontalLayout_6->addLayout(verticalLayout_2);

        horizontalLayout_6->setStretch(0, 2);
        horizontalLayout_6->setStretch(1, 1);

        retranslateUi(KmDialog);

        QMetaObject::connectSlotsByName(KmDialog);
    } // setupUi

    void retranslateUi(QDialog *KmDialog)
    {
        KmDialog->setWindowTitle(QApplication::translate("KmDialog", "Kit Method", 0));
        groupBox->setTitle(QApplication::translate("KmDialog", "Method", 0));
        typeLabel->setText(QApplication::translate("KmDialog", "Type", 0));
        waveLabel->setText(QApplication::translate("KmDialog", "Wave", 0));
        waveSpinBox->setSuffix(QApplication::translate("KmDialog", " nm", 0));
        cancelPBtn->setText(QApplication::translate("KmDialog", "Cancel", 0));
        okPBtn->setText(QApplication::translate("KmDialog", "OK", 0));
    } // retranslateUi

};

namespace Ui {
    class KmDialog: public Ui_KmDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_KMDIALOG_H
