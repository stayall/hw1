#pragma once
#include "Bindable.h"
class PixelShader : public Bindable
{

public:
	PixelShader(Graphics& ghs, const wchar_t *pathname);
	virtual void bind(Graphics& ghs) override;
private:
	Microsoft::WRL::ComPtr<ID3D11PixelShader> ps;

	
};

