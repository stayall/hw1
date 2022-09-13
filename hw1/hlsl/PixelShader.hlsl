
cbuffer colo
{
	float4 colo[8];
};

float4 main( uint id : SV_PrimitiveID) : SV_TARGET
{
	return colo[id / 2  % 6];
}