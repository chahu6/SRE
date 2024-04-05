#include "Recorder.h"
#include <AvEncoder.h>
#include <AvFrame.h>
#include <QTimer>
#include <AudioRecorder.h>

#include "SingletonUtils.h"
#include "CaptureVideoThread.h"
#include "CaptureAudioThread.h"

using namespace UMediaLibrary;

Recorder::Recorder(QObject *parent)
    :QObject(parent)
{}

Recorder::~Recorder()
{
    this->stop();
}

bool Recorder::start(CaptureVideoDevice *videoDevice, CaptureAudioDevice *audioDevice, const QString &url)
{
    mVideoDevice = videoDevice;
    mAudioDevice = audioDevice;

    // 采集视频相关参数
    int videoBitrate = 2000000;
    mVideoDevice->width = SingletonUtils::getInstance()->getScreenWidth();
    mVideoDevice->height = SingletonUtils::getInstance()->getScreenHeight();

    int fps = mVideoDevice->getFps();
    bool hasVideo = mVideoDevice->isUse();
    const char* videoCodecName = "libx264";

    // 采集音频相关参数
    bool hasAudio = mAudioDevice->isUse();
    const char* audioCodecName = "aac";
    int audioBitrate = 128000;

    int ret;

    if(hasVideo)
    {
        const char* videoCapture = mVideoDevice->getName().toStdString().data();
        mVideoRecorder = new VideoRecorder(videoCapture, mVideoDevice->width, mVideoDevice->height, 0);

        ret = VideoRecorder_Open(mVideoRecorder);
        if(ret < 0)
        {
            return false;
        }

        mVideoDevice->width = mVideoRecorder->factWidth;
        mVideoDevice->height = mVideoRecorder->factHeight;
        mPixelFormat = mVideoRecorder->pixelFormat;
    }

    if(hasAudio)
    {
        const char* audioCapture = mAudioDevice->getName().toStdString().data();
        mAudioRecorder = new AudioRecorder(audioCapture);

        ret = AudioRecorder_Open(mAudioRecorder);
        if(ret < 0)
        {
            return false;
        }
    }

    mAvEncoder = new AvEncoder(hasVideo, videoCodecName, videoBitrate, mPixelFormat,
                               mVideoDevice->width, mVideoDevice->height, fps,
                               hasAudio, audioCodecName, audioBitrate);

    ret = AvEncoder_Open(mAvEncoder, url.toLatin1().constData());
    if(ret < 0)
    {
        return false;
    }

    mIsStop = false;

    // 开启采集视频帧线程
    if(hasVideo)
    {
        mCaptureVideoThread = new CaptureVideoThread(this, mVideoDevice);
        mCaptureVideoThread->start(QThread::NormalPriority);
    }

    // 开启采集音频线程
    if(hasAudio)
    {
        mCaptureAudioThread = new CaptureAudioThread(this, mAudioDevice);
        mCaptureAudioThread->start(QThread::NormalPriority);
    }

    return true;
}

bool Recorder::pause()
{
    return false;
}

bool Recorder::stop()
{
    mIsStop = true;

    if(mCaptureVideoThread)
    {
        delete mCaptureVideoThread;
        mCaptureVideoThread = nullptr;
    }

    if(mCaptureAudioThread)
    {
        delete mCaptureAudioThread;
        mCaptureAudioThread = nullptr;
    }

    if(mVideoRecorder)
    {
        VideoRecorder_Close(mVideoRecorder);
        delete mVideoRecorder;
        mVideoRecorder = nullptr;
    }

    if(mAudioRecorder)
    {
        AudioRecorder_Close(mAudioRecorder);
        delete mAudioRecorder;
        mAudioRecorder = nullptr;
    }

    if(mAvEncoder)
    {
        AvEncoder_Close(mAvEncoder);
        delete mAvEncoder;
        mAvEncoder = nullptr;
    }

    if(mVideoDevice && mVideoDevice->isUse())
    {
        QTimer::singleShot(100, this, [this]()
        {
            QImage image(mVideoDevice->width, mVideoDevice->height, QImage::Format_RGB32);
            image.fill(QColor(25, 27, 38));
            emit this->setImage(image.copy());
        });
    }
    return true;
}

VideoRecorder *Recorder::getVideoRecorder()
{
    return mVideoRecorder;
}

AudioRecorder *Recorder::getAudioRecorder()
{
    return mAudioRecorder;
}

AvEncoder *Recorder::getAvEncoder()
{
    return mAvEncoder;
}

EPixelFormat Recorder::getPixelFormat()
{
    return mPixelFormat;
}
