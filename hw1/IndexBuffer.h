#pragma once
#include "Bindable.h"
#include <vector>

class IndexBuffer :
    public Bindable
{
public:
    IndexBuffer(Graphics& ghs, const std::vector<unsigned short>& idx);
    void bind(Graphics& ghs) override;
    size_t getCount() const noexcept;

private:
    Microsoft::WRL::ComPtr<ID3D11Buffer> pIndexBuffer;
    size_t count;
};

