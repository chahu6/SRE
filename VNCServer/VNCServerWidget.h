#ifndef VNCSERVERWIDGET_H
#define VNCSERVERWIDGET_H

#include <QWidget>

class ControlServer;

class VNCServerWidget : public QWidget
{
    Q_OBJECT
public:
    explicit VNCServerWidget(QWidget *parent = nullptr);

private:
    void initUI();

private:
    ControlServer* mServer;

signals:

public slots:
    void listenServer();
};

#endif // VNCSERVERWIDGET_H
