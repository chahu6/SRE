#ifndef TESTSERVERTHREAD_H
#define TESTSERVERTHREAD_H

#include <QThread>
#include <VideoRecorder.h>

namespace UMediaLibrary
{
struct VideoRecorder;
struct AudioRecorder;
struct AvEncoder;
}

class QTcpSocket;

class TestServerThread : public QThread
{
    Q_OBJECT
public:
    explicit TestServerThread(QObject *parent = nullptr, QTcpSocket* tcp = nullptr);
    ~TestServerThread();

protected:
    virtual void run() override;

private:
    UMediaLibrary::VideoRecorder* mVideoRecorder;

    UMediaLibrary::EPixelFormat mPixelFormat = UMediaLibrary::PIXEL_None;

    bool bIsStop = false;

    QTcpSocket* m_tcp;

    int factWidth;
    int factHeight;
};

#endif // TESTSERVERTHREAD_H
