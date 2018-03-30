/********************************************************************************
** Form generated from reading UI file 'fsdialog.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FSDIALOG_H
#define UI_FSDIALOG_H

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
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_FsDialog
{
public:
    QHBoxLayout *horizontalLayout_3;
    QGroupBox *groupBox;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *concLabel;
    QDoubleSpinBox *concDoubleSpinBox;
    QHBoxLayout *horizontalLayout_2;
    QLabel *unitLabel;
    QComboBox *unitComboBox;
    QVBoxLayout *verticalLayout_2;
    QPushButton *cancelPBtn;
    QPushButton *okPBtn;
    QSpacerItem *verticalSpacer;

    void setupUi(QDialog *FsDialog)
    {
        if (FsDialog->objectName().isEmpty())
            FsDialog->setObjectName(QStringLiteral("FsDialog"));
        FsDialog->resize(462, 167);
        FsDialog->setStyleSheet(QString::fromUtf8("QLabel,QSpinBox,QDoubleSpinBox,QPushButton,QLineEdit,QComboBox{\n"
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
        horizontalLayout_3 = new QHBoxLayout(FsDialog);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        groupBox = new QGroupBox(FsDialog);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setStyleSheet(QStringLiteral(""));
        verticalLayout = new QVBoxLayout(groupBox);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        concLabel = new QLabel(groupBox);
        concLabel->setObjectName(QStringLiteral("concLabel"));

        horizontalLayout->addWidget(concLabel);

        concDoubleSpinBox = new QDoubleSpinBox(groupBox);
        concDoubleSpinBox->setObjectName(QStringLiteral("concDoubleSpinBox"));
        concDoubleSpinBox->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        concDoubleSpinBox->setDecimals(6);
        concDoubleSpinBox->setMaximum(1e+14);

        horizontalLayout->addWidget(concDoubleSpinBox);

        horizontalLayout->setStretch(1, 1);

        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        unitLabel = new QLabel(groupBox);
        unitLabel->setObjectName(QStringLiteral("unitLabel"));

        horizontalLayout_2->addWidget(unitLabel);

        unitComboBox = new QComboBox(groupBox);
        unitComboBox->setObjectName(QStringLiteral("unitComboBox"));
        unitComboBox->setIconSize(QSize(48, 48));

        horizontalLayout_2->addWidget(unitComboBox);

        horizontalLayout_2->setStretch(1, 1);

        verticalLayout->addLayout(horizontalLayout_2);


        horizontalLayout_3->addWidget(groupBox);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(0);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        cancelPBtn = new QPushButton(FsDialog);
        cancelPBtn->setObjectName(QStringLiteral("cancelPBtn"));

        verticalLayout_2->addWidget(cancelPBtn);

        okPBtn = new QPushButton(FsDialog);
        okPBtn->setObjectName(QStringLiteral("okPBtn"));

        verticalLayout_2->addWidget(okPBtn);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_2->addItem(verticalSpacer);


        horizontalLayout_3->addLayout(verticalLayout_2);

        horizontalLayout_3->setStretch(0, 2);
        horizontalLayout_3->setStretch(1, 1);

        retranslateUi(FsDialog);

        QMetaObject::connectSlotsByName(FsDialog);
    } // setupUi

    void retranslateUi(QDialog *FsDialog)
    {
        FsDialog->setWindowTitle(QApplication::translate("FsDialog", "ConcSetting", 0));
        groupBox->setTitle(QApplication::translate("FsDialog", "Setting", 0));
        concLabel->setText(QApplication::translate("FsDialog", "Conc", 0));
        unitLabel->setText(QApplication::translate("FsDialog", "Unit", 0));
        cancelPBtn->setText(QApplication::translate("FsDialog", "Cancel", 0));
        okPBtn->setText(QApplication::translate("FsDialog", "OK", 0));
    } // retranslateUi

};

namespace Ui {
    class FsDialog: public Ui_FsDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FSDIALOG_H
