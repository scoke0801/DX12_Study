#ifndef _UTILS_HLSLI_
#define _UTILS_HLSLI_

LightColor CalculateLightColor(int lightIndex, float3 viewNormal, float3 viewPos)
{
    LightColor color = (LightColor)0.f;

    float3 viewLightDir = (float3)0.f;

    float diffuseRatio = 0.f;
    float specularRatio = 0.f;
    float distanceRatio = 1.f;

    if (g_light[lightIndex].lightType == 0)
    {
        // Directional Light
        // 1.빛의 방향을 viewspace로 변환
        // 2. -L과 N을 내적
        // 3. 0 ~ 1사이의 값으로 보정(saturate), <- 값이 음수면 0
        viewLightDir = normalize(mul(float4(g_light[lightIndex].direction.xyz, 0.f), g_matView).xyz);
        diffuseRatio = saturate(dot(-viewLightDir, viewNormal));
    }
    else if (g_light[lightIndex].lightType == 1)
    {
        // Point Light
        // 1. directional Light와 다르게 빛의 방향을 계산해줌, 광원 위치의 view space 좌표    
        // 2.빛의 방향을 viewspace로 변환
        // 3. -L과 N을 내적
        // 4. 0 ~ 1사이의 값으로 보정(saturate), <- 값이 음수면 0
        float3 viewLightPos = mul(float4(g_light[lightIndex].position.xyz, 1.f), g_matView).xyz;
        viewLightDir = normalize(viewPos - viewLightPos);
        diffuseRatio = saturate(dot(-viewLightDir, viewNormal));

        float dist = distance(viewPos, viewLightPos);
        if (g_light[lightIndex].range == 0.f)
        {
            distanceRatio = 0.f;
        }
        else
        {
            // 거리에 따라서 빛의 영향을 적게 받도록
            // 1 - dist해줘도 되지만
            // 시각적인 효과를 위해 pow
            // 범위를 벗어나는 경우를 막기 위해 saturate
            distanceRatio = saturate(1.f - pow(dist / g_light[lightIndex].range, 2));
        }
    }
    else
    {
        // Spot Light
        // 1. directional Light와 다르게 빛의 방향을 계산해줌, 광원 위치의 view space 좌표    
        // 2.빛의 방향을 viewspace로 변환
        // 3. -L과 N을 내적
        // 4. 0 ~ 1사이의 값으로 보정(saturate), <- 값이 음수면 0
        float3 viewLightPos = mul(float4(g_light[lightIndex].position.xyz, 1.f), g_matView).xyz;
        viewLightDir = normalize(viewPos - viewLightPos);
        diffuseRatio = saturate(dot(-viewLightDir, viewNormal));

        if (g_light[lightIndex].range == 0.f)
        {
            distanceRatio = 0.f;
        }
        else
        {
            float halfAngle = g_light[lightIndex].angle * 0.5f;

            float3 viewLightVec = viewPos - viewLightPos;

            // SpotLight 중심 방향
            float3 viewCenterLightDir = normalize(mul(float4(g_light[lightIndex].direction.xyz, 0.f), g_matView).xyz);

            // 빛이 나가고 있는 방향을 기준으로 거리계산
            // L은 normal된 값, V는 노말처리 안된 값이므로
            // 거리 d는 L과 A를 내적한 값( 1 * * cos())
            float centerDist = dot(viewLightVec, viewCenterLightDir);
            distanceRatio = saturate(1.f - centerDist / g_light[lightIndex].range);

            float lightAngle = acos(dot(normalize(viewLightVec), viewCenterLightDir));

            if (centerDist < 0.f || centerDist > g_light[lightIndex].range)
            {   // 최대 거리를 벗어났는지
                distanceRatio = 0.f;
            }
            else if (lightAngle > halfAngle)
            {   // 최대 시야각을 벗어났는지
                distanceRatio = 0.f;
            }
            else
            {   // 거리에 따라 적절히 세기를 조절
                distanceRatio = saturate(1.f - pow(centerDist / g_light[lightIndex].range, 2));
            }
        }
    }

    // 반사 벡터R ( L + dot(-L, N) )
    // 카메라로의 벡터 eyeDir, viewSpace를 기준으로 하면 카메라의 좌표는? :: 0,0,0
    // -> Normalize만 해줌
    // eyeDir과 reflectionDir를 내적하여 비율 계산 
    // + ratio를 변화가 가파르게 나타나도록 하기 위해 pow를 처리, 
    // 더 큰 변화를 보려면 pow의 인자(기본 2)를 조절
    float3 reflectionDir = normalize(viewLightDir + 2 * (saturate(dot(-viewLightDir, viewNormal)) * viewNormal));
    float3 eyeDir = normalize(viewPos);
    specularRatio = saturate(dot(-eyeDir, reflectionDir));
    specularRatio = pow(specularRatio, 2);

    // ambient는 그 자체가 영향을 주니 별도의 Ratio계산을 하지않지만
    // point,spot Light를 위해 거리 계산은 해줌
    color.diffuse = g_light[lightIndex].color.diffuse * diffuseRatio * distanceRatio;
    color.ambient = g_light[lightIndex].color.ambient * distanceRatio;
    color.specular = g_light[lightIndex].color.specular * specularRatio * distanceRatio;

    return color;
} 

#endif