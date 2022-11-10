#pragma once
#include "Drawable.h"
class line : public Drawable
{
public:
	line(Graphics& ghs);
	virtual DirectX::XMMATRIX getMatrix() const noexcept override;
	virtual void update(float dt) noexcept override;
};

