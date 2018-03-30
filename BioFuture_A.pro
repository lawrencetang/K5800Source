#-------------------------------------------------
#
# Project created by QtCreator 2016-01-29T17:04:39
#
#-------------------------------------------------

QT       += core gui printsupport multimedia multimediawidgets serialport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

win32 {
    Debug:TARGET = K5800_d
    Release:TARGET = K5800
}
TEMPLATE = app

DESTDIR+= ./bin/K5800pb
UI_DIR = tmp/uic
RCC_DIR = tmp/rcc
MOC_DIR = tmp/moc
OBJECTS_DIR = tmp/obj

INCLUDEPATH += C:\opencv\build\include\opencv \
               C:\opencv\build\include\opencv2 \
               C:\opencv\build\include
LIBS += -L C:\opencvMinGW\lib\libopencv_*.a

LIBS += -L"C:\Qt\Qt5.4.2\5.4\mingw491_32\lib"-lqwt
INCLUDEPATH += "C:\Qt\Qt5.4.2\5.4\mingw491_32\include\Qwt" \
               "C:\Program Files (x86)\Ocean Optics\OmniDriver\include" \
               "C:\Program Files\Java\jdk1.6.0_45\include\win32" \
               "C:\Program Files\Java\jdk1.6.0_45\include"
               #$(OMNIDRIVER_HOME)\include \
               #$(JAVA_HOME)\include\win32 \
               #$(JAVA_HOME)\include

#lt:已更改文件路�
include (C:\Qwt-6.1.2\features\qwt.prf)
include (DataView/DataView.pri)
include (CameraView/CameraView.pri)
include (OligoCalculator/OligoCalculator.pri)
include (RecordView/RecordView.pri)
include (FittingView/FittingView.pri)
include (PlotView/PlotView.pri)
include (SettingsView/SettingsView.pri)
include (ToolsView/ToolsView.pri)
include (TempControlView/TempControlView.pri)
include (CheckView/CheckView.pri)
include (DataModel/DataModel.pri)
include (Controller/Controller.pri)
include (Logger/Logger.pri)
include (Accredit/accredit.pri)
include (Spectrograph/Spectrograph.pri)

SOURCES += main.cpp \
        mainwindow.cpp \
    singleapplication.cpp \
    olistscroll.cpp \
    otablescroll.cpp

HEADERS  += mainwindow.h \
    singleapplication.h \
    olistscroll.h \
    otablescroll.h

FORMS    += \
    mainwindow.ui

RESOURCES += \
    mainwindow.qrc

RC_FILE += \
    app.rc

TRANSLATIONS += cn.ts

DISTFILES += \
    BioFuture-help.docx \
    ./bin/K5800pb/configure/plot.ini \
    ./bin/K5800pb/configure/system.ini \
    ./bin/K5800pb/configure/setting.ini \
    cn.ts
