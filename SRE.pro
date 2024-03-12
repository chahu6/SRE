#-------------------------------------------------
#
# Project created by QtCreator 2024-02-17T14:14:28
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets multimedia # 如果 Qt 的主要版本号大于 4，则添加 widgets 模块到项目中
greaterThan(QT_MAJOR_VERSION, 5): QT += core5compat # 如果 Qt 的主要版本号大于 5，则添加 core5compat 模块到项目中。这个模块提供了一些兼容性支持，帮助迁移 Qt 5 项目到 Qt 6。

CONFIG += c++11 # 启用 C++11 的特性

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
# DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

DEFINES += DYNAMIC_LINK

SOURCES += \
     main.cpp \
     mainwindow.cpp

HEADERS += \
     mainwindow.h \
     style.h

RESOURCES += \
     res.qrc

RC_ICONS = logo.ico # 配置桌面软件和的图标

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

include(3rdparty/3rdparty.pri)
include(Index/Index.pri)
include(Recorder/Recorder.pri)
include(Utils/Utils.pri)
include(VNCServer/VNCServer.pri)
include(VNCClient/VNCClient.pri)

# windows
# win32: LIBS += -lws2_32

# MediaLibrary
win32: LIBS += -L$$PWD/3rdparty/MediaLibrary/lib -lAvEncoder -lVideoRecorder
INCLUDEPATH += $$PWD/3rdparty/MediaLibrary/include
DEPENDPATH += $$PWD/3rdparty/MediaLibrary/include
