#ifndef CAPTURETEXTURETHREAD_H
#define CAPTURETEXTURETHREAD_H

#include <QThread>

class Client;

class CaptureTextureThread : public QThread
{
    Q_OBJECT
public:
    explicit CaptureTextureThread(QObject *parent = nullptr);
    ~CaptureTextureThread();

protected:
    virtual void run() override;

private:
    Client* mClient;

    bool bIsStop = false;
};

#endif // CAPTURETEXTURETHREAD_H
