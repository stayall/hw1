#include "VertexBuffer.h"






void VertexBuffer::bind(Graphics& ghs)
{
   
    UINT Offsets = 0u;
    GetContext(ghs)->IASetVertexBuffers(0u, 1u, pBuffer.GetAddressOf(), &stride, &Offsets);
}

void VertexBuffer2::bind(Graphics& ghs)
{
}
