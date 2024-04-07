#ifndef RECVTEXTURETHREAD_H
#define RECVTEXTURETHREAD_H

#include <QThread>

class Client;

class RecvTextureThread : public QThread
{
    Q_OBJECT
public:
    explicit RecvTextureThread(QObject *parent);
    ~RecvTextureThread();

protected:
    virtual void run() override;

private:
    bool bIsStop = false;

    Client* mClient = nullptr;
};

#endif // RECVTEXTURETHREAD_H
