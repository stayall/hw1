#pragma once

#include <DirectXMath.h>

class Camera
{
public:
	Camera();
	DirectX::FXMMATRIX getMatrix() const;
	void reset() noexcept;

#define XX(s) void set##s(float s) noexcept
	XX(r);
	XX(theata);
	XX(phi);
	XX(pitch);
	XX(yaw);
	XX(roll);
#undef XX

	void cameraWindowController();
private:
	float r;
	float theata;
	float phi;

	float pitch;
	float yaw;
	float roll;

};

