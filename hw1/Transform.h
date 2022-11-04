#pragma once
#include "Bindable.h"
#include "Drawable.h"
#include "ConstantBuffer.h"
class Transform : public Bindable
{
public:

	Transform(Graphics& ghs, Drawable& p, UINT slot = 0u);
	virtual void bind(Graphics& ghs) override;
private:
	struct Trans
	{
		DirectX::XMMATRIX modelview;
		DirectX::XMMATRIX mvp;
	};
	const Drawable& parent;
	VertexConstantsBuffer<Trans> vcb;
	UINT slot;
};

