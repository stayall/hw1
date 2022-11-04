#pragma once

#include "SliderSphere.h"
#include "Graphics.h"
#include "ConstantBuffer.h"

class PiontLight
{
public:
	PiontLight(Graphics& ghs, float reduis = 0.5f);

	__declspec(align(16)) struct LightPos
	{
		alignas(16) DirectX::XMFLOAT3 pos = { 0.0f, 0.0f, 0.0f };
		alignas(16) DirectX::XMFLOAT3 ambient = { 0.1f, 0.1f, 0.1f };
		alignas(16) DirectX::XMFLOAT3  indensy = { 1.0f, 1.0f, 1.0f };
		alignas(16) DirectX::XMFLOAT3 kd = { 1.0f, 1.0f, 1.0f };
		float consAttr = 1.0;
		float linerAttr = 0.045f;
		float quaAttr = 0.0075f;
	};
	void lightEditor();

	void DrawCall(Graphics& ghs);
	void Bind(Graphics& ghs);

	void reset();
private:
	LightPos cbuf;
	DirectX::XMFLOAT3 pos ;
	mutable SliderSphere mesh;
	PixelConstantsBuffer<LightPos> cuf;
};

