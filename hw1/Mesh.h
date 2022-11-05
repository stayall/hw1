#pragma once
#include "DrawableBase.h"
#include "BindableBase.h"
#include <assimp\scene.h>
#include <assimp\Importer.hpp>
#include <assimp\postprocess.h>
#include <DirectXMath.h>


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
public:
	Node(std::vector<Mesh*> ms, DirectX::XMMATRIX);
	void Draw(Graphics& ghs, DirectX::XMMATRIX ts) const;
private:
	void addChildNode(std::unique_ptr<Node> n);
private:
	std::vector<std::unique_ptr<Node>> childNode;
	std::vector<Mesh*> meshs;
	DirectX::XMFLOAT4X4 transform;
};

class Model
{
public:
	Model(Graphics& ghs, const char* filepath);
	void Draw(Graphics& ghs, DirectX::XMMATRIX ts) const;
private:
	std::unique_ptr<Node> parseRoot(aiNode* node);
	static std::vector<std::unique_ptr<Bindable>> parseMesh(Graphics& ghs, aiMesh* mesh);
private:
	std::unique_ptr<Node> rootNode;
	std::vector<std::unique_ptr<Mesh>> meshs;
	//DirectX::XMFLOAT4X4 transform;
};