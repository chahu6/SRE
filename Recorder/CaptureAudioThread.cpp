#include "CaptureAudioThread.h"
#include <AudioRecorder.h>
#include <AvFrame.h>
#include <AvEncoder.h>

#include "Recorder.h"

using namespace UMediaLibrary;

CaptureAudioThread::CaptureAudioThread(QObject *parent, CaptureAudioDevice *audioDevice)
    : QThread{parent}, mAudioDevice(audioDevice)
{
    mRecorder = (Recorder*)parent;
}

CaptureAudioThread::~CaptureAudioThread()
{
    mIsStop = true;
    wait();
}

void CaptureAudioThread::run()
{
    mIsStop = false;
    int ret;
    AudioRecorder* audioRecorder = mRecorder->getAudioRecorder();
    AvEncoder* avEncoder = mRecorder->getAvEncoder();

    FFrame* audioFrame = new FFrame(AV_Audio, 10000);

    uint8_t* audioBuff = new uint8_t[10000];
    int audioBuffSize = 0;

    int recvBuffSize = 0;
    uint8_t* recvBuff = new uint8_t[10000];

    const int frameSize = 4608;
    int64_t timestamp = 0;
    int64_t frameTimestamp = 0;
    int64_t frameCount = 0;

    while(true)
    {
        if(mIsStop) break;

        ret = get_sample(audioRecorder, recvBuff, recvBuffSize, timestamp);
        if(ret >= 0)
        {
            if(recvBuffSize > 0)
            {
                if(0 == audioBuffSize)
                {
                    frameTimestamp = timestamp;
                }

                memcpy(audioBuff + audioBuffSize, recvBuff, recvBuffSize);
                audioBuffSize += recvBuffSize;

                if(audioBuffSize >= frameSize)
                {
                    memcpy(audioFrame->data, audioBuff, frameSize);
                    audioFrame->size = frameSize;
                    audioFrame->timestamp = timestamp;
                    audioFrame->count = frameCount;

                    send_frame(avEncoder, audioFrame);

                    audioBuffSize -= frameSize;
                    memmove(audioBuff, audioBuff + frameSize, audioBuffSize);
                    frameTimestamp = timestamp;
                    ++frameCount;
                }
            }
        }
        else
        {

        }
    }

    if (recvBuff)
    {
        delete[]recvBuff;
        recvBuff = nullptr;
    }
    if (audioBuff)
    {
        delete[]audioBuff;
        audioBuff = nullptr;
    }
    this->exit();
}
