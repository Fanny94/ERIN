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
	
	float4 color = (0.0f, 0.0f, 1.0f, 0.0f);

	return color;
};