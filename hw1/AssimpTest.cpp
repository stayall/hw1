#include "AssimpTest.h"
#include "DrawableBase.h"
#include "BindableBase.h"
#include <assimp\Importer.hpp>
#include <assimp\scene.h>
#include <assimp\postprocess.h>
#include "Vertex.h"

AssTest::AssTest(Graphics &ghs, const char* filepath,
    std::mt19937& mt,
    std::uniform_real_distribution<float>& adist,
    std::uniform_real_distribution<float>& ddist,
    std::uniform_real_distribution<float>& odist,
    std::uniform_real_distribution<float>& rdist,
    std::uniform_real_distribution<float>& cdist)
    :TestGraphics<AssTest>(mt, adist, ddist, odist, rdist, cdist)
{
    
    if (!isInit())
    {
    Proc::VertexLayout vl;
    vl.append(Proc::VertexLayout::ElementType::VertexPosition3D);
    vl.append(Proc::VertexLayout::ElementType::VertexNormal);
    Proc::VertexBuferr vb(std::move(vl));

    

	Assimp::Importer importer;
    const aiScene* pScene = importer.ReadFile(filepath,
        aiProcess_Triangulate |
        aiProcess_JoinIdenticalVertices );

    aiMesh* pMesh = pScene->mMeshes[0];

    for (size_t i = 0; i < pMesh->mNumVertices; i++)
    {
        auto a = pMesh->mVertices[i];
        vb.emplaceBack(*reinterpret_cast<DirectX::XMFLOAT3*>(&pMesh->mVertices[i]), 
            *reinterpret_cast<DirectX::XMFLOAT3*>(&pMesh->mNormals[i]));
    }

    std::vector<unsigned short> indices;
    indices.reserve(pMesh->mNumFaces * 3);
    for (size_t i = 0; i < pMesh->mNumFaces; i++)
    {
        indices.emplace_back(pMesh->mFaces[i].mIndices[0]);
        indices.emplace_back(pMesh->mFaces[i].mIndices[1]);
        indices.emplace_back(pMesh->mFaces[i].mIndices[2]);
    }

    AddBind(std::make_unique<VertexBuffer>(ghs, vb));
    AddIndexBind(std::make_unique<IndexBuffer>(ghs, indices));

    auto vs = std::make_unique<VertexShader>(ghs, L"PhongVS.cso");
    auto pvs = vs->getByteCode();
    AddBind(std::move(vs));
    AddBind(std::make_unique<PixelShader>(ghs, L"PhongPS.cso"));


    AddBind(std::make_unique<InputLayout>(ghs, vb.getLayout().get3DLayOut(), pvs));
    AddBind(std::make_unique<PrimitiveTology>(ghs, D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST));


    
    }

    DirectX::XMFLOAT3A color{ cdist(mt), cdist(mt) , cdist(mt) };


    struct Objec
    {
        DirectX::XMFLOAT3A materiaColor = { 0.5f, 0.0f, 0.0f };
        DirectX::XMFLOAT3A speculerColor = { 1.0f, 1.0f, 1.0f };
        DirectX::XMFLOAT3A speculerIndensy = { 1.0f, 1.0f, 1.0f };
    };

    Objec ob;
    ob.materiaColor = color;
    addBind(std::make_unique<PixelConstantsBuffer<Objec>>(ghs, ob, 1));

    addBind(std::make_unique<Transform>(ghs, *this));
}

void AssTest::update(float dt) noexcept
{
    roll += droll * dt;
    pitch += dpitch * dt;
    yaw += dyaw * dt;
    theta += dtheta * dt;
    phi += dphi * dt;
    chi += dchi * dt;
}

DirectX::XMMATRIX AssTest::getMatrix() const noexcept
{
    return DirectX::XMMatrixRotationRollPitchYaw(pitch, yaw, roll) *
        DirectX::XMMatrixTranslation(r, 0.0f, 0.0f) *
        DirectX::XMMatrixRotationRollPitchYaw(theta, phi, chi);
}