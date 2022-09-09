#pragma once
#include "Drawable.h"
#include <random>

class Box : public Drawable
{
public:
	Box(Graphics &ghs,
		std::mt19937 &mt, 
		std::uniform_real_distribution<float> &adist,
		std::uniform_real_distribution<float> &ddist,
		std::uniform_real_distribution<float> &odist,
		std::uniform_real_distribution<float> &rdist
		);
	virtual void update(float dt) noexcept override;

	virtual DirectX::XMMATRIX getMatrix() const noexcept override;

private:
	float r;
	float roll = 0.0f;
	float pitch = 0.0f;
	float yaw = 0.0f;
	float theta;
	float phi;
	float chi;

	float droll;
	float dpicth;
	float dyaw;
	float dtheta;
	float dphi;
	float dchi;
};

