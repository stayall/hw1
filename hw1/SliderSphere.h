#pragma once
#include "Sphere.h"
#include "Graphics.h"
#include "DrawableBase.h"

class SliderSphere : public  DrawableBase<SliderSphere>
{
public:
    SliderSphere(Graphics& ghs, float raduis = 0.5f);

    virtual DirectX::XMMATRIX getMatrix() const noexcept ;
    virtual void update(float dt) noexcept ;
    void setPos(DirectX::XMFLOAT3 pos);

private:

private:
    DirectX::XMFLOAT3 pos = { 0.0f, 0.0f, 0.0f };
};

