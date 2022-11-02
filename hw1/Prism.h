#pragma once


#include "Math.h"
#include "IndexedTrigerList.h"
class Prism
{
public:
	template<class T>
	static IndexedTrigerList<T> make(int longDiv);
private:
	template<class T>
	static IndexedTrigerList<T> makeTessellate(int longDiv);
};

template<class T>
inline IndexedTrigerList<T> Prism::make(int longDiv)
{
	
	return makeTessellate<T>(longDiv);
}

template<class T>
inline IndexedTrigerList<T> Prism::makeTessellate(int longDiv)
{
	const float raduis = 1.0f;
	const float height = 2.0f;
	const auto base = DirectX::XMVectorSet(raduis, 0.0f, 0.0f, 0.0f);
	const auto topBase = DirectX::XMVectorSet(raduis, 0.0f, height, 0.0f);;
	const auto center = DirectX::XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f);
	const auto topCenter = DirectX::XMVectorSet(0.0f, 0.0f, height, 0.0f);
	const float longDivAngle = 2 * PI / longDiv;


	std::vector<T> vertices;

	for (size_t iLong = 0; iLong < longDiv; iLong++)
	{
	
		
		{
			vertices.emplace_back();
			DirectX::XMStoreFloat3(&vertices.back().pos, DirectX::XMVector3Transform(base, DirectX::XMMatrixRotationZ(iLong * longDivAngle)));
		}

		{
			vertices.emplace_back();
			DirectX::XMStoreFloat3(&vertices.back().pos, DirectX::XMVector3Transform(topBase, DirectX::XMMatrixRotationZ(iLong * longDivAngle)));
		}
	}

	const size_t centerBottomSize = vertices.size();
	vertices.emplace_back();
	DirectX::XMStoreFloat3(&vertices.back().pos, center);

	const size_t centerTopSize = vertices.size();
	vertices.emplace_back();
	DirectX::XMStoreFloat3(&vertices.back().pos, topCenter);
	

	std::vector<unsigned short> indices;
	for (size_t iLong = 0; iLong < longDiv; iLong++)
	{
		const size_t i = iLong * 2;
		const size_t  model = 2 * longDiv;
		{
			indices.emplace_back(i);
			indices.emplace_back((i + 2) % model);
			indices.emplace_back(i + 1 % model);

			indices.emplace_back((i + 1) % model);
			indices.emplace_back((i + 2) % model);
			indices.emplace_back((i + 3) % model);
		}

		{
			indices.emplace_back(i );
			indices.emplace_back(centerBottomSize );
			indices.emplace_back((i + 2) %model);
			
			indices.emplace_back((i + 3) %model);
			indices.emplace_back(centerTopSize);
			indices.emplace_back((i + 1) % model);
		}
	}
	return {std::move(vertices), std::move(indices)};
}
