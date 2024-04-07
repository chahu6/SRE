#include "Client.h"
#include <QHostAddress>
#include <QTcpSocket>
#include <AvEncoder.h>
#include <RecvTextureThread.h>
#include "SingletonUtils.h"

using namespace UMediaLibrary;

Client::Client(QObject *parent)
    : QObject{parent}
{
    mConnectSocket = new QTcpSocket(this);

    int width = SingletonUtils::getInstance()->getScreenWidth();
    int height = SingletonUtils::getInstance()->getScreenHeight();

    mVideoRecorder = new VideoRecorder("DXGI", width, height, 0);

    // VideoRecorder_Open(mVideoRecorder);

    factWidth = mVideoRecorder->factWidth;
    factHeight = mVideoRecorder->factHeight;
    mPixelFormat = mVideoRecorder->pixelFormat;
}

bool Client::initNewConnect(QTcpSocket *&newConnect, unsigned short port)
{
    if(newConnect)
    {
        newConnect->connectToHost(QHostAddress(mServerIp), port);
        return true;
    }
    return false;
}

bool Client::connectServer(const QString &Ip)
{
    mServerIp = Ip;
    if(!initNewConnect(mConnectSocket, 8899))
    {
        // return false;
    }
    // return true;

    mTestThread = new RecvTextureThread(this);
    mTestThread->start();
}

void Client::sendMsg()
{
    // mConnectSocket->write("核理论");
    // mConnectSocket->write()

}

void Client::sendImage(const QByteArray &data)
{
    mConnectSocket->write(data);
}

void Client::recvMsg()
{

}

void Client::recvData(QByteArray& data)
{
    if(mConnectSocket->waitForReadyRead())
    {
        data = mConnectSocket->readAll();
    }
}

void Client::startRecvVideo()
{

}

void Client::startSendVideo()
{

}

bool Client::initVideo()
{

}
