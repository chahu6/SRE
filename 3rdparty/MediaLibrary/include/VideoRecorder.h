#ifndef VIDEORECORDER_H
#define VIDEORECORDER_H

#include <cstdint>

#ifdef _WIN32
    #if defined(DYNAMIC_LINK) 
        #ifdef MEDIALIBRARY_EXPORTS
			#define __DECLSPEC_INC __declspec(dllexport)
		#else
			#define __DECLSPEC_INC __declspec(dllimport)
		#endif // XW_BUILD_DLL
    #else
        #define __DECLSPEC_INC
    #endif
#else
    #error VideoRecorder only supports Windows!
#endif

namespace UMediaLibrary
{
#ifdef __cplusplus
extern "C"{
#endif

    enum EPixelFormat
    {
        PIXEL_None = 20,
        PIXEL_BGRA,
        PIXEL_RGB,
    };

    struct VideoRecorder
    {
    public:
        VideoRecorder() = delete;
        VideoRecorder(const char* capture, int width, int height, int idx)
        {
            this->capture = capture;
            this->width = width;
            this->height = height;
            this->idx = idx;
        } 

        ~VideoRecorder() = default;
        
    public:
        int id = -1;
        const char* capture;
        int width;
        int height;
        int idx;

        EPixelFormat pixelFormat;
        int factWidth;
        int factHeight;
    };
    
    int __DECLSPEC_INC VideoRecorder_Open(VideoRecorder* recorder);

    int __DECLSPEC_INC VideoRecorder_Close(VideoRecorder* recorder);

    int __DECLSPEC_INC get_frame(VideoRecorder* recorder, unsigned char*& buffer, int& size, int64_t& timestamp);

#ifdef __cplusplus
}
#endif

} // namespace FMediaLibrary


#endif
