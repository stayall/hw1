
cbuffer ts
{
	matrix model;
	matrix modelviwprj;
};


struct VSout
{
	float4 worldPos : Position3D;
	float4 normal : Normal;
	float4 pos : SV_Position;
};



VSout main(float3 pos : Position3D, float3 normal : Normal)
	{
	VSout vs;
	
	vs.pos = mul(float4(pos, 1.0f), modelviwprj);
	vs.worldPos = mul(float4(pos, 1.0f), model);
	vs.normal = float4(normalize(mul(normal, (float3x3)model)), 0.0f);
	
	return vs;
}