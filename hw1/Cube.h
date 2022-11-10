#pragma once
#include <algorithm>
#include "IndexedTrigerList.h"

class Cube
{
public:
	template<class T>
	static IndexedTrigerList<T> make();


};

template<class T>
inline IndexedTrigerList<T> Cube::make()
{
	const float side = 1.0f;
	const float len = side / 2;

	std::vector<DirectX::XMFLOAT3> vertices;
	vertices.reserve(8);
	vertices.emplace_back(-side, -side, -side);
	vertices.emplace_back(side, -side, -side);
	vertices.emplace_back(-side, side, -side);
	vertices.emplace_back(side, side, -side);
	vertices.emplace_back(-side, -side, side);
	vertices.emplace_back(side, -side, side);
	vertices.emplace_back(-side, side, side);
	vertices.emplace_back(side, side, side);

	std::vector<T> ver(8);
	for (size_t i = 0; i < vertices.size(); i++)
	{
		ver[i].pos = vertices[i];
	}

	std::vector<unsigned short> indices;
	
	return { std::move(ver),
			{0,2,1, 2,3,1,
			1,3,5, 3,7,5,
			2,6,3, 3,6,7,
			4,5,7, 4,7,6,
			0,4,2, 2,4,6,
			0,1,4, 1,5,4} };

	
}


