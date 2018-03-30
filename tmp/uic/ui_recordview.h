/********************************************************************************
** Form generated from reading UI file 'recordview.ui'
**
** Created by: Qt User Interface Compiler version 5.4.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_RECORDVIEW_H
#define UI_RECORDVIEW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_RecordView
{
public:
    QVBoxLayout *verticalLayout;
    QTableWidget *tableWidget;
    QHBoxLayout *horizontalLayout;
    QLabel *sampleLabel;
    QSpacerItem *horizontalSpacer;
    QLineEdit *sampleLineEdit;
    QPushButton *saveAsBtn;
    QPushButton *moveUpBtn;
    QPushButton *hideRowBtn;
    QPushButton *hideColumnBtn;
    QPushButton *clearBtn;

    void setupUi(QFrame *RecordView)
    {
        if (RecordView->objectName().isEmpty())
            RecordView->setObjectName(QStringLiteral("RecordView"));
        RecordView->resize(937, 444);
        RecordView->setFrameShape(QFrame::StyledPanel);
        RecordView->setFrameShadow(QFrame::Raised);
        verticalLayout = new QVBoxLayout(RecordView);
        verticalLayout->setSpacing(1);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        tableWidget = new QTableWidget(RecordView);
        tableWidget->setObjectName(QStringLiteral("tableWidget"));
        tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
        tableWidget->horizontalHeader()->setDefaultSectionSize(100);
        tableWidget->horizontalHeader()->setMinimumSectionSize(50);
        tableWidget->horizontalHeader()->setStretchLastSection(false);

        verticalLayout->addWidget(tableWidget);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(0);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        sampleLabel = new QLabel(RecordView);
        sampleLabel->setObjectName(QStringLiteral("sampleLabel"));
        QFont font;
        font.setFamily(QString::fromUtf8("\345\276\256\350\275\257\351\233\205\351\273\221"));
        font.setPointSize(14);
        font.setBold(true);
        font.setWeight(75);
        sampleLabel->setFont(font);

        horizontalLayout->addWidget(sampleLabel);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        sampleLineEdit = new QLineEdit(RecordView);
        sampleLineEdit->setObjectName(QStringLiteral("sampleLineEdit"));
        sampleLineEdit->setMinimumSize(QSize(144, 48));
        QFont font1;
        font1.setFamily(QString::fromUtf8("\345\276\256\350\275\257\351\233\205\351\273\221"));
        font1.setPointSize(12);
        sampleLineEdit->setFont(font1);

        horizontalLayout->addWidget(sampleLineEdit);

        saveAsBtn = new QPushButton(RecordView);
        saveAsBtn->setObjectName(QStringLiteral("saveAsBtn"));
        saveAsBtn->setMinimumSize(QSize(144, 48));
        QFont font2;
        font2.setFamily(QString::fromUtf8("\345\276\256\350\275\257\351\233\205\351\273\221"));
        font2.setPointSize(14);
        saveAsBtn->setFont(font2);

        horizontalLayout->addWidget(saveAsBtn);

        moveUpBtn = new QPushButton(RecordView);
        moveUpBtn->setObjectName(QStringLiteral("moveUpBtn"));
        moveUpBtn->setMinimumSize(QSize(144, 48));
        moveUpBtn->setFont(font2);
        moveUpBtn->setIconSize(QSize(40, 40));
        moveUpBtn->setCheckable(false);
        moveUpBtn->setFlat(false);

        horizontalLayout->addWidget(moveUpBtn);

        hideRowBtn = new QPushButton(RecordView);
        hideRowBtn->setObjectName(QStringLiteral("hideRowBtn"));
        hideRowBtn->setMinimumSize(QSize(144, 48));
        hideRowBtn->setFont(font2);

        horizontalLayout->addWidget(hideRowBtn);

        hideColumnBtn = new QPushButton(RecordView);
        hideColumnBtn->setObjectName(QStringLiteral("hideColumnBtn"));
        hideColumnBtn->setMinimumSize(QSize(144, 48));
        hideColumnBtn->setFont(font2);

        horizontalLayout->addWidget(hideColumnBtn);

        clearBtn = new QPushButton(RecordView);
        clearBtn->setObjectName(QStringLiteral("clearBtn"));
        clearBtn->setMinimumSize(QSize(144, 48));
        clearBtn->setFont(font2);

        horizontalLayout->addWidget(clearBtn);


        verticalLayout->addLayout(horizontalLayout);


        retranslateUi(RecordView);

        QMetaObject::connectSlotsByName(RecordView);
    } // setupUi

    void retranslateUi(QFrame *RecordView)
    {
        RecordView->setWindowTitle(QApplication::translate("RecordView", "Frame", 0));
        sampleLabel->setText(QApplication::translate("RecordView", "Name", 0));
        saveAsBtn->setText(QApplication::translate("RecordView", "Save As", 0));
        moveUpBtn->setText(QApplication::translate("RecordView", "Move Up", 0));
        hideRowBtn->setText(QApplication::translate("RecordView", "Hide Row", 0));
        hideColumnBtn->setText(QApplication::translate("RecordView", "Hide Column", 0));
        clearBtn->setText(QApplication::translate("RecordView", "Clear", 0));
    } // retranslateUi

};

namespace Ui {
    class RecordView: public Ui_RecordView {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_RECORDVIEW_H
