#include "Client.h"
#include <QHostAddress>
#include <QTcpSocket>

Client::Client(QObject *parent)
    : QObject{parent}
{
    mConnectSocket = new QTcpSocket(this);
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
        return false;
    }
    return true;
}

void Client::sendMsg()
{
    // mConnectSocket->write();
}

void Client::recvMsg()
{

}

void Client::startRecvVideo()
{

}

bool Client::initVideo()
{

}
