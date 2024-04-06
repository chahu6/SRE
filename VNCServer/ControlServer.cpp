#include "ControlServer.h"
#include <QTcpServer>

ControlServer::ControlServer(QObject *parent)
    : QObject{parent}
{
    mServer = new QTcpServer(this);

    // connect(mServer, &QTcpServer::newConnection, this, [=](){
    //     m_tcp = mServer->nextPendingConnection();
    //     m_status->setText("√");
    //     ui->sendMsg->setEnabled(true);
    //     connect(m_tcp, &QTcpSocket::readyRead, this, [=](){
    //         QByteArray data = m_tcp->readAll();
    //         ui->record->append("客户端说：" + data);
    //     });
    //     connect(m_tcp, &QTcpSocket::disconnected, this, [=]()
    //             {
    //                 m_tcp->close();
    //                 m_tcp->deleteLater();
    //                 m_status->setText("✖");
    //                 ui->sendMsg->setDisabled(true);
    //             });
    // });
}

bool ControlServer::listenServer(unsigned short port)
{
    return mServer->listen(QHostAddress::Any, port);
}
