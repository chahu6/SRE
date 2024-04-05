#ifndef DESKTOPCONTROL_H
#define DESKTOPCONTROL_H

#include <QObject>

class DesktopControl : public QObject
{
    Q_OBJECT
public:
    explicit DesktopControl(QObject *parent = nullptr);

signals:
};

#endif // DESKTOPCONTROL_H
