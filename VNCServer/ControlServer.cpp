#include "ControlServer.h"
#include <QTcpServer>
#include <QTcpSocket>

#include "TestServerThread.h"

ControlServer::ControlServer(QObject *parent)
    : QObject{parent}
{
    mServer = new QTcpServer(this);

    connect(mServer, &QTcpServer::newConnection, this, [this](){
        m_tcp = mServer->nextPendingConnection();

        qDebug() << "新的连接";

        connect(m_tcp, &QTcpSocket::readyRead, this, &ControlServer::recvMsg);

        connect(m_tcp, &QTcpSocket::disconnected, this, [=]()
        {
            m_tcp->close();
            m_tcp->deleteLater();
        });

        mTestThread = new TestServerThread(this, m_tcp);
        mTestThread->start();
    });
}

bool ControlServer::listenServer(unsigned short port)
{
    return mServer->listen(QHostAddress::Any, port);
}

void ControlServer::recvMsg()
{
    QByteArray data = m_tcp->readAll();
    qDebug() << "Server: 接受: " << data.toStdString().c_str();
}
