#include <vector>
#include <DirectXMath.h>
#include<type_traits>

namespace Proc
{
	struct RBGColor
	{
		unsigned char r;
		unsigned char g;
		unsigned char b;
		unsigned char a;
	};


	class VertexLayout
	{
	public:
		enum class ElementType
		{
			VertexPosition2D,
			VertexPosition3D,
			VertexNormal,
			Teture2D,
			VertexColor3D,
			VertexColor4D,
			VertexRGBColor,
			Invaild
		};
		class Element
		{
		public:
			Element(ElementType Type, size_t Offset) : type(Type), offset(Offset) {};
			size_t getOffset() const noexcept;
			ElementType getElmentType() const noexcept { return type; };
			size_t getOffsetAffter() const;

			size_t Size() const;
			static constexpr size_t SizeOf(ElementType Type);
		private:
			ElementType type;
			size_t offset;
		};

		const Element& resolve(ElementType type) const;
		const Element& resolveIndex(size_t i) const;
		size_t Size() const;
		void append(ElementType type);

	private:
		std::vector<Element> elment;

	};

	class Vertex
	{
		friend class VertexBuferr;
	public:
		Vertex(char* p, VertexLayout vl) : data(p), layout(vl) {};

		template<VertexLayout::ElementType type>
		auto& attr();

		template<typename T>
		void setAttrByIndex(size_t index, T&& val);

		template<typename Dest, typename Src>
		void setAttr(char* p, Src&& val);
	private:
		template<typename First, typename ...Reset>
		void setAttrByIndex(size_t index, First&& first, Reset &&... reset);

	private:
		char* data;
		VertexLayout layout;
	};


	class VertexBuferr
	{
	public:
		VertexBuferr(VertexLayout ly) : layout(std::move(ly)) {};

		template<typename... T>
		void emplaceBack(T &&...args);


		size_t Size() const;

		Vertex Front();
		Vertex Back();
		Vertex operator[](size_t index);
	private:
		std::vector<char> buffer;
		VertexLayout layout;
	};

	template<VertexLayout::ElementType type>
	inline auto& Vertex::attr()
	{
		const auto& e = layout.resolve(type);
		auto pAttr = data + e.getOffset();
		if constexpr (type == VertexLayout::ElementType::VertexPosition2D)
		{
			return *reinterpret_cast<DirectX::XMFLOAT2*>(pAttr);
		}
		else if constexpr (type == VertexLayout::ElementType::Teture2D)
		{
			return *reinterpret_cast<DirectX::XMFLOAT2*>(pAttr);
		}
		else if constexpr (type == VertexLayout::ElementType::VertexPosition3D)
		{
			return *reinterpret_cast<DirectX::XMFLOAT3*>(pAttr);
		}
		else if constexpr (type == VertexLayout::ElementType::VertexNormal)
		{
			return *reinterpret_cast<DirectX::XMFLOAT3*>(pAttr);
		}
		else if constexpr (type == VertexLayout::ElementType::VertexColor3D)
		{
			return *reinterpret_cast<DirectX::XMFLOAT3*>(pAttr);
		}
		else if constexpr (type == VertexLayout::ElementType::VertexColor4D)
		{
			return *reinterpret_cast<DirectX::XMFLOAT4 *>(pAttr);
		}
		else if constexpr (type == VertexLayout::ElementType::VertexRGBColor)
		{
			return *reinterpret_cast<unsigned int*>(pAttr);
		}
		else
		{
			assert("error type" && false);
			return *reinterpret_cast<char *>(pAttr);
		}
		

	}

	template<typename T>
	inline void Vertex::setAttrByIndex(size_t index, T&& val)
	{
		const auto& e = layout.resolveIndex(index);
		auto pAtrr = data + e.getOffset();
		switch (e.getElmentType())
		{
		case VertexLayout::ElementType::VertexPosition2D:
		case VertexLayout::ElementType::Teture2D:
			setAttr<DirectX::XMFLOAT2>(pAtrr, std::forward<T>(val));
			break;
		case VertexLayout::ElementType::VertexPosition3D:
		case VertexLayout::ElementType::VertexNormal:
		case VertexLayout::ElementType::VertexColor3D:
			setAttr<DirectX::XMFLOAT3>(pAtrr, std::forward<T>(val));
			break;

		case VertexLayout::ElementType::VertexColor4D:
			setAttr<DirectX::XMFLOAT4>(pAtrr, std::forward<T>(val));
			break;

		case VertexLayout::ElementType::VertexRGBColor:
			setAttr<unsigned int>(pAtrr, std::forward<T>(val));
			break;

		default:
			assert("Invaild Type" && false);
		}
	}
	template<typename Dest, typename Src>
	inline void Vertex::setAttr(char* p, Src&& val)
	{
		if constexpr (std::is_assignable<Dest, Src>::value)
		{
			*reinterpret_cast<Dest*>(p) = val;
		}
		else
		{
			assert("type dismatch" && false);
		}
	}

	template<typename First, typename ...Reset>
	inline void Vertex::setAttrByIndex(size_t index, First&& first, Reset && ...reset)
	{
		setAttrByIndex(index, std::forward<First>(first));
		setAttrByIndex(index + 1, std::forward<Reset>(reset)...);
	}

	template<typename ...T>
	inline void VertexBuferr::emplaceBack(T && ...args)
	{
		buffer.resize(buffer.size() + layout.Size());
		Back().setAttrByIndex(0u, std::forward<T>(args)...);
	}

}