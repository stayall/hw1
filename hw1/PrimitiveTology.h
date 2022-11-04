#pragma once
#include "Bindable.h"
class PrimitiveTology : public Bindable
{
public:
	PrimitiveTology(Graphics& ghs, const D3D11_PRIMITIVE_TOPOLOGY pt);
	virtual void bind(Graphics& ghs) override;
	virtual ~PrimitiveTology() = default;
private:
	D3D11_PRIMITIVE_TOPOLOGY pt;
};

