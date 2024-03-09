#ifndef RECORDER_H
#define RECORDER_H

#include <QObject>
#include <QImage>
#include <VideoRecorder.h>

namespace UMediaLibrary {
    struct VideoRecorder;
    struct AudioRecorder;
    struct AvEncoder;
}

class CaptureVideoThread;

struct CaptureVideoDevice
{
    CaptureVideoDevice() = delete;
    CaptureVideoDevice(QString nickname) :mNickname(nickname) {}

    CaptureVideoDevice(bool use, bool isCamera, QString nickname, QString name, int fps):
        mUse(use), mIsCamera(isCamera), mNickname(nickname), mName(name), mFps(fps) {}

public:
    bool isUse(){
        return mUse;
    }
    bool isCamera(){
        return mIsCamera;
    }
    QString getNickname(){
        return mNickname;
    }
    QString getName(){
        return mName;
    }

    int getFps(){
        return mFps;
    }

public:
    int width;
    int height;

private:
    bool mUse = false;
    bool mIsCamera = false;
    QString mNickname;
    QString mName;
    int mFps;
};

struct CaptureAudioDevice
{
    CaptureAudioDevice() = delete;
    CaptureAudioDevice(QString nickname):
        mUse(false),mNickname(nickname){

    }
    CaptureAudioDevice(bool use,QString nickname,QString name):
        mUse(use),mNickname(nickname),mName(name){

    }
public:
    bool isUse(){
        return mUse;
    }
    QString getNickname(){
        return mNickname;
    }
    QString getName(){
        return mName;
    }
private:
    bool mUse;
    QString mNickname;
    QString mName;
};

class Recorder : public QObject
{
    Q_OBJECT
public:
    explicit Recorder(QObject *parent);
    ~Recorder();

public:
    bool start(CaptureVideoDevice* videoDevice, CaptureAudioDevice* audioDevice, const QString& url);
    bool pause();
    bool stop();

    UMediaLibrary::VideoRecorder* getVideoRecorder();
    UMediaLibrary::AudioRecorder* getAudioRecorder();
    UMediaLibrary::AvEncoder* getAvEncoder();
    UMediaLibrary::EPixelFormat getPixelFormat();

private:
    CaptureVideoDevice* mVideoDevice = nullptr;
    CaptureAudioDevice* mAudioDevice = nullptr;

    UMediaLibrary::VideoRecorder* mVideoRecorder = nullptr;
    UMediaLibrary::AudioRecorder* mAudioRecorder = nullptr;
    UMediaLibrary::AvEncoder*  mAvEncoder = nullptr;

    CaptureVideoThread* mCaptureVideoThread = nullptr;

    bool mIsStop = true;
    UMediaLibrary::EPixelFormat mPixelFormat = UMediaLibrary::PIXEL_None;

signals:
    void setImage(QImage image);

public slots:
};

#endif // RECORDER_H
