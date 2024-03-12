#ifndef VNCSERVERWIDGET_H
#define VNCSERVERWIDGET_H

#include <QWidget>

class VNCServerWidget : public QWidget
{
    Q_OBJECT
public:
    explicit VNCServerWidget(QWidget *parent = nullptr);

private:
    void initUI();

signals:
};

#endif // VNCSERVERWIDGET_H
