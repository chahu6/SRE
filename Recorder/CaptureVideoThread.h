#ifndef CAPTUREVIDEOTHREAD_H
#define CAPTUREVIDEOTHREAD_H

#include <QThread>

struct CaptureVideoDevice;
class Recorder;

class CaptureVideoThread : public QThread
{
    Q_OBJECT
public:
    CaptureVideoThread(QObject* parent, CaptureVideoDevice* videoDevice);
    ~CaptureVideoThread();

protected:
    virtual void run() override;

private:
    Recorder* mRecorder;
    CaptureVideoDevice* mVideoDevice;
    bool mIsStop = false;
};

#endif // CAPTUREVIDEOTHREAD_H
