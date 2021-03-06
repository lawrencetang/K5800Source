/********************************************************************************
** Form generated from reading UI file 'ptdialog.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PTDIALOG_H
#define UI_PTDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
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

class Ui_PtDialog
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
    QHBoxLayout *horizontalLayout_2;
    QLabel *coefLabel;
    QDoubleSpinBox *coefDoubleSpinBox;
    QHBoxLayout *horizontalLayout_3;
    QLabel *unitLabel;
    QComboBox *unitComboBox;
    QVBoxLayout *verticalLayout_2;
    QPushButton *cancelPBtn;
    QPushButton *okPBtn;
    QSpacerItem *verticalSpacer;

    void setupUi(QDialog *PtDialog)
    {
        if (PtDialog->objectName().isEmpty())
            PtDialog->setObjectName(QStringLiteral("PtDialog"));
        PtDialog->resize(502, 283);
        PtDialog->setStyleSheet(QString::fromUtf8("QLabel,QSpinBox,QDoubleSpinBox,QPushButton,QLineEdit,QComboBox{\n"
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
        horizontalLayout_6 = new QHBoxLayout(PtDialog);
        horizontalLayout_6->setObjectName(QStringLiteral("horizontalLayout_6"));
        groupBox = new QGroupBox(PtDialog);
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
        waveSpinBox->setStyleSheet(QString::fromUtf8("QLabel,QSpinBox,QDoubleSpinBox,QPushButton,QLineEdit,QComboBox{\n"
"	min-height:48px;\n"
"	font: 12pt \"\351\273\221\344\275\223\";\n"
"}\n"
"\n"
"QGroupBox{\n"
"	font: Bold 14pt \"\351\273\221\344\275\223\";\n"
"}\n"
"\n"
"QDialog{\n"
"	\n"
"	background-color: rgb(255, 255, 255);\n"
"}"));
        waveSpinBox->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        waveSpinBox->setMinimum(200);
        waveSpinBox->setMaximum(850);

        horizontalLayout_5->addWidget(waveSpinBox);

        horizontalLayout_5->setStretch(1, 1);

        verticalLayout->addLayout(horizontalLayout_5);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        coefLabel = new QLabel(groupBox);
        coefLabel->setObjectName(QStringLiteral("coefLabel"));

        horizontalLayout_2->addWidget(coefLabel);

        coefDoubleSpinBox = new QDoubleSpinBox(groupBox);
        coefDoubleSpinBox->setObjectName(QStringLiteral("coefDoubleSpinBox"));
        coefDoubleSpinBox->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout_2->addWidget(coefDoubleSpinBox);

        horizontalLayout_2->setStretch(1, 1);

        verticalLayout->addLayout(horizontalLayout_2);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        unitLabel = new QLabel(groupBox);
        unitLabel->setObjectName(QStringLiteral("unitLabel"));

        horizontalLayout_3->addWidget(unitLabel);

        unitComboBox = new QComboBox(groupBox);
        unitComboBox->setObjectName(QStringLiteral("unitComboBox"));
        unitComboBox->setIconSize(QSize(48, 48));

        horizontalLayout_3->addWidget(unitComboBox);

        horizontalLayout_3->setStretch(1, 1);

        verticalLayout->addLayout(horizontalLayout_3);


        horizontalLayout_6->addWidget(groupBox);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(0);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        cancelPBtn = new QPushButton(PtDialog);
        cancelPBtn->setObjectName(QStringLiteral("cancelPBtn"));

        verticalLayout_2->addWidget(cancelPBtn);

        okPBtn = new QPushButton(PtDialog);
        okPBtn->setObjectName(QStringLiteral("okPBtn"));

        verticalLayout_2->addWidget(okPBtn);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_2->addItem(verticalSpacer);


        horizontalLayout_6->addLayout(verticalLayout_2);

        horizontalLayout_6->setStretch(0, 2);
        horizontalLayout_6->setStretch(1, 1);

        retranslateUi(PtDialog);

        QMetaObject::connectSlotsByName(PtDialog);
    } // setupUi

    void retranslateUi(QDialog *PtDialog)
    {
        PtDialog->setWindowTitle(QApplication::translate("PtDialog", "Protein", 0));
        groupBox->setTitle(QApplication::translate("PtDialog", "Method", 0));
        typeLabel->setText(QApplication::translate("PtDialog", "Type", 0));
        waveLabel->setText(QApplication::translate("PtDialog", "Wave", 0));
        waveSpinBox->setSuffix(QApplication::translate("PtDialog", " nm", 0));
        coefLabel->setText(QApplication::translate("PtDialog", "Coef", 0));
        unitLabel->setText(QApplication::translate("PtDialog", "Unit", 0));
        cancelPBtn->setText(QApplication::translate("PtDialog", "Cancel", 0));
        okPBtn->setText(QApplication::translate("PtDialog", "OK", 0));
    } // retranslateUi

};

namespace Ui {
    class PtDialog: public Ui_PtDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PTDIALOG_H
