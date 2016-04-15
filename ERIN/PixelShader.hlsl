SamplerState ObjSamplerState;
Texture2D ObjTexture: register(t0);

cbuffer OBJ
{
	float4 difColor;
	int hasTexture;
	float3 padding;
};

struct VS_OUT
{
	float4 Pos : SV_POSITION;
	float4 WPos : POSITION;
	float3 Nor: NORMAL;
	float2 uv : UV;
};

float4 PS_main(VS_OUT input) : SV_Target
{
	float4 lightPosition = float4(0.0, 0.0, 10.0, 0.0);
	float3 lightIntensity = float3(1.0, 1.0, 1.0);

	input.Nor = normalize(input.Nor);

	float4 s = normalize(lightPosition - input.WPos);

	float3 diffuse = difColor.xyz;

	if (hasTexture == true)
		diffuse = ObjTexture.Sample(ObjSamplerState, input.uv).xyz;

	float3 diffuseLight = diffuse * max(dot(s, input.Nor), 0.0f);

	float3 ambient = float3(0.2f, 0.2f, 0.2f);

	float4 color = float4((lightIntensity * (ambient + diffuseLight)), 1.0f);

	return color;
};