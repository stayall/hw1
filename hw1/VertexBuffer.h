#pragma once
#include "Bindable.h"
#include "Window.h"

class VertexBuffer : public Bindable
{
public:
	template<class V>
	VertexBuffer(Graphics&phs, const std::vector<V> &vertex);
	virtual void bind(Graphics& ghs)  override;

private:
	size_t stride;
	Microsoft::WRL::ComPtr<ID3D11Buffer> pBuffer;
};

template<class T>
VertexBuffer::VertexBuffer(Graphics& phs, const std::vector<T>& vertex)
    : stride(sizeof(T))
{
    D3D11_BUFFER_DESC bd = {};
    bd.ByteWidth = vertex.size() * sizeof(T);
    bd.Usage = D3D11_USAGE_DEFAULT;
    bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
    bd.CPUAccessFlags = 0;
    bd.MiscFlags = 0;
    bd.StructureByteStride = sizeof(T);

    D3D11_SUBRESOURCE_DATA sd = {};
    sd.pSysMem = vertex.data();
    THROW_IF_FILUIED(GetDevice(phs)->CreateBuffer(&bd, &sd, &pBuffer));
    
    //Fiexd: set maroc to check error ;
}

class VertexBuffer2 : Bindable
{
public:
    // Í¨¹ý Bindable ¼Ì³Ð
    VertexBuffer2() = default;
    virtual void bind(Graphics& ghs) override;
};