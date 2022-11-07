#include "Mesh.h"
#include "Vertex.h"
#include <memory>
#include "imgui\imgui.h"

Mesh::Mesh(Graphics& ghs, std::vector<std::unique_ptr<Bindable>> binds)
{
	if (!isInit())
	{
		AddBind(std::make_unique<PrimitiveTology>(ghs, D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST));
	}

	for (auto& b : binds)
	{

		if (auto pi = dynamic_cast<IndexBuffer*>(b.get()))
		{
			addIndexBind(std::unique_ptr<IndexBuffer>{ pi });
			b.release();
		}
		else
		{
			addBind(std::move(b));
		}
	}

	addBind(std::make_unique<Transform>(ghs, *this));
}

void Mesh::Draw(Graphics& ghs, DirectX::FXMMATRIX ts) const
{
	DirectX::XMStoreFloat4x4(&transform, ts);
	Drawable::drawCall(ghs);
}

DirectX::XMMATRIX Mesh::getMatrix() const noexcept
{
	return DirectX::XMLoadFloat4x4(&transform);
}

Node::Node(const std::string& nodeName, std::vector<Mesh*> ms, DirectX::XMMATRIX ts)
	: name(nodeName), meshs(std::move(ms))
{
	DirectX::XMStoreFloat4x4(&transform, ts);
}

void Node::Draw(Graphics& ghs, DirectX::XMMATRIX ts) const
{
	auto build = DirectX::XMLoadFloat4x4(&transform) * ts;
	for (const auto& m : meshs)
	{
		m->Draw(ghs, build);
	}
	for (const auto& n : childNode)
	{
		n->Draw(ghs, build);
	}
}

void Node::RenderTree() const
{
	if (ImGui::TreeNode(name.c_str()))
	{
		for (const auto& node : childNode)
		{
			node->RenderTree();
		}

		ImGui::TreePop();
	}
}

void Node::addChildNode(std::unique_ptr<Node> n)
{
	assert(n.get() != nullptr);
	childNode.push_back(std::move(n));
}

Model::Model(Graphics& ghs, const char* filepath)

{
	using namespace Assimp;

	Importer importer;
	const aiScene* scene = importer.ReadFile(filepath, aiProcess_JoinIdenticalVertices | \
		aiProcess_Triangulate);

	for (size_t i = 0; i < scene->mNumMeshes; i++)
	{
		meshs.push_back(std::make_unique<Mesh>(ghs, parseMesh(ghs, scene->mMeshes[i])));
	}

	rootNode = parseRoot(scene->mRootNode);


}

void Model::Draw(Graphics& ghs, DirectX::XMMATRIX ts) const
{
	DirectX::XMMATRIX build = DirectX::XMMatrixRotationRollPitchYaw(pos.pitch, pos.yaw, pos.roll) * 
		DirectX::XMMatrixTranslation(pos.x, pos.y, pos.z);
	rootNode->Draw(ghs, build);
}

void Model::ShowModelWindow(const char* windowName)
{
	std::string wn = windowName ? windowName : "Model";
	if (ImGui::Begin(wn.c_str()))
	{
		ImGui::Columns(2, nullptr);

		ImGui::Text("Herirachy");

		rootNode->RenderTree();

		ImGui::NextColumn();
		ImGui::Text("Position");
#define XX(T) \
		ImGui::SliderFloat(#T, &##T, 0.0, 20.0f);
		XX(pos.x);
		XX(pos.y);
		XX(pos.z);

		ImGui::Text("Queration");
		XX(pos.pitch);
		XX(pos.yaw);
		XX(pos.roll);
#undef XX
	}
	ImGui::End();
}

std::unique_ptr<Node> Model::parseRoot(aiNode* node)
{
	auto ts = DirectX::XMMatrixTranspose(DirectX::XMLoadFloat4x4(reinterpret_cast<DirectX::XMFLOAT4X4*>(&node->mTransformation)));

	std::vector<Mesh*> m;
	for (size_t i = 0; i < node->mNumMeshes; i++)
	{
		const auto index = node->mMeshes[i];
		m.push_back(meshs.at(index).get());
	}
	const char* nodeName = node->mName.data;

	auto root = std::make_unique<Node>(nodeName, m, ts);
	for (size_t i = 0; i < node->mNumChildren; i++)
	{
		root->addChildNode(parseRoot(node->mChildren[i]));
	}
	return root;
}

std::vector<std::unique_ptr<Bindable>> Model::parseMesh(Graphics& ghs, aiMesh* mesh)
{

	using namespace DirectX;
	Proc::VertexLayout vl;
	vl.append(Proc::VertexLayout::ElementType::VertexPosition3D);
	vl.append(Proc::VertexLayout::ElementType::VertexNormal);
	Proc::VertexBuferr vb(std::move(vl));

	for (size_t i = 0; i < mesh->mNumVertices; i++)
	{
		vb.emplaceBack(*reinterpret_cast<XMFLOAT3*>(&mesh->mVertices[i]),
			*reinterpret_cast<XMFLOAT3*>(&mesh->mNormals[i]));
	}

	std::vector<unsigned short> indecies;
	for (size_t i = 0; i < mesh->mNumFaces; i++)
	{
		const auto& face = mesh->mFaces[i];
		indecies.emplace_back(face.mIndices[0]);
		indecies.emplace_back(face.mIndices[1]);
		indecies.emplace_back(face.mIndices[2]);
	}

	std::vector<std::unique_ptr<Bindable>> binds;

	binds.push_back(std::make_unique<VertexBuffer>(ghs, vb));
	binds.push_back(std::make_unique<IndexBuffer>(ghs, indecies));
	auto vs = std::make_unique<VertexShader>(ghs, L"PhongVS.cso");
	auto pvs = vs->getByteCode();
	binds.push_back(std::move(vs));
	binds.push_back(std::make_unique<PixelShader>(ghs, L"PhongPS.cso"));
	binds.push_back(std::make_unique<InputLayout>(ghs, vb.getLayout().get3DLayOut(), pvs));

	struct Objec
	{
		DirectX::XMFLOAT3A materiaColor = { 0.5f, 0.0f, 0.0f };
		DirectX::XMFLOAT3A speculerColor = { 1.0f, 1.0f, 1.0f };
		DirectX::XMFLOAT3A speculerIndensy = { 1.0f, 1.0f, 1.0f };
	};
	Objec ob;
	binds.push_back(std::make_unique<PixelConstantsBuffer<Objec>>(ghs, ob, 1));
	return std::move(binds);
}
