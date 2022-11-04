#pragma once
#include "Bindable.h"
#include <vector>
class InputLayout : public Bindable
{
public:
	InputLayout(Graphics& ghs, const std::vector<D3D11_INPUT_ELEMENT_DESC>& ed, ID3DBlob* pvs);
	virtual void bind(Graphics& ghs) override;
private:
	Microsoft::WRL::ComPtr<ID3D11InputLayout> layout;
};

