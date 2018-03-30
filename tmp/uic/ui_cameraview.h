/********************************************************************************
** Form generated from reading UI file 'cameraview.ui'
**
** Created by: Qt User Interface Compiler version 5.4.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CAMERAVIEW_H
#define UI_CAMERAVIEW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_CameraView
{
public:
    QHBoxLayout *horizontalLayout_2;
    QVBoxLayout *verticalLayout;
    QPushButton *openBtn;
    QPushButton *cameraBtn;
    QPushButton *removeBtn;
    QPushButton *moveToBtn;
    QSpacerItem *verticalSpacer;
    QStackedWidget *stackedWidget;
    QWidget *cameraPage;
    QHBoxLayout *horizontalLayout;
    QLabel *cameraLabel;
    QWidget *imagePage;
    QVBoxLayout *verticalLayout_2;
    QLabel *imageLabel;
    QLabel *titleLabel;
    QListWidget *listWidget;

    void setupUi(QFrame *CameraView)
    {
        if (CameraView->objectName().isEmpty())
            CameraView->setObjectName(QStringLiteral("CameraView"));
        CameraView->resize(862, 481);
        CameraView->setStyleSheet(QString::fromUtf8("QLabel,QSpinBox,QDoubleSpinBox,QPushButton,QLineEdit,QComboBox{\n"
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
"}"));
        CameraView->setFrameShape(QFrame::StyledPanel);
        CameraView->setFrameShadow(QFrame::Raised);
        horizontalLayout_2 = new QHBoxLayout(CameraView);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(1);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        openBtn = new QPushButton(CameraView);
        openBtn->setObjectName(QStringLiteral("openBtn"));
        openBtn->setMinimumSize(QSize(140, 50));
        openBtn->setMaximumSize(QSize(140, 40));

        verticalLayout->addWidget(openBtn);

        cameraBtn = new QPushButton(CameraView);
        cameraBtn->setObjectName(QStringLiteral("cameraBtn"));
        cameraBtn->setMinimumSize(QSize(140, 50));
        cameraBtn->setMaximumSize(QSize(140, 40));

        verticalLayout->addWidget(cameraBtn);

        removeBtn = new QPushButton(CameraView);
        removeBtn->setObjectName(QStringLiteral("removeBtn"));
        removeBtn->setMinimumSize(QSize(140, 50));
        removeBtn->setMaximumSize(QSize(140, 40));

        verticalLayout->addWidget(removeBtn);

        moveToBtn = new QPushButton(CameraView);
        moveToBtn->setObjectName(QStringLiteral("moveToBtn"));
        moveToBtn->setMinimumSize(QSize(140, 50));
        moveToBtn->setMaximumSize(QSize(140, 40));

        verticalLayout->addWidget(moveToBtn);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);


        horizontalLayout_2->addLayout(verticalLayout);

        stackedWidget = new QStackedWidget(CameraView);
        stackedWidget->setObjectName(QStringLiteral("stackedWidget"));
        cameraPage = new QWidget();
        cameraPage->setObjectName(QStringLiteral("cameraPage"));
        horizontalLayout = new QHBoxLayout(cameraPage);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        cameraLabel = new QLabel(cameraPage);
        cameraLabel->setObjectName(QStringLiteral("cameraLabel"));
        cameraLabel->setStyleSheet(QLatin1String("background-color: rgb(0, 0, 0);\n"
"color: rgb(255, 255, 255);"));
        cameraLabel->setScaledContents(false);
        cameraLabel->setAlignment(Qt::AlignCenter);

        horizontalLayout->addWidget(cameraLabel);

        stackedWidget->addWidget(cameraPage);
        imagePage = new QWidget();
        imagePage->setObjectName(QStringLiteral("imagePage"));
        verticalLayout_2 = new QVBoxLayout(imagePage);
        verticalLayout_2->setSpacing(0);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        imageLabel = new QLabel(imagePage);
        imageLabel->setObjectName(QStringLiteral("imageLabel"));
        imageLabel->setScaledContents(true);

        verticalLayout_2->addWidget(imageLabel);

        titleLabel = new QLabel(imagePage);
        titleLabel->setObjectName(QStringLiteral("titleLabel"));
        titleLabel->setAlignment(Qt::AlignCenter);

        verticalLayout_2->addWidget(titleLabel);

        verticalLayout_2->setStretch(0, 10);
        stackedWidget->addWidget(imagePage);

        horizontalLayout_2->addWidget(stackedWidget);

        listWidget = new QListWidget(CameraView);
        listWidget->setObjectName(QStringLiteral("listWidget"));
        listWidget->setMinimumSize(QSize(240, 0));
        listWidget->setMaximumSize(QSize(170, 16777215));
        listWidget->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
        listWidget->setSelectionMode(QAbstractItemView::ExtendedSelection);
        listWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
        listWidget->setIconSize(QSize(80, 80));
        listWidget->setMovement(QListView::Static);
        listWidget->setFlow(QListView::TopToBottom);
        listWidget->setViewMode(QListView::ListMode);

        horizontalLayout_2->addWidget(listWidget);

        horizontalLayout_2->setStretch(1, 1);

        retranslateUi(CameraView);

        stackedWidget->setCurrentIndex(1);


        QMetaObject::connectSlotsByName(CameraView);
    } // setupUi

    void retranslateUi(QFrame *CameraView)
    {
        CameraView->setWindowTitle(QApplication::translate("CameraView", "Frame", 0));
        openBtn->setText(QApplication::translate("CameraView", "Open", 0));
        cameraBtn->setText(QApplication::translate("CameraView", "Image", 0));
        removeBtn->setText(QApplication::translate("CameraView", "Remove", 0));
        moveToBtn->setText(QApplication::translate("CameraView", "Save As", 0));
        cameraLabel->setText(QString());
        imageLabel->setText(QString());
        titleLabel->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class CameraView: public Ui_CameraView {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CAMERAVIEW_H
