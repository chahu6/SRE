#include "FFmpegEncoder.h"
#include <QDebug>

FFmpegEncoder::FFmpegEncoder(QObject *parent, PreviewPlayer *previewPlayer)
    : QObject(parent), mPreviewPlayer(previewPlayer)
{
    qDebug() << "FFmpegEncoder::FFmpegEncoder()";
    unsigned version = avcodec_version();
    qDebug()<<"FFmpeg version: "<<version;

}

FFmpegEncoder::~FFmpegEncoder()
{
    qDebug() << "FFmpegEncoder::~FFmpegEncoder()";
    if(oVideoCodecCtx)
    {
        avcodec_close(oVideoCodecCtx);
        avcodec_free_context(&oVideoCodecCtx);
    }

    if(oFrame_yuv420p)
    {
        av_freep(&oFrame_yuv420p->data[0]);
        av_frame_free(&oFrame_yuv420p);
    }

    if(oFmtCtx)
    {
        if(oFmtCtx && !(oFmtCtx->oformat->flags & AVFMT_NOFILE))
        {
            avio_close(oFmtCtx->pb);
        }

        avformat_free_context(oFmtCtx);
    }
}

int FFmpegEncoder::start()
{

}

int FFmpegEncoder::pause()
{

}

int FFmpegEncoder::stop()
{

}

void FFmpegEncoder::run_thread(void *arg)
{

}

int FFmpegEncoder::init(const char *codec_name, int width, int height, int fps, int bitrate, const char *url)
{

}

void FFmpegEncoder::encode(Frame *frame)
{

}
