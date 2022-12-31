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
        // 1.���� ������ viewspace�� ��ȯ
        // 2. -L�� N�� ����
        // 3. 0 ~ 1������ ������ ����(saturate), <- ���� ������ 0
        viewLightDir = normalize(mul(float4(g_light[lightIndex].direction.xyz, 0.f), g_matView).xyz);
        diffuseRatio = saturate(dot(-viewLightDir, viewNormal));
    }
    else if (g_light[lightIndex].lightType == 1)
    {
        // Point Light
        // 1. directional Light�� �ٸ��� ���� ������ �������, ���� ��ġ�� view space ��ǥ    
        // 2.���� ������ viewspace�� ��ȯ
        // 3. -L�� N�� ����
        // 4. 0 ~ 1������ ������ ����(saturate), <- ���� ������ 0
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
            // �Ÿ��� ���� ���� ������ ���� �޵���
            // 1 - dist���൵ ������
            // �ð����� ȿ���� ���� pow
            // ������ ����� ��츦 ���� ���� saturate
            distanceRatio = saturate(1.f - pow(dist / g_light[lightIndex].range, 2));
        }
    }
    else
    {
        // Spot Light
        // 1. directional Light�� �ٸ��� ���� ������ �������, ���� ��ġ�� view space ��ǥ    
        // 2.���� ������ viewspace�� ��ȯ
        // 3. -L�� N�� ����
        // 4. 0 ~ 1������ ������ ����(saturate), <- ���� ������ 0
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

            // SpotLight �߽� ����
            float3 viewCenterLightDir = normalize(mul(float4(g_light[lightIndex].direction.xyz, 0.f), g_matView).xyz);

            // ���� ������ �ִ� ������ �������� �Ÿ����
            // L�� normal�� ��, V�� �븻ó�� �ȵ� ���̹Ƿ�
            // �Ÿ� d�� L�� A�� ������ ��( 1 * * cos())
            float centerDist = dot(viewLightVec, viewCenterLightDir);
            distanceRatio = saturate(1.f - centerDist / g_light[lightIndex].range);

            float lightAngle = acos(dot(normalize(viewLightVec), viewCenterLightDir));

            if (centerDist < 0.f || centerDist > g_light[lightIndex].range)
            {   // �ִ� �Ÿ��� �������
                distanceRatio = 0.f;
            }
            else if (lightAngle > halfAngle)
            {   // �ִ� �þ߰��� �������
                distanceRatio = 0.f;
            }
            else
            {   // �Ÿ��� ���� ������ ���⸦ ����
                distanceRatio = saturate(1.f - pow(centerDist / g_light[lightIndex].range, 2));
            }
        }
    }

    // �ݻ� ����R ( L + dot(-L, N) )
    // ī�޶���� ���� eyeDir, viewSpace�� �������� �ϸ� ī�޶��� ��ǥ��? :: 0,0,0
    // -> Normalize�� ����
    // eyeDir�� reflectionDir�� �����Ͽ� ���� ��� 
    // + ratio�� ��ȭ�� ���ĸ��� ��Ÿ������ �ϱ� ���� pow�� ó��, 
    // �� ū ��ȭ�� ������ pow�� ����(�⺻ 2)�� ����
    float3 reflectionDir = normalize(viewLightDir + 2 * (saturate(dot(-viewLightDir, viewNormal)) * viewNormal));
    float3 eyeDir = normalize(viewPos);
    specularRatio = saturate(dot(-eyeDir, reflectionDir));
    specularRatio = pow(specularRatio, 2);

    // ambient�� �� ��ü�� ������ �ִ� ������ Ratio����� ����������
    // point,spot Light�� ���� �Ÿ� ����� ����
    color.diffuse = g_light[lightIndex].color.diffuse * diffuseRatio * distanceRatio;
    color.ambient = g_light[lightIndex].color.ambient * distanceRatio;
    color.specular = g_light[lightIndex].color.specular * specularRatio * distanceRatio;

    return color;
} 

#endif