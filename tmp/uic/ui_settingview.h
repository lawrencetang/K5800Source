/********************************************************************************
** Form generated from reading UI file 'settingview.ui'
**
** Created by: Qt User Interface Compiler version 5.4.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SETTINGVIEW_H
#define UI_SETTINGVIEW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFrame>
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
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_SettingView
{
public:
    QHBoxLayout *horizontalLayout_14;
    QGroupBox *systemGBox;
    QVBoxLayout *verticalLayout_4;
    QGroupBox *measureGBox;
    QHBoxLayout *horizontalLayout_8;
    QRadioButton *microsaleRBtn;
    QRadioButton *cuvetteRBtn;
    QGroupBox *functionGBox;
    QVBoxLayout *verticalLayout_3;
    QCheckBox *adCbox;
    QCheckBox *amCBox;
    QGroupBox *channelGBox;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_3;
    QLabel *unLabel;
    QSpinBox *unSpinBox;
    QHBoxLayout *horizontalLayout_2;
    QLabel *mnLabel;
    QSpinBox *mnSpinBox;
    QGroupBox *stirGBox;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout_4;
    QLabel *rsLabel;
    QSpinBox *rsSpinBox;
    QHBoxLayout *horizontalLayout_5;
    QLabel *ktLabel;
    QSpinBox *ktSpinBox;
    QHBoxLayout *horizontalLayout_6;
    QLabel *rtLabel;
    QSpinBox *rtSpinBox;
    QHBoxLayout *horizontalLayout_7;
    QLabel *itLabel;
    QSpinBox *itSpinBox;
    QVBoxLayout *verticalLayout_8;
    QGroupBox *customGBox;
    QHBoxLayout *horizontalLayout_13;
    QGroupBox *sampleGBox;
    QVBoxLayout *verticalLayout_6;
    QHBoxLayout *horizontalLayout_9;
    QLabel *idLabel;
    QLineEdit *idLineEdit;
    QHBoxLayout *horizontalLayout_11;
    QLabel *nameLabel;
    QLineEdit *nameLineEdit;
    QGroupBox *baseGBox;
    QVBoxLayout *verticalLayout_7;
    QHBoxLayout *horizontalLayout_10;
    QLabel *blLabel;
    QSpinBox *blSpinBox;
    QHBoxLayout *horizontalLayout_12;
    QRadioButton *radioButtonDefault;
    QLabel *opLabel;
    QComboBox *opComboBox;
    QGroupBox *caseGBox;
    QVBoxLayout *verticalLayout_5;
    QTableWidget *tableWidget;
    QHBoxLayout *horizontalLayout;
    QPushButton *addPBtn;
    QPushButton *editPBtn;
    QPushButton *removePBtn;
    QSpacerItem *horizontalSpacer;
    QPushButton *cancelPBtn;
    QPushButton *okPBtn;

    void setupUi(QFrame *SettingView)
    {
        if (SettingView->objectName().isEmpty())
            SettingView->setObjectName(QStringLiteral("SettingView"));
        SettingView->resize(1113, 676);
        SettingView->setStyleSheet(QString::fromUtf8("/*RadioButton\346\240\267\345\274\217\350\256\276\347\275\256*/\n"
"QFrame {\n"
"background-color: rgb(255, 255, 255);\n"
"}\n"
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
"/*checkbox\346\240\267\345\274\217\350\256\276\347\275\256*/\n"
"QCheckBox::indicator { \n"
"	width: 64px;\n"
"	height: 32px;\n"
"}\n"
"/*\346\234\252\351\200\211\344\270\255*/\n"
"QCheckBox::indicator::unchecked {	\n"
"	image: "
                        "url(:/icons/uncheck1.png);\n"
"}\n"
"/*\351\200\211\344\270\255*/\n"
"QCheckBox::indicator::checked { \n"
"	image: url(:/icons/check1.png);\n"
"}\n"
"\n"
"QLabel,QComboBox,QSpinBox,QDoubleSpinBox,QLineEdit {\n"
"	font:12pt \"\351\273\221\344\275\223\";\n"
"	min-height:48px;\n"
"}\n"
"\n"
"QPushButton {\n"
"	font:12pt \"\351\273\221\344\275\223\";\n"
"	min-width:144px;\n"
"	min-height:48px\n"
"}\n"
"\n"
"QGroupBox{\n"
"	font: bold 14pt \"\351\273\221\344\275\223\";\n"
"}\n"
"\n"
"/*spinbox \346\212\254\350\265\267\346\240\267\345\274\217*/\n"
"QTimeEdit::up-button,QDoubleSpinBox::up-button,QSpinBox::up-button {subcontrol-origin:border;\n"
"    subcontrol-position:right;\n"
"	image: url(:/icons/up_left.png);\n"
"	background-color: rgb(255, 255, 255);\n"
"    width: 50px;\n"
"    height: 50px;       \n"
"}\n"
"QTimeEdit::down-button,QDoubleSpinBox::down-button,QSpinBox::down-button {subcontrol-origin:border;\n"
"    subcontrol-position:left;\n"
"	image: url(:/icons/up_right.png);\n"
"	background-color: rgb(255, 2"
                        "55, 255);\n"
"    width: 50px;\n"
"    height: 50px;\n"
"}\n"
"\n"
"/*\346\214\211\351\222\256\346\214\211\344\270\213\346\240\267\345\274\217*/\n"
"QTimeEdit::up-button:pressed,QDoubleSpinBox::up-button:pressed,QSpinBox::up-button:pressed{subcontrol-origin:border;\n"
"    subcontrol-position:right;\n"
"    image: url(:/icons/up_left.png);\n"
"	background-color: rgb(255, 255, 255);\n"
"    width: 49px;\n"
"    height: 49px;       \n"
"}\n"
"  \n"
"QTimeEdit::down-button:pressed,QDoubleSpinBox::down-button:pressed,QSpinBox::down-button:pressed,QSpinBox::down-button:pressed{\n"
"    subcontrol-position:left;\n"
"    image: url(:/icons/up_right.png);\n"
"	background-color: rgb(255, 255, 255);\n"
"    width: 49px;\n"
"    height: 49px;   \n"
"}\n"
""));
        SettingView->setFrameShape(QFrame::StyledPanel);
        SettingView->setFrameShadow(QFrame::Raised);
        horizontalLayout_14 = new QHBoxLayout(SettingView);
        horizontalLayout_14->setObjectName(QStringLiteral("horizontalLayout_14"));
        systemGBox = new QGroupBox(SettingView);
        systemGBox->setObjectName(QStringLiteral("systemGBox"));
        verticalLayout_4 = new QVBoxLayout(systemGBox);
        verticalLayout_4->setSpacing(6);
        verticalLayout_4->setObjectName(QStringLiteral("verticalLayout_4"));
        verticalLayout_4->setContentsMargins(-1, 6, -1, 6);
        measureGBox = new QGroupBox(systemGBox);
        measureGBox->setObjectName(QStringLiteral("measureGBox"));
        horizontalLayout_8 = new QHBoxLayout(measureGBox);
        horizontalLayout_8->setSpacing(6);
        horizontalLayout_8->setObjectName(QStringLiteral("horizontalLayout_8"));
        horizontalLayout_8->setContentsMargins(-1, 6, -1, 6);
        microsaleRBtn = new QRadioButton(measureGBox);
        microsaleRBtn->setObjectName(QStringLiteral("microsaleRBtn"));
        microsaleRBtn->setChecked(true);

        horizontalLayout_8->addWidget(microsaleRBtn);

        cuvetteRBtn = new QRadioButton(measureGBox);
        cuvetteRBtn->setObjectName(QStringLiteral("cuvetteRBtn"));

        horizontalLayout_8->addWidget(cuvetteRBtn);


        verticalLayout_4->addWidget(measureGBox);

        functionGBox = new QGroupBox(systemGBox);
        functionGBox->setObjectName(QStringLiteral("functionGBox"));
        verticalLayout_3 = new QVBoxLayout(functionGBox);
        verticalLayout_3->setSpacing(3);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        verticalLayout_3->setContentsMargins(-1, 3, -1, 3);
        adCbox = new QCheckBox(functionGBox);
        adCbox->setObjectName(QStringLiteral("adCbox"));
        adCbox->setChecked(true);

        verticalLayout_3->addWidget(adCbox);

        amCBox = new QCheckBox(functionGBox);
        amCBox->setObjectName(QStringLiteral("amCBox"));
        amCBox->setChecked(false);

        verticalLayout_3->addWidget(amCBox);


        verticalLayout_4->addWidget(functionGBox);

        channelGBox = new QGroupBox(systemGBox);
        channelGBox->setObjectName(QStringLiteral("channelGBox"));
        verticalLayout = new QVBoxLayout(channelGBox);
        verticalLayout->setSpacing(3);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(-1, 3, -1, 3);
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        unLabel = new QLabel(channelGBox);
        unLabel->setObjectName(QStringLiteral("unLabel"));

        horizontalLayout_3->addWidget(unLabel);

        unSpinBox = new QSpinBox(channelGBox);
        unSpinBox->setObjectName(QStringLiteral("unSpinBox"));
        unSpinBox->setMinimumSize(QSize(0, 50));
        unSpinBox->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout_3->addWidget(unSpinBox);

        horizontalLayout_3->setStretch(1, 1);

        verticalLayout->addLayout(horizontalLayout_3);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        mnLabel = new QLabel(channelGBox);
        mnLabel->setObjectName(QStringLiteral("mnLabel"));

        horizontalLayout_2->addWidget(mnLabel);

        mnSpinBox = new QSpinBox(channelGBox);
        mnSpinBox->setObjectName(QStringLiteral("mnSpinBox"));
        mnSpinBox->setMinimumSize(QSize(0, 50));
        mnSpinBox->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        mnSpinBox->setReadOnly(true);
        mnSpinBox->setMinimum(1);
        mnSpinBox->setMaximum(8);

        horizontalLayout_2->addWidget(mnSpinBox);

        horizontalLayout_2->setStretch(1, 1);

        verticalLayout->addLayout(horizontalLayout_2);


        verticalLayout_4->addWidget(channelGBox);

        stirGBox = new QGroupBox(systemGBox);
        stirGBox->setObjectName(QStringLiteral("stirGBox"));
        verticalLayout_2 = new QVBoxLayout(stirGBox);
        verticalLayout_2->setSpacing(3);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(9, 3, 9, 3);
        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        rsLabel = new QLabel(stirGBox);
        rsLabel->setObjectName(QStringLiteral("rsLabel"));

        horizontalLayout_4->addWidget(rsLabel);

        rsSpinBox = new QSpinBox(stirGBox);
        rsSpinBox->setObjectName(QStringLiteral("rsSpinBox"));
        rsSpinBox->setMinimumSize(QSize(0, 50));
        rsSpinBox->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        rsSpinBox->setMinimum(1);
        rsSpinBox->setMaximum(3);

        horizontalLayout_4->addWidget(rsSpinBox);

        horizontalLayout_4->setStretch(1, 1);

        verticalLayout_2->addLayout(horizontalLayout_4);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        ktLabel = new QLabel(stirGBox);
        ktLabel->setObjectName(QStringLiteral("ktLabel"));

        horizontalLayout_5->addWidget(ktLabel);

        ktSpinBox = new QSpinBox(stirGBox);
        ktSpinBox->setObjectName(QStringLiteral("ktSpinBox"));
        ktSpinBox->setMinimumSize(QSize(0, 50));
        ktSpinBox->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        ktSpinBox->setMinimum(0);
        ktSpinBox->setMaximum(1000);
        ktSpinBox->setValue(0);

        horizontalLayout_5->addWidget(ktSpinBox);

        horizontalLayout_5->setStretch(1, 1);

        verticalLayout_2->addLayout(horizontalLayout_5);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName(QStringLiteral("horizontalLayout_6"));
        rtLabel = new QLabel(stirGBox);
        rtLabel->setObjectName(QStringLiteral("rtLabel"));

        horizontalLayout_6->addWidget(rtLabel);

        rtSpinBox = new QSpinBox(stirGBox);
        rtSpinBox->setObjectName(QStringLiteral("rtSpinBox"));
        rtSpinBox->setMinimumSize(QSize(0, 50));
        rtSpinBox->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        rtSpinBox->setMaximum(1000);
        rtSpinBox->setValue(0);

        horizontalLayout_6->addWidget(rtSpinBox);

        horizontalLayout_6->setStretch(1, 1);

        verticalLayout_2->addLayout(horizontalLayout_6);

        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setObjectName(QStringLiteral("horizontalLayout_7"));
        itLabel = new QLabel(stirGBox);
        itLabel->setObjectName(QStringLiteral("itLabel"));

        horizontalLayout_7->addWidget(itLabel);

        itSpinBox = new QSpinBox(stirGBox);
        itSpinBox->setObjectName(QStringLiteral("itSpinBox"));
        itSpinBox->setMinimumSize(QSize(0, 50));
        itSpinBox->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        itSpinBox->setMaximum(1000);
        itSpinBox->setValue(0);

        horizontalLayout_7->addWidget(itSpinBox);

        horizontalLayout_7->setStretch(1, 1);

        verticalLayout_2->addLayout(horizontalLayout_7);


        verticalLayout_4->addWidget(stirGBox);

        verticalLayout_4->setStretch(3, 1);

        horizontalLayout_14->addWidget(systemGBox);

        verticalLayout_8 = new QVBoxLayout();
        verticalLayout_8->setObjectName(QStringLiteral("verticalLayout_8"));
        customGBox = new QGroupBox(SettingView);
        customGBox->setObjectName(QStringLiteral("customGBox"));
        horizontalLayout_13 = new QHBoxLayout(customGBox);
        horizontalLayout_13->setObjectName(QStringLiteral("horizontalLayout_13"));
        sampleGBox = new QGroupBox(customGBox);
        sampleGBox->setObjectName(QStringLiteral("sampleGBox"));
        verticalLayout_6 = new QVBoxLayout(sampleGBox);
        verticalLayout_6->setObjectName(QStringLiteral("verticalLayout_6"));
        horizontalLayout_9 = new QHBoxLayout();
        horizontalLayout_9->setObjectName(QStringLiteral("horizontalLayout_9"));
        idLabel = new QLabel(sampleGBox);
        idLabel->setObjectName(QStringLiteral("idLabel"));

        horizontalLayout_9->addWidget(idLabel);

        idLineEdit = new QLineEdit(sampleGBox);
        idLineEdit->setObjectName(QStringLiteral("idLineEdit"));
        idLineEdit->setClearButtonEnabled(true);

        horizontalLayout_9->addWidget(idLineEdit);


        verticalLayout_6->addLayout(horizontalLayout_9);

        horizontalLayout_11 = new QHBoxLayout();
        horizontalLayout_11->setObjectName(QStringLiteral("horizontalLayout_11"));
        nameLabel = new QLabel(sampleGBox);
        nameLabel->setObjectName(QStringLiteral("nameLabel"));

        horizontalLayout_11->addWidget(nameLabel);

        nameLineEdit = new QLineEdit(sampleGBox);
        nameLineEdit->setObjectName(QStringLiteral("nameLineEdit"));
        nameLineEdit->setClearButtonEnabled(true);

        horizontalLayout_11->addWidget(nameLineEdit);


        verticalLayout_6->addLayout(horizontalLayout_11);


        horizontalLayout_13->addWidget(sampleGBox);

        baseGBox = new QGroupBox(customGBox);
        baseGBox->setObjectName(QStringLiteral("baseGBox"));
        verticalLayout_7 = new QVBoxLayout(baseGBox);
        verticalLayout_7->setObjectName(QStringLiteral("verticalLayout_7"));
        horizontalLayout_10 = new QHBoxLayout();
        horizontalLayout_10->setObjectName(QStringLiteral("horizontalLayout_10"));
        blLabel = new QLabel(baseGBox);
        blLabel->setObjectName(QStringLiteral("blLabel"));

        horizontalLayout_10->addWidget(blLabel);

        blSpinBox = new QSpinBox(baseGBox);
        blSpinBox->setObjectName(QStringLiteral("blSpinBox"));
        blSpinBox->setMinimumSize(QSize(0, 50));
        blSpinBox->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        blSpinBox->setMinimum(200);
        blSpinBox->setMaximum(850);
        blSpinBox->setValue(340);

        horizontalLayout_10->addWidget(blSpinBox);

        horizontalLayout_10->setStretch(1, 1);

        verticalLayout_7->addLayout(horizontalLayout_10);

        horizontalLayout_12 = new QHBoxLayout();
        horizontalLayout_12->setObjectName(QStringLiteral("horizontalLayout_12"));
        radioButtonDefault = new QRadioButton(baseGBox);
        radioButtonDefault->setObjectName(QStringLiteral("radioButtonDefault"));
        radioButtonDefault->setChecked(true);

        horizontalLayout_12->addWidget(radioButtonDefault);

        opLabel = new QLabel(baseGBox);
        opLabel->setObjectName(QStringLiteral("opLabel"));

        horizontalLayout_12->addWidget(opLabel);

        opComboBox = new QComboBox(baseGBox);
        opComboBox->setObjectName(QStringLiteral("opComboBox"));
        opComboBox->setMinimumSize(QSize(0, 50));
        opComboBox->setIconSize(QSize(48, 48));

        horizontalLayout_12->addWidget(opComboBox);

        horizontalLayout_12->setStretch(2, 1);

        verticalLayout_7->addLayout(horizontalLayout_12);


        horizontalLayout_13->addWidget(baseGBox);


        verticalLayout_8->addWidget(customGBox);

        caseGBox = new QGroupBox(SettingView);
        caseGBox->setObjectName(QStringLiteral("caseGBox"));
        verticalLayout_5 = new QVBoxLayout(caseGBox);
        verticalLayout_5->setObjectName(QStringLiteral("verticalLayout_5"));
        tableWidget = new QTableWidget(caseGBox);
        tableWidget->setObjectName(QStringLiteral("tableWidget"));
        tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
        tableWidget->setSelectionMode(QAbstractItemView::SingleSelection);
        tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);

        verticalLayout_5->addWidget(tableWidget);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(0);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        addPBtn = new QPushButton(caseGBox);
        addPBtn->setObjectName(QStringLiteral("addPBtn"));

        horizontalLayout->addWidget(addPBtn);

        editPBtn = new QPushButton(caseGBox);
        editPBtn->setObjectName(QStringLiteral("editPBtn"));

        horizontalLayout->addWidget(editPBtn);

        removePBtn = new QPushButton(caseGBox);
        removePBtn->setObjectName(QStringLiteral("removePBtn"));

        horizontalLayout->addWidget(removePBtn);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        cancelPBtn = new QPushButton(caseGBox);
        cancelPBtn->setObjectName(QStringLiteral("cancelPBtn"));

        horizontalLayout->addWidget(cancelPBtn);

        okPBtn = new QPushButton(caseGBox);
        okPBtn->setObjectName(QStringLiteral("okPBtn"));

        horizontalLayout->addWidget(okPBtn);


        verticalLayout_5->addLayout(horizontalLayout);


        verticalLayout_8->addWidget(caseGBox);

        verticalLayout_8->setStretch(1, 1);

        horizontalLayout_14->addLayout(verticalLayout_8);

        horizontalLayout_14->setStretch(0, 1);
        horizontalLayout_14->setStretch(1, 3);

        retranslateUi(SettingView);

        QMetaObject::connectSlotsByName(SettingView);
    } // setupUi

    void retranslateUi(QFrame *SettingView)
    {
        SettingView->setWindowTitle(QApplication::translate("SettingView", "Frame", 0));
        systemGBox->setTitle(QApplication::translate("SettingView", "System", 0));
        measureGBox->setTitle(QApplication::translate("SettingView", "Measure", 0));
        microsaleRBtn->setText(QApplication::translate("SettingView", "Microscale", 0));
        cuvetteRBtn->setText(QApplication::translate("SettingView", "Cuvette", 0));
        functionGBox->setTitle(QApplication::translate("SettingView", "Function", 0));
        adCbox->setText(QApplication::translate("SettingView", "Auto Detection Fault", 0));
        amCBox->setText(QApplication::translate("SettingView", "Auto Measure", 0));
        channelGBox->setTitle(QApplication::translate("SettingView", "Channel", 0));
        unLabel->setText(QApplication::translate("SettingView", "Use Number", 0));
        mnLabel->setText(QApplication::translate("SettingView", "Max Number", 0));
        stirGBox->setTitle(QApplication::translate("SettingView", "Stir", 0));
        rsLabel->setText(QApplication::translate("SettingView", "Run Speed ", 0));
        rsSpinBox->setSuffix(QApplication::translate("SettingView", " Level", 0));
        ktLabel->setText(QApplication::translate("SettingView", "Stir Time ", 0));
        ktSpinBox->setSuffix(QApplication::translate("SettingView", "min", 0));
        rtLabel->setText(QApplication::translate("SettingView", "Rest Time ", 0));
        rtSpinBox->setSuffix(QApplication::translate("SettingView", "min", 0));
        itLabel->setText(QApplication::translate("SettingView", "Intervals ", 0));
        itSpinBox->setSuffix(QApplication::translate("SettingView", "min", 0));
        customGBox->setTitle(QApplication::translate("SettingView", "Custom", 0));
        sampleGBox->setTitle(QApplication::translate("SettingView", "Sample", 0));
        idLabel->setText(QApplication::translate("SettingView", "Sample ID  ", 0));
        idLineEdit->setInputMask(QString());
        idLineEdit->setText(QApplication::translate("SettingView", "1", 0));
        idLineEdit->setPlaceholderText(QApplication::translate("SettingView", "Please input id", 0));
        nameLabel->setText(QApplication::translate("SettingView", "Sample Name", 0));
        nameLineEdit->setText(QApplication::translate("SettingView", "KAIAO", 0));
        nameLineEdit->setPlaceholderText(QApplication::translate("SettingView", "Please input name", 0));
        baseGBox->setTitle(QApplication::translate("SettingView", "Base", 0));
        blLabel->setText(QApplication::translate("SettingView", "BaseLine", 0));
        blSpinBox->setSuffix(QApplication::translate("SettingView", " nm", 0));
        radioButtonDefault->setText(QApplication::translate("SettingView", "Default", 0));
        opLabel->setText(QApplication::translate("SettingView", "  Optical ", 0));
        caseGBox->setTitle(QString());
        addPBtn->setText(QApplication::translate("SettingView", "Add", 0));
        editPBtn->setText(QApplication::translate("SettingView", "Edit", 0));
        removePBtn->setText(QApplication::translate("SettingView", "Remove", 0));
        cancelPBtn->setText(QApplication::translate("SettingView", "Cancel", 0));
        okPBtn->setText(QApplication::translate("SettingView", "OK", 0));
    } // retranslateUi

};

namespace Ui {
    class SettingView: public Ui_SettingView {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SETTINGVIEW_H
