SamplerState ObjSamplerState;
Texture2D ObjTexture;

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
	input.Nor = normalize(input.Nor);
	
	float4 color = difColor;

	if (hasTexture == true)
		color = ObjTexture.Sample(ObjSamplerState, input.uv);

	return color;
};