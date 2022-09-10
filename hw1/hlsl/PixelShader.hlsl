cbuffer color
{
	float4 face_corlor[6];
};

float4 main() : SV_TARGET
{
	return(1.0f, 1.0f, 1.0f, 0);
	//return face_corlor[tid / 2];
}