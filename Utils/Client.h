#ifndef CLIENT_H
#define CLIENT_H

#include <QImage>
#include <QObject>
#include <VideoRecorder.h>

namespace UMediaLibrary
{
    struct VideoRecorder;
    struct AudioRecorder;
    struct AvEncoder;
}

class QTcpSocket;

class Client : public QObject
{
    Q_OBJECT
public:
    explicit Client(QObject *parent = nullptr);

    bool initNewConnect(QTcpSocket*& newConnect, unsigned short port);

    bool connectServer(const QString& Ip);

    void sendMsg();

    void sendImage(const QByteArray& data);

    void recvMsg();

    void recvData(QByteArray& data);

    void startRecvVideo();

    void startSendVideo();

private:
    bool initVideo();

private:
    QTcpSocket* mConnectSocket;

    QString mServerIp;

    UMediaLibrary::VideoRecorder* mVideoRecorder = nullptr;

    UMediaLibrary::EPixelFormat mPixelFormat = UMediaLibrary::PIXEL_None;

    int factWidth;
    int factHeight;


    class RecvTextureThread* mTestThread;

public:
    inline int getFactWidth() const { return factWidth; }
    inline int getFactHeight() const { return factHeight; }
    inline UMediaLibrary::VideoRecorder* getVideoRecorder() const { return mVideoRecorder; }
    inline UMediaLibrary::EPixelFormat getPixelFormat() const { return mPixelFormat; }

signals:
    void setImage(QImage image);
};

#endif // CLIENT_H
