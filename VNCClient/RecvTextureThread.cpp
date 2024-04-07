#include "RecvTextureThread.h"

#include "Client.h"

RecvTextureThread::RecvTextureThread(QObject *parent)
    : QThread{parent}
{
    mClient = (Client*)parent;
}

RecvTextureThread::~RecvTextureThread()
{
    bIsStop = true;

    wait();
}

void RecvTextureThread::run()
{
    bIsStop = false;

    QByteArray data;
    mClient->recvData(data);

    QImage image;
    image.loadFromData(data);

    emit mClient->setImage(image);
}
