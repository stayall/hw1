#pragma once

#include "Graphics.h"

class Bindable
{
public:
	virtual void bind(Graphics& ghs) = 0;
	virtual ~Bindable() = default;
protected:
	static ID3D11Device* GetDevice(Graphics &ghs) noexcept;
	static ID3D11DeviceContext* GetContext(Graphics& ghs) noexcept;
};

