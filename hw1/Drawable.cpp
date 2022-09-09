#include "Drawable.h"

void Drawable::addBind(std::unique_ptr<Bindable> pb) noexcept
{
	binds.push_back(std::move(pb));
}

void Drawable::addIndexBind(std::unique_ptr<IndexBuffer> pb) noexcept
{
	pIndexBuffer = pb.get();
	binds.push_back(std::move(pb));
}
