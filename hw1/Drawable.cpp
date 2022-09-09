#include "Drawable.h"

void Drawable::drawCall(Graphics& ghs) noexcept
{
	for (auto& b : binds)
	{
		b->bind(ghs);
	}

	ghs.drawIndex(pIndexBuffer->getCount());
}

void Drawable::addBind(std::unique_ptr<Bindable> pb) noexcept
{
	binds.push_back(std::move(pb));
}

void Drawable::addIndexBind(std::unique_ptr<IndexBuffer> pb) noexcept
{
	pIndexBuffer = pb.get();
	binds.push_back(std::move(pb));
}
