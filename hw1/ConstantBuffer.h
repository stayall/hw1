#pragma once
#include "Bindable.h"
#include "Window.h"

template<class T>
class ConstantBuffer : public Bindable
{
public:
	void update(Graphics& ghs, const T& consts);
	ConstantBuffer(Graphics& ghs, const T& consts) ;
	ConstantBuffer(Graphics& ghs) ;
protected:
	Microsoft::WRL::ComPtr<ID3D11Buffer> cbf;
};

template<class T>
class VertexConstantsBuffer : public ConstantBuffer<T>
{
	using Bindable::GetContext;
	using ConstantBuffer<T>::cbf;
	
public:
	using ConstantBuffer<T>::ConstantBuffer;
	virtual void bind(Graphics& ghs) override;
};

template<class T>
class PixelConstantsBuffer : public ConstantBuffer<T>
{
	using Bindable::GetContext;
	using ConstantBuffer<T>::cbf;
public:
	using ConstantBuffer<T>::ConstantBuffer;
	virtual void bind(Graphics& ghs) override;
};


template<class T>
void ConstantBuffer<T>::update(Graphics& ghs, const T& consts)
{
    D3D11_MAPPED_SUBRESOURCE ms;
    THROW_IF_FILUIED(GetContext(ghs)->Map(cbf.Get(), 0u, D3D11_MAP_WRITE_DISCARD, 0, &ms));
    memcpy(ms.pData, &consts, sizeof(consts));
    GetContext(ghs)->Unmap(cbf.Get(), 0u);
}

template<class T>
ConstantBuffer<T>::ConstantBuffer(Graphics& ghs, const T& consts)
{
    D3D11_BUFFER_DESC cbd = {};
    cbd.ByteWidth = sizeof(consts);
    cbd.Usage = D3D11_USAGE_DYNAMIC;
    cbd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
    cbd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
    cbd.MiscFlags = 0;
    
    D3D11_SUBRESOURCE_DATA csd = {};
    csd.pSysMem = &consts;

    THROW_IF_FILUIED(GetDevice(ghs)->CreateBuffer(&cbd, &csd, &cbf));
}

template<class T>
ConstantBuffer<T>::ConstantBuffer(Graphics& ghs)
{
    D3D11_BUFFER_DESC cbd = {};
    cbd.ByteWidth = sizeof(T);
    cbd.Usage = D3D11_USAGE_DYNAMIC;
    cbd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
    cbd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
    cbd.MiscFlags = 0;
    cbd.StructureByteStride = 0;
    D3D11_SUBRESOURCE_DATA csd = {};
    csd.pSysMem = nullptr;


    THROW_IF_FILUIED(GetDevice(ghs)->CreateBuffer(&cbd, nullptr , &cbf));
}

template<class T>
void VertexConstantsBuffer<T>::bind(Graphics& ghs)
{
    GetContext(ghs)->VSSetConstantBuffers(0u, 1u, cbf.GetAddressOf());
}

template<class T>
void PixelConstantsBuffer<T>::bind(Graphics& ghs)
{
    GetContext(ghs)->PSSetConstantBuffers(0u, 1u, cbf.GetAddressOf());
}