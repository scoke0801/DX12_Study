#pragma once

#include "Component.h"
#include "Frustum.h"

enum class PROJECTION_TYPE : uint8
{ 
	PERSPECTIVE,		// 원근 투영
	ORTHOGRAPHIC,		// 직교 투영
};

class Camera : public Component
{
public:
	Camera();
	virtual ~Camera();
	virtual void FinalUpdate() override;

public:
	void SortGameObject();
	void Render_Deferred();
	void Render_Forward();
	
public:
	void SetProjectionType(PROJECTION_TYPE type) { _projType = type; }
	PROJECTION_TYPE GetProjectionType() { return _projType; }

	const Matrix& GetView() { return _matView; }
	const Matrix& GetProjection() { return _matProjection; }

	// 컬링마스크 값이 1이면 안그림, 0이면 그림
	void SetCullingMaskLayerLayerOff(uint8 layer, bool on);

	void SetCullingMaskAll() { SetCullingMask(UINT32_MAX); }
	void SetCullingMask(uint32 mask) { _cullingMask = mask; }
	bool IsCulled(uint8 layer) { return (_cullingMask & (1 << layer)) != 0; }
private:
	PROJECTION_TYPE _projType = PROJECTION_TYPE::PERSPECTIVE;

	float _near = 1.0f;			// 근 평면
	float _far = 1000.0f;		// 먼 평면
	float _fov = XM_PI / 4.f;	// 시야각, 45도
	float _scale = 1.0f;

	Matrix _matView = {};
	Matrix _matProjection = {}; 

	Frustum	_frustum;
	uint32 _cullingMask = 0;

private:
	vector<shared_ptr<GameObject>>	_vecDeferred;
	vector<shared_ptr<GameObject>>	_vecForward;
	vector<shared_ptr<GameObject>>	_vecParticle;

public:
	// TEMP
	static Matrix S_MatView;
	static Matrix S_MatProjection;
};

