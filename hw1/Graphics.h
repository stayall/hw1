#ifndef __GRAPHICS__H__
#define __GRAPHICS__H__
#include <d3d11.h>
#include <wrl.h>
#include <DirectXMath.h>
#include <vector>
#include "Camera.h"

#pragma comment(lib, "d3d11.lib")

class Graphics
{
	friend class Bindable;
public:
	Graphics(HWND hWnd, int width, int hight);
	Graphics(const Graphics&) = delete;
	Graphics& operator= (const Graphics&) = delete;
	~Graphics() = default;

	void clearColor(const float red, const float green, const float blue);
	void draTrigger(float angle, float x, float y);
	void drawIndex(size_t indexCount) noexcept;
	void swapBuffer();
	void beginFream(const float red, const float green, const float blue);

	DirectX::XMMATRIX getProjection() const noexcept;
	void setProjection(DirectX::XMMATRIX p)  noexcept;


	DirectX::XMMATRIX getCamera() const noexcept;
	void setCamera(DirectX::XMMATRIX p)  noexcept;

	void enableImGui();
	void disableImGui();
	bool isShowImGui();
private:
	Microsoft::WRL::ComPtr<IDXGISwapChain> swapChain;
	Microsoft::WRL::ComPtr<ID3D11Device> device;
	Microsoft::WRL::ComPtr<ID3D11DeviceContext> context;
	Microsoft::WRL::ComPtr<ID3D11RenderTargetView > targetView;
	Microsoft::WRL::ComPtr<ID3D11DepthStencilView> pDSV;
	DirectX::XMMATRIX project;
	DirectX::XMMATRIX camera;
	bool showImGui = true;
};

#endif // !__GRAPHICS__H__



