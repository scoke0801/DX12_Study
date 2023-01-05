#pragma once

#include "Component.h"

enum class LIGHT_TYPE : uint8
{
	DIRECTIONAL_LIGHT,
	POINT_LIGHT,
	SPOT_LIGHT,
	
	END
};

// Diffuse : 전반사광
// 입사각의 각도에 따라서 빛의 세기가 달라진다
// Ambient : 환경광
// 적어도 일정한 크기의 빛은 받는다
// Specular : 난반사광
// 반사 벡터와 카메라로의 벡터 사이의 각도가 작을수록 빛나 보인다.

// pragma pack 4가 기본 정렬 규칙이지만
// HLSL에서는 특히 16바이트 크기를 지켜줘야 함
// --> 규칙을 맞춰주기 위해 Vec3만 있어도 되지만 Vec4로 사용
struct LightColor
{
	Vec4 diffuse;
	Vec4 ambient;
	Vec4 specular;
};

struct LightInfo
{
	LightColor	color;
	Vec4		position;
	Vec4		direction;
	int32		lightType;
	float		range;
	float		angle;	
	int32		padding;
};

struct LightParams
{
	uint32		lightCount;	// 조명 개수
	Vec3		padding;	
	LightInfo	lights[50];
};

class Light : public Component
{
public:
	Light();
	virtual ~Light();

	virtual void FinalUpdate() override;
	void Render();
	void RenderShadow();

public:
	LIGHT_TYPE GetLightType() { return static_cast<LIGHT_TYPE>(_lightInfo.lightType); }
	
	const LightInfo& GetLightInfo() { return _lightInfo; }

	void SetLightDirection(Vec3 direction);
	
	void SetDiffuse(const Vec3& diffuse) { _lightInfo.color.diffuse = diffuse; }
	void SetAmbient(const Vec3& ambient) { _lightInfo.color.ambient = ambient; }
	void SetSpecular(const Vec3& specular) { _lightInfo.color.specular = specular; }

	void SetLightType(LIGHT_TYPE type);
	void SetLightRange(float range) { _lightInfo.range = range; }
	void SetLightAngle(float angle) { _lightInfo.angle = angle; }

	void SetLightIndex(int8 index) { _lightIndex = index; }

private:
	LightInfo _lightInfo = {};

	int8 _lightIndex = -1;
	shared_ptr<class Mesh> _volumeMesh;
	shared_ptr<class Material> _lightMaterial;

	shared_ptr<GameObject> _shadowCamera;
};

