#ifndef PREVIEWPLAYER_H
#define PREVIEWPLAYER_H

#include <QWidget>

QT_BEGIN_NAMESPACE
class QVBoxLayout;
class QLabel;
QT_END_NAMESPACE

class PreviewPlayer : public QWidget
{
    Q_OBJECT
public:
    explicit PreviewPlayer(QWidget *parent);

private:
    void initUI();
    QWidget* initNameWidget();
    QWidget* initImageWidget();

private:
    QVBoxLayout *mainVLayout;
    QLabel *imageLabel;

signals:
    void setImage(QImage image);

public slots:
    void onSetImage(QImage image);
};

#endif // PREVIEWPLAYER_H
