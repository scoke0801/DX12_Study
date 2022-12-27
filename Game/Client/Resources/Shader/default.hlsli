cbuffer TEST_BO : register(b0)
{
	float4 offset0;
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

	output.pos = float4(input.pos, 1.f); 
	// output.pos += offset0;
	output.pos.x += fParam_0;
	output.pos.y += fParam_1;
	output.pos.z += fParam_2;
	
	output.color = input.color; 
	output.uv = input.uv;

	return output;
}

float4 PS_Main(VS_OUT input) : SV_Target
{
	float4 color = tex_0.Sample(sam_0, input.uv);

    return color;
}