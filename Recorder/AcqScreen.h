#ifndef ACQSCREEN_H
#define ACQSCREEN_H

#include <QObject>
#include <thread>

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
    FFmpegEncoder* m_Encoder;
    bool bIsRecording = false;
    bool bIsStop = true;
    std::thread* m_Thread;

signals:

public slots:
};

#endif // ACQSCREEN_H
