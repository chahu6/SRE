#include "RecordWidget.h"
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QDesktopServices>
#include <QUrl>
#include <QMediaDevices>

#include "ComLineWidget.h"
#include "Utils.h"
#include "SingletonUtils.h"

RecordWidget::RecordWidget(QWidget *parent)
    :QWidget(parent)
{
    initUI();
}

RecordWidget::~RecordWidget()
{

}

void RecordWidget::initUI()
{
    QVBoxLayout* mainVLayout = new QVBoxLayout(this);
    mainVLayout->setContentsMargins(0,0,0,0);
    mainVLayout->setSpacing(0);

    // name start
    QWidget* nameWidget = new QWidget(this);
    nameWidget->setFixedHeight(50);
    QHBoxLayout* nameHLayout = new QHBoxLayout(nameWidget);
    nameHLayout->setContentsMargins(0,0,0,0);
    nameHLayout->setSpacing(0);
    QLabel* nameLabel = new QLabel(nameWidget);
    nameLabel->setFixedHeight(30);
    nameLabel->setStyleSheet(".QLabel{color:rgb(255,255,255);font-size:15px;border:1px solid rgb(76,76,76); border-radius: 2px;padding: 4px 8px;}");
    nameLabel->setText(tr("录制屏幕"));
    nameHLayout->addStretch(10);
    nameHLayout->addWidget(nameLabel);
    nameHLayout->addStretch(10);
    //name end

    // image start
    QWidget* imageWidget = new QWidget(this);
    imageWidget->setStyleSheet(QString(".QWidget{background-color:%1;}").arg("rgb(25,27,38)"));
    QHBoxLayout *imageHLayout = new QHBoxLayout(imageWidget);
    imageHLayout->setContentsMargins(0,1,0,1);
    imageHLayout->setSpacing(0);

    imageLabel = new QLabel(imageWidget);
    imageLabel->setFixedSize(880, 500);
    imageHLayout->addStretch(10);
    imageHLayout->addWidget(imageLabel);
    imageHLayout->addStretch(10);
    // image end

    // record start
    QWidget* recordWidget = initRecordWidget();
    //record end

    // bottom start
    QWidget* bottomWidget = new QWidget(this);
    bottomWidget->setFixedHeight(40);
    QHBoxLayout* bottomHLayout = new QHBoxLayout(bottomWidget);
    bottomHLayout->setContentsMargins(0,0,0,0);
    bottomHLayout->setSpacing(0);

    QLabel* durationNameLabel = new QLabel(bottomWidget);
    durationNameLabel->setStyleSheet(".QLabel{color:rgb(255,242,252);font-size:16px;}");
    durationNameLabel->setText("REC:");

    durationLabel = new QLabel(bottomWidget);
    durationLabel->setStyleSheet(".QLabel{color:rgb(255,242,252);font-size:18px;}");
    durationLabel->setText(Utils::secondsToDurationStr(0));

    QPushButton* videoBtn = new QPushButton(bottomWidget);
    videoBtn->setStyleSheet(".QPushButton {color:rgb(255,255,255);font-size:15px;border:1px solid rgb(76,76,76); border-radius: 3px;padding: 2px;}\
                    .QPushButton:pressed {background-color: rgba(64,65,66,0.5);}\
                                       .QPushButton:hover {background-color: rgba(64,65,66,0.5);}\
                                                          .QPushButton:focus{outline: none;}");
                                                                         videoBtn->setFixedSize(100,30);
    videoBtn->setCursor(Qt::PointingHandCursor);
    videoBtn->setText(tr("录制列表"));
    connect(videoBtn, &QPushButton::clicked, this, [this]()
    {
        QDesktopServices::openUrl(QUrl::fromLocalFile(SingletonUtils::getInstance()->getRecordDir()));
    });

    bottomHLayout->addSpacing(20);
    bottomHLayout->addWidget(durationNameLabel);
    bottomHLayout->addSpacing(10);
    bottomHLayout->addWidget(durationLabel);
    bottomHLayout->addStretch(10);
    bottomHLayout->addWidget(videoBtn);
    bottomHLayout->addSpacing(60);
    // bottom end

    mainVLayout->addWidget(nameWidget);
    mainVLayout->addWidget(imageWidget);
    mainVLayout->addWidget(recordWidget);
    ComLineWidget*line = new ComLineWidget(this);
    line->setStyleSheet(QString(".ComLineWidget{background-color:%1;}").arg("rgb(25,27,38)"));
    mainVLayout->addWidget(line);

    mainVLayout->addWidget(bottomWidget);
    ComLineWidget*line2 = new ComLineWidget(this);
    line2->setStyleSheet(QString(".ComLineWidget{background-color:%1;}").arg("rgb(25,27,38)"));
    mainVLayout->addWidget(line2);

    mainVLayout->addStretch(10);
}

QWidget *RecordWidget::initRecordWidget()
{
    QWidget* widget = new QWidget(this);
    widget->setFixedHeight(80);
    QHBoxLayout* widgetHLayout = new QHBoxLayout(widget);
    widgetHLayout->setContentsMargins(0,0,0,0);
    widgetHLayout->setSpacing(0);

    QWidget* recordSourceWidget = initRecordSourceWidget();

    startBtn = new QPushButton(widget);
    startBtn->setFixedSize(120,40);
    startBtn->setCursor(Qt::PointingHandCursor);
    startBtn->setText(tr("开始"));
    pauseBtn = new QPushButton(widget);
    pauseBtn->setFixedSize(120,40);
    pauseBtn->setCursor(Qt::PointingHandCursor);
    pauseBtn->setText(tr("暂停"));
    stopBtn = new QPushButton(widget);
    stopBtn->setFixedSize(120,40);
    stopBtn->setCursor(Qt::PointingHandCursor);
    stopBtn->setText(tr("停止"));
    connect(startBtn,&QPushButton::clicked, this, &RecordWidget::onStartBtn);
    connect(stopBtn,&QPushButton::clicked, this, &RecordWidget::onStopBtn);
    pauseBtn->hide();
    stopBtn->hide();

    widgetHLayout->addWidget(recordSourceWidget);
    widgetHLayout->addWidget(pauseBtn);
    widgetHLayout->addSpacing(10);
    widgetHLayout->addWidget(startBtn);
    widgetHLayout->addSpacing(10);
    widgetHLayout->addWidget(stopBtn);
    widgetHLayout->addSpacing(40);

    return widget;
}

QWidget *RecordWidget::initRecordSourceWidget()
{
    // mMediaDevices = new QMediaDevices(this);

    return nullptr;
}

void RecordWidget::onStartBtn(bool checked)
{

}

void RecordWidget::onStopBtn(bool checked)
{

}

void RecordWidget::onSetImage(QImage image)
{

}
