#include "AcqScreen.h"
#include <QDebug>

#include "FFmpegEncoder.h"
#include "Duplication.h"
#include "Utils.h"
#include "Frame.h"

AcqScreen::AcqScreen(QObject *parent, FFmpegEncoder *encoder)
    : QObject(parent), mEncoder(encoder)
{
    qDebug()<<"AcqScreen::AcqScreen()";
}

AcqScreen::~AcqScreen()
{
    qDebug()<<"AcqScreen::~AcqScreen()";
}

int AcqScreen::start()
{
    qDebug()<<"AcqScreen::start()";
    bIsStop.store(false);
    mThread = new std::thread(AcqScreen::run_thread, this);

    return 0;
}

int AcqScreen::pause()
{
    return 0;
}

int AcqScreen::stop()
{
    qDebug()<<"AcqScreen::stop()";
    bIsStop.store(true);

    mThread->join();

    delete mThread;
    mThread = nullptr;

    return 0;
}

void AcqScreen::run_thread(void *arg)
{
    AcqScreen* acq = (AcqScreen*)arg;

   Duplication dup;
   if(!dup.InitDevice())
   {
       qDebug() << "InitDevice error";
       return;
   }

   if(!dup.InitDupl(0))
   {
       qDebug() << "InitDupl error";
       return;
   }

   int width = 2560;
   int height = 1600;

   int bufferSize = height * width * 4;
   uint8_t* buffer = new uint8_t[bufferSize];

   int64_t frameCount = 0;

   int64_t t1, t2;
   int interval_duration = int(1000 / acq->mEncoder->get_fps());
   int interval_sleep;
   int total_latency_sleep = 0;

   while(true)
   {
       t1 = Utils::getCurTimestamp();
       if(acq->bIsStop.load())
       {
           break;
       }

       if(dup.GetFrame())
       {
           if(dup.copyFrameDataToBuffer(buffer, bufferSize, width, height))
           {
               dup.DoneWithFrame(); // 释放

               Frame* frame = new Frame(FrameFmt::Frame_Fmt_BGRA, bufferSize, width, height, frameCount);
               memcpy_s(frame->data, bufferSize, buffer, bufferSize);
               acq->mEncoder->push_frame(frame);

               ++frameCount;
           }
           else
           {
               qDebug() << __FILE__ << __FUNCTION__ << __LINE__ << "copyFrameDataToBuffer error";
           }
       }
       else
       {
           Frame* frame = new Frame(FrameFmt::Frame_Fmt_BGRA, bufferSize, width, height, frameCount);
           memcpy_s(frame->data, bufferSize, buffer, bufferSize);
           acq->mEncoder->push_frame(frame);

           ++frameCount;
       }

       t2 = Utils::getCurTimestamp();
       interval_sleep = interval_duration - (t2 - t1);

       // 时间补偿
       if(interval_sleep > 0)
       {
           if(total_latency_sleep > 0)
           {
               if(total_latency_sleep >= interval_sleep)
               {
                   total_latency_sleep -= interval_sleep;
               }
               else
               {
                   interval_sleep -= total_latency_sleep;
                   total_latency_sleep = 0;
                   std::this_thread::sleep_for(std::chrono::milliseconds(interval_sleep));
               }
           }
           else
           {
               std::this_thread::sleep_for(std::chrono::milliseconds(interval_sleep));
           }
       }
       else if(interval_sleep < 0)
       {
           total_latency_sleep += (-interval_sleep);
       }
   }

   if(buffer)
   {
       delete[] buffer;
       buffer = nullptr;
   }
}
