#include "Settings.h"
#include <QVBoxLayout>
#include <QPushButton>
#include "ComLineWidget.h"
#include "style.h"

Settings::Settings(QWidget *parent)
    :QDialog(parent)
{
    setWindowFlags(Qt::Dialog | Qt::WindowCloseButtonHint);
    setAttribute(Qt::WA_StyledBackground, true);
    setWindowTitle(tr("设置"));
    setFixedSize(660, 340);

    mainVLayout = new QVBoxLayout(this);
    mainVLayout->setContentsMargins(0, 0, 0, 0);
    mainVLayout->setSpacing(0);

    mainVLayout->addStretch(10);
    mainVLayout->addWidget(new ComLineWidget(this));
    initBottomUI();
}

void Settings::initBottomUI()
{
    QWidget* bottomWidget = new QWidget(this);
    bottomWidget->setFixedHeight(50);
    QHBoxLayout* bottomHLayout = new QHBoxLayout(bottomWidget);
    bottomHLayout->setContentsMargins(0,0,0,0);
    bottomHLayout->setSpacing(0);

    QPushButton* okBtn = new QPushButton(bottomWidget);
    okBtn->setText(tr("保存"));
    okBtn->setStyleSheet(m_stylesheet_QPushButton_blue);
    okBtn->setCursor(Qt::PointingHandCursor);
    okBtn->setFixedSize(90,32);
    connect(okBtn, &QPushButton::clicked, this, []()
    {

    });

    QPushButton* cancelBtn = new QPushButton(bottomWidget);
    cancelBtn->setText(tr("取消"));
    cancelBtn->setStyleSheet(m_stylesheet_QPushButton_hollow);
    cancelBtn->setCursor(Qt::PointingHandCursor);
    cancelBtn->setFixedSize(90, 32);
    connect(cancelBtn, &QPushButton::clicked, this, [this]()
    {
        this->close();
    });

    bottomHLayout->addStretch(10);
    bottomHLayout->addWidget(okBtn);
    bottomHLayout->addSpacing(20);
    bottomHLayout->addWidget(cancelBtn);
    bottomHLayout->addSpacing(20);

    mainVLayout->addWidget(bottomWidget);
}
