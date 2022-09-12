
struct VsOut
{
	float4 color: Color;
	float4 pos: SV_Position;
};

cbuffer cBuf
{
	matrix ts;
};

VsOut main(float2 pos : Position, float4 color : Color)
{
	VsOut vt;
	vt.pos = mul(ts, float4(pos.x, pos.y, 0, 1.0f));
	vt.color = color;
	return vt;
}