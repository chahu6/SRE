#ifndef CLIENT_H
#define CLIENT_H

#include <QObject>

class QTcpSocket;

class Client : public QObject
{
    Q_OBJECT
public:
    explicit Client(QObject *parent = nullptr);

    bool initNewConnect(QTcpSocket*& newConnect, unsigned short port);

    bool connectServer(const QString& Ip);

    void sendMsg();

    void recvMsg();

    void startRecvVideo();

private:
    bool initVideo();

private:
    QTcpSocket* mConnectSocket;

    QString mServerIp;

signals:

};

#endif // CLIENT_H
