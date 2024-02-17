#include "mainwindow.h"
#include <QApplication>

#ifdef Q_OS_WIN
#include <windows.h>
#endif

#include <QApplication>
#include <QSharedMemory>
#include <QDebug>
#include <QsLog.h>
#include "Utils.h"
#include "Utils/ComMessageBox.h"

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
    QCoreApplication::setOrganizationName("any12345");
    QCoreApplication::setOrganizationDomain("www.any12345.com");
    QCoreApplication::setApplicationName("SRE");
    QCoreApplication::setApplicationVersion("1.0");

    //注冊异常捕获函数
    SetUnhandledExceptionFilter((LPTOP_LEVEL_EXCEPTION_FILTER)ApplicationCrashHandler);

#if(QT_VERSION >= QT_VERSION_CHECK(6, 0, 0))
    QGuiApplication::setHighDpiScaleFactorRoundingPolicy(QT::HighDpiScaleFactorRoundingPolicy::Floor);
#elif(QT_VERSION >= QT_VERSION_CHECK(5, 6, 0))
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QCoreApplication::setAttribute(Qt::AA_UseHighDpiPixmaps);
#endif

    QApplication a(argc, argv);
    a.setWindowIcon(QIcon(QStringLiteral(":/images/logo.png")));

    QSharedMemory shared("SRE");
    if(shared.attach())
    {
        ComMessageBox::error(NULL, "软件已经在运行中");
        qDebug() << "已经打开";
        return 0;
    }
    shared.create(1);

    QString logDir = QApplication::applicationDirPath() + "/logs";

    // 初始化日志库
    initLogger(logDir);

    QString vInfo = QString("SRE V%1").arg(QCoreApplication::applicationVersion());

    qDebug() << vInfo;
    QLOG_INFO() << vInfo;

    MainWindow mainWindow;
    mainWindow.show();

    return a.exec();
}
