/********************************************************************************
** Form generated from reading UI file 'dataview.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DATAVIEW_H
#define UI_DATAVIEW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_DataView
{
public:
    QVBoxLayout *verticalLayout;
    QComboBox *comboBox;
    QSpacerItem *verticalSpacer;
    QHBoxLayout *horizontalLayout;
    QPushButton *moveToBtn;
    QPushButton *deleteBtn;

    void setupUi(QFrame *DataView)
    {
        if (DataView->objectName().isEmpty())
            DataView->setObjectName(QStringLiteral("DataView"));
        DataView->resize(285, 486);
        DataView->setStyleSheet(QStringLiteral(""));
        DataView->setFrameShape(QFrame::StyledPanel);
        DataView->setFrameShadow(QFrame::Raised);
        verticalLayout = new QVBoxLayout(DataView);
        verticalLayout->setSpacing(1);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        comboBox = new QComboBox(DataView);
        comboBox->setObjectName(QStringLiteral("comboBox"));
        comboBox->setMinimumSize(QSize(0, 40));
        QFont font;
        font.setFamily(QString::fromUtf8("\345\276\256\350\275\257\351\233\205\351\273\221"));
        font.setPointSize(14);
        comboBox->setFont(font);
        comboBox->setIconSize(QSize(48, 48));

        verticalLayout->addWidget(comboBox);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(1);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        moveToBtn = new QPushButton(DataView);
        moveToBtn->setObjectName(QStringLiteral("moveToBtn"));
        moveToBtn->setMinimumSize(QSize(0, 48));
        moveToBtn->setFont(font);

        horizontalLayout->addWidget(moveToBtn);

        deleteBtn = new QPushButton(DataView);
        deleteBtn->setObjectName(QStringLiteral("deleteBtn"));
        deleteBtn->setMinimumSize(QSize(0, 48));
        deleteBtn->setFont(font);

        horizontalLayout->addWidget(deleteBtn);


        verticalLayout->addLayout(horizontalLayout);


        retranslateUi(DataView);

        QMetaObject::connectSlotsByName(DataView);
    } // setupUi

    void retranslateUi(QFrame *DataView)
    {
        DataView->setWindowTitle(QApplication::translate("DataView", "Frame", 0));
        moveToBtn->setText(QApplication::translate("DataView", "Move to", 0));
        deleteBtn->setText(QApplication::translate("DataView", "Delete", 0));
    } // retranslateUi

};

namespace Ui {
    class DataView: public Ui_DataView {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DATAVIEW_H
