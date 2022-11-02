#include "Box.h"
#include "BindableBase.h"
#include "Sphere.h"
#include "Plan.h"
#include "Cube.h"
#include "Cone.h"
#include "Prism.h"
#include "imgui\imgui.h"

Box::Box(Graphics& ghs, std::mt19937 & rng, std::uniform_real_distribution<float>& adist, std::uniform_real_distribution<float>& ddist, std::uniform_real_distribution<float>& odist, std::uniform_real_distribution<float>& rdist, std::uniform_real_distribution<float>& cdist)
   : TestGraphics<Box>(rng, adist, ddist, odist, rdist, cdist)
{
    if (!isInit())
    {
        struct Vertex
        {
            
                DirectX::XMFLOAT3 pos;
                DirectX::XMFLOAT3 normal;

        /*        struct  Color
                {
                    unsigned short r;
                    unsigned short g;
                    unsigned short b;
                    unsigned short a;
                } color;*/
        };

      

        auto model = Cube::make<Vertex>();
        model.makeNormal();
     
        model.transform(DirectX::XMMatrixScaling(1.0f, 1.0f, 1.2f));
        AddBind(std::make_unique<VertexBuffer>(ghs, model.verties));
        

        auto vs = std::make_unique<VertexShader>(ghs, L"PhongVS.cso");
        auto pvs = vs->getByteCode();
        AddBind(std::move(vs));
        AddBind(std::make_unique<PixelShader>(ghs, L"PhongPS.cso"));


        Microsoft::WRL::ComPtr<ID3D11InputLayout> layout;
        std::vector<D3D11_INPUT_ELEMENT_DESC> ed = {
            {"Position", 0u, DXGI_FORMAT_R32G32B32_FLOAT, 0u, 0u, D3D11_INPUT_PER_VERTEX_DATA, 0},
            {"Normal", 0u, DXGI_FORMAT_R32G32B32_FLOAT, 0u, sizeof(DirectX::XMFLOAT3), D3D11_INPUT_PER_VERTEX_DATA, 0},
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

        struct LghitPos
        {
            DirectX::XMFLOAT3 pos = {0.0f, 0.0f, 0.0f};
            float pedding = 0;
        };

        LghitPos ss;

       
    }

    DirectX::XMFLOAT3A color{ cdist(rng), cdist(rng) , cdist(rng) };

    

   
    ob.materiaColor = color;
    addBind(std::make_unique<PixelConstantsBuffer<Objec>>(ghs, ob, 1));

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
        DirectX::XMMatrixRotationRollPitchYaw(theta, phi, chi);
}

bool Box::spawnBoxCountroller(int i, Graphics &ghs)
{
    bool change = false;
    bool open = true;

    using namespace std::string_literals;
    if (ImGui::Begin(("Box"s + std::to_string(i)).c_str(), &open))
    {
        ImGui::Text("Position");
        ImGui::SliderFloat("R ", &r, 1.f, 80.0f);
        ImGui::SliderFloat("Theata ", &theta, -180.0f, 180.0f);
        ImGui::SliderFloat("Phi ", &phi, -90.f, 90.f);
        ImGui::SliderFloat("Chi ", &chi, -180.0f, 180.0f);
        ImGui::Text("Orientation");
        ImGui::SliderFloat("Pitch ", &pitch, -180.0f, 180.0f);
        ImGui::SliderFloat("Yaw ", &yaw, -180.0f, 180.0f);
        ImGui::SliderFloat("Roll ", &roll, -180.0f, 180.0f);
        //yaw = phi;
        if (ImGui::Button("Reset"))
        {
            positionReset();
        }

        ImGui::Text("Material");
        //can't use &&, logic interupt
        change |= ImGui::ColorEdit3("Material Color", &ob.materiaColor.x);
    }
 

    if (change)
    {
        syncMaterial(ghs);
    }

    ImGui::End();

    return open;
}

void Box::positionReset()
{
     r = 0;
     roll = 0.0f;
     pitch = 0.0f;
     yaw = 0.0f;
     theta = 0.0f;
     phi = 0.0f;
     chi = 0.0f;

     droll = 0.0f;
     dpitch = 0.0f;
     dyaw = 0.0f;
     dtheta = 0.0f;
     dphi = 0.0f;
     dchi = 0.0f;
}

void Box::syncMaterial(Graphics& ghs)
{
    auto p = getBindable<PixelConstantsBuffer<Objec>>();
    assert(p != nullptr);
    p->update(ghs, ob);
}
