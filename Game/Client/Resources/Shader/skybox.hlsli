#ifndef _SKYBOX_HLSLI_
#define _SKYBOX_HLSLI_

#include "Params.hlsli" 
 
struct VS_IN
{
    float3 localPos : POSITION;
    float2 uv       : TEXCOORD;
};

struct VS_OUT
{
    float4 pos : SV_Position;
    float2 uv : TEXCOORD;
};

VS_OUT VS_Main(VS_IN input)
{
    VS_OUT output = (VS_OUT)0;

    // Translation은 하지 않고 Rotaion만 적용( w를 0으로 설정 )
    float4 viewPos = mul(float4(input.localPos, 0.0f), g_matView);
    float4 clipSpacePos = mul(viewPos, g_matProj);

    // w / w = 1이기 때문에,
    // cilpspace의 xyww값으로 전달하면 항상 깊이가 1로 유지.
    output.pos = clipSpacePos.xyww;
    output.uv = input.uv;

    return output;
}

float4 PS_Main(VS_OUT input) : SV_Target
{
    float4 color = g_tex_0.Sample(g_sam_0, input.uv);
    return color;
}
#endif