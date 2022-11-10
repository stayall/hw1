#include "PixelShader.h"
#include <d3dcompiler.h>
#include "Window.h"

namespace wrl = Microsoft::WRL;

PixelShader::PixelShader(Graphics& ghs, const wchar_t* pathname)
{
    wrl::ComPtr<ID3DBlob> blob;
    THROW_IF_FILUIED(D3DReadFileToBlob(pathname, &blob));
    THROW_IF_FILUIED(GetDevice(ghs)->CreatePixelShader(blob->GetBufferPointer(), blob->GetBufferSize(), nullptr, &ps));
    
}

void PixelShader::bind(Graphics& ghs)
{
    GetContext(ghs)->PSSetShader(ps.Get(), nullptr, 0u);
}
