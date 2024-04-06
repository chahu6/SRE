#ifndef VNCCLIENTWIDGET_H
#define VNCCLIENTWIDGET_H

#include <QWidget>
QT_BEGIN_INCLUDE_NAMESPACE
class QLineEdit;
class QPushButton;
QT_END_INCLUDE_NAMESPACE

class Client;
class ClientDialog;

class VNCClientWidget : public QWidget
{
    Q_OBJECT
public:
    explicit VNCClientWidget(QWidget *parent = nullptr);

private:
    void initUI();

private:
    QLineEdit* mIpLineEdit;
    QLineEdit* mPortLineEdit;
    Client* mClient;

    ClientDialog *clientDialog;

signals:

public slots:
    void connectServer(bool checked);
};

#endif // VNCCLIENTWIDGET_H
