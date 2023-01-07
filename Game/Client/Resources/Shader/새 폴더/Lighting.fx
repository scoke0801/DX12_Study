#ifndef _LIGHTING_FX_
#define _LIGHTING_FX_

#include "Params.fx"
#include "Utils.fx"

struct VS_IN
{
    float3 pos      : POSITION;
    float2 uv       : TEXCOORD;
};

struct VS_OUT
{
    float4 pos : SV_Position;
    float2 uv : TEXCOORD;
};

struct PS_OUT
{
    float4 diffuse : SV_Target0;
    float4 specular : SV_Target1;
};

// Directional Light
// g_int_0 : Light Index
// g_tex_0 : Position RenderTarget
// g_tex_1 : Normal RenderTarget
// g_tex_2 : Shadow RenderTarget. ShadowShader��� �����
// g_mat_0 : ShadowCamera matViewProj
// Mesh : Rectangle
VS_OUT VS_DirLight(VS_IN input)
{
    VS_OUT output = (VS_OUT)0;

    // mesh�� -0.5 ~ 0.5�� ����
    // -1 ~ 1 ������ ������ֱ� ���� * 2
    output.pos = float4(input.pos * 2.f, 1.f);
    output.uv = input.uv;

    return output;
}

PS_OUT PS_DirLight(VS_OUT input)
{
    PS_OUT output = (PS_OUT)0;

    // ī�޶� �ڿ� �ִ� ��ǥ�� �׸� �ʿ䰡 ������ clipó��
    float3 viewPos = g_tex_0.Sample(g_sam_0, input.uv).xyz;
    if (viewPos.z <= 0.f) {
        clip(-1);
    }

    float3 viewNormal = g_tex_1.Sample(g_sam_0, input.uv).xyz;

    LightColor color = CalculateLightColor(g_int_0, viewNormal, viewPos);

    // �׸���
    if (length(color.diffuse) != 0) {
        matrix shadowCameraVP = g_mat_0;

        float4 worldPos = mul(float4(viewPos.xyz, 1.f), g_matViewInv);
        float4 shadowClipPos = mul(worldPos, shadowCameraVP);   // viewProj
        float depth = shadowClipPos.z / shadowClipPos.w;

        // Ŭ���������� NDC�� ��ȯ, ( -1 ~ 1 )����
        // x[-1 ~ 1] -> u[0 ~ 1]
        // y[1 ~ -1] -> v[0 ~ 1]
        float2 uv = shadowClipPos.xy / shadowClipPos.w;
        uv.y = -uv.y;
        uv = uv * 0.5 + 0.5;

        if (0 < uv.x && uv.x < 1 && 0 < uv.y && uv.y < 1)
        {
            float shadowDepth = g_tex_2.Sample(g_sam_0, uv).x;
            if (shadowDepth > 0 && depth > shadowDepth + 0.00001f)
            {
                // �׸��� ���� ������ ���� ������
                color.diffuse *= 0.5f;
                color.specular = (float4) 0.f;
            }
        }
    }

    output.diffuse = color.diffuse + color.ambient;
    output.specular = color.specular;

    return output;
}

// Point Light
// g_int_0 : Light index
// g_tex_0 : Position Render Target
// g_tex_1 : Normal Render Target
// g_vec_0 : RenderTaget Resolution :: screen (w, h)
// Mesh : sphere
VS_OUT VS_PointLight(VS_IN input)
{
    VS_OUT output = (VS_OUT)0;
     
    output.pos = mul(float4(input.pos, 1.f), g_matWorldViewProj);
    output.uv = input.uv;

    return output;
}

PS_OUT PS_PointLight(VS_OUT input)
{
    PS_OUT output = (PS_OUT)0;

    // input.pos = SV_Position = Screen ��ǥ
    float2 uv = float2(input.pos.x / g_vec_0.x, input.pos.y / g_vec_0.y);
    float3 viewPos = g_tex_0.Sample(g_sam_0, uv).xyz;
    if (viewPos.z <= 0.f) {
        clip(-1);
    }

    int lightIndex = g_int_0;
    float3 viewLightPos = mul(float4(g_light[lightIndex].position.xyz, 1.f), g_matView).xyz;
    float distance = length(viewPos - viewLightPos);
    if (distance > g_light[lightIndex].range) {
        clip(-1);
    }

    float3 viewNormal = g_tex_1.Sample(g_sam_0, input.uv).xyz;

    LightColor color = CalculateLightColor(g_int_0, viewNormal, viewPos);
    output.diffuse = color.diffuse + color.ambient;
    output.specular = color.specular;   
    
    return output;
}

// Final (��� ����) 
// g_tex_0 : Diffuse Color Target
// g_tex_1 : Diffuse Light Target
// g_tex_2 : Specular Render Target
// Mesh : Rectangle

VS_OUT VS_FinalLight(VS_IN input)
{
    VS_OUT output = (VS_OUT)0;

    // mesh�� -0.5 ~ 0.5�� ����
    // -1 ~ 1 ������ ������ֱ� ���� * 2
    output.pos = float4(input.pos * 2.f, 1.f);
    output.uv = input.uv;

    return output;
}

float4 PS_FinalLight(VS_OUT input) : SV_Target
{
    float4 output = (float4)0;

    float4 lightPower = g_tex_1.Sample(g_sam_0, input.uv);
    if (lightPower.x == 0.f && lightPower.y == 0.f && lightPower.z == 0.f)
        clip(-1);

    float4 color = g_tex_0.Sample(g_sam_0, input.uv);
    float4 specular = g_tex_2.Sample(g_sam_0, input.uv);

    output = (color * lightPower) + specular;
    return output;
}
#endif