#ifndef DESKTOPCONTROLWIDGET_H
#define DESKTOPCONTROLWIDGET_H

#include <QWidget>

class DesktopControlWidget : public QWidget
{
    Q_OBJECT
public:
    explicit DesktopControlWidget(QWidget *parent = nullptr);

private:
    void initUI();

signals:
};

#endif // DESKTOPCONTROLWIDGET_H
