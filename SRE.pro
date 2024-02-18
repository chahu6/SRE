#-------------------------------------------------
#
# Project created by QtCreator 2024-02-17T14:14:28
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets # 如果 Qt 的主要版本号大于 4，则添加 widgets 模块到项目中
greaterThan(QT_MAJOR_VERSION, 5): QT += core5compat # 如果 Qt 的主要版本号大于 5，则添加 core5compat 模块到项目中。这个模块提供了一些兼容性支持，帮助迁移 Qt 5 项目到 Qt 6。

CONFIG += c++11 # 启用 C++11 的特性

TARGET = SRE
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
        mainwindow.cpp

HEADERS += \
        mainwindow.h \
        style.h

RESOURCES += \
    res/res.qrc

RC_ICONS = logo.ico # 配置桌面软件和的图标

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

include(./Utils/Utils.pri)
include(./View/View.pri)
include(./3rdparty/3rdparty.pri)
include(./Recorder/Recorder.pri)

# MinGW是32位的，所以ffmpeg也用32位的，不然不行，在这里搞了好久
# 将 $$PWD/3rdparty/ffmpeg/include 目录添加到头文件搜索路径中。这个目录包含了 FFmpeg 库的头文件。
INCLUDEPATH += $$PWD/3rdparty/ffmpeg/include

# 将 $$PWD/3rdparty/ffmpeg/include 目录添加到依赖文件搜索路径中。这个目录同样包含了 FFmpeg 库的头文件。
#DEPENDPATH += $$PWD/3rdparty/ffmpeg/include

# 这行代码将名为 d3d11 的库添加到链接阶段。这通常用于在 Windows 平台上使用 Direct3D 11 图形库进行开发。
#win32: LIBS += -ld3d11

# 指定了链接阶段需要使用的一系列 FFmpeg 库，包括 avcodec、avfilter、avformat、avutil、postproc、swresample 和 swscale。同时通过 -L 选项指定了库文件的路径为 $$PWD/3rdparty/ffmpeg/lib/。
win32: LIBS += -L$$PWD/3rdparty/ffmpeg/lib -lavcodec -lavfilter -lavformat -lavutil -lpostproc -lswresample -lswscale
