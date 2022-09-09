#include "VertexShader.h"
#include <d3dcompiler.h>
#include "Window.h"

namespace wrl = Microsoft::WRL;

VertexShader::VertexShader(Graphics& ghs, const wchar_t* pathname)
{
  

    wrl::ComPtr<ID3D11VertexShader> vs;
    D3DReadFileToBlob(pathname, &blob);

    THROW_IF_FILUIED(GetDevice(ghs)->CreateVertexShader(blob->GetBufferPointer(), blob->GetBufferSize(), nullptr, &vs));
    
}

void VertexShader::bind(Graphics& ghs)
{
   GetContext(ghs)->VSSetShader(vs.Get(), nullptr, 0);
}

ID3D10Blob* VertexShader::getByteCode() noexcept
{
    return blob.Get();
}
