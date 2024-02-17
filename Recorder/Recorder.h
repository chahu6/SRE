#ifndef RECORDER_H
#define RECORDER_H

#include <QObject>

class AcqFFmpeg;
class AcqScreen;
class FFmpegEncoder;
class PreviewPlayer;

class Recorder : public QObject
{
    Q_OBJECT
public:
    explicit Recorder(QObject *parent, PreviewPlayer* previewPlayer);
    ~Recorder();

public:
    int start();
    int pause();
    int stop();

private:
    PreviewPlayer* mPreviewPlayer;
    bool bIsRecording = false;

    FFmpegEncoder* mEncoder = nullptr;
    AcqScreen*      mAcqScreen = nullptr;
    AcqFFmpeg*      mAcqMicrophone = nullptr;

signals:

public slots:
};

#endif // RECORDER_H
