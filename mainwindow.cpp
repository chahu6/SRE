#include "mainwindow.h"
#include <QCoreApplication>
#include <QGuiApplication>
#include <QScreen>
#include <QsLog.h>
#include <QTimer>
#include <QLabel>
#include <QMenuBar>
#include <QUrl>
#include <QDesktopServices>
#include <QMessageBox>
#include <QApplication>

#include "Recorder.h"
#include "Settings.h"
#include "constant.h"
#include "About.h"

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
    int screenW = screenRect.width();
    int screenH = screenRect.height();

    int initW = screenW * 1080 / 1920;
    int initH = screenH * 680 / 1080;

    QLOG_INFO() << "MainWindow::MainWindow() screens.size = " << screens.size() << ", screenW="<<screenW<<",screenH="<<screenH<<",initW="<<initW<<",initH="<<initH;
    this->resize(initW, initH);

    initMenu();
    initUI();

    mRecorder = new Recorder(this, mPreviewPlayer);

    bIsRecording = false;
    durationTimer = new QTimer(this);
    connect(durationTimer, &QTimer::timeout, this, [this]()
    {
        int seconds = QDateTime::currentDateTime().toSecsSinceEpoch() - recordStartDate.toSecsSinceEpoch();
        QString durationStr = QString("REC : %1 Sec").arg(seconds);
        durationLabel->setText(durationStr);
//      durationLabel->setText(QTime::currentTime().toString());
    });
}

MainWindow::~MainWindow()
{}

void MainWindow::initMenu()
{
    // 文件菜单
    QMenu* fileMenu = new QMenu(tr("文件"));
    QAction* settingsAct = fileMenu->addAction(tr("设置"));
    settingsAct->setShortcut(QKeySequence::WhatsThis);
    connect(settingsAct, &QAction::triggered, this, [this]()
    {
        Settings dlg(this);
        dlg.exec();
    });
    QAction* logoutAct = fileMenu->addAction("退出");
    logoutAct->setShortcut(QKeySequence::Quit);
    connect(logoutAct, &QAction::triggered, this, [this]()
    {
        switch (QMessageBox::information(this, "提示", "确定要退出吗？", "确定", "取消", 0))
        {
            case 0:
                QLOG_INFO() << "logout";
                QApplication* app;
                app->quit();
                break;
            default:
                break;
        }
    });
    fileMenu->addAction(settingsAct);
    fileMenu->addSeparator();
    fileMenu->addAction(logoutAct);


    // 帮助菜单
    QMenu* helpMenu = new QMenu(tr("&帮助"));
    QAction* aboutAct = helpMenu->addAction("关于");
    aboutAct->setShortcut(QKeySequence::Preferences);
    connect(aboutAct, &QAction::triggered, this, [this]()
    {
        About dlg(this);
        dlg.exec();
    });
    QAction* feedbackAct = helpMenu->addAction("反馈");
    connect(feedbackAct, &QAction::triggered, this, []()
    {
        QDesktopServices::openUrl(QUrl(URL_FEEDBACK));
    });
    helpMenu->addAction(aboutAct);
    helpMenu->addSeparator();
    helpMenu->addAction(feedbackAct);

    menuBar()->addMenu(fileMenu);
    menuBar()->addMenu(helpMenu);
}

void MainWindow::initUI()
{

}

QWidget *MainWindow::initSourceWidget()
{

}
