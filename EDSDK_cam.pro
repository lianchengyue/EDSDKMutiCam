QT += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

TARGET = EDSDK_cam
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    CanonCameraWrapper.cpp \
    CameraControlDlg.cpp

HEADERS += \
    CanonCameraWrapper.h \
    CameraControlDlg.h \
    EDSDK/include/EDSDK.h \
    EDSDK/include/EDSDKErrors.h \
    EDSDK/include/EDSDKTypes.h

INCLUDEPATH += \
"C:\Program Files (x86)\Windows Kits\10\Include\10.0.10240.0\ucrt" \
#D:\VS2015_project\EDsdk\EDSDK\Header \
D:\Qt\Qt5.6.2_x86\project\EDSDK_cam\EDSDK\include \

LIBS += \
D:\VS2015_project\EDsdk\EDSDK\Library\EDSDK.lib \
"C:\Program Files (x86)\Windows Kits\10\Lib\10.0.10150.0\ucrt\x86\ucrtd.lib" \

FORMS += \
    CameraControlDlg.ui
