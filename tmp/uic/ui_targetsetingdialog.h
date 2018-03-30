/********************************************************************************
** Form generated from reading UI file 'targetsetingdialog.ui'
**
** Created by: Qt User Interface Compiler version 5.4.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TARGETSETINGDIALOG_H
#define UI_TARGETSETINGDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_TargetSetingDialog
{
public:
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label;
    QDoubleSpinBox *doubleSpinBox;
    QHBoxLayout *horizontalLayout;
    QPushButton *cancelpBtn;
    QPushButton *startpBtn;

    void setupUi(QDialog *TargetSetingDialog)
    {
        if (TargetSetingDialog->objectName().isEmpty())
            TargetSetingDialog->setObjectName(QStringLiteral("TargetSetingDialog"));
        TargetSetingDialog->resize(308, 124);
        verticalLayout = new QVBoxLayout(TargetSetingDialog);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        label = new QLabel(TargetSetingDialog);
        label->setObjectName(QStringLiteral("label"));
        QFont font;
        font.setFamily(QString::fromUtf8("\351\273\221\344\275\223"));
        font.setPointSize(14);
        label->setFont(font);

        horizontalLayout_2->addWidget(label);

        doubleSpinBox = new QDoubleSpinBox(TargetSetingDialog);
        doubleSpinBox->setObjectName(QStringLiteral("doubleSpinBox"));
        doubleSpinBox->setMinimumSize(QSize(0, 48));
        doubleSpinBox->setFont(font);
        doubleSpinBox->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        doubleSpinBox->setDecimals(1);
        doubleSpinBox->setValue(25);

        horizontalLayout_2->addWidget(doubleSpinBox);

        horizontalLayout_2->setStretch(1, 1);

        verticalLayout->addLayout(horizontalLayout_2);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(0);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        cancelpBtn = new QPushButton(TargetSetingDialog);
        cancelpBtn->setObjectName(QStringLiteral("cancelpBtn"));
        cancelpBtn->setMinimumSize(QSize(144, 48));
        cancelpBtn->setFont(font);

        horizontalLayout->addWidget(cancelpBtn);

        startpBtn = new QPushButton(TargetSetingDialog);
        startpBtn->setObjectName(QStringLiteral("startpBtn"));
        startpBtn->setMinimumSize(QSize(144, 48));
        startpBtn->setFont(font);

        horizontalLayout->addWidget(startpBtn);


        verticalLayout->addLayout(horizontalLayout);


        retranslateUi(TargetSetingDialog);

        QMetaObject::connectSlotsByName(TargetSetingDialog);
    } // setupUi

    void retranslateUi(QDialog *TargetSetingDialog)
    {
        TargetSetingDialog->setWindowTitle(QApplication::translate("TargetSetingDialog", "TempSetting", 0));
        label->setText(QApplication::translate("TargetSetingDialog", "Target:", 0));
        doubleSpinBox->setSuffix(QApplication::translate("TargetSetingDialog", " \342\204\203", 0));
        cancelpBtn->setText(QApplication::translate("TargetSetingDialog", "Cancel", 0));
        startpBtn->setText(QApplication::translate("TargetSetingDialog", "OK", 0));
    } // retranslateUi

};

namespace Ui {
    class TargetSetingDialog: public Ui_TargetSetingDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TARGETSETINGDIALOG_H
