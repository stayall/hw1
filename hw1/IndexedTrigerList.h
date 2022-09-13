#pragma once
#include <DirectXMath.h>

#include <vector>
#include <cassert>

template<class T>
class IndexedTrigerList
{
public:
	IndexedTrigerList(const std::vector<T> vet_in, const std::vector<unsigned short> indices_in);
	void transform(DirectX::FXMMATRIX &matrix);
private:
	std::vector<T> verties;
	std::vector<unsigned short> indices;
};

template<class T>
inline IndexedTrigerList<T>::IndexedTrigerList(const std::vector<T> vet_in, const std::vector<unsigned short> indices_in)
	: verties(std::move(vet_in)), 
	indices(std::move(indices_in))
{
	assert(vet_in.size() > 3);
	assert(indices_in.size() > 3);
}

template<class T>
inline void IndexedTrigerList<T>::transform(DirectX::FXMMATRIX &matrix)
{
	for (auto& v : verties)
	{
		auto xv = DirectX::XMLoadFloat3(&v.pos);
		DirectX::XMStoreFloat3(&v.pos, DirectX::XMVector3Transform(xv, matrix));
	}
}
