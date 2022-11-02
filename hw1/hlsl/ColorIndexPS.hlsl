
cbuffer colo
{
	float4 colo[8];
};

float4 main(uint id : SV_PrimitiveID) : SV_TARGET
{
	//return float4(1, 1, 1,1);
	return colo[id / 2  % 8];
}