#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDateTime>

class QVBoxLayout;
class QPushButton;
class QLabel;
class Recorder;
class PreviewPlayer;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    void initMenu();
    void initUI();

    QVBoxLayout* mainVLayout;

    QPushButton* startBtn;
    QPushButton* stopBtn;
    QPushButton* pauseBtn;

    QLabel* durationLabel;
    QTimer* durationTimer;

    QWidget* initSourceWidget();

private:
    PreviewPlayer* mPreviewPlayer;
    Recorder* mRecorder;

    bool bIsRecording;  // 是否在录制中
    QDateTime recordStartDate;  // 开始录制时间
};

#endif // MAINWINDOW_H
