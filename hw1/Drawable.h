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
	void drawCall(Graphics &ghs) const noexcept;
	virtual DirectX::XMMATRIX getMatrix() const noexcept = 0;
	virtual void update(float dt) noexcept {};
	virtual ~Drawable() = default;
protected:

	void addBind(std::unique_ptr<Bindable> pb) noexcept;
	void addIndexBind(std::unique_ptr< IndexBuffer> pb) noexcept;

	template<typename T>
	T* getBindable() const noexcept;

	template<typename T>
	T* getShareBindable() const noexcept;
	
private:
	virtual size_t getShareCount()const noexcept = 0;
	virtual const std::vector<std::unique_ptr<Bindable>>& getShareBinds() const noexcept = 0;
private:

	const IndexBuffer* pIndexBuffer = nullptr;
	std::vector<std::unique_ptr<Bindable>> binds;
};

template<typename T>
inline T* Drawable::getBindable() const noexcept
{
	for (auto& b : binds)
	{
		if (T* p = dynamic_cast<T *>(b.get()))
		{
			return p;
		}
	}
	return nullptr;
}

template<typename T>
inline T* Drawable::getShareBindable() const noexcept
{
	for (auto& b : getShareBindable())
	{
		if (T* p = dynamic_cast<T>(b.get()))
		{
			return p;
		}
	}

	return nullptr;
}
