#ifndef DUPLICATION_H
#define DUPLICATION_H

#include <windows.h>
#include <d3d11.h>
#include <dxgi1_2.h>
#include <cstdint>

class Duplication
{
public:
    Duplication();
    ~Duplication();
    bool GetFrame(int timeout = 100);
    bool copyFrameDataToBuffer(uint8_t* buffer, int bufferSize, int& width, int& height);
    bool DoneWithFrame();
    bool InitDevice();
    bool InitDupl(UINT Output);

private:
    IDXGIOutputDuplication* m_DeskDupl;
    ID3D11Texture2D* m_AcquiredDesktopImage;
    UINT m_OutputNumber;
    DXGI_OUTPUT_DESC m_OutputDesc;
    ID3D11Device* m_Device;
};

#endif // DUPLICATION_H
