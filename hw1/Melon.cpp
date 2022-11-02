#include "Melon.h"
#include "BindableBase.h"

Melon::Melon(Graphics &ghs)
{
    if (!isInit())
    {
        struct Vertex
        {

            DirectX::XMFLOAT3 pos;

        };

        const std::vector<std::vector<float>> ver = {
           { -1.0f,-1.0f,-1.0f },
           { 1.0f,-1.0f,-1.0f },
           { -1.0f,1.0f,-1.0f },
           { 1.0f,1.0f,-1.0f },
           { -1.0f,-1.0f,1.0f },
           { 1.0f,-1.0f,1.0f },
           { -1.0f,1.0f,1.0f },
           { 1.0f,1.0f,1.0f },
        };

        auto model = Sphere::make<Vertex>(12, 24);
        AddBind(std::make_unique<VertexBuffer>(ghs, model.verties));
        model.transform(DirectX::XMMatrixScaling(1.0f, 3.0f, 3.0f));

        auto vs = std::make_unique<VertexShader>(ghs, L"ColorIndexVS.cso");
        auto pvs = vs->getByteCode();
        AddBind(std::move(vs));
        AddBind(std::make_unique<PixelShader>(ghs, L"ColorIndexPS.cso"));


        Microsoft::WRL::ComPtr<ID3D11InputLayout> layout;
        std::vector<D3D11_INPUT_ELEMENT_DESC> ed = {
            {"Position", 0u, DXGI_FORMAT_R32G32B32_FLOAT, 0u, 0u, D3D11_INPUT_PER_VERTEX_DATA, 0},
        };
        AddBind(std::make_unique<InputLayout>(ghs, ed, pvs));
        AddBind(std::make_unique<PrimitiveTology>(ghs, D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST));



        const std::vector<unsigned short> iec =
        {
            0,2,1, 2,3,1,
            1,3,5, 3,7,5,
            2,6,3, 3,6,7,
            4,5,7, 4,7,6,
            0,4,2, 2,4,6,
            0,1,4, 1,5,4
        };

        AddIndexBind(std::make_unique<IndexBuffer>(ghs, model.indices));

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

        const ConstBuffer2  cb2 = {
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


        AddBind(std::make_unique<PixelConstantsBuffer<ConstBuffer2>>(ghs, cb2));
    }

    addBind(std::make_unique<Transform>(ghs, *this));
}

void Melon::update(float dt) noexcept
{
    roll += droll * dt;
    pitch += dpitch * dt;
    yaw += dyaw * dt;
    theta += dtheta * dt;
    phi += dphi * dt;
    chi += dchi * dt;
}

DirectX::XMMATRIX Melon::getMatrix() const noexcept
{
    namespace dx = DirectX;
    return dx::XMMatrixRotationRollPitchYaw(pitch, yaw, roll) *
        dx::XMMatrixTranslation(r, 0.0f, 0.0f) *
        dx::XMMatrixRotationRollPitchYaw(theta, phi, chi) *
        dx::XMMatrixTranslation(0.0f, 0.0f, 20.0f);
}
