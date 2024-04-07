#include "mainwindow.h"
#include <QApplication>

#ifdef Q_OS_WIN
#include <windows.h>
#endif

#include <QSharedMemory>
#include <QDebug>
#include <QsLog.h>
#include <QDesktopWidget>

#include "Utils.h"
#include "ComMessageBox.h"

using namespace QsLogging;

void initLogger(const QString& logDir)
{
    if(Utils::mkDirs(logDir))
    {
        Logger& logger = Logger::instance();
        logger.setLoggingLevel(QsLogging::TraceLevel);
        //    QString timeStr = QDate::currentDate().toString("yyyy-MM-dd");
        //    QDateTime time = QDateTime::fromString(timeStr,"yyyy-MM-dd");
        QString logFile = QString("%1/run.log").arg(logDir);
        DestinationPtr des(
                    DestinationFactory::MakeFileDestination(logFile,
                                EnableLogRotation,
                                MaxSizeBytes(1*1024*1024),
                                MaxOldLogCount(1)));
        logger.addDestination(des);
        QLOG_INFO() << "initLogger() success logDir=" << logDir;
    }
    else
    {
        QLOG_INFO() << "initLogger() error logDir=" << logDir;
    }
}

LONG ApplicationCrashHandler(EXCEPTION_POINTERS* pException)
{
    EXCEPTION_RECORD* record = pException->ExceptionRecord;
    (void)record;
    return EXCEPTION_EXECUTE_HANDLER;
}

int main(int argc, char *argv[])
{
    QCoreApplication::setOrganizationName("Chahu666");
    QCoreApplication::setOrganizationDomain("https://gitee.com/chahu666");
    QCoreApplication::setApplicationName("SRE");
    QCoreApplication::setApplicationVersion("2.0");

    //注冊异常捕获函数
    SetUnhandledExceptionFilter((LPTOP_LEVEL_EXCEPTION_FILTER)ApplicationCrashHandler);

#if(QT_VERSION >= QT_VERSION_CHECK(6, 0, 0))
    QGuiApplication::setHighDpiScaleFactorRoundingPolicy(Qt::HighDpiScaleFactorRoundingPolicy::Floor);
#elif(QT_VERSION >= QT_VERSION_CHECK(5, 6, 0))
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QCoreApplication::setAttribute(Qt::AA_UseHighDpiPixmaps);
#endif

    QApplication a(argc, argv);
    a.setWindowIcon(QIcon(QStringLiteral(":/res/images/logo.png")));

    // QSharedMemory shared("SRE");
    // if(shared.attach())
    // {
    //     ComMessageBox::error(NULL, "软件已经在运行中");
    //     qDebug() << "已经打开";
    //     return 0;
    // }
    // shared.create(1);

    // 初始化日志库
    QString logDir = QApplication::applicationDirPath() + "/logs";
    initLogger(logDir);

    QString vInfo = QString("SRE V%1").arg(QCoreApplication::applicationVersion());

    qDebug() << vInfo;
    QLOG_INFO() << vInfo;

    MainWindow mainWindow;

    // @TODO: 将窗口移动到屏幕中心,有点问题
    // int pixelRatio = QApplication::desktop()->screen()->devicePixelRatio(); // 获取缩放因素
    // int currentScreen = a.desktop()->screenNumber(&mainWindow);//程序所在的屏幕编号
    // QRect rect = a.desktop()->screenGeometry(currentScreen);//程序所在屏幕尺寸
    // mainWindow.move((rect.width() - mainWindow.width()) / 2, (rect.height() - mainWindow.height()) / 2);//移动到所在屏幕中间

    mainWindow.show();

    return a.exec();
}
