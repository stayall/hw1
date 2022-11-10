#include "PrimitiveTology.h"

PrimitiveTology::PrimitiveTology(Graphics& ghs, const D3D11_PRIMITIVE_TOPOLOGY pt)
	: pt(pt)
{
}

void PrimitiveTology::bind(Graphics& ghs)
{
	GetContext(ghs)->IASetPrimitiveTopology(pt);
}
