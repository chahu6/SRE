#ifndef RECORDWIDGET_H
#define RECORDWIDGET_H

#include <QWidget>
#include <QDateTime>

QT_BEGIN_NAMESPACE
class QLabel;
class QPushButton;
class QTimer;
QT_END_NAMESPACE

class CaptureVideoDevice;
class CaptureAudioDevice;
class Recorder;

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
    QVector<CaptureVideoDevice*> mVideoDevices;
    int mSelectedVideoIndex = 0;

    QVector<CaptureAudioDevice*> mAudioDevices;
    int mSelectedAudioIndex = 0;

private:
    Recorder* mRecorder;
    bool mIsRecord; // 是否在录制中
    QDateTime mRecordStartDate; //开始录制时间

public slots:
    void onStartBtn(bool checked);
    void onStopBtn(bool checked);
    void onSetImage(QImage image);
};

#endif // RECORDWIDGET_H
