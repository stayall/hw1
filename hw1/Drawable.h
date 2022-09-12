#pragma once

#include "Graphics.h"
#include "IndexBuffer.h"
#include "Bindable.h"

#include <DirectXMath.h>
#include <vector>
#include <memory>
//class Bindable;

class Drawable
{
public:
	Drawable() = default;
	Drawable(const Drawable&) = delete;
	void drawCall(Graphics &ghs) noexcept;
	virtual DirectX::XMMATRIX getMatrix() const noexcept = 0;
	virtual void update(float dt) noexcept = 0;
	
protected:

	void addBind(std::unique_ptr<Bindable> pb) noexcept;
	void addIndexBind(std::unique_ptr<IndexBuffer> pb) noexcept;
	virtual ~Drawable() = default;
private:
	virtual size_t getShareCount()const noexcept = 0;
	virtual const std::vector<std::unique_ptr<Bindable>>& getShareBinds() const noexcept = 0;
private:

	const IndexBuffer* pIndexBuffer = nullptr;
	std::vector<std::unique_ptr<Bindable>> binds;
};

