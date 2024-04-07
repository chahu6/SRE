#include "VNCClientWidget.h"
#include <QHBoxLayout>
#include <QPushButton>
#include <QLineEdit>
#include <QDebug>
#include <QHostAddress>
#include "ClientDialog.h"
#include "Client.h"


VNCClientWidget::VNCClientWidget(QWidget *parent)
    : QWidget{parent}
{
    setAttribute(Qt::WA_StyledBackground,true);
    setStyleSheet(QString(".VNCClientWidget{background-color:%1;}").arg("rgb(25,27,38)"));

    mClient = new Client(this);
    clientDialog = new ClientDialog(mClient, this);

    initUI();
}

void VNCClientWidget::initUI()
{
    QHBoxLayout *mainHLayout = new QHBoxLayout(this);
    mainHLayout->setContentsMargins(0,0,0,0);
    mainHLayout->setSpacing(0);

    // test
    QWidget* testWidget = new QWidget(this);
    QVBoxLayout* testVLayout = new QVBoxLayout(testWidget);
    testVLayout->setContentsMargins(0,0,0,0);
    testVLayout->setSpacing(0);

    mIpLineEdit = new QLineEdit(this);
    mIpLineEdit->setFixedSize(300, 30);
    mIpLineEdit->setText("127.0.0.1");

    mPortLineEdit = new QLineEdit(this);
    mPortLineEdit->setFixedSize(300, 30);
    mPortLineEdit->setText("8899");

    QPushButton* connectBtn = new QPushButton(this);
    connectBtn->setText("发起远程");
    connectBtn->setFixedSize(300, 30);

    connect(connectBtn, &QPushButton::clicked, this, &VNCClientWidget::connectServer);

    testVLayout->addStretch();
    testVLayout->addWidget(mIpLineEdit);
    testVLayout->addSpacing(10);
    testVLayout->addWidget(mPortLineEdit);
    testVLayout->addSpacing(10);
    testVLayout->addWidget(connectBtn);
    testVLayout->addStretch();

    mainHLayout->addStretch();
    mainHLayout->addWidget(testWidget);
    mainHLayout->addStretch();
}

void VNCClientWidget::connectServer(bool checked)
{
    QString ip = mIpLineEdit->text();
    unsigned short port = mPortLineEdit->text().toUShort();

    mClient->connectServer(ip);

    clientDialog->show();
}
