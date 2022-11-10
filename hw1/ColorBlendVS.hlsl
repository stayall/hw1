struct Vsout
{
	float4 color : Color;
	float4 position : SV_Position;
};

cbuffer cb1
{
	matrix transform;
};

Vsout main( float3 pos : Position, float4 color : Color ) 
{
	Vsout vo;
	vo.color = color;
    vo.position = mul(transform, float4(pos, 1.0f));
	return vo;
}