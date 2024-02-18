#ifndef FFMPEGENCODER_H
#define FFMPEGENCODER_H

#include <QObject>

extern "C"
{
    #include <libavcodec/avcodec.h>
    #include <libavformat/avformat.h>
    #include <libavfilter/buffersink.h>
    #include <libavfilter/buffersrc.h>
    #include <libavutil/opt.h>
    #include <libavutil/pixdesc.h>
    #include <libavutil/imgutils.h>
    #include <libswscale/swscale.h>
}

#include <thread>
#include <QMutex>
#include <QQueue>

class Frame;
class PreviewPlayer;

class FFmpegEncoder : public QObject
{
    Q_OBJECT
public:
    FFmpegEncoder(QObject *parent, PreviewPlayer* previewPlayer);
    ~FFmpegEncoder();

public:
    int start();
    int pause();
    int stop();

private:
    static void run_thread(void* arg);

public:
    int init(const char* codec_name, int width, int height, int fps, int bitrate, const char* url);
    void encode(Frame* frame);

private:
    PreviewPlayer* mPreviewPlayer;
    bool bIsRecording = false;
    bool bIsStop = true;
    std::thread* mThread;

    int mFps;

    AVFormatContext* oFmtCtx = nullptr;
    AVCodecContext* oVideoCodecCtx = nullptr;
    AVStream* oVideoStream = nullptr;
    SwsContext* swsCtx_bgra2yuv420p = nullptr;
    AVFrame* oFrame_yuv420p;

    QQueue<Frame*> mVideoFrameQ;
    QMutex         mVideoFrameQ_mtx;

signals:

public slots:
};

#endif // FFMPEGENCODER_H
