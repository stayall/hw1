#include "SliderSphere.h"
#include "Sphere.h"
#include "IndexedTrigerList.h"
#include "BindableBase.h"

SliderSphere::SliderSphere(Graphics& ghs, float raduis)
{
	struct Vertex
	{
		DirectX::XMFLOAT3 pos;
	};

	auto model =  Sphere::make<Vertex>(24, 12);
	model.transform(DirectX::XMMatrixScaling(raduis, raduis, raduis));

	if (!isInit())
	{
		AddBind(std::make_unique<VertexBuffer>(ghs, model.verties));
		AddIndexBind(std::make_unique<IndexBuffer>(ghs, model.indices));
		auto vs = std::make_unique<VertexShader>(ghs, L"sliderVS.cso");
		auto pvs = vs->getByteCode();
		AddBind(std::move(vs));

		AddBind(std::make_unique<PixelShader>(ghs, L"sliderPS.cso"));

	

		
		std::vector<D3D11_INPUT_ELEMENT_DESC> ied = {
			{"Position", 0u, DXGI_FORMAT_R32G32B32_FLOAT, 0u, 0u, D3D11_INPUT_PER_VERTEX_DATA, 0},
			
		};
		
		AddBind(std::make_unique<InputLayout>(ghs, ied, pvs));
		AddBind(std::make_unique<PrimitiveTology>(ghs, D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST));
	}
	
	addBind(std::make_unique<Transform>(ghs, *this));
}

DirectX::XMMATRIX SliderSphere::getMatrix() const noexcept
{
	DirectX::XMVECTOR p = DirectX::XMLoadFloat3(&pos);
	return DirectX::XMMatrixTranslationFromVector(p);
}

void SliderSphere::update(float dt) noexcept
{
}

void SliderSphere::setPos(DirectX::XMFLOAT3 p)
{
	pos = p;
}
