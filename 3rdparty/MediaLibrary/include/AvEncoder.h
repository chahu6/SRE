#ifndef BXC_AVENCODER_H
#define BXC_AVENCODER_H
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
    #error AvEncoder only supports Windows!
#endif

#include "AvFrame.h"

namespace UMediaLibrary
{
#ifdef __cplusplus
extern "C"{
#endif

    int __DECLSPEC_INC AvEncoder_Open(AvEncoder* encoder, const char* url);

    int __DECLSPEC_INC AvEncoder_Close(AvEncoder* encoder);

    int64_t __DECLSPEC_INC gettime();

    int __DECLSPEC_INC send_frame(AvEncoder* encoder, FFrame* frame);

    int __DECLSPEC_INC recive_packet(AvEncoder* encoder, FPacket* packet);

#ifdef __cplusplus
}
#endif
} // namespace UMediaLibrary


#endif