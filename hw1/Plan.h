#pragma once

#include <DirectXMath.h>

#include <array>
#include <vector>

#include "Math.h"
#include "IndexedTrigerList.h"
class Plan
{
public:
	template<class T>
	static IndexedTrigerList<T> make(int xDiv, int yDiv);

private:
	template<class T>
	static IndexedTrigerList<T> makeTessellate(int xDiv, int yDiv);

};

template<class T>
inline IndexedTrigerList<T> Plan::makeTessellate(int xDiv, int yDiv)
{
	
	assert(xDiv >= 1);
	assert(yDiv >= 1);
	
	const float width = 2.0f;
	const float height = 2.0f;

	const float divisionSize_x = width / (float) xDiv;
	const float divisionSize_y = height / (float)xDiv;
	const float vertexNumber_x = xDiv + 1;
	const float vertexNumber_y = yDiv + 1;

	DirectX::FXMVECTOR leftAndBottem = DirectX::XMVectorSet(-width / 2, -height / 2, 0.0f, 0.0f);
	std::vector<T> verties(vertexNumber_x * vertexNumber_y);

	

		for (size_t y = 0, i = 0; y < vertexNumber_y; y++)
		{
		
		const auto lastBase = DirectX::XMVector3Transform(leftAndBottem, DirectX::XMMatrixTranslation(y * divisionSize_y, 0.0f, 0.0f));
		for (size_t x = 0; x < vertexNumber_x; x++, i++)
		{
			const auto v = DirectX::XMVector3Transform(lastBase, DirectX::XMMatrixTranslation(0.0f, x * divisionSize_x, 0.0f));

			DirectX::XMStoreFloat3(&verties.at(i).pos, v);
		}
	}
	auto calcIdx = [vertexNumber_x, vertexNumber_y](int x, int y)
	{return y * vertexNumber_x + x; };

	std::vector<unsigned short> indices;
	
	indices.reserve(vertexNumber_x * vertexNumber_y * 8);
	for (size_t y = 0; y < yDiv; y++)
	{
	for (size_t x = 0; x < xDiv; x++)
		{
			std::array<unsigned short, 4> indexArray =
			{ calcIdx(x, y), calcIdx(x, y + 1), calcIdx(x + 1, y), calcIdx(x + 1, y + 1) };
			indices.emplace_back(indexArray[0]);
			indices.emplace_back(indexArray[1]);
			indices.emplace_back(indexArray[2]);
			indices.emplace_back(indexArray[2]);
			indices.emplace_back(indexArray[1]);
			indices.emplace_back(indexArray[3]);

			indices.emplace_back(indexArray[1]);
			indices.emplace_back(indexArray[0]);
			indices.emplace_back(indexArray[2]);
			indices.emplace_back(indexArray[1]);
			indices.emplace_back(indexArray[2]);
			indices.emplace_back(indexArray[3]);
		}
	}

	
	return {std::move(verties), std::move(indices)};
}

template<class T>
inline IndexedTrigerList<T> Plan::make(int xDiv, int yDiv)
{
	return makeTessellate<T>(xDiv, yDiv);
}


