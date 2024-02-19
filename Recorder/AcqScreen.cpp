#include "AcqScreen.h"
#include <QDebug>

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
    mThread = new std::thread(run_thread, this);

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

//    Duplication dup;
//    if(!dup)
}
