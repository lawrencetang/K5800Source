/********************************************************************************
** Form generated from reading UI file 'fittingview.ui'
**
** Created by: Qt User Interface Compiler version 5.4.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FITTINGVIEW_H
#define UI_FITTINGVIEW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QToolBox>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_FittingView
{
public:
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_6;
    QLabel *typeLabel;
    QComboBox *typeComboBox;
    QHBoxLayout *horizontalLayout_5;
    QLabel *label_2;
    QComboBox *unitComboBox;
    QToolBox *toolBox;
    QWidget *fittingPage;
    QHBoxLayout *horizontalLayout_2;
    QTableWidget *fittingTableWidget;
    QWidget *measurePage;
    QHBoxLayout *horizontalLayout;
    QTableWidget *measureTableWidget;
    QHBoxLayout *horizontalLayout_3;
    QPushButton *fitBtn;
    QPushButton *removeBtn;

    void setupUi(QFrame *FittingView)
    {
        if (FittingView->objectName().isEmpty())
            FittingView->setObjectName(QStringLiteral("FittingView"));
        FittingView->resize(264, 504);
        FittingView->setFrameShape(QFrame::StyledPanel);
        FittingView->setFrameShadow(QFrame::Raised);
        verticalLayout = new QVBoxLayout(FittingView);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName(QStringLiteral("horizontalLayout_6"));
        typeLabel = new QLabel(FittingView);
        typeLabel->setObjectName(QStringLiteral("typeLabel"));
        QFont font;
        font.setFamily(QString::fromUtf8("\351\273\221\344\275\223"));
        font.setPointSize(14);
        typeLabel->setFont(font);

        horizontalLayout_6->addWidget(typeLabel);

        typeComboBox = new QComboBox(FittingView);
        typeComboBox->setObjectName(QStringLiteral("typeComboBox"));
        typeComboBox->setMinimumSize(QSize(0, 48));
        typeComboBox->setFont(font);
        typeComboBox->setIconSize(QSize(48, 48));

        horizontalLayout_6->addWidget(typeComboBox);

        horizontalLayout_6->setStretch(1, 1);

        verticalLayout->addLayout(horizontalLayout_6);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        label_2 = new QLabel(FittingView);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setFont(font);

        horizontalLayout_5->addWidget(label_2);

        unitComboBox = new QComboBox(FittingView);
        unitComboBox->setObjectName(QStringLiteral("unitComboBox"));
        unitComboBox->setMinimumSize(QSize(0, 48));
        unitComboBox->setFont(font);
        unitComboBox->setIconSize(QSize(48, 48));

        horizontalLayout_5->addWidget(unitComboBox);

        horizontalLayout_5->setStretch(1, 1);

        verticalLayout->addLayout(horizontalLayout_5);

        toolBox = new QToolBox(FittingView);
        toolBox->setObjectName(QStringLiteral("toolBox"));
        toolBox->setFont(font);
        fittingPage = new QWidget();
        fittingPage->setObjectName(QStringLiteral("fittingPage"));
        fittingPage->setGeometry(QRect(0, 0, 240, 233));
        horizontalLayout_2 = new QHBoxLayout(fittingPage);
        horizontalLayout_2->setSpacing(0);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(0, 3, 0, 3);
        fittingTableWidget = new QTableWidget(fittingPage);
        fittingTableWidget->setObjectName(QStringLiteral("fittingTableWidget"));
        fittingTableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
        fittingTableWidget->setSelectionMode(QAbstractItemView::SingleSelection);
        fittingTableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
        fittingTableWidget->horizontalHeader()->setMinimumSectionSize(50);
        fittingTableWidget->horizontalHeader()->setStretchLastSection(true);
        fittingTableWidget->verticalHeader()->setDefaultSectionSize(50);
        fittingTableWidget->verticalHeader()->setMinimumSectionSize(25);

        horizontalLayout_2->addWidget(fittingTableWidget);

        toolBox->addItem(fittingPage, QStringLiteral("Fitting"));
        measurePage = new QWidget();
        measurePage->setObjectName(QStringLiteral("measurePage"));
        measurePage->setGeometry(QRect(0, 0, 240, 233));
        horizontalLayout = new QHBoxLayout(measurePage);
        horizontalLayout->setSpacing(0);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 3, 0, 3);
        measureTableWidget = new QTableWidget(measurePage);
        measureTableWidget->setObjectName(QStringLiteral("measureTableWidget"));
        measureTableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
        measureTableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
        measureTableWidget->horizontalHeader()->setStretchLastSection(true);

        horizontalLayout->addWidget(measureTableWidget);

        toolBox->addItem(measurePage, QStringLiteral("Measure"));

        verticalLayout->addWidget(toolBox);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(0);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        fitBtn = new QPushButton(FittingView);
        fitBtn->setObjectName(QStringLiteral("fitBtn"));
        fitBtn->setMinimumSize(QSize(0, 48));
        QFont font1;
        font1.setFamily(QString::fromUtf8("\345\276\256\350\275\257\351\233\205\351\273\221"));
        font1.setPointSize(14);
        fitBtn->setFont(font1);

        horizontalLayout_3->addWidget(fitBtn);

        removeBtn = new QPushButton(FittingView);
        removeBtn->setObjectName(QStringLiteral("removeBtn"));
        removeBtn->setMinimumSize(QSize(0, 48));
        removeBtn->setFont(font1);

        horizontalLayout_3->addWidget(removeBtn);


        verticalLayout->addLayout(horizontalLayout_3);

        verticalLayout->setStretch(2, 1);

        retranslateUi(FittingView);

        toolBox->setCurrentIndex(1);


        QMetaObject::connectSlotsByName(FittingView);
    } // setupUi

    void retranslateUi(QFrame *FittingView)
    {
        FittingView->setWindowTitle(QApplication::translate("FittingView", "Frame", 0));
        typeLabel->setText(QApplication::translate("FittingView", "Type", 0));
        label_2->setText(QApplication::translate("FittingView", "Unit", 0));
        toolBox->setItemText(toolBox->indexOf(fittingPage), QApplication::translate("FittingView", "Fitting", 0));
        toolBox->setItemText(toolBox->indexOf(measurePage), QApplication::translate("FittingView", "Measure", 0));
        fitBtn->setText(QApplication::translate("FittingView", "Fit", 0));
        removeBtn->setText(QApplication::translate("FittingView", "Remove", 0));
    } // retranslateUi

};

namespace Ui {
    class FittingView: public Ui_FittingView {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FITTINGVIEW_H
