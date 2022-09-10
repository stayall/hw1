
struct VsOut
{
	float4 color: Color;
	float4 pos: SV_Position;
};

cbuffer cBuf
{
	matrix ts;
};

float4 main(float3 pos : Position) : SV_Position
{
	return float4(pos.x, pos.y, 0, 0);
	return mul(ts, float4(pos.x, pos.y, pos.z, 1.0f));
	
	
}