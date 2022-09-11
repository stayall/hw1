#include "Box.h"
#include "BindableBase.h"

Box::Box(Graphics& ghs, std::mt19937 & rng, std::uniform_real_distribution<float>& adist, std::uniform_real_distribution<float>& ddist, std::uniform_real_distribution<float>& odist, std::uniform_real_distribution<float>& rdist)
    : 
    r(rdist(rng)),
    droll(ddist(rng)),
    dpitch(ddist(rng)),
    dyaw(ddist(rng)),
    dphi(odist(rng)),
    dtheta(odist(rng)),
    dchi(odist(rng)),
    chi(adist(rng)),
    theta(adist(rng)),
    phi(adist(rng))
{
    struct Vertex
    {
        struct Positiom
        {
            float x;
            float y;
            float z;
        }pos;
    };

    const std::vector<Vertex> ver = { 
        { -1.0f,-1.0f,-1.0f },
        { 1.0f,-1.0f,-1.0f },
        { -1.0f,1.0f,-1.0f },
        { 1.0f,1.0f,-1.0f },
        { -1.0f,-1.0f,1.0f },
        { 1.0f,-1.0f,1.0f },
        { -1.0f,1.0f,1.0f },
        { 1.0f,1.0f,1.0f },
    };
    addBind(std::make_unique<VertexBuffer>(ghs, ver));

    auto vs = std::make_unique<VertexShader>(ghs, L"VertexShader.cso");
    auto pvs = vs->getByteCode();
    addBind(std::move(vs));
    addBind(std::make_unique<PixelShader>(ghs, L"PixelShader.cso"));

  
    Microsoft::WRL::ComPtr<ID3D11InputLayout> layout;
    std::vector<D3D11_INPUT_ELEMENT_DESC> ed = {
        {"Position", 0u, DXGI_FORMAT_R32G32B32_FLOAT, 0u, 0u, D3D11_INPUT_PER_VERTEX_DATA, 0},
    };
    addBind(std::make_unique<InputLayout>(ghs, ed, pvs));
    addBind(std::make_unique<PrimitiveTology>(ghs, D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST));
    
   

    const std::vector<unsigned short> iec =
    {
        0,2,1, 2,3,1,
        1,3,5, 3,7,5,
        2,6,3, 3,6,7,
        4,5,7, 4,7,6,
        0,4,2, 2,4,6,
        0,1,4, 1,5,4
    };

    addIndexBind(std::make_unique<IndexBuffer>(ghs, iec));
    
    struct ConstBuffer2
    {
        struct
        {
            float r;
            float g;
            float b;
            float a;
        }color[8];
    };

    const ConstBuffer2  cb2= {
        {
        {1.0f, 0.0f, 1.0f},
        {1.0f, 0.0f, 0.0f},
        {0.0f, 1.0f, 0.0f},
        {0.0f, 0.0f, 1.0f},
        {1.0f, 1.0f, 0.0f},
        {0.0f, 1.0f, 1.0f},
        {0.0f, 1.0f, 1.0f},
        {0.0f, 1.0f, 1.0f}
        }
    };

   
    addBind(std::make_unique<PixelConstantsBuffer<ConstBuffer2>>(ghs, cb2));
    addBind(std::make_unique<Transform>(ghs, *this));
}

void Box::update(float dt) noexcept
{
    roll += droll * dt;
    pitch += dpitch * dt;
    yaw += dyaw * dt;
    theta += dtheta * dt;
    phi += dphi * dt;
    chi += dchi * dt;
}

DirectX::XMMATRIX Box::getMatrix() const noexcept
{
    return DirectX::XMMatrixRotationRollPitchYaw(pitch, yaw, roll) *
        DirectX::XMMatrixTranslation(r, 0.0f, 0.0f) *
        DirectX::XMMatrixRotationRollPitchYaw(theta, phi, chi) *
        DirectX::XMMatrixTranslation(0.0f, 0.0f, 20.0f);
}
