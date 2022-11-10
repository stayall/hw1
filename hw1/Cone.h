#pragma once

#include "Math.h"
#include "IndexedTrigerList.h"

class Cone
{
public:
	template<class T>
	static IndexedTrigerList<T> make(int divison);

private:
	template<class T>
	static IndexedTrigerList<T> makeTessellate(int division);
};

template<class T>
inline IndexedTrigerList<T> Cone::make(int divison)
{
	return makeTessellate<T>(divison);
}

template<class T>
inline IndexedTrigerList<T> Cone::makeTessellate(int division)
{
	assert(division >= 3);
	const float raduis = 1.0f;
	const float height = 1.0f;
	const float divisionAngle = 2 * PI / (float)division;
	const auto base = DirectX::XMVectorSet(raduis, 0.0f, 0.0f, 0.0f);
	const auto conic = DirectX::XMVectorSet(0.0f, 0.0f, height, 0.0f);
	const auto centre = DirectX::XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f);

	std::vector<T> vertices;
	for (size_t i = 0; i < division; i++)
	{
		
		vertices.emplace_back();
		DirectX::XMStoreFloat3(
			&vertices.back().pos, 
			DirectX::XMVector3Transform(
				base, 
				DirectX::XMMatrixRotationZ((float)i * divisionAngle)
			)
		);
	}
	size_t conicNode = vertices.size();
	vertices.emplace_back();
	DirectX::XMStoreFloat3(&vertices.back().pos, conic);

	size_t lip = vertices.size();
	vertices.emplace_back();
	DirectX::XMStoreFloat3(&vertices.back().pos, DirectX::XMVectorNegate(conic));

	size_t center = vertices.size();
	vertices.emplace_back();
	DirectX::XMStoreFloat3(&vertices.back().pos, centre);

	std::vector<unsigned short> indices;
	for (size_t i = 0; i < division - 1; i++)
	{
		indices.emplace_back(conicNode);
		indices.emplace_back(i);
		indices.emplace_back(i + 1);

		/*indices.emplace_back(lip);
		indices.emplace_back(i + 1);
		indices.emplace_back(i);*/

		/*indices.emplace_back(i);
		indices.emplace_back(center);
		indices.emplace_back(i + 1);
		*/

		indices.emplace_back(i);
		indices.emplace_back(center);
		indices.emplace_back(i + 1);

	}

	indices.emplace_back(conicNode);
	indices.emplace_back(division - 1);
	indices.emplace_back(0);
	
	/*indices.emplace_back(lip);
	indices.emplace_back(division - 1);
	indices.emplace_back(0);*/

	/*indices.emplace_back(division - 1);
	indices.emplace_back(center);
	indices.emplace_back(0);

	*/
	indices.emplace_back(division - 1);
	indices.emplace_back(center);
	indices.emplace_back(0);


	
	return { std::move(vertices), std::move(indices) };
}
