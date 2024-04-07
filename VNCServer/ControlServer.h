#ifndef CONTROLSERVER_H
#define CONTROLSERVER_H

#include <QObject>

class QTcpServer;
class QTcpSocket;

class TestServerThread;

class ControlServer : public QObject
{
    Q_OBJECT
public:
    explicit ControlServer(QObject *parent = nullptr);

    bool listenServer(unsigned short port);

    void recvMsg();

private:
    QTcpServer* mServer;
    QTcpSocket* m_tcp;

    TestServerThread* mTestThread;

signals:
};

#endif // CONTROLSERVER_H
