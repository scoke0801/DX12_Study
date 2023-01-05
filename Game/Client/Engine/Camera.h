#pragma once

#include "Component.h"
#include "Frustum.h"

enum class PROJECTION_TYPE : uint8
{ 
	PERSPECTIVE,		// ���� ����
	ORTHOGRAPHIC,		// ���� ����
};

class Camera : public Component
{
public:
	Camera();
	virtual ~Camera();
	virtual void FinalUpdate() override;

public:
	void SortGameObject();
	void SortShadowObject();

public:
	void Render_Deferred();
	void Render_Forward();
	void Render_Shadow();
	
public:
	void SetProjectionType(PROJECTION_TYPE type) { _projType = type; }
	PROJECTION_TYPE GetProjectionType() { return _projType; }

	const Matrix& GetView() { return _matView; }
	const Matrix& GetProjection() { return _matProjection; }

	// �ø�����ũ ���� 1�̸� �ȱ׸�, 0�̸� �׸�
	void SetCullingMaskLayerOff(uint8 layer, bool on);

	void SetCullingMaskAll() { SetCullingMask(UINT32_MAX); }
	void SetCullingMask(uint32 mask) { _cullingMask = mask; }
	bool IsCulled(uint8 layer) { return (_cullingMask & (1 << layer)) != 0; }

	void SetNear(float value) { _near = value; }
	void SetFar(float value) { _far = value; }
	void SetFOV(float value) { _fov = value; }
	void SetScale(float value) { _scale = value; }
	void SetWidth(float value) { _width = value; }
	void SetHeight(float value) { _height = value; }

	Matrix& GetViewMatrix() { return _matView; }
	Matrix& GetProjectionMatrix() { return _matProjection; }

private:
	PROJECTION_TYPE _projType = PROJECTION_TYPE::PERSPECTIVE;

	float _near = 1.0f;			// �� ���
	float _far = 1000.0f;		// �� ���
	float _fov = XM_PI / 4.f;	// �þ߰�, 45��
	float _scale = 1.0f;

	// ������ ī�޶󿡼� �ػ� ������ ���� ����.
	float _width = 0.f;
	float _height = 0.f;

	Matrix _matView = {};
	Matrix _matProjection = {}; 

	Frustum	_frustum;
	uint32 _cullingMask = 0;

private:
	vector<shared_ptr<GameObject>>	_vecDeferred;
	vector<shared_ptr<GameObject>>	_vecForward;
	vector<shared_ptr<GameObject>>	_vecParticle;
	vector<shared_ptr<GameObject>>	_vecShadow;
public:
	// TEMP
	static Matrix S_MatView;
	static Matrix S_MatProjection;
};

