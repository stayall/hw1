#pragma once
#include "Bindable.h"
#include "Drawable.h"
#include "ConstantBuffer.h"
class Transform : public Bindable
{
public:

	Transform(Graphics& ghs, Drawable& p);
	virtual void bind(Graphics& ghs) override;
private:
	const Drawable& parent;
	VertexConstantsBuffer<DirectX::FXMMATRIX> vcb;
};

