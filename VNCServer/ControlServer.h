#ifndef CONTROLSERVER_H
#define CONTROLSERVER_H

#include <QObject>

class QTcpServer;

class ControlServer : public QObject
{
    Q_OBJECT
public:
    explicit ControlServer(QObject *parent = nullptr);

    bool listenServer(unsigned short port);

private:
    QTcpServer* mServer;

signals:
};

#endif // CONTROLSERVER_H
