#include "CaptureVideoThread.h"
#include <AvFrame.h>
#include <VideoRecorder.h>
#include <AvEncoder.h>
#include <QImage>

#include "Recorder.h"
#include "FpsControl.h"

using namespace UMediaLibrary;

CaptureVideoThread::CaptureVideoThread(QObject *parent, CaptureVideoDevice *videoDevice)
    :QThread(parent), mVideoDevice(videoDevice)
{
    mRecorder = (Recorder*)parent;
}

CaptureVideoThread::~CaptureVideoThread()
{

}

void CaptureVideoThread::run()
{
    mIsStop = false;

    int fps = mVideoDevice->getFps();
    int width = mVideoDevice->width;
    int height = mVideoDevice->height;

    int frameBuffSize = height * width * 4;
    uint8_t* frameBuff = new uint8_t[frameBuffSize];
    uint8_t* frameBuff_rgba = new uint8_t[frameBuffSize];

    FFrame* videoFrame = new FFrame(AV_Video, frameBuffSize);

    int64_t frameTimestamp = 0;
    int64_t frameCount = 0;

    int show_interval = 5; // 屏幕显示时间隔数量
    if(mVideoDevice->isCamera())
    {
        show_interval = 2;
    }

    int ret;
    FpsControl fpsControl(fps);
    fpsControl.realTimeStart();

    while(true)
    {
        fpsControl.intervalStart();
        if(mIsStop)
        {
            break;
        }
        ret = get_frame(mRecorder->getVideoRecorder(), frameBuff, frameBuffSize, frameTimestamp);

        if(ret >= 0)
        {
            memcpy(videoFrame->data, frameBuff, frameBuffSize);
            videoFrame->size = frameBuffSize;
            videoFrame->timestamp = frameTimestamp;
            videoFrame->count = frameCount;

            send_frame(mRecorder->getAvEncoder(), videoFrame);

            if(0 == frameCount % show_interval)
            {
                if(PIXEL_BGRA == mRecorder->getPixelFormat())
                {
                    // (bgra->rgba)大端模式，RGBA中R存储在高位，A存储在低位
                    memcpy_s(frameBuff_rgba, frameBuffSize, frameBuff, frameBuffSize);
                    for(int i = 0; i < width * height; ++i)
                    {
                        frameBuff_rgba[i] = (frameBuff_rgba[i] & 0x000000FF) |         // ______AA
                                            ((frameBuff_rgba[i] & 0x0000FF00) << 16) | // RR______
                                            (frameBuff_rgba[i] & 0x00FF0000) |         // __GG____
                                            ((frameBuff_rgba[i] & 0xFF000000) >> 16);  // ____BB__
                    }
                    QImage image(frameBuff_rgba, width, height, QImage::Format_RGB32);
                    emit mRecorder->setImage(image.copy());
                }
                else if(PIXEL_RGB == mRecorder->getPixelFormat())
                {
                    QImage image(frameBuff, width, height, QImage::Format_RGB888);
                    emit mRecorder->setImage(image.copy());
                }
            }
            ++frameCount;
            fpsControl.realTimeIncrease();
        }
        else
        {
            continue;
        }
        fpsControl.adjust();
    }

    if(frameBuff)
    {
        delete[] frameBuff;
        frameBuff = nullptr;
    }

    if(frameBuff_rgba)
    {
        delete[] frameBuff_rgba;
        frameBuff_rgba = nullptr;
    }
    this->exit();
}
