cbuffer LightPos
{
	float3 lightpos;
	float3 ambient = { 0.1f, 0.1f, 0.1f };
// const float3 diffuse = float3(0.3f, 0.3f, 0.3f);
	float3  indensy = float3(1.0f, 1.0f, 1.0f);
	float3 kd = float3(1.0f, 1.0f, 1.0f);
	float consAttr = 1.0;
	float linerAttr = 0.045f;
	float quaAttr = 0.0075f;
};

cbuffer Objec
{
    float3 materiaColor;
    float3 speculerColor;
    float3 speculerIndensy;
};


static float powCount = 5.0f;

float4 main(float4 worldPos : Position3D, float4 normal : Normal) : SV_TARGET
{
	float4 pos ={ lightpos, 1.0f };
	float len = distance(worldPos, pos);
	float4 dirPos = (pos -  worldPos) / len;
	float attr = 1 / (consAttr + linerAttr * len + quaAttr * len * len);
	float3 diffuse = kd * attr * indensy * max(dot(dirPos, normal), 0.0f);
	
    float3 r = normal * dot(normal, pos - worldPos) * 2 - (pos - worldPos);
    float3 speculer = indensy * kd * speculerColor * speculerIndensy * attr * pow(max(dot(normalize(-r), normalize((float3)worldPos)), 0.0f), powCount);
    return float4(saturate(ambient + diffuse + speculer) * materiaColor, 1.0f);
}