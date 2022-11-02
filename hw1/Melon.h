#pragma once
#include "DrawableBase.h"
#include "Sphere.h"

class Melon : public DrawableBase<Melon>
{
public:
	Melon(Graphics& ghs);
	virtual void update(float dt) noexcept  override;

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
	float dpitch;
	float dyaw;
	float dtheta;
	float dphi;
	float dchi;
};

