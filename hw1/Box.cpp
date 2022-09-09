#include "Box.h"
#include "BindableBase.h"

Box::Box(Graphics& ghs, std::mt19937 &mt, std::uniform_real_distribution<float>& adist, std::uniform_real_distribution<float>& ddist, std::uniform_real_distribution<float>& odist, std::uniform_real_distribution<float>& rdist)
    : 
    r(adist(mt)),
    theta(adist(mt)),
    phi(adist(mt)),
    chi(adist(mt)),
    droll(adist(mt)),
    dpicth(adist(mt)),
    dyaw(adist(mt)),
    dtheta(adist(mt)),
    dphi(adist(mt)),
    dchi(adist(mt))
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
        {-1.0, -1.0f, -1.0f },
        {1.0, -1.0f, -1.0f },
        {-1.0, 1.0f, -1.0f },
        {1.0, 1.0f, -1.0f },
        {-1.0, -1.0f, 1.0f },
        {1.0, -1.0f, 1.0f },
        {-1.0, 1.0f, 1.0f },
        {1.0, 1.0f, 1.0f },
    };

    auto vs = std::make_unique<VertexShader>(ghs, L"VertexShader.cso");
    auto pvs = vs->getByteCode();
    addBind(std::move(vs));
    addBind(std::make_unique<PrimitiveTology>(ghs, D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST));
    Microsoft::WRL::ComPtr<ID3D11InputLayout> layout;
    std::vector<D3D11_INPUT_ELEMENT_DESC> ed = {
        {"Position", 0u, DXGI_FORMAT_R32G32_FLOAT, 0u, 0u, D3D11_INPUT_PER_VERTEX_DATA, 0},
    };
    addBind(std::make_unique<InputLayout>(ghs, ed, pvs));
    addBind(std::make_unique<PixelShader>(ghs, L"PixelShader.cso"));
    addBind(std::make_unique<Transform>(ghs, *this));
    addBind(std::make_unique<VertexBuffer>(ghs, ver));

    const std::vector<unsigned short> iec =
    {
        0, 2, 1, 2, 3, 1,
        1, 3, 5, 3, 7, 5,
        2, 6, 3, 3, 6, 7,
        4, 5, 7, 4, 7, 6,
        0, 4, 2, 2, 4, 6,
        0, 1, 4, 1, 5, 4
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
        }color[6];
    };

    const ConstBuffer2  cb2= {
        {
        {1.0f, 0.0f, 1.0f},
        {1.0f, 0.0f, 0.0f},
        {0.0f, 1.0f, 0.0f},
        {0.0f, 0.0f, 1.0f},
        {1.0f, 1.0f, 0.0f},
        {0.0f, 1.0f, 1.0f}
        }
    };

    addBind(std::make_unique<PixelConstantsBuffer<ConstBuffer2>>(ghs, cb2));
}

void Box::update(float dt) noexcept
{
    roll += droll * dt;
    pitch += dpicth * dt;
    yaw += dyaw * dt;
    theta += dtheta * dt;
    phi += dphi * dt;
    phi += dchi * dt;
}

DirectX::XMMATRIX Box::getMatrix() const noexcept
{
    return DirectX::XMMatrixRotationRollPitchYaw(pitch, yaw, roll) *
        DirectX::XMMatrixTranslation(r, 0.0f, 0.0f) *
        DirectX::XMMatrixRotationRollPitchYaw(theta, phi, chi) *
        DirectX::XMMatrixTranslation(0.0f, 0.0f, 2.0f);
}
