#include "InputLayout.h"
#include "Window.h"

InputLayout::InputLayout(Graphics& ghs, const std::vector<D3D11_INPUT_ELEMENT_DESC>& ed, ID3DBlob* pvs)
{
	THROW_IF_FILUIED(GetDevice(ghs)->CreateInputLayout(&ed.at(0), std::size(ed), pvs->GetBufferPointer(), pvs->GetBufferSize(), &layout));
	
}

void InputLayout::bind(Graphics& ghs)
{
	GetContext(ghs)->IASetInputLayout(layout.Get());
}
