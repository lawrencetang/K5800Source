/********************************************************************************
** Form generated from reading UI file 'madialog.ui'
**
** Created by: Qt User Interface Compiler version 5.4.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MADIALOG_H
#define UI_MADIALOG_H

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
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_MaDialog
{
public:
    QVBoxLayout *verticalLayout_3;
    QHBoxLayout *horizontalLayout_9;
    QVBoxLayout *verticalLayout_2;
    QGroupBox *measureGBox;
    QHBoxLayout *horizontalLayout_6;
    QRadioButton *naRBtn;
    QRadioButton *ptRBtn;
    QGroupBox *methodGBox;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *typeLabel;
    QComboBox *typeComboBox;
    QHBoxLayout *horizontalLayout_5;
    QLabel *waveLabel;
    QSpinBox *waveSpinBox;
    QHBoxLayout *horizontalLayout_2;
    QLabel *ceofLabel;
    QDoubleSpinBox *ceofDoubleSpinBox;
    QHBoxLayout *horizontalLayout_3;
    QLabel *uintLabel;
    QComboBox *uintComboBox;
    QGroupBox *dyeGBox;
    QVBoxLayout *verticalLayout_4;
    QTableWidget *tableWidget;
    QGroupBox *customGBox;
    QHBoxLayout *horizontalLayout_7;
    QLabel *nameLabel;
    QLineEdit *nameLineEdit;
    QLabel *label_2;
    QSpinBox *spinBox;
    QLabel *Label;
    QSpinBox *wlSpinBox;
    QToolButton *addTBtn;
    QHBoxLayout *horizontalLayout_8;
    QSpacerItem *horizontalSpacer;
    QPushButton *cancelPBtn;
    QPushButton *okPBtn;

    void setupUi(QDialog *MaDialog)
    {
        if (MaDialog->objectName().isEmpty())
            MaDialog->setObjectName(QStringLiteral("MaDialog"));
        MaDialog->resize(900, 422);
        MaDialog->setMaximumSize(QSize(900, 480));
        MaDialog->setStyleSheet(QString::fromUtf8("QLabel,QSpinBox,QDoubleSpinBox,QPushButton,QToolButton,QLineEdit,QComboBox{\n"
"	min-height:48px;\n"
"	font: 12pt \"\351\273\221\344\275\223\";\n"
"}\n"
"\n"
"QGroupBox{\n"
"	font: Bold 14pt \"\351\273\221\344\275\223\";\n"
"}\n"
"\n"
"\n"
"QRadioButton::indicator { \n"
"	width: 32px;\n"
"	height: 32px;\n"
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
"QRadioButton ,QCheckBox{\n"
"	spacing: 5px;\n"
"	font: 12pt \"\351\273\221\344\275\223\";\n"
"}\n"
"\n"
"/*spinbox \346\212\254\350\265\267\346\240\267\345\274\217*/\n"
"QTimeEdit::up-button,QDoubleSpinBox::up-button,QSpi"
                        "nBox::up-button {subcontrol-origin:border;\n"
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
"QTimeEdit::up-button:pressed,QDoubleSpinBox::up-button:pressed,QSpinBox::up-button:pressed{subcontrol-origin:border;\n"
"    subcontrol-position:right;\n"
"    image: url(:/icons/up_left.png);\n"
"	background-color: rgb(255, 255, 255);\n"
"    width: 35px;\n"
"    height: 49px;       \n"
"}\n"
"  \n"
"QTimeEdit::down-button:pressed,QDoubleSpinBox::down-button:pressed,QSpinBox::down-button:pressed,QSpinBox::down-button:pressed{\n"
"    subcontrol-p"
                        "osition:left;\n"
"    image: url(:/icons/up_right.png);\n"
"	background-color: rgb(255, 255, 255);\n"
"    width: 35px;\n"
"    height: 49px;   \n"
"}"));
        verticalLayout_3 = new QVBoxLayout(MaDialog);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        horizontalLayout_9 = new QHBoxLayout();
        horizontalLayout_9->setObjectName(QStringLiteral("horizontalLayout_9"));
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        measureGBox = new QGroupBox(MaDialog);
        measureGBox->setObjectName(QStringLiteral("measureGBox"));
        horizontalLayout_6 = new QHBoxLayout(measureGBox);
        horizontalLayout_6->setObjectName(QStringLiteral("horizontalLayout_6"));
        naRBtn = new QRadioButton(measureGBox);
        naRBtn->setObjectName(QStringLiteral("naRBtn"));
        naRBtn->setChecked(true);

        horizontalLayout_6->addWidget(naRBtn);

        ptRBtn = new QRadioButton(measureGBox);
        ptRBtn->setObjectName(QStringLiteral("ptRBtn"));

        horizontalLayout_6->addWidget(ptRBtn);


        verticalLayout_2->addWidget(measureGBox);

        methodGBox = new QGroupBox(MaDialog);
        methodGBox->setObjectName(QStringLiteral("methodGBox"));
        verticalLayout = new QVBoxLayout(methodGBox);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        typeLabel = new QLabel(methodGBox);
        typeLabel->setObjectName(QStringLiteral("typeLabel"));

        horizontalLayout->addWidget(typeLabel);

        typeComboBox = new QComboBox(methodGBox);
        typeComboBox->setObjectName(QStringLiteral("typeComboBox"));
        typeComboBox->setIconSize(QSize(48, 48));

        horizontalLayout->addWidget(typeComboBox);

        horizontalLayout->setStretch(1, 1);

        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        waveLabel = new QLabel(methodGBox);
        waveLabel->setObjectName(QStringLiteral("waveLabel"));

        horizontalLayout_5->addWidget(waveLabel);

        waveSpinBox = new QSpinBox(methodGBox);
        waveSpinBox->setObjectName(QStringLiteral("waveSpinBox"));
        waveSpinBox->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        waveSpinBox->setMinimum(200);
        waveSpinBox->setMaximum(850);

        horizontalLayout_5->addWidget(waveSpinBox);

        horizontalLayout_5->setStretch(1, 1);

        verticalLayout->addLayout(horizontalLayout_5);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        ceofLabel = new QLabel(methodGBox);
        ceofLabel->setObjectName(QStringLiteral("ceofLabel"));

        horizontalLayout_2->addWidget(ceofLabel);

        ceofDoubleSpinBox = new QDoubleSpinBox(methodGBox);
        ceofDoubleSpinBox->setObjectName(QStringLiteral("ceofDoubleSpinBox"));
        ceofDoubleSpinBox->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout_2->addWidget(ceofDoubleSpinBox);

        horizontalLayout_2->setStretch(1, 1);

        verticalLayout->addLayout(horizontalLayout_2);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        uintLabel = new QLabel(methodGBox);
        uintLabel->setObjectName(QStringLiteral("uintLabel"));

        horizontalLayout_3->addWidget(uintLabel);

        uintComboBox = new QComboBox(methodGBox);
        uintComboBox->setObjectName(QStringLiteral("uintComboBox"));
        uintComboBox->setIconSize(QSize(48, 48));

        horizontalLayout_3->addWidget(uintComboBox);

        horizontalLayout_3->setStretch(1, 1);

        verticalLayout->addLayout(horizontalLayout_3);


        verticalLayout_2->addWidget(methodGBox);


        horizontalLayout_9->addLayout(verticalLayout_2);

        dyeGBox = new QGroupBox(MaDialog);
        dyeGBox->setObjectName(QStringLiteral("dyeGBox"));
        verticalLayout_4 = new QVBoxLayout(dyeGBox);
        verticalLayout_4->setObjectName(QStringLiteral("verticalLayout_4"));
        tableWidget = new QTableWidget(dyeGBox);
        if (tableWidget->columnCount() < 5)
            tableWidget->setColumnCount(5);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(3, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(4, __qtablewidgetitem4);
        tableWidget->setObjectName(QStringLiteral("tableWidget"));
        tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
        tableWidget->horizontalHeader()->setStretchLastSection(true);
        tableWidget->verticalHeader()->setVisible(false);

        verticalLayout_4->addWidget(tableWidget);

        customGBox = new QGroupBox(dyeGBox);
        customGBox->setObjectName(QStringLiteral("customGBox"));
        horizontalLayout_7 = new QHBoxLayout(customGBox);
        horizontalLayout_7->setObjectName(QStringLiteral("horizontalLayout_7"));
        nameLabel = new QLabel(customGBox);
        nameLabel->setObjectName(QStringLiteral("nameLabel"));

        horizontalLayout_7->addWidget(nameLabel);

        nameLineEdit = new QLineEdit(customGBox);
        nameLineEdit->setObjectName(QStringLiteral("nameLineEdit"));

        horizontalLayout_7->addWidget(nameLineEdit);

        label_2 = new QLabel(customGBox);
        label_2->setObjectName(QStringLiteral("label_2"));

        horizontalLayout_7->addWidget(label_2);

        spinBox = new QSpinBox(customGBox);
        spinBox->setObjectName(QStringLiteral("spinBox"));
        spinBox->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        spinBox->setMaximum(10000000);

        horizontalLayout_7->addWidget(spinBox);

        Label = new QLabel(customGBox);
        Label->setObjectName(QStringLiteral("Label"));

        horizontalLayout_7->addWidget(Label);

        wlSpinBox = new QSpinBox(customGBox);
        wlSpinBox->setObjectName(QStringLiteral("wlSpinBox"));
        wlSpinBox->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        wlSpinBox->setMinimum(200);
        wlSpinBox->setMaximum(850);

        horizontalLayout_7->addWidget(wlSpinBox);

        addTBtn = new QToolButton(customGBox);
        addTBtn->setObjectName(QStringLiteral("addTBtn"));
        addTBtn->setMinimumSize(QSize(50, 50));
        addTBtn->setMaximumSize(QSize(50, 50));

        horizontalLayout_7->addWidget(addTBtn);


        verticalLayout_4->addWidget(customGBox);


        horizontalLayout_9->addWidget(dyeGBox);

        horizontalLayout_9->setStretch(0, 1);
        horizontalLayout_9->setStretch(1, 3);

        verticalLayout_3->addLayout(horizontalLayout_9);

        horizontalLayout_8 = new QHBoxLayout();
        horizontalLayout_8->setSpacing(0);
        horizontalLayout_8->setObjectName(QStringLiteral("horizontalLayout_8"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_8->addItem(horizontalSpacer);

        cancelPBtn = new QPushButton(MaDialog);
        cancelPBtn->setObjectName(QStringLiteral("cancelPBtn"));
        cancelPBtn->setMinimumSize(QSize(140, 50));

        horizontalLayout_8->addWidget(cancelPBtn);

        okPBtn = new QPushButton(MaDialog);
        okPBtn->setObjectName(QStringLiteral("okPBtn"));
        okPBtn->setMinimumSize(QSize(140, 50));

        horizontalLayout_8->addWidget(okPBtn);


        verticalLayout_3->addLayout(horizontalLayout_8);

        verticalLayout_3->setStretch(0, 1);

        retranslateUi(MaDialog);

        QMetaObject::connectSlotsByName(MaDialog);
    } // setupUi

    void retranslateUi(QDialog *MaDialog)
    {
        MaDialog->setWindowTitle(QApplication::translate("MaDialog", "Micro Array", 0));
        measureGBox->setTitle(QApplication::translate("MaDialog", "Measure", 0));
        naRBtn->setText(QApplication::translate("MaDialog", "Nucleic Acid", 0));
        ptRBtn->setText(QApplication::translate("MaDialog", "Protein", 0));
        methodGBox->setTitle(QApplication::translate("MaDialog", "Method", 0));
        typeLabel->setText(QApplication::translate("MaDialog", "Type", 0));
        waveLabel->setText(QApplication::translate("MaDialog", "Wave", 0));
        waveSpinBox->setSuffix(QApplication::translate("MaDialog", " nm", 0));
        ceofLabel->setText(QApplication::translate("MaDialog", "Coef", 0));
        uintLabel->setText(QApplication::translate("MaDialog", "Unit", 0));
        dyeGBox->setTitle(QApplication::translate("MaDialog", "Dye", 0));
        QTableWidgetItem *___qtablewidgetitem = tableWidget->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QApplication::translate("MaDialog", "Name", 0));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidget->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QApplication::translate("MaDialog", "1/M*cm", 0));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidget->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QApplication::translate("MaDialog", "Wave Length", 0));
        QTableWidgetItem *___qtablewidgetitem3 = tableWidget->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QApplication::translate("MaDialog", "260nm%", 0));
        QTableWidgetItem *___qtablewidgetitem4 = tableWidget->horizontalHeaderItem(4);
        ___qtablewidgetitem4->setText(QApplication::translate("MaDialog", "280nm%", 0));
        customGBox->setTitle(QApplication::translate("MaDialog", "Custom", 0));
        nameLabel->setText(QApplication::translate("MaDialog", "Name", 0));
        label_2->setText(QApplication::translate("MaDialog", "1/M*cm", 0));
        Label->setText(QApplication::translate("MaDialog", "Wave Length", 0));
        wlSpinBox->setSuffix(QApplication::translate("MaDialog", " nm", 0));
        addTBtn->setText(QApplication::translate("MaDialog", "Add", 0));
        cancelPBtn->setText(QApplication::translate("MaDialog", "Cancel", 0));
        okPBtn->setText(QApplication::translate("MaDialog", "OK", 0));
    } // retranslateUi

};

namespace Ui {
    class MaDialog: public Ui_MaDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MADIALOG_H
