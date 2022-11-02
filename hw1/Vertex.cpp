#include "Vertex.h"
#include <DirectXMath.h>
#include <algorithm>





namespace Proc
{


	size_t VertexLayout::Element::getOffset() const noexcept
	{
		return offset;
	}

	size_t VertexLayout::Element::getOffsetAffter() const
	{
		return offset + Size();

	}

	size_t VertexLayout::Element::Size() const
	{
		return SizeOf(type);
	}

	constexpr size_t VertexLayout::Element::SizeOf(ElementType Type)
	{
		switch (Type)
		{
		case VertexLayout::ElementType::VertexPosition2D:
		case VertexLayout::ElementType::Teture2D:
			return sizeof(DirectX::XMFLOAT2);

		case VertexLayout::ElementType::VertexPosition3D:
		case VertexLayout::ElementType::VertexNormal:
		case VertexLayout::ElementType::VertexColor3D:
			return sizeof(DirectX::XMFLOAT3);

		case VertexLayout::ElementType::VertexColor4D:
			return sizeof(DirectX::XMFLOAT4);

		case VertexLayout::ElementType::VertexRGBColor:
			return sizeof(unsigned int);

		default:
			assert("Invaild Type" && false);
			return 0u;

		}
	}

	const VertexLayout::Element& VertexLayout::resolve(ElementType type) const
	{
		for (auto& b : elment)
		{
			if (b.getElmentType() == type)
			{
				return b;
			}
		}

		assert("Cant reslove the type" && false);

		return elment.front();

	}

	const VertexLayout::Element& VertexLayout::resolveIndex(size_t i) const
	{
		assert("Elemnt Index Out The Range" && i <= elment.size());

		return elment[i];
	}

	size_t VertexLayout::Size() const
	{
		return elment.empty() ? 0u : elment.back().getOffsetAffter();
	}

	void VertexLayout::append(ElementType type)
	{
		elment.emplace_back(type, Size());
	}

	size_t VertexBuferr::Size() const
	{
		return buffer.size() / layout.Size();
	}

	Vertex VertexBuferr::Front()
	{
		assert(buffer.size() > 0u);

		return Vertex{ buffer.data(), layout };
	}

	Vertex VertexBuferr::Back()
	{
		assert(buffer.size() > 0u);

		return Vertex{ buffer.data() + buffer.size() - layout.Size(), layout };
	}

	Vertex VertexBuferr::operator[](size_t index)
	{
		return Vertex{ buffer.data() + layout.Size() * index, layout };
	}

}