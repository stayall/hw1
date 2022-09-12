#ifndef __GRAPHICS__H__
#define __GRAPHICS__H__
#include <d3d11.h>
#include <wrl.h>
#include <DirectXMath.h>
#include <vector>

#pragma comment(lib, "d3d11.lib")

class Graphics
{
	friend class Bindable;
public:
	Graphics(HWND hWnd);
	Graphics(const Graphics&) = delete;
	Graphics& operator= (const Graphics&) = delete;
	~Graphics() = default;

	void clearColor(const float red, const float green, const float blue);
	void draTrigger(float angle);
	void drawIndex(size_t indexCount) noexcept;
	void swapBuffer();
	DirectX::FXMMATRIX getProjection() const noexcept;
private:
	Microsoft::WRL::ComPtr<IDXGISwapChain> swapChain;
	Microsoft::WRL::ComPtr<ID3D11Device> device;
	Microsoft::WRL::ComPtr<ID3D11DeviceContext> context;
	Microsoft::WRL::ComPtr<ID3D11RenderTargetView > targetView;
};

#endif // !__GRAPHICS__H__



