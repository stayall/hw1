#include "VertexBuffer.h"






VertexBuffer::VertexBuffer(Graphics& phs, const Proc::VertexBuferr& buffer)
    : stride(buffer.getLayout().Size())
{
    D3D11_BUFFER_DESC bd = {};
    bd.ByteWidth = buffer.getByteSize();
    bd.Usage = D3D11_USAGE_DEFAULT;
    bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
    bd.CPUAccessFlags = 0;
    bd.MiscFlags = 0;
    bd.StructureByteStride = stride;

    D3D11_SUBRESOURCE_DATA sd = {};
    sd.pSysMem = buffer.getData();
    THROW_IF_FILUIED(GetDevice(phs)->CreateBuffer(&bd, &sd, &pBuffer));
}

void VertexBuffer::bind(Graphics& ghs)
{
   
    UINT Offsets = 0u;
    GetContext(ghs)->IASetVertexBuffers(0u, 1u, pBuffer.GetAddressOf(), &stride, &Offsets);
}

void VertexBuffer2::bind(Graphics& ghs)
{
}
