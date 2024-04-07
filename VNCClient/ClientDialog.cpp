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

    connect(mClient, &Client::setImage, this, &ClientDialog::onSetImage);

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

void ClientDialog::onSetImage(QImage image)
{
    //    update(); //调用update将执行 paintEvent函数
    int scaled_h = imageLabel->height();
    int scaled_w = int(float(scaled_h) * float(image.width())/float(image.height()));

    QImage scaled_image = image.scaled(scaled_w, scaled_h, Qt::IgnoreAspectRatio);

    //    qDebug()<<"RecordWidget::onSetImage width="<<this->width()<<",height="<<this->height()<<
    //              ",image.width="<<image.width()<<",image.height="<<image.height()<<
    //              ",scaled_image.width="<<scaled_image.width()<<",scaled_image.height="<<scaled_image.height();

    QPixmap pixmap = QPixmap::fromImage(scaled_image);
    imageLabel->setPixmap(pixmap);
}
