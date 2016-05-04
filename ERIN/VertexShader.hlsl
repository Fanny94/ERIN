struct VS_IN
{
	float3 Pos : POSITION;
	float3 Nor: NORMAL;
	float2 uv : UV;
};

struct VS_OUT
{
	float4 Pos : SV_POSITION;
	float4 WPos : POSITION;
	float4 Nor: NORMAL;
	float2 uv : UV;
	float4 CamPos :POSITION1;
};

cbuffer MATRICES:register(b0)
{
	matrix worldViewProj;
	matrix world;
	matrix view;
	matrix projection;
	float4 camPos;
};

VS_OUT VS_main(VS_IN input)
{
	VS_OUT output = (VS_OUT)0;

	output.Pos = mul(float4(input.Pos, 1), worldViewProj);
	output.WPos = mul(float4(input.Pos, 1), world);
	output.Nor = mul(float4(input.Nor, 0), world);
	output.uv = input.uv;
	output.CamPos = mul(float4(input.Pos, 1), camPos);

	return output;
}