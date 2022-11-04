
cbuffer colo
{
	float4 colo[8];
};

float4 main() : SV_TARGET
{
	//return float4(1, 1, 1,1);
	return colo[0 / 2  % 8];
}