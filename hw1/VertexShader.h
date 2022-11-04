#pragma once
#include "Bindable.h"
class VertexShader : public Bindable
{
public:
	VertexShader(Graphics& ghs, const wchar_t* pathname);
	virtual void bind(Graphics& ghs) override;
	ID3D10Blob* getByteCode() noexcept;

private:
	Microsoft::WRL::ComPtr<ID3D11VertexShader> vs;
	Microsoft::WRL::ComPtr<ID3D10Blob> blob;
	
};

