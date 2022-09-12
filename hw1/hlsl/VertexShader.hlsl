
struct VsOut
{
	float4 color: Color;
	float4 pos: SV_Position;
};

cbuffer cBuf
{
	 matrix ts;
};

float4 main(float3 pos : Position) : SV_POSITION
{
	
	return mul( float4(pos, 1.0f), ts);
	
}