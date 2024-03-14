#ifndef CAPTUREAUDIOTHREAD_H
#define CAPTUREAUDIOTHREAD_H

#include <QThread>

class Recorder;
class CaptureAudioDevice;

class CaptureAudioThread : public QThread
{
    Q_OBJECT
public:
    explicit CaptureAudioThread(QObject *parent, CaptureAudioDevice* audioDevice);
    ~CaptureAudioThread();

protected:
    virtual void run() override;

private:
    Recorder* mRecorder;
    CaptureAudioDevice* mAudioDevice;
    bool mIsStop = false;

};

#endif // CAPTUREAUDIOTHREAD_H
