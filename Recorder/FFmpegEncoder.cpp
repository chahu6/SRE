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
    mFps = fps;

    int ret;
    const AVCodec* videoCodec = avcodec_find_encoder_by_name(codec_name);

    if(!videoCodec)
    {
        qDebug()<<"avcodec_find_encoder_by_name error";
        return -1;
    }

    oVideoCodecCtx = avcodec_alloc_context3(videoCodec);
    if(!oVideoCodecCtx)
    {
        qDebug()<<"avcodec_alloc_context3 error";
        return -1;
    }

    // CBR: 固定比特率
//    oVideoCodecCtx->flags |= AV_CODEC_FLAG_QSCALE;
//    oVideoCodecCtx->bit_rate = bitrate;
//    oVideoCodecCtx->rc_min_rate = bitrate;
//    oVideoCodecCtx->rc_max_rate = bitrate;
//    oVideoCodecCtx->bit_rate_tolerance = bitrate;

    // VBR: 可变码率
    oVideoCodecCtx->flags |= AV_CODEC_FLAG_QSCALE;
    oVideoCodecCtx->rc_min_rate = bitrate / 2;
    oVideoCodecCtx->rc_max_rate = bitrate / 2 + bitrate;
    oVideoCodecCtx->bit_rate = bitrate;

    // ABR: 平均码率
//    oVideoCodecCtx->bit_rate = bitrate;

//    oVideoCodecCtx->pix_fmt = AV_PIX_FMT_NV12;

    oVideoCodecCtx->flags |= AV_CODEC_FLAG_QSCALE;
    oVideoCodecCtx->pix_fmt = AV_PIX_FMT_YUV420P;
    oVideoCodecCtx->codec_type = AVMEDIA_TYPE_VIDEO;
    oVideoCodecCtx->time_base = {1, fps};
    oVideoCodecCtx->framerate = {fps, 1};
    oVideoCodecCtx->width = width;
    oVideoCodecCtx->height = height;
//    oVideoCodecCtx->keyint_min = fps;
//    oVideoCodecCtx->thread_count = 3;
//    oVideoCodecCtx->max_b_frames = 5;

    if(oVideoCodecCtx->codec_id == AV_CODEC_ID_H264)
    {
        av_opt_set(oVideoCodecCtx->priv_data, "profile", "main", 0);
        av_opt_set(oVideoCodecCtx->priv_data, "b-pyramid", "none", 0);
        av_opt_set(oVideoCodecCtx->priv_data, "preset", "superfast", 0);
        av_opt_set(oVideoCodecCtx->priv_data, "tune", "zerolatency", 0);
    }

    return 0;
}

void FFmpegEncoder::encode(Frame *frame)
{

}
