#include "Transform.h"

Transform::Transform(Graphics& ghs, Drawable& p)
	: parent(p), vcb(ghs)
{
	
}

void Transform::bind(Graphics& ghs)
{
	vcb.update(ghs, parent.getMatrix() * ghs.getProjection());

	vcb.bind(ghs);
}
