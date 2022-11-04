#include "IndexBuffer.h"
#include "Window.h"

//namespace wrl = Microsoft::WRL;

IndexBuffer::IndexBuffer(Graphics& ghs, const std::vector<unsigned short>& idx)
    : count(idx.size())
{
    
    D3D11_BUFFER_DESC bd = {};
    bd.ByteWidth = count * sizeof(unsigned short);
    bd.Usage = D3D11_USAGE_DEFAULT;
    bd.BindFlags = D3D11_BIND_INDEX_BUFFER;
    bd.CPUAccessFlags = 0;
    bd.MiscFlags = 0;
    bd.StructureByteStride = sizeof(unsigned short);

    D3D11_SUBRESOURCE_DATA sd = {};
    sd.pSysMem = idx.data();
    THROW_IF_FILUIED(GetDevice(ghs)->CreateBuffer(&bd, &sd, &pIndexBuffer));
}

void IndexBuffer::bind(Graphics& ghs)
{
    GetContext(ghs)->IASetIndexBuffer(pIndexBuffer.Get(), DXGI_FORMAT_R16_UINT, 0u);
}

size_t IndexBuffer::getCount() const noexcept
{
    return count;
}
