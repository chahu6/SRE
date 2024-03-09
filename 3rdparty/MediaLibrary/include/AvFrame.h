#ifndef AVFRAME_H
#define AVFRAME_H

#include <cstdint>
#include <memory>

namespace UMediaLibrary
{

#ifdef __cplusplus
extern "C"{
#endif

    enum AvType
    {
        AV_None = 20,
        AV_Video,
        AV_Audio,
    };
    
    struct FFrame
    {
    public:
        FFrame() = delete;
        FFrame(AvType type, int size)
        {
            this->type = type;
            this->size = size;
            this->data = (uint8_t*)malloc(this->size);
        }

        FFrame(AvType type, int size, int64_t timestamp, int64_t count)
        {
            this->type = type;
            this->size = size;
            this->timestamp = timestamp;
            this->count = count;
            this->data = (uint8_t*)malloc(this->size);
        }

        ~FFrame()
        {
            if(this->data)
            {
                free(data);
                this->data = nullptr;
            }
        }

    public:
        AvType type;
        int size;
        int64_t timestamp;
        int64_t count;
        uint8_t* data;
    };

    struct FPacket
    {
    public:
        FPacket() = delete;
        FPacket(AvType type, int size)
        {
            this->type = type;
            this->size = size;
            this->data = (uint8_t*)malloc(this->size);
        }

        FPacket(AvType type, int size, int64_t stream_index , int64_t pts, int64_t dts, int64_t duration, int64_t pos,
            int64_t timestamp, int64_t count)
        {
            this->type = type;
            this->size = size;
            this->stream_index = stream_index;
            this->pts = pts;
            this->dts = dts;
            this->duration = duration;
            this->pos = pos;

            this->timestamp = timestamp;
            this->count = count;

            this->data = (uint8_t*)malloc(this->size);
        }

    public:
        AvType type;
        int size;
        int64_t stream_index;
        int64_t pts;
        int64_t dts;
        int64_t duration;
        int64_t pos;

        int64_t timestamp;
        int64_t count;

        uint8_t* data;
    };
    
    struct AvEncoder
    {
    public:
        AvEncoder() = delete;
        AvEncoder(bool hasVideo, const char* videoCodecName, int videoBitrate, int pixelFormat, int width, int height, int fps,
            bool hasAudio, const char* audioCodecName, int audioBitrate)
        {
            this->hasVideo = hasVideo;
            this->videoCodecName = videoCodecName;
            this->videoBitrate = videoBitrate;
            this->pixelFormat = pixelFormat;
            this->width = width;
            this->height = height;
            this->fps = fps;

            this->hasAudio = hasAudio;
            this->audioCodecName = audioCodecName;
            this->audioBitrate = audioBitrate;
        }

        ~AvEncoder()
        {
        }

    public:
        int id = -1;

        bool hasVideo = false;//是否编码视频流
        const char* videoCodecName = nullptr;//视频编码名称
        int width = 0;//视频宽
        int height = 0;//视频高
        int fps = 0;// 视频编码帧率
        int pixelFormat;//视频帧像素格式（BXC_PixelFormat）
        int videoBitrate = 0;//视频编码码率

        bool hasAudio = false;//是否编码音频流
        const char* audioCodecName = nullptr;//音频编码名称
        int audioBitrate = 0;//音频编码码率
    };
    
#ifdef __cplusplus
}
#endif

} // namespace UMediaLibrary

#endif