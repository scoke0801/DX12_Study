cbuffer TRANSFORM_PARAMS : register(b0)
{
	// 쉐이더에서는 column기준
	// 다렉에서는 row기준이므로, 다렉에 맞춰주도록 row_major키워드 사용
	row_major matrix matWorldViewProj;
};

cbuffer MATERIAL_PARAMS : register(b1)
{
	int iParam_0;
	int iParam_1;
	int iParam_2;
	int iParam_3;
	int iParam_4;

	float fParam_0;
	float fParam_1;
	float fParam_2;
	float fParam_3;
	float fParam_4;
};

Texture2D tex_0 : register(t0);
Texture2D tex_1 : register(t1);
Texture2D tex_2 : register(t2);
Texture2D tex_3 : register(t3);
Texture2D tex_4 : register(t4);

SamplerState sam_0 : register(s0);

struct VS_IN
{
	float3 pos		: POSITION;
	float4 color	: COLOR;
	float2 uv		: TEXCOORD;
};

struct VS_OUT
{
	float4 pos		: SV_Position;
	float4 color	: COLOR;
	float2 uv		: TEXCOORD;
};

VS_OUT VS_Main(VS_IN input)
{
	VS_OUT output = (VS_OUT)0;

	output.pos = mul( float4(input.pos, 1.f), matWorldViewProj);
	output.color = input.color; 
	output.uv = input.uv;

	return output;
}

float4 PS_Main(VS_OUT input) : SV_Target
{
	float4 color = tex_0.Sample(sam_0, input.uv);

    return color;
}