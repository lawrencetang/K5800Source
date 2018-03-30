/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionNa;
    QAction *actionPt;
    QAction *actionCc;
    QAction *actionUv;
    QAction *actionMa;
    QAction *actionDy;
    QAction *actionKm;
    QAction *actionDc;
    QAction *actionCt;
    QAction *actionSt;
    QAction *actionTl;
    QAction *actionBk;
    QAction *actionMs;
    QAction *actionSh;
    QAction *actionAm;
    QWidget *centralwidget;
    QMenuBar *menubar;
    QStatusBar *statusbar;
    QToolBar *toolBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(1427, 131);
        actionNa = new QAction(MainWindow);
        actionNa->setObjectName(QStringLiteral("actionNa"));
        actionPt = new QAction(MainWindow);
        actionPt->setObjectName(QStringLiteral("actionPt"));
        actionCc = new QAction(MainWindow);
        actionCc->setObjectName(QStringLiteral("actionCc"));
        actionUv = new QAction(MainWindow);
        actionUv->setObjectName(QStringLiteral("actionUv"));
        actionMa = new QAction(MainWindow);
        actionMa->setObjectName(QStringLiteral("actionMa"));
        actionDy = new QAction(MainWindow);
        actionDy->setObjectName(QStringLiteral("actionDy"));
        actionKm = new QAction(MainWindow);
        actionKm->setObjectName(QStringLiteral("actionKm"));
        actionDc = new QAction(MainWindow);
        actionDc->setObjectName(QStringLiteral("actionDc"));
        actionCt = new QAction(MainWindow);
        actionCt->setObjectName(QStringLiteral("actionCt"));
        actionCt->setCheckable(true);
        actionCt->setEnabled(true);
        actionSt = new QAction(MainWindow);
        actionSt->setObjectName(QStringLiteral("actionSt"));
        actionTl = new QAction(MainWindow);
        actionTl->setObjectName(QStringLiteral("actionTl"));
        actionBk = new QAction(MainWindow);
        actionBk->setObjectName(QStringLiteral("actionBk"));
        actionMs = new QAction(MainWindow);
        actionMs->setObjectName(QStringLiteral("actionMs"));
        actionSh = new QAction(MainWindow);
        actionSh->setObjectName(QStringLiteral("actionSh"));
        actionAm = new QAction(MainWindow);
        actionAm->setObjectName(QStringLiteral("actionAm"));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QStringLiteral("menubar"));
        menubar->setGeometry(QRect(0, 0, 1427, 26));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QStringLiteral("statusbar"));
        statusbar->setMinimumSize(QSize(0, 64));
        MainWindow->setStatusBar(statusbar);
        toolBar = new QToolBar(MainWindow);
        toolBar->setObjectName(QStringLiteral("toolBar"));
        toolBar->setMovable(false);
        toolBar->setIconSize(QSize(80, 80));
        toolBar->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
        MainWindow->addToolBar(Qt::TopToolBarArea, toolBar);

        toolBar->addAction(actionNa);
        toolBar->addAction(actionPt);
        toolBar->addAction(actionCc);
        toolBar->addAction(actionUv);
        toolBar->addAction(actionMa);
        toolBar->addAction(actionDy);
        toolBar->addAction(actionKm);
        toolBar->addSeparator();
        toolBar->addAction(actionDc);
        toolBar->addAction(actionCt);
        toolBar->addAction(actionSt);
        toolBar->addAction(actionTl);
        toolBar->addSeparator();
        toolBar->addAction(actionAm);
        toolBar->addAction(actionBk);
        toolBar->addAction(actionMs);
        toolBar->addAction(actionSh);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0));
        actionNa->setText(QApplication::translate("MainWindow", "Nucleic Acid", 0));
#ifndef QT_NO_TOOLTIP
        actionNa->setToolTip(QApplication::translate("MainWindow", "Nucleic Acid", 0));
#endif // QT_NO_TOOLTIP
        actionPt->setText(QApplication::translate("MainWindow", "Protein", 0));
#ifndef QT_NO_TOOLTIP
        actionPt->setToolTip(QApplication::translate("MainWindow", "Protein", 0));
#endif // QT_NO_TOOLTIP
        actionCc->setText(QApplication::translate("MainWindow", "Cell Culture", 0));
#ifndef QT_NO_TOOLTIP
        actionCc->setToolTip(QApplication::translate("MainWindow", "Cell Culture", 0));
#endif // QT_NO_TOOLTIP
        actionUv->setText(QApplication::translate("MainWindow", "UV-VIS", 0));
#ifndef QT_NO_TOOLTIP
        actionUv->setToolTip(QApplication::translate("MainWindow", "UV-VIS", 0));
#endif // QT_NO_TOOLTIP
        actionMa->setText(QApplication::translate("MainWindow", "Micro Array", 0));
#ifndef QT_NO_TOOLTIP
        actionMa->setToolTip(QApplication::translate("MainWindow", "Micro Array", 0));
#endif // QT_NO_TOOLTIP
        actionDy->setText(QApplication::translate("MainWindow", "Dynamics", 0));
#ifndef QT_NO_TOOLTIP
        actionDy->setToolTip(QApplication::translate("MainWindow", "Dynamics", 0));
#endif // QT_NO_TOOLTIP
        actionKm->setText(QApplication::translate("MainWindow", "Kit Method", 0));
#ifndef QT_NO_TOOLTIP
        actionKm->setToolTip(QApplication::translate("MainWindow", "Kit Method", 0));
#endif // QT_NO_TOOLTIP
        actionDc->setText(QApplication::translate("MainWindow", "Device Check", 0));
#ifndef QT_NO_TOOLTIP
        actionDc->setToolTip(QApplication::translate("MainWindow", "Device Check", 0));
#endif // QT_NO_TOOLTIP
        actionCt->setText(QApplication::translate("MainWindow", "Temperture", 0));
#ifndef QT_NO_TOOLTIP
        actionCt->setToolTip(QApplication::translate("MainWindow", "Temperture", 0));
#endif // QT_NO_TOOLTIP
        actionSt->setText(QApplication::translate("MainWindow", "Setings", 0));
#ifndef QT_NO_TOOLTIP
        actionSt->setToolTip(QApplication::translate("MainWindow", "Setings", 0));
#endif // QT_NO_TOOLTIP
        actionTl->setText(QApplication::translate("MainWindow", "Tools", 0));
#ifndef QT_NO_TOOLTIP
        actionTl->setToolTip(QApplication::translate("MainWindow", "Tools", 0));
#endif // QT_NO_TOOLTIP
        actionBk->setText(QApplication::translate("MainWindow", "Blank", 0));
#ifndef QT_NO_TOOLTIP
        actionBk->setToolTip(QApplication::translate("MainWindow", "Blank", 0));
#endif // QT_NO_TOOLTIP
        actionMs->setText(QApplication::translate("MainWindow", "Measure", 0));
#ifndef QT_NO_TOOLTIP
        actionMs->setToolTip(QApplication::translate("MainWindow", "Measure", 0));
#endif // QT_NO_TOOLTIP
        actionSh->setText(QApplication::translate("MainWindow", "Shut Down", 0));
#ifndef QT_NO_TOOLTIP
        actionSh->setToolTip(QApplication::translate("MainWindow", "Shut", 0));
#endif // QT_NO_TOOLTIP
        actionAm->setText(QApplication::translate("MainWindow", "Auto Measure", 0));
#ifndef QT_NO_TOOLTIP
        actionAm->setToolTip(QApplication::translate("MainWindow", "Auto", 0));
#endif // QT_NO_TOOLTIP
        toolBar->setWindowTitle(QApplication::translate("MainWindow", "toolBar", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
