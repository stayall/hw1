#include "Bindable.h"



ID3D11Device* Bindable::GetDevice(Graphics& ghs) noexcept
{
	return ghs.device.Get();
}

ID3D11DeviceContext* Bindable::GetContext(Graphics& ghs) noexcept
{
   
	return ghs.context.Get();
}
