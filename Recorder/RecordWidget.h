#ifndef RECORDWIDGET_H
#define RECORDWIDGET_H

#include <QWidget>

QT_BEGIN_NAMESPACE
class QLabel;
class QPushButton;
class QTimer;
QT_END_NAMESPACE

class RecordWidget : public QWidget
{
    Q_OBJECT
public:
    explicit RecordWidget(QWidget* parent = nullptr);
    ~RecordWidget();

private:
    void initUI();

    QWidget* initRecordWidget();
    QWidget* initRecordSourceWidget();

private:
    QLabel* imageLabel; // 渲染录屏画面

    QPushButton* startBtn;
    QPushButton* stopBtn;
    QPushButton* pauseBtn;

    QLabel* durationLabel;
    QTimer* durationTimer;

private:

public slots:
    void onStartBtn(bool checked);
    void onStopBtn(bool checked);
    void onSetImage(QImage image);
};

#endif // RECORDWIDGET_H
