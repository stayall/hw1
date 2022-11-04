#pragma once
#include <DirectXMath.h>

#include "IndexedTrigerList.h"
#include "Math.h"

class Sphere
{
public:
	template<typename T>
	static IndexedTrigerList<T> makeTessellate(int latDiv, int longDiv);
	template<typename T>
	static IndexedTrigerList<T> make(int latDiv, int longDiv);
};

template<typename T>
inline IndexedTrigerList<T> Sphere::makeTessellate(int latDiv, int longDiv)
{
	assert(latDiv >= 3);
	assert(longDiv >= 3);
	const float radius = 1.0f;
	const auto base = DirectX::XMVectorSet(0.0f, 0.0f, radius, 1.0f);
	const float lattitudeAngle = PI / (float)latDiv;
	const float longitudeAngle = 2 * PI / longDiv;

	std::vector<T> vertices;
	for (size_t iLat  = 1; iLat < latDiv ; iLat++)
	{
		
		const auto lastBase = DirectX::XMVector3Transform(base, DirectX::XMMatrixRotationX(iLat * lattitudeAngle));
		for (size_t iLong = 0; iLong < longDiv ; iLong++)
		{
			vertices.emplace_back();
			DirectX::XMStoreFloat3(
				&(vertices.back().pos),
				DirectX::XMVector3Transform(
					lastBase,
					DirectX::XMMatrixRotationZ(iLong * longitudeAngle) 
				)
			);
		}
	}

	int iNorthPole = vertices.size();
	vertices.emplace_back();
	DirectX::XMStoreFloat3(&vertices.back().pos, base);
	int iSouthPole = vertices.size();
	vertices.emplace_back();
	DirectX::XMStoreFloat3(&vertices.back().pos, DirectX::XMVectorNegate( base ));

	auto calcIdx = [latDiv, longDiv](unsigned short iLat, unsigned short iLong) {return iLat * longDiv + iLong; };
	std::vector<unsigned short> indices;

	for (size_t iLat = 0; iLat < latDiv - 2; iLat++)
	{
		for (size_t iLong = 0; iLong < longDiv - 1; iLong++)
		{
			indices.emplace_back(calcIdx(iLat, iLong));
			indices.emplace_back(calcIdx(iLat + 1, iLong));
			indices.emplace_back(calcIdx(iLat, iLong + 1));
			indices.emplace_back(calcIdx(iLat, iLong + 1));
			indices.emplace_back(calcIdx(iLat + 1, iLong));
			indices.emplace_back(calcIdx(iLat + 1, iLong + 1));
		}
		indices.emplace_back(calcIdx(iLat, longDiv - 1));
		indices.emplace_back(calcIdx(iLat + 1, longDiv - 1));
		indices.emplace_back(calcIdx(iLat, 0));
		indices.emplace_back(calcIdx(iLat, 0));
		indices.emplace_back(calcIdx(iLat + 1, longDiv - 1));
		indices.emplace_back(calcIdx(iLat + 1, 0));
	}

	for (size_t iLong = 0; iLong < longDiv - 1; iLong++)
	{
		indices.emplace_back(iNorthPole);
		indices.emplace_back(calcIdx(0, iLong));
		indices.emplace_back(calcIdx(0, iLong + 1));

		indices.emplace_back(calcIdx(latDiv - 2, iLong + 1));
		indices.emplace_back(calcIdx(latDiv - 2, iLong));
		indices.emplace_back(iSouthPole);
	
	}

	indices.emplace_back(iNorthPole);
	indices.emplace_back(calcIdx(0, longDiv - 1));
	indices.emplace_back(calcIdx(0, 0));

	indices.emplace_back(calcIdx(latDiv - 2, 0));
	indices.emplace_back(calcIdx(latDiv - 2, longDiv - 1));
	indices.emplace_back(iSouthPole);

	std::vector<T> test;
	
	test.emplace_back();
	DirectX::XMStoreFloat3(&test.back().pos, { -1.0f,-1.0f,-1.0f });
	test.emplace_back();
	DirectX::XMStoreFloat3(&test.back().pos, { 1.0f,-1.0f,-1.0f });
	test.emplace_back();
	DirectX::XMStoreFloat3(&test.back().pos, { -1.0f,1.0f,-1.0f });
	test.emplace_back();
	DirectX::XMStoreFloat3(&test.back().pos, { 1.0f,1.0f,-1.0f });
	test.emplace_back();
	DirectX::XMStoreFloat3(&test.back().pos, { -1.0f,-1.0f,1.0f });
	test.emplace_back();
	DirectX::XMStoreFloat3(&test.back().pos, { 1.0f,-1.0f,1.0f });
	test.emplace_back();
	DirectX::XMStoreFloat3(&test.back().pos, { -1.0f,1.0f,1.0f });
	test.emplace_back();
	DirectX::XMStoreFloat3(&test.back().pos, { 1.0f,1.0f,1.0f });
	std::vector<unsigned short> itest{ 
			0,2,1, 2,3,1,
			1,3,5, 3,7,5,
			2,6,3, 3,6,7,
			4,5,7, 4,7,6,
			0,4,2, 2,4,6,
			0,1,4, 1,5,4 };
	
	//return { std::move(test), std::move(itest) };
	return { std::move(vertices), std::move(indices) };
}

template<typename T>
inline IndexedTrigerList<T> Sphere::make(int latDiv, int longDiv )
{
	return makeTessellate<T>(latDiv, longDiv);
}
