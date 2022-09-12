#include "Graphics.h"
#include "Window.h"
#include <d3dcompiler.h>
#include <DirectXMath.h>

#pragma comment(lib, "d3dcompiler.lib")

namespace wrl = Microsoft::WRL;

Graphics::Graphics(HWND hWnd)
{
    DXGI_SWAP_CHAIN_DESC sd = {};
    sd.BufferDesc.Width = 0;
    sd.BufferDesc.Height = 0;
    sd.BufferDesc.Format = DXGI_FORMAT_B8G8R8A8_UNORM;
    sd.BufferDesc.RefreshRate.Numerator = 0;
    sd.BufferDesc.RefreshRate.Denominator = 0;
    sd.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
    sd.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
    sd.SampleDesc.Count = 1;
    sd.SampleDesc.Quality = 0;
    sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    sd.BufferCount = 1;
    sd.OutputWindow = hWnd;
    sd.Windowed = TRUE;
    sd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
    sd.Flags = 0;


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

    // create depth stensil state
    D3D11_DEPTH_STENCIL_DESC dsDesc = {};
    dsDesc.DepthEnable = TRUE;
    dsDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
    dsDesc.DepthFunc = D3D11_COMPARISON_LESS;
    wrl::ComPtr<ID3D11DepthStencilState> pDSState;
    THROW_IF_FILUIED(device->CreateDepthStencilState(&dsDesc, &pDSState));

    // bind depth state
    context->OMSetDepthStencilState(pDSState.Get(), 1u);

    // create depth stensil texture
    wrl::ComPtr<ID3D11Texture2D> pDepthStencil;
    D3D11_TEXTURE2D_DESC descDepth = {};
    descDepth.Width = 800u;
    descDepth.Height = 600u;
    descDepth.MipLevels = 1u;
    descDepth.ArraySize = 1u;
    descDepth.Format = DXGI_FORMAT_D32_FLOAT;
    descDepth.SampleDesc.Count = 1u;
    descDepth.SampleDesc.Quality = 0u;
    descDepth.Usage = D3D11_USAGE_DEFAULT;
    descDepth.BindFlags = D3D11_BIND_DEPTH_STENCIL;
    THROW_IF_FILUIED(device->CreateTexture2D(&descDepth, nullptr, &pDepthStencil));

    // create view of depth stensil texture
    D3D11_DEPTH_STENCIL_VIEW_DESC descDSV = {};
    descDSV.Format = DXGI_FORMAT_D32_FLOAT;
    descDSV.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
    descDSV.Texture2D.MipSlice = 0u;
    THROW_IF_FILUIED(device->CreateDepthStencilView(
        pDepthStencil.Get(), &descDSV, &pDSV
    ));

    D3D11_VIEWPORT dp = {};
    dp.TopLeftX = 0;
    dp.TopLeftY = 0;
    dp.Width = 800;
    dp.Height = 600;
    dp.MinDepth = 0;
    dp.MaxDepth = 1;
    context->RSSetViewports(1u, &dp);

    // bind depth stensil view to OM
    context->OMSetRenderTargets(1u, targetView.GetAddressOf(), pDSV.Get());

   // context->OMSetRenderTargets(1u, targetView.GetAddressOf(), nullptr);
  
}



void Graphics::clearColor(const float red, const float green, const float blue)
{
    const FLOAT color[] = { red, green, blue, 1.0f };
    context->ClearRenderTargetView(targetView.Get(), color);
    context->ClearDepthStencilView(pDSV.Get(), D3D11_CLEAR_DEPTH, 1.0f, 0u);
}

void Graphics::draTrigger(float angle, float x, float y)
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
            float z;
        }pos;
    };

    Vertex ves[] =
    {
           { -1.0f,-1.0f,-1.0f },
        { 1.0f,-1.0f,-1.0f },
        { -1.0f,1.0f,-1.0f },
        { 1.0f,1.0f,-1.0f },
        { -1.0f,-1.0f,1.0f },
        { 1.0f,-1.0f,1.0f },
        { -1.0f,1.0f,1.0f },
        { 1.0f,1.0f,1.0f },
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

    const unsigned short ices[] =
    {
        0,2,1, 2,3,1,
        1,3,5, 3,7,5,
        2,6,3, 3,6,7,
        4,5,7, 4,7,6,
        0,4,2, 2,4,6,
        0,1,4, 1,5,4
    };

    wrl::ComPtr<ID3D11Buffer> pIndexBuffer;
    bd = {};
    bd.ByteWidth = sizeof(ices);
    bd.Usage = D3D11_USAGE_DEFAULT;
    bd.BindFlags = D3D11_BIND_INDEX_BUFFER;
    bd.CPUAccessFlags = 0;
    bd.MiscFlags = 0;
    bd.StructureByteStride = sizeof(const unsigned short);

    sd = {};
    sd.pSysMem = ices;
    THROW_IF_FILUIED(device->CreateBuffer(&bd, &sd, &pIndexBuffer));
    context->IASetIndexBuffer(pIndexBuffer.Get(), DXGI_FORMAT_R16_UINT, 0u);

    context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

    wrl::ComPtr<ID3DBlob> blob;

    wrl::ComPtr<ID3D11VertexShader> vs;
    D3DReadFileToBlob(L"VertexShader.cso", &blob);

    THROW_IF_FILUIED(device->CreateVertexShader(blob->GetBufferPointer(), blob->GetBufferSize(), nullptr, &vs));
    context->VSSetShader(vs.Get(), nullptr, 0);

    wrl::ComPtr<ID3D11InputLayout> layout;
    D3D11_INPUT_ELEMENT_DESC ed[] = {
        {"Position", 0u, DXGI_FORMAT_R32G32B32_FLOAT, 0u, 0u, D3D11_INPUT_PER_VERTEX_DATA, 0}
    };
    THROW_IF_FILUIED(device->CreateInputLayout(ed, std::size(ed), blob->GetBufferPointer(), blob->GetBufferSize(), &layout));
    context->IASetInputLayout(layout.Get());

    wrl::ComPtr<ID3D11PixelShader> ps;
    THROW_IF_FILUIED(D3DReadFileToBlob(L"PixelShader.cso", &blob));
    THROW_IF_FILUIED(device->CreatePixelShader(blob->GetBufferPointer(), blob->GetBufferSize(), nullptr, &ps));
    context->PSSetShader(ps.Get(), nullptr, 0u);

    struct ConstBuffer
    {
       
        DirectX::XMMATRIX xm;
    };

    const ConstBuffer cb = {
        {
        DirectX::XMMatrixTranspose(
        DirectX::XMMatrixRotationZ(angle) *
        DirectX::XMMatrixRotationX(angle) *
            // DirectX::XMMatrixRotationY(angle) *
             //DirectX::XMMatrixScaling(1.0f,3.0f / 4.0f, 0.25) *
            DirectX::XMMatrixTranslation(x, 0, 8 + y) *
           //DirectX::XMMatrixRotationX(angle)* 
            DirectX::XMMatrixPerspectiveLH(1.0f,3.0f / 4.0f,0.5f,10.0f)
                )
           }
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


    struct ConstBuffer2
    {
        struct
        {
            float r;
            float g;
            float b;
            float a;
        }color[8];
    };

    const ConstBuffer2  cb2 = {
        {
        {1.0f,0.0f,1.0f},
            {1.0f,0.0f,0.0f},
            {0.0f,1.0f,0.0f},
            {0.0f,0.0f,1.0f},
            {1.0f,1.0f,0.0f},
            {0.0f,1.0f,1.0f},
        }
    };

    wrl::ComPtr<ID3D11Buffer> pbf;

     cbd = {};
    cbd.ByteWidth = sizeof(cb2);
    cbd.Usage = D3D11_USAGE_DYNAMIC;
    cbd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
    cbd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
    cbd.MiscFlags = 0;

     csd = {};
    csd.pSysMem = &cb2;

    THROW_IF_FILUIED(device->CreateBuffer(&cbd, &csd, &pbf));

    context->PSSetConstantBuffers(0u, 1u, pbf.GetAddressOf());

  

    //context->OMSetRenderTargets(1u, targetView.GetAddressOf(), nullptr);
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

DirectX::XMMATRIX Graphics::getProjection() const noexcept
{
    return project;
}

void Graphics::setProjection( DirectX::XMMATRIX p)  noexcept
{
   
    project = p;
}
