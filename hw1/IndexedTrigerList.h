#pragma once
#include <DirectXMath.h>

#include <vector>
#include <cassert>

template<class T>
class IndexedTrigerList
{
public:
	IndexedTrigerList(const std::vector<T> vet_in, const std::vector<unsigned short> indices_in);
	void transform(DirectX::FXMMATRIX matrix);

	void makeNormal();
	
public:
	std::vector<T> verties;
	std::vector<unsigned short> indices;
};

template<class T>
inline IndexedTrigerList<T>::IndexedTrigerList(const std::vector<T> vet_in, const std::vector<unsigned short> indices_in)
	: verties(std::move(vet_in)), 
	indices(std::move(indices_in))
{
	assert(vet_in.size() > 2);
	assert(indices_in.size() %3 == 0);
}

template<class T>
inline void IndexedTrigerList<T>::transform(DirectX::FXMMATRIX matrix)
{
	for (auto& v : verties)
	{
		auto xv = DirectX::XMLoadFloat3(&v.pos);
		DirectX::XMStoreFloat3(&v.pos, DirectX::XMVector3Transform(xv, matrix));
	}
}


template<class T>
inline void IndexedTrigerList<T>::makeNormal()
{
	assert(indices.size() % 3 == 0 && indices.size() > 0);

	using namespace DirectX;
	size_t length = indices.size();
	for (size_t i = 0; i < length; i+=3)
	{
		auto &v0 = verties[indices[i]];
		auto &v1 = verties[indices[i + 1]];
		auto &v2 = verties[indices[i + 2]];
		
		const auto p0 = DirectX::XMLoadFloat3(&v0.pos);
		const auto p1 = DirectX::XMLoadFloat3(&v1.pos);
		const auto p2 = DirectX::XMLoadFloat3(&v2.pos);
		
		const auto normal = DirectX::XMVector3Cross((p0 - p1), (p0  - p2));

		DirectX::XMStoreFloat3(&v0.normal, normal);
		DirectX::XMStoreFloat3(&v1.normal, normal);
		DirectX::XMStoreFloat3(&v2.normal, normal);

		
	}

}
