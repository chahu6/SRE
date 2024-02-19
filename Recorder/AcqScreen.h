#ifndef ACQSCREEN_H
#define ACQSCREEN_H

#include <QObject>
#include <thread>
#include <atomic>

class FFmpegEncoder;

class AcqScreen : public QObject
{
    Q_OBJECT
public:
    explicit AcqScreen(QObject *parent, FFmpegEncoder* encoder);
    ~AcqScreen();

public:
    int start();
    int pause();
    int stop();

private:
    static void run_thread(void* arg);

private:
    FFmpegEncoder* mEncoder;
    bool bIsRecording = false;
    std::atomic<bool> bIsStop{true};
    std::thread* mThread;

signals:

public slots:
};

#endif // ACQSCREEN_H
