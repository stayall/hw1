#include <vector>
#include <DirectXMath.h>
#include <d3d11.h>
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
			D3D11_INPUT_ELEMENT_DESC getElemntDesc() const;

			template<ElementType type>
			static constexpr D3D11_INPUT_ELEMENT_DESC getED(size_t offset)
				{
					return D3D11_INPUT_ELEMENT_DESC{ dataMap<type>::semantie, 0u, dataMap<type>::format, 0u, offset, D3D11_INPUT_PER_VERTEX_DATA, 0 };
				}
			//TODO: anglisy this magic error
			/*template<VertexLayout::ElementType type>
			D3D11_INPUT_ELEMENT_DESC VertexLayout::Element::getED()
			{
				dataMap<type>::format;
				return D3D11_INPUT_ELEMENT_DESC();
			}*/

			size_t Size() const;
			static constexpr size_t SizeOf(ElementType Type);

			
		private:
			ElementType type;
			size_t offset;
		};

		std::vector<D3D11_INPUT_ELEMENT_DESC> get3DLayOut() const;

		const Element& resolve(ElementType type) const;
		const Element& resolveIndex(size_t i) const;
		size_t Size() const;
		void append(ElementType type);
		size_t getElemntCount() const;

		template<VertexLayout::ElementType> struct dataMap;

		template<>
		struct dataMap<VertexLayout::ElementType::VertexPosition2D>
		{
			using sys = DirectX::XMFLOAT2;
			static constexpr DXGI_FORMAT format = DXGI_FORMAT_R32G32_UINT;
			static constexpr const char* semantie = "Position2D";
		};

		template<>
		struct dataMap<VertexLayout::ElementType::VertexPosition3D>
		{
			using sys = DirectX::XMFLOAT3;
			static constexpr DXGI_FORMAT format = DXGI_FORMAT_R32G32B32_UINT;
			static constexpr const char* semantie = "Positione3D";
		};

		template<>
		struct dataMap<VertexLayout::ElementType::VertexNormal>
		{
			using sys = DirectX::XMFLOAT3;
			static constexpr DXGI_FORMAT format = DXGI_FORMAT_R32G32B32_UINT;
			static constexpr const char* semantie = "Normal";
		};

		template<>
		struct dataMap<VertexLayout::ElementType::Teture2D>
		{
			using sys = DirectX::XMFLOAT2;
			static constexpr DXGI_FORMAT format = DXGI_FORMAT_R32G32_UINT;
			static constexpr const char* semantie = "Teture";
		};

		template<>
		struct dataMap<VertexLayout::ElementType::VertexColor3D>
		{
			using sys = DirectX::XMFLOAT3;
			static constexpr DXGI_FORMAT format = DXGI_FORMAT_R32G32B32_UINT;
			static constexpr const char* semantie = "Color3D";
		};

		template<>
		struct dataMap<VertexLayout::ElementType::VertexColor4D>
		{
			using sys = DirectX::XMFLOAT4;
			static constexpr DXGI_FORMAT format = DXGI_FORMAT_R32G32B32A32_UINT;
			static constexpr const char* semantie = "Color4D";
		};

		template<>
		struct dataMap<VertexLayout::ElementType::VertexRGBColor>
		{
			using sys = unsigned int;
			static constexpr DXGI_FORMAT format = DXGI_FORMAT_R8G8B8A8_UINT;
			static constexpr const char* semantie = "RGBColor";
		};

		


	private:
		std::vector<Element> elment;

	};
		
	

	class Vertex
	{
		friend class VertexBuferr;
	public:
		Vertex(char* p, VertexLayout &vl) : data(p), layout(vl) {};

		template<VertexLayout::ElementType type>
		auto& attr();

		template<typename T>
		void setAttrByIndex(size_t index, T&& val);

		template<VertexLayout::ElementType type, typename Src>
		void setAttr(char* p, Src&& val);
	private:
		template<typename First, typename ...Reset>
		void setAttrByIndex(size_t index, First&& first, Reset &&... reset);

	private:
		char* data;
		VertexLayout &layout;
	};

	class ConsVertex
	{
	public:
		ConsVertex(const Vertex& vl) : vertex(vl) {};

		template<VertexLayout::ElementType type>
		const auto& attr();
	private:
		Vertex vertex;
	};

	class VertexBuferr
	{
	public:
		VertexBuferr(VertexLayout ly) : layout(std::move(ly)) {};

		template<typename... T>
		void emplaceBack(T &&...args);


		size_t Size() const;
		size_t getByteSize() const;
		char* getData() const;

		ConsVertex Front() const;
		ConsVertex Back() const;
		const VertexLayout getLayout() const;
		ConsVertex operator[](size_t index) const;

		Vertex Front();
		Vertex Back();
		VertexLayout getLayout();

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
		return *reinterpret_cast<typename VertexLayout::dataMap<type>::sys *>(pAttr);

	}

	template<typename T>
	inline void Vertex::setAttrByIndex(size_t index, T&& val)
	{
		const auto& e = layout.resolveIndex(index);
		auto pAtrr = data + e.getOffset();
		switch (e.getElmentType())
		{
		/*case VertexLayout::ElementType::Teture2D:
			setAttr<typename dataMap<VertexLayout::ElementType::Teture2D>::sys>(pAtrr, std::forward<T>(val));
			break;*/
#define SETATTR(S) \
		case S: \
			setAttr<S>(pAtrr, std::forward<T>(val)); \
			break;
		
			SETATTR(VertexLayout::ElementType::VertexPosition2D);
			SETATTR(VertexLayout::ElementType::VertexPosition3D);
			SETATTR(VertexLayout::ElementType::VertexNormal);
			SETATTR(VertexLayout::ElementType::Teture2D);
			SETATTR(VertexLayout::ElementType::VertexColor3D);
			SETATTR(VertexLayout::ElementType::VertexColor4D);
			SETATTR(VertexLayout::ElementType::VertexRGBColor);
			
#undef SETATTR
			default:
			assert("Invaild Type" && false);
		}
	}
	template<VertexLayout::ElementType type, typename Src>
	inline void Vertex::setAttr(char* p, Src&& val)
	{
		using Dest = typename VertexLayout::dataMap<type>::sys;
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
		assert(sizeof...(args) % layout.getElemntCount() == 0 && "Tset Argenment Number");
		buffer.resize(buffer.size() + layout.Size());
		Back().setAttrByIndex(0u, std::forward<T>(args)...);
	}

	template<VertexLayout::ElementType type>
	inline const auto& ConsVertex::attr()
	{
		return const_cast<Vertex&>(vertex).attr<type>();
	}

	




	

}