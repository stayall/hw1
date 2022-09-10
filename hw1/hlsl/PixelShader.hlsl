cbuffer color
{
	float4 face_corlor[6];
};

float4 main(float4 color : Color) : SV_TARGET
{
	return  color;
	//return face_corlor[tid / 2];
}