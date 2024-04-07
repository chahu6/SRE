#ifndef CLIENTDIALOG_H
#define CLIENTDIALOG_H

#include <QDialog>

QT_BEGIN_INCLUDE_NAMESPACE
class QLabel;
QT_END_INCLUDE_NAMESPACE

class Client;

class ClientDialog : public QDialog
{
    Q_OBJECT
public:
    explicit ClientDialog(Client* client, QWidget *parent);

private:
    void initUi();

private:
    Client* mClient;

    QLabel* imageLabel; // 渲染录屏画面

public slots:
    void onSetImage(QImage image);
};

#endif // CLIENTDIALOG_H
