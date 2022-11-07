#pragma once
#include "DrawableBase.h"
#include "BindableBase.h"
#include <assimp\scene.h>
#include <assimp\Importer.hpp>
#include <assimp\postprocess.h>
#include <DirectXMath.h>
#include <optional>

class Mesh : public DrawableBase<Mesh>
{
public:
	Mesh(Graphics& ghs, std::vector<std::unique_ptr<Bindable>> binds);
	void Draw(Graphics &ghs, DirectX::FXMMATRIX ts) const;
	virtual DirectX::XMMATRIX getMatrix() const noexcept;

private:
	mutable DirectX::XMFLOAT4X4 transform;
};

class Node
{
	friend class Model;
	friend class ModelWindow;
public:
	Node(const std::string &nodeName, std::vector<Mesh*> ms, DirectX::XMMATRIX);
	void Draw(Graphics& ghs, DirectX::XMMATRIX ts) const;
	void RenderTree() const;
private:
	void addChildNode(std::unique_ptr<Node> n);
private:
	std::string name;
	std::vector<std::unique_ptr<Node>> childNode;
	std::vector<Mesh*> meshs;
	DirectX::XMFLOAT4X4 transform;
};

class Model
{
public:
	Model(Graphics& ghs, const char* filepath);
	void Draw(Graphics& ghs, DirectX::XMMATRIX ts) const;
	void ShowModelWindow(const char* windowName = nullptr);
	~Model();
private:
	std::unique_ptr<Node> parseRoot(aiNode* node);
	static std::vector<std::unique_ptr<Bindable>> parseMesh(Graphics& ghs, aiMesh* mesh);

private:
	struct
	{
		float x = 0.0f;
		float y = 0.0f;
		float z = 0.0f;
		float roll = 0.0f;
		float pitch = 0.0f;
		float yaw = 0.0f;
		float theta = 0.0f;
		float phi = 0.0f;
		float chi = 0.0f;
	}pos;
	std::unique_ptr<Node> rootNode;
	std::vector<std::unique_ptr<Mesh>> meshs;
	std::unique_ptr<class ModelWindow> wnd;
	//DirectX::XMFLOAT4X4 transform;
};