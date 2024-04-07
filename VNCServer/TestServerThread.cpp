#include "TestServerThread.h"

#include <AvFrame.h>
#include <FpsControl.h>
#include <QImage>
#include <QTcpSocket>
#include <SingletonUtils.h>
#include <VideoRecorder.h>
#include <qbuffer.h>

using namespace UMediaLibrary;

TestServerThread::TestServerThread(QObject *parent, QTcpSocket *tcp)
    :QThread(parent), m_tcp(tcp)
{
    int width = SingletonUtils::getInstance()->getScreenWidth();
    int height = SingletonUtils::getInstance()->getScreenHeight();

    mVideoRecorder = new VideoRecorder("GDI", width, height, 0);

    // VideoRecorder_Open(mVideoRecorder);

    factWidth = mVideoRecorder->factWidth;
    factHeight = mVideoRecorder->factHeight;
    mPixelFormat = mVideoRecorder->pixelFormat;
}

TestServerThread::~TestServerThread()
{
    bIsStop = true;

    wait();
}

void TestServerThread::run()
{
    int fps = 25;
    int width = factWidth;
    int height = factHeight;

    int frameBuffSize = height * width * 4;
    uint8_t* frameBuff = new uint8_t[frameBuffSize];
    uint8_t* frameBuff_rgba = new uint8_t[frameBuffSize];

    FFrame* videoFrame = new FFrame(AV_Video, frameBuffSize);

    int64_t frameTimestamp = 0;
    int64_t frameCount = 0;

    int show_interval = 5; // 屏幕显示时间隔数量

    int ret;
    FpsControl fpsControl(fps);
    fpsControl.realTimeStart();

    while(true)
    {
        fpsControl.intervalStart();

        if(bIsStop) break;

        ret = get_frame(mVideoRecorder, frameBuff, frameBuffSize, frameTimestamp);

        if(ret >= 0)
        {
            memcpy(videoFrame->data, frameBuff, frameBuffSize);
            videoFrame->size = frameBuffSize;
            videoFrame->timestamp = frameTimestamp;
            videoFrame->count = frameCount;

            if(0 == frameCount % show_interval)
            {
                QByteArray imageByteArray;
                QBuffer buffer(&imageByteArray);
                buffer.open(QIODevice::WriteOnly);

                if(PIXEL_BGRA == mPixelFormat)
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
                    image.save(&buffer, "JPEG"); // 或者使用"PNG"来保存为PNG格式

                    m_tcp->write(imageByteArray);
                }
                else if(PIXEL_RGB == mPixelFormat)
                {
                    QImage image(frameBuff, width, height, QImage::Format_RGB888);
                    image.save(&buffer, "JPEG"); // 或者使用"PNG"来保存为PNG格式

                    m_tcp->write(imageByteArray);
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


        break;
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
