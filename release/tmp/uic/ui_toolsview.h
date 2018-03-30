/********************************************************************************
** Form generated from reading UI file 'toolsview.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TOOLSVIEW_H
#define UI_TOOLSVIEW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_ToolsView
{
public:
    QVBoxLayout *verticalLayout;
    QSpacerItem *verticalSpacer_2;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QToolButton *datatBtn;
    QToolButton *recordtBtn;
    QToolButton *oligotBtn;
    QToolButton *cameratBtn;
    QSpacerItem *horizontalSpacer_2;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer_3;
    QToolButton *mergetBtn;
    QToolButton *printtBtn;
    QToolButton *picturetBtn;
    QToolButton *helptBtn;
    QSpacerItem *horizontalSpacer_4;
    QSpacerItem *verticalSpacer;

    void setupUi(QDialog *ToolsView)
    {
        if (ToolsView->objectName().isEmpty())
            ToolsView->setObjectName(QStringLiteral("ToolsView"));
        ToolsView->resize(485, 169);
        verticalLayout = new QVBoxLayout(ToolsView);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalSpacer_2 = new QSpacerItem(20, 42, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer_2);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        datatBtn = new QToolButton(ToolsView);
        datatBtn->setObjectName(QStringLiteral("datatBtn"));
        datatBtn->setIconSize(QSize(80, 80));
        datatBtn->setCheckable(true);
        datatBtn->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
        datatBtn->setAutoRaise(true);

        horizontalLayout->addWidget(datatBtn);

        recordtBtn = new QToolButton(ToolsView);
        recordtBtn->setObjectName(QStringLiteral("recordtBtn"));
        recordtBtn->setIconSize(QSize(80, 80));
        recordtBtn->setCheckable(true);
        recordtBtn->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
        recordtBtn->setAutoRaise(true);

        horizontalLayout->addWidget(recordtBtn);

        oligotBtn = new QToolButton(ToolsView);
        oligotBtn->setObjectName(QStringLiteral("oligotBtn"));
        oligotBtn->setIconSize(QSize(80, 80));
        oligotBtn->setCheckable(true);
        oligotBtn->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
        oligotBtn->setAutoRaise(true);

        horizontalLayout->addWidget(oligotBtn);

        cameratBtn = new QToolButton(ToolsView);
        cameratBtn->setObjectName(QStringLiteral("cameratBtn"));
        cameratBtn->setIconSize(QSize(80, 80));
        cameratBtn->setCheckable(true);
        cameratBtn->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
        cameratBtn->setAutoRaise(true);

        horizontalLayout->addWidget(cameratBtn);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_3);

        mergetBtn = new QToolButton(ToolsView);
        mergetBtn->setObjectName(QStringLiteral("mergetBtn"));
        mergetBtn->setIconSize(QSize(80, 80));
        mergetBtn->setCheckable(true);
        mergetBtn->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
        mergetBtn->setAutoRaise(true);

        horizontalLayout_2->addWidget(mergetBtn);

        printtBtn = new QToolButton(ToolsView);
        printtBtn->setObjectName(QStringLiteral("printtBtn"));
        printtBtn->setIconSize(QSize(80, 80));
        printtBtn->setCheckable(false);
        printtBtn->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
        printtBtn->setAutoRaise(true);

        horizontalLayout_2->addWidget(printtBtn);

        picturetBtn = new QToolButton(ToolsView);
        picturetBtn->setObjectName(QStringLiteral("picturetBtn"));
        picturetBtn->setIconSize(QSize(80, 80));
        picturetBtn->setCheckable(false);
        picturetBtn->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
        picturetBtn->setAutoRaise(true);

        horizontalLayout_2->addWidget(picturetBtn);

        helptBtn = new QToolButton(ToolsView);
        helptBtn->setObjectName(QStringLiteral("helptBtn"));
        helptBtn->setIconSize(QSize(80, 80));
        helptBtn->setCheckable(false);
        helptBtn->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
        helptBtn->setAutoRaise(true);

        horizontalLayout_2->addWidget(helptBtn);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_4);


        verticalLayout->addLayout(horizontalLayout_2);

        verticalSpacer = new QSpacerItem(20, 41, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);


        retranslateUi(ToolsView);

        QMetaObject::connectSlotsByName(ToolsView);
    } // setupUi

    void retranslateUi(QDialog *ToolsView)
    {
        ToolsView->setWindowTitle(QApplication::translate("ToolsView", "Dialog", 0));
        datatBtn->setText(QApplication::translate("ToolsView", "Data View", 0));
        recordtBtn->setText(QApplication::translate("ToolsView", "Record View", 0));
        oligotBtn->setText(QApplication::translate("ToolsView", "Oligo", 0));
        cameratBtn->setText(QApplication::translate("ToolsView", "Camera", 0));
        mergetBtn->setText(QApplication::translate("ToolsView", "Merge", 0));
        printtBtn->setText(QApplication::translate("ToolsView", "Print", 0));
        picturetBtn->setText(QApplication::translate("ToolsView", "Export Image", 0));
        helptBtn->setText(QApplication::translate("ToolsView", "Help", 0));
    } // retranslateUi

};

namespace Ui {
    class ToolsView: public Ui_ToolsView {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TOOLSVIEW_H
