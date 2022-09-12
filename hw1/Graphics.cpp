#include "Graphics.h"
#include "Window.h"
#include <d3dcompiler.h>

#pragma comment(lib, "d3dcompiler.lib")

namespace wrl = Microsoft::WRL;

Graphics::Graphics(HWND hWnd)
{
    DXGI_SWAP_CHAIN_DESC sd;
    memset(reinterpret_cast<void*>(&sd), 0, sizeof(sd));
    sd.OutputWindow = hWnd;
    sd.BufferCount = 1;
    sd.Windowed = TRUE;
    sd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
    sd.BufferDesc.Format = DXGI_FORMAT_B8G8R8A8_UNORM;
    sd.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
    sd.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
    sd.SampleDesc.Count = 1;
    sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    


	D3D_FEATURE_LEVEL level[] =
    {
        D3D_FEATURE_LEVEL_11_0,
        D3D_FEATURE_LEVEL_10_1,
        D3D_FEATURE_LEVEL_10_0,
        D3D_FEATURE_LEVEL_9_3,
        D3D_FEATURE_LEVEL_9_2,
        D3D_FEATURE_LEVEL_9_1,
    };
    THROW_IF_FILUIED(D3D11CreateDeviceAndSwapChain(nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr, 0, nullptr, 0, D3D11_SDK_VERSION,
        &sd, &swapChain, &device, nullptr, &context));

    wrl::ComPtr<ID3D11Resource > pBuffer;
    THROW_IF_FILUIED(swapChain->GetBuffer(0, __uuidof(ID3D11Resource), &pBuffer));
    THROW_IF_FILUIED(device->CreateRenderTargetView(pBuffer.Get(), nullptr, &targetView));

    D3D11_VIEWPORT dp = {};
    dp.TopLeftX = 0;
    dp.TopLeftY = 0;
    dp.Width = 800;
    dp.Height = 800;
    dp.MinDepth = 0;
    dp.MaxDepth = 1;
    context->RSSetViewports(1u, &dp);

    context->OMSetRenderTargets(1u, targetView.GetAddressOf(), nullptr);
  
}



void Graphics::clearColor(const float red, const float green, const float blue)
{
    const FLOAT color[] = { red, green, blue, 1.0f };
    context->ClearRenderTargetView(targetView.Get(), color);
}

void Graphics::draTrigger(float angle)
{
    /* struct Vertex
     {
         struct Position
         {
             float x;
             float y;
         }pos;

         struct Color
         {
             unsigned char r;
             unsigned char g;
             unsigned char b;
             unsigned char a;

         }color;
     };

     Vertex ves[] =
     {
         {0.0f, 0.5f, 255, 255, 0, 1},
         {0.5f, -0.5f, 255, 0, 255, 1},
         {-0.5f, -0.5f, 0, 255, 255, 1}
         ,
         {0.0f, 0.5f, 255, 255, 0, 1},
         {-0.5f, -0.5f, 255, 0, 255, 1},
         {-0.3f, 0.3f, 0, 255, 255, 1}
         ,
         {0.0f, 0.5f, 255, 255, 0, 1},
         {0.3f, 0.3f, 255, 0, 255, 1},
         {0.5f, -0.5f, 0, 255, 255, 1}
         ,
         {0.0f, -0.8f, 255, 255, 0, 1},
         {-0.5f, -0.5f, 0, 255, 255, 1},
         {0.5f, -0.5f, 255, 0, 255, 1}
     };

     wrl::ComPtr<ID3D11Buffer> pBuffer;
     D3D11_BUFFER_DESC bd = {};
     bd.ByteWidth = sizeof(ves);
     bd.Usage = D3D11_USAGE_DEFAULT;
     bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
     bd.CPUAccessFlags = 0;
     bd.MiscFlags = 0;
     bd.StructureByteStride = sizeof(Vertex);

     D3D11_SUBRESOURCE_DATA sd = {};
     sd.pSysMem = ves;
     THROW_IF_FILUIED(device->CreateBuffer(&bd, &sd, &pBuffer));
     //Fiexd: set maroc to check error
     UINT Strides = sizeof(Vertex);
     UINT Offsets = 0u;
     context->IASetVertexBuffers(0u, 1u, pBuffer.GetAddressOf(), &Strides, &Offsets);
     context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);


     wrl::ComPtr<ID3DBlob> blob;

     wrl::ComPtr<ID3D11VertexShader > vs;
     THROW_IF_FILUIED(D3DReadFileToBlob(L"VertexShader.cso", &blob));
     THROW_IF_FILUIED(device->CreateVertexShader(blob->GetBufferPointer(), blob->GetBufferSize(), nullptr, &vs));
     context->VSSetShader(vs.Get(), nullptr, 0u);

     wrl::ComPtr<ID3D11InputLayout> layout;
     D3D11_INPUT_ELEMENT_DESC ed[] = {
         {"Position", 0u, DXGI_FORMAT_R32G32_FLOAT, 0u, 0u, D3D11_INPUT_PER_VERTEX_DATA, 0},
         {"Color", 0u, DXGI_FORMAT_R8G8B8A8_UNORM, 0u, sizeof(Vertex::Position),  D3D11_INPUT_PER_VERTEX_DATA, 0}
     };

     THROW_IF_FILUIED(device->CreateInputLayout(ed, std::size(ed), blob->GetBufferPointer(), blob->GetBufferSize(), &layout));
     context->IASetInputLayout(layout.Get());

     wrl::ComPtr<ID3D11PixelShader > ps;
     THROW_IF_FILUIED(D3DReadFileToBlob(L"PixelShader.cso", &blob));
     THROW_IF_FILUIED(device->CreatePixelShader(blob->GetBufferPointer(), blob->GetBufferSize(), nullptr, &ps));
     context->PSSetShader(ps.Get(), nullptr, 0u);





     D3D11_VIEWPORT viewport;
     viewport.Width = 800;
     viewport.Height = 600;
     viewport.TopLeftX = 0;
     viewport.TopLeftY = 0;
     viewport.MinDepth = 0;
     viewport.MaxDepth = 1;
     context->RSSetViewports(1u, &viewport);

     context->OMSetRenderTargets(1u, targetView.GetAddressOf(), nullptr);

     context->Draw(std::size(ves), 0u); */

    struct Vertex
    {
        struct Position
        {
            float x;
            float y;
        }pos;

        struct Color
        {
            unsigned char r;
            unsigned char g;
            unsigned char b;
            unsigned char a;

        }color;
    };

    Vertex ves[] =
    {
        {0.0f, 0.5f, 255, 255, 0, 1},
        {0.5f, -0.5f, 255, 0, 255, 1},
        {-0.5f, -0.5f, 0, 255, 255, 1},
        {-0.3f, 0.3f, 0, 255, 255, 1},
        {0.3f, 0.3f, 255, 0, 255, 1},
        {0.0f, -0.8f, 255, 255, 0, 1}
    };

    wrl::ComPtr<ID3D11Buffer> pBuffer;
    D3D11_BUFFER_DESC bd = {};
    bd.ByteWidth = sizeof(ves);
    bd.Usage = D3D11_USAGE_DEFAULT;
    bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
    bd.CPUAccessFlags = 0;
    bd.MiscFlags = 0;
    bd.StructureByteStride = sizeof(Vertex);

    D3D11_SUBRESOURCE_DATA sd = {};
    sd.pSysMem = ves;
    THROW_IF_FILUIED(device->CreateBuffer(&bd, &sd, &pBuffer));
    //Fiexd: set maroc to check error 
    UINT Strides = sizeof(Vertex);
    UINT Offsets = 0u;
    context->IASetVertexBuffers(0u, 1u, pBuffer.GetAddressOf(), &Strides, &Offsets);

    UINT ices[] =
    {
        0, 1, 2,
        0, 2, 3,
        0, 4, 1,
        2, 1, 5
    };

    wrl::ComPtr<ID3D11Buffer> pIndexBuffer;
    bd = {};
    bd.ByteWidth = sizeof(ices);
    bd.Usage = D3D11_USAGE_DEFAULT;
    bd.BindFlags = D3D11_BIND_INDEX_BUFFER;
    bd.CPUAccessFlags = 0;
    bd.MiscFlags = 0;
    bd.StructureByteStride = sizeof(UINT);

    sd = {};
    sd.pSysMem = ices;
    THROW_IF_FILUIED(device->CreateBuffer(&bd, &sd, &pIndexBuffer));
    context->IASetIndexBuffer(pIndexBuffer.Get(), DXGI_FORMAT_R32_UINT, 0u);

    context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

    wrl::ComPtr<ID3DBlob> blob;

    wrl::ComPtr<ID3D11VertexShader> vs;
    D3DReadFileToBlob(L"VertexShader.cso", &blob);

    THROW_IF_FILUIED(device->CreateVertexShader(blob->GetBufferPointer(), blob->GetBufferSize(), nullptr, &vs));
    context->VSSetShader(vs.Get(), nullptr, 0);

    wrl::ComPtr<ID3D11InputLayout> layout;
    D3D11_INPUT_ELEMENT_DESC ed[] = {
        {"Position", 0u, DXGI_FORMAT_R32G32_FLOAT, 0u, 0u, D3D11_INPUT_PER_VERTEX_DATA, 0},
        {"Color", 0u, DXGI_FORMAT_R8G8B8A8_UNORM, 0u, sizeof(Vertex::Position),  D3D11_INPUT_PER_VERTEX_DATA, 0}
    };
    THROW_IF_FILUIED(device->CreateInputLayout(ed, std::size(ed), blob->GetBufferPointer(), blob->GetBufferSize(), &layout));
    context->IASetInputLayout(layout.Get());

    wrl::ComPtr<ID3D11PixelShader> ps;
    THROW_IF_FILUIED(D3DReadFileToBlob(L"PixelShader.cso", &blob));
    THROW_IF_FILUIED(device->CreatePixelShader(blob->GetBufferPointer(), blob->GetBufferSize(), nullptr, &ps));
    context->PSSetShader(ps.Get(), nullptr, 0u);

    struct ConstBuffer
    {
        struct
        {
            float element[4][4];
        }transform;
    };

    const ConstBuffer cb =
    {
        cos(angle), -sin(angle), 0.0f, 0.0f,
        sin(angle), cos(angle), 0.0f, 0.0f,
        0.0f, 0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 1.0f
    };

    wrl::ComPtr<ID3D11Buffer> cbf;

    D3D11_BUFFER_DESC cbd = {};
    cbd.ByteWidth = sizeof(cb);
    cbd.Usage = D3D11_USAGE_DYNAMIC;
    cbd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
    cbd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
    cbd.MiscFlags = 0;
    D3D11_SUBRESOURCE_DATA csd = {};
    csd.pSysMem = &cb;

    device->CreateBuffer(&cbd, &csd, &cbf);

    context->VSSetConstantBuffers(0, 1, cbf.GetAddressOf());

    D3D11_VIEWPORT dp = {};
    dp.TopLeftX = 0;
    dp.TopLeftY = 0;
    dp.Width = 800;
    dp.Height = 800;
    dp.MinDepth = 0;
    dp.MaxDepth = 1;
    context->RSSetViewports(1u, &dp);

    context->OMSetRenderTargets(1u, targetView.GetAddressOf(), nullptr);
    context->DrawIndexed(std::size(ices), 0, 0);
}

void Graphics::drawIndex(size_t ic) noexcept
{
    context->DrawIndexed(ic, 0u, 0u);
}

void Graphics::swapBuffer()
{
     swapChain->Present(1u, 0u);
}

DirectX::FXMMATRIX Graphics::getProjection() const noexcept
{
    return DirectX::FXMMATRIX { 3/4, 0, 0.0f, 0.0f,
                    0.0f, 1.0f, 0.0f, 0.0f,
            0.0f, 0.0f, 1.0f, 0.0f,
            0.0f, 0.0f, 0.0f, 1.0f };
}
