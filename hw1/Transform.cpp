#include "Transform.h"

Transform::Transform(Graphics& ghs, Drawable &p, UINT slot)
	: parent(p), vcb(ghs, slot)
{
}

void Transform::bind(Graphics& ghs)
{
	Trans ts = {
		DirectX::XMMatrixTranspose(parent.getMatrix() * ghs.getCamera()),
		DirectX::XMMatrixTranspose(parent.getMatrix() * ghs.getCamera() * ghs.getProjection())
	};
	
	vcb.update( ghs, ts);

	vcb.bind(ghs);
}
