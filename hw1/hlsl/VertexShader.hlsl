
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
	VsOut vs;

	vs.pos = float4(pos.x, pos.y, 0, 0);
	vs.color = color;
	return vs;
	//return mul(ts, float4(pos.x, pos.y, pos.z, 1.0f));
	
	
}