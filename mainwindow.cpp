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
#include <QVBoxLayout>
#include <QComboBox>
#include <QStyledItemDelegate>
#include <QPushButton>

#include "Recorder.h"
#include "Settings.h"
#include "constant.h"
#include "About.h"
#include "PreviewPlayer.h"
#include "style.h"
#include "ComLineWidget.h"

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
    QWidget* mainWidget = new QWidget(this);
    mainVLayout = new QVBoxLayout(mainWidget);

    setCentralWidget(mainWidget);

    mainVLayout->setContentsMargins(0,0,0,0);
    mainVLayout->setSpacing(0);

    // 预览播放器
    QWidget* topWidget = new QWidget(mainWidget);
    topWidget->setStyleSheet(QString(".QWidget{background-color:%1}").arg("rgb(31,33,42)"));
    QHBoxLayout* topHLayout = new QHBoxLayout(topWidget);
    topHLayout->setContentsMargins(0,0,0,0);
    topHLayout->setSpacing(0);
    mPreviewPlayer = new PreviewPlayer(topWidget);
    topHLayout->addWidget(mPreviewPlayer);


    // 录屏界面
    QWidget* recorderWidget = new QWidget(mainWidget);
    recorderWidget->setFixedHeight(100);
    recorderWidget->setStyleSheet(QString(".QWidget{background-color:%1;}").arg("rgb(31,33,42)"));
    QHBoxLayout *recorderHLayout = new QHBoxLayout(recorderWidget);
    recorderHLayout->setContentsMargins(0,0,0,0);
    recorderHLayout->setSpacing(0);

    QWidget* sourceWidget = initSourceWidget();

    startBtn = new QPushButton(recorderWidget);
    startBtn->setFixedSize(120, 40);
    startBtn->setCursor(Qt::PointingHandCursor);
    startBtn->setText("开始");

    pauseBtn = new QPushButton(recorderWidget);
    pauseBtn->setFixedSize(120,40);
    pauseBtn->setCursor(Qt::PointingHandCursor);
    pauseBtn->setText("暂停");

    stopBtn = new QPushButton(recorderWidget);
    stopBtn->setFixedSize(120,40);
    stopBtn->setCursor(Qt::PointingHandCursor);
    stopBtn->setText("停止");

    connect(startBtn, &QPushButton::clicked, this, [this]()
    {
        if(bIsRecording)
        {
            qDebug() << "正在录制中， 请先停止录制";
        }
        else
        {
            qDebug() << "开始录制";
            startBtn->hide();
            pauseBtn->show();
            stopBtn->show();

            bIsRecording = true;
            recordStartDate = QDateTime::currentDateTime();
            durationLabel->setText("REC : 0 Sec");
            durationTimer->start(1000);

            mRecorder->start();
        }
    });

    connect(stopBtn, &QPushButton::clicked, this, [this]()
    {
        if(bIsRecording)
        {
            qDebug()<<"正在录制中，可以执行停止录制";
            startBtn->show();
            pauseBtn->hide();
            stopBtn->hide();

            bIsRecording = false;
            durationTimer->stop();

            mRecorder->stop();
        }
        else
        {
            qDebug()<<"暂未开始录制，无法执行停止";
        }
    });
    pauseBtn->hide();
    stopBtn->hide();

    recorderHLayout->addWidget(sourceWidget);
    recorderHLayout->addWidget(pauseBtn);
    recorderHLayout->addSpacing(10);
    recorderHLayout->addWidget(startBtn);
    recorderHLayout->addSpacing(10);
    recorderHLayout->addWidget(stopBtn);
    recorderHLayout->addSpacing(50);

    // bottom
    QWidget* bottomWidget = new QWidget(mainWidget);
    bottomWidget->setFixedHeight(40);
    bottomWidget->setStyleSheet(QString(".QWidget{background-color:%1;}").arg("rgb(31,33,42)"));

    QHBoxLayout* bottomHLayout = new QHBoxLayout(bottomWidget);
    bottomHLayout->setContentsMargins(0,0,0,0);
    bottomHLayout->setSpacing(0);

    durationLabel = new QLabel(bottomWidget);
    durationLabel->setStyleSheet(".QLabel{color:rgb(255,255,255);font-size:20px;}");

    bottomHLayout->addSpacing(20);
    bottomHLayout->addWidget(durationLabel);
    bottomHLayout->addStretch(10);

    mainVLayout->addWidget(topWidget);
    mainVLayout->addWidget(new ComLineWidget(this));
    mainVLayout->addWidget(recorderWidget);
    mainVLayout->addWidget(new ComLineWidget(this));
    mainVLayout->addWidget(bottomWidget);
}

QWidget *MainWindow::initSourceWidget()
{
    QWidget* widget = new QWidget(this);
    QHBoxLayout* widgetHLayout = new QHBoxLayout(widget);
    widgetHLayout->setContentsMargins(0,0,0,0);
    widgetHLayout->setSpacing(0);

    // 视频源
    QComboBox* videoSourceBox = new QComboBox(widget);
    videoSourceBox->setFixedSize(150, 40);
    QStyledItemDelegate* videoSourceDelegate = new QStyledItemDelegate(videoSourceBox);
    videoSourceBox->setItemDelegate(videoSourceDelegate);
    videoSourceBox->setStyleSheet(m_stylesheet_QComboBox);
    videoSourceBox->clear();

    QStringList videoSources = {"屏幕", "摄像头"};
    for(int i = 0; i < videoSources.size(); ++i)
    {
        videoSourceBox->addItem(videoSources[i]);
    }

    connect(videoSourceBox, QOverload<int>::of(&QComboBox::currentIndexChanged), [this](int index)
    {
        qDebug() << "sourceBox index = " << index;
    });

    // 音频源
    QComboBox* audioSourceBox = new QComboBox(widget);
    audioSourceBox->setFixedSize(150,40);
    QStyledItemDelegate *audioSourceDelegate = new QStyledItemDelegate(audioSourceBox);
    audioSourceBox->setItemDelegate(audioSourceDelegate);
    audioSourceBox->setStyleSheet(m_stylesheet_QComboBox);
    audioSourceBox->clear();

    QStringList audioSources = {"系统声音","麦克风"};
    for (int i = 0; i < audioSources.size(); ++i)
    {

        audioSourceBox->addItem(audioSources[i]);
    }

    connect(audioSourceBox, QOverload<int>::of(&QComboBox::currentIndexChanged), [this](int index)
    {
        qDebug()<<"sourceBox index="<<index;

    });

    widgetHLayout->addSpacing(40);
    widgetHLayout->addWidget(videoSourceBox);
    widgetHLayout->addSpacing(20);
    widgetHLayout->addWidget(audioSourceBox);

    widgetHLayout->addStretch(10);

    return widget;
}
