SamplerState ObjSamplerState;
Texture2D ObjTexture: register(t0);

cbuffer CustomFormat
{
	float3 diffuseColor;
	float paddingDC;
	float3 ambientColor;
	float paddingAC;
	float3 specularColor;
	float shininess;
};

struct VS_OUT
{
	float4 Pos : SV_POSITION;
	float4 WPos : POSITION;
	float3 Nor: NORMAL;
	float2 uv : UV;
	float4 CamPos :POSITION1;
};

float4 PS_main(VS_OUT input) : SV_Target
{
	float4 lightPosition = float4(0.0, 0.0, -5.0, 0.0);
	float3 lightIntensity = float3(0.9, 0.9, 0.9);

	float4 s = normalize(lightPosition - input.WPos);
	float4 v = normalize(input.CamPos - input.WPos);
	float3 r = reflect(-s, input.Nor);

	/*if (hasTexture == true)
		diffuse = ObjTexture.Sample(ObjSamplerState, input.uv).xyz;*/

	input.Nor = normalize(input.Nor);

	float3 diffuseLight = diffuseColor * max(dot(s, input.Nor), 0.0f);

	float3 ambientLight = {0.2, 0.2, 0.2};

	float3 specularLight = specularColor * pow(max(dot(r, v), 0.0f), shininess);

	float4 color = float4((lightIntensity * ( ambientLight + diffuseLight + specularLight)), 1.0f);

	return color;
};