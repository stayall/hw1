#include "line.h"
#include "BindableBase.h"

line::line(Graphics& ghs)
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
        {1.0, -1.0f, -1.0f }
    };
    addBind(std::make_unique<VertexBuffer>(ghs, ver));

    auto vs = std::make_unique<VertexShader>(ghs, L"VertexShader.cso");
    auto pvs = vs->getByteCode();
    addBind(std::move(vs));
    addBind(std::make_unique<PrimitiveTology>(ghs, D3D_PRIMITIVE_TOPOLOGY_LINELIST));
    Microsoft::WRL::ComPtr<ID3D11InputLayout> layout;
    std::vector<D3D11_INPUT_ELEMENT_DESC> ed = {
        {"Position", 0u, DXGI_FORMAT_R32G32B32_FLOAT, 0u, 0u, D3D11_INPUT_PER_VERTEX_DATA, 0},
    };
    addBind(std::make_unique<InputLayout>(ghs, ed, pvs));
    addBind(std::make_unique<PixelShader>(ghs, L"PixelShader.cso"));



    const std::vector<unsigned short> iec =
    {
        0u, 1u
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

    const ConstBuffer2  cb2 = {
        {
        {1.0f, 0.0f, 1.0f},
        {1.0f, 0.0f, 0.0f},
        {0.0f, 1.0f, 0.0f},
        {0.0f, 0.0f, 1.0f},
        {1.0f, 1.0f, 0.0f},
        {0.0f, 1.0f, 1.0f}
        }
    };

    addBind(std::make_unique<Transform>(ghs, *this));
    addBind(std::make_unique<PixelConstantsBuffer<ConstBuffer2>>(ghs, cb2));
}

DirectX::XMMATRIX line::getMatrix() const noexcept
{
    return DirectX::XMMATRIX();
}

void line::update(float dt) noexcept
{
}
