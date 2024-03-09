#include "Recorder.h"

Recorder::Recorder(QObject *parent)
    :QObject(parent)
{
}

Recorder::~Recorder()
{
    this->stop();
}

bool Recorder::start(CaptureVideoDevice *videoDevice, CaptureAudioDevice *audioDevice, const QString &url)
{

    return false;
}

bool Recorder::pause()
{
    return false;
}

bool Recorder::stop()
{
    return false;
}
