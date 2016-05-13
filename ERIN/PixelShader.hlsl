Texture2D CustomTexture: register(t0);
SamplerState CustomSamplerState;

cbuffer CustomFormat
{
	float3 diffuseColor;
	float paddingDC;
	float3 ambientColor;
	float paddingAC;
	float3 specularColor;
	float shininess;
	float4 CamPos;
	int textureBool;
	float padding[3];
};

struct VS_OUT
{
	float4 Pos : SV_POSITION;
	float4 WPos : POSITION;
	float4 Nor: NORMAL;
	float2 uv : UV;

};

float4 PS_main(VS_OUT input) : SV_Target
{
	float3 diffuseLight;
	float4 lightPosition = float4(-60.0, 0.0, -60.0, 0.0);
	float3 lightIntensity = float3(0.9, 0.9, 0.9);

	float4 s = normalize(lightPosition - input.WPos);
	float4 v = normalize(CamPos - input.WPos);
	float4 r = reflect(-s, input.Nor);

	float3 diffuseMap = CustomTexture.Sample(CustomSamplerState, input.uv).xyz;

	input.Nor = normalize(input.Nor);
	if(textureBool == true)
		diffuseLight = diffuseMap * diffuseColor * max(dot(s, input.Nor), 0.0f);
	else if(textureBool == false)
		diffuseLight = diffuseColor * max(dot(s, input.Nor), 0.0f);

	float3 ambientLight = {0.2, 0.2, 0.2};

	float3 specularLight = specularColor * pow(max(dot(r, v), 0.0f), shininess);

	float4 color = float4((lightIntensity * ( ambientLight + diffuseLight /* + specularLight*/)), 1.0f);

	return color;
};