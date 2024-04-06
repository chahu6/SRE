#include "ClientDialog.h"
#include <QDebug>
#include <QLabel>
#include <QVBoxLayout>

#include "Client.h"

ClientDialog::ClientDialog(Client* client, QWidget *parent)
    :QDialog(parent), mClient(client)
{
    qDebug()<<"ClientDialog::ClientDialog()";
    Qt::WindowFlags flags=Qt::Dialog;
    flags |= Qt::WindowMinMaxButtonsHint;
    flags |= Qt::WindowCloseButtonHint;
    setWindowFlags(flags);
    resize(1000,600);
    setAttribute(Qt::WA_StyledBackground,true);
    setStyleSheet(QString(".ClientDialog{background-color:%1;}").arg("rgb(43,46,56)"));
    setWindowTitle(tr("远程控制"));

    initUi();
}

void ClientDialog::initUi()
{
    QVBoxLayout* mainVLayout = new QVBoxLayout(this);
    mainVLayout->setContentsMargins(0,0,0,0);
    mainVLayout->setSpacing(0);

    imageLabel = new QLabel(this);
    imageLabel->setStyleSheet(".QLabel{background-color:rgb(255,0,0)}");
    mainVLayout->addWidget(imageLabel);
}
