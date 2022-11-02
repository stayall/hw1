#pragma once
#include "testGraphics.h"
#include <random>

class Box : public TestGraphics<Box>
{
public:
	Box(Graphics &ghs,
		std::mt19937 &mt, 
		std::uniform_real_distribution<float> &adist,
		std::uniform_real_distribution<float> &ddist,
		std::uniform_real_distribution<float> &odist,
		std::uniform_real_distribution<float> &rdist,
		std::uniform_real_distribution<float>& cdist
		);
	virtual void update(float dt) noexcept override;

	virtual DirectX::XMMATRIX getMatrix() const noexcept override;

	bool spawnBoxCountroller(int i, Graphics& ghs);
	void positionReset();

	void syncMaterial(Graphics& ghs);

private:
	struct Objec
	{
		DirectX::XMFLOAT3A materiaColor = { 0.5f, 0.0f, 0.0f };
		DirectX::XMFLOAT3A speculerColor = { 1.0f, 1.0f, 1.0f };
		DirectX::XMFLOAT3A speculerIndensy = { 1.0f, 1.0f, 1.0f };
	};

private:

	DirectX::XMFLOAT3A materiaColor;
	Objec ob;
};

