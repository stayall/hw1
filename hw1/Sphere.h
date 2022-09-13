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
	const float radius = 1.0f;
	const auto base = DirectX::XMVectorSet(0.0f, 0.0f, radius, 0.0f);
	const float lattitudeAngle = PI / latDiv;
	const float longitudeAngle = 2 * PI / longDiv;

	std::vector<T> vertices;
	for (size_t iLat  = 1; iLat < latDiv ; iLat++)
	{
		for (size_t iLong = 0; iLong < longDiv ; iLong++)
		{
			vertices.emplace_back();
			DirectX::XMStoreFloat(
				&vertices.back().pos,
				DirectX::XMVector2Transform(
					base, 
					DirectX::XMMatrixRotationX(iLat * lattitudeAngle) *
						DirectX::XMMatrixRotationZ(iLong * longitudeAngle)
				)
			)
		}
	}

	int iNorthPole = vertices.size();
	vertices.emplace_back();
	DirectX::XMStoreFloat(&vertices.back().pos, base);
	int iSouthPole = vertices.size();
	vertices.emplace_back();
	DirectX::XMStoreFloat(&vertices.back().pos, DirectX::XMVectorNegate( base ));

	auto calcIdx = [latDiv, longDiv](unsigned short iLat, unsigned shrot iLong)
	{return iLat * longDiv + longDiv};
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

	return { std::move(vertices), std::move(indices) };
}

template<typename T>
inline IndexedTrigerList<T> Sphere::make(int latDiv, int longDiv)
{
	return makeTessellate<T>(12, 24);
}
