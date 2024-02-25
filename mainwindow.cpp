#include "mainwindow.h"
#include <QCoreApplication>
#include <QGuiApplication>
#include <QScreen>
#include <QDebug>
#include <QsLog.h>
#include "IndexWidget.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setAttribute(Qt::WA_StyledBackground, true);
    setStyleSheet(QString(".MainWindow{background-color:%1;}").arg("rgb(246,247,251)"));

    QString title = QString("SRE V%1 (64-bit, windows)").arg(QCoreApplication::applicationVersion());
    setWindowTitle(title);

    QList<QScreen*> screens = QGuiApplication::screens(); // 获取到多个屏幕
//    QScreen* screen = QGuiApplication::primaryScreen(); // 获取主屏幕
    QScreen* screen = screens.at(0);
    QRect screenRect = screen->geometry();
    int screenWidth = screenRect.width();
    int screenHeight = screenRect.height();
    // SingletonUtils::getInstance()->setScreenSize(screenWidth, screenHeight);

    int w = int(float(screenWidth) * 0.5);
    int h = int(float(screenHeight) * 0.5);

    QLOG_INFO() << "screens="<<screens.size()<<",screenWidth="<<screenWidth<<",screenHeight="<<screenHeight<<",w="<<w<<",h="<<h;
    qDebug() << "screens="<<screens.size()<<",screenWidth="<<screenWidth<<",screenHeight="<<screenHeight<<",w="<<w<<",h="<<h;
    this->resize(w,h);

    IndexWidget* index = new IndexWidget(this);
    setCentralWidget(index);
}

void MainWindow::resizeEvent(QResizeEvent *event)
{
}
