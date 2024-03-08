#ifndef RECORDER_H
#define RECORDER_H

#include <QObject>
#include <QImage>

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

private:

signals:
    void setImage(QImage image);

public slots:
};

#endif // RECORDER_H
