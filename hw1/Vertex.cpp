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

	D3D11_INPUT_ELEMENT_DESC VertexLayout::Element::getElemntDesc() const
	{
		switch (type)
		{
#define ED(T) \
		case T:\
			return getED<T>(getOffset());

			ED(ElementType::VertexPosition2D);
			ED(ElementType::VertexPosition3D);
			ED(ElementType::VertexNormal);
			ED(ElementType::Teture2D);
			ED(ElementType::VertexColor3D);
			ED(ElementType::VertexColor4D);
			ED(ElementType::VertexRGBColor);
#undef ED
		default:

			assert("No Macth Type" && false);
			return D3D11_INPUT_ELEMENT_DESC{"Invaild"};
	
		}
		
	}

	

	size_t VertexLayout::Element::Size() const
	{
		return SizeOf(type);
	}


	constexpr size_t VertexLayout::Element::SizeOf(ElementType Type)
	{

		switch (Type)
		{
#define DATASIZE(T)\
		case T:\
			return sizeof(typename dataMap<T>::sys)
		

			DATASIZE(ElementType::VertexPosition2D);
			DATASIZE(ElementType::VertexPosition3D);
			DATASIZE(ElementType::VertexNormal);
			DATASIZE(ElementType::Teture2D);
			DATASIZE(ElementType::VertexColor3D);
			DATASIZE(ElementType::VertexColor4D);
			DATASIZE(ElementType::VertexRGBColor);

#undef DATASIZE
		default:
			assert("Invaild Type" && false);
			return 0u;

		}
	}

	

	std::vector<D3D11_INPUT_ELEMENT_DESC> VertexLayout::get3DLayOut() const
	{
		std::vector<D3D11_INPUT_ELEMENT_DESC> ed;
		for (const auto& b : elment)
		{
			auto e = b.getElmentType();
			ed.emplace_back(b.getElemntDesc());
		}
		return std::move(ed);
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

	size_t VertexLayout::getElemntCount() const
	{
		return elment.size();
	}

	

	VertexLayout VertexBuferr::getLayout()
	{
		return layout;
	}

	

	size_t VertexBuferr::Size() const
	{
		return buffer.size() / layout.Size();
	}

	size_t VertexBuferr::getByteSize() const
	{
		return buffer.size();
	}

	char* VertexBuferr::getData() const
	{
		return const_cast<std::vector<char>&>(buffer).data();
	}

	ConsVertex VertexBuferr::Front() const
	{
		return  const_cast<VertexBuferr *>(this)->Front();
	}

	ConsVertex VertexBuferr::Back() const
	{
		return const_cast<VertexBuferr *>(this)->Back();
	}

	const VertexLayout VertexBuferr::getLayout() const
	{
		
		return const_cast<VertexBuferr *>(this)->getLayout();
	}

	ConsVertex VertexBuferr::operator[](size_t index) const
	{
		return const_cast<VertexBuferr&>(*this)[index];
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