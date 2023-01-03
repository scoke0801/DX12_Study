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
	void Render_Deferred();
	void Render_Forward();
	
public:
	void SetProjectionType(PROJECTION_TYPE type) { _projType = type; }
	PROJECTION_TYPE GetProjectionType() { return _projType; }

	const Matrix& GetView() { return _matView; }
	const Matrix& GetProjection() { return _matProjection; }

	// �ø�����ũ ���� 1�̸� �ȱ׸�, 0�̸� �׸�
	void SetCullingMaskLayerLayerOff(uint8 layer, bool on);

	void SetCullingMaskAll() { SetCullingMask(UINT32_MAX); }
	void SetCullingMask(uint32 mask) { _cullingMask = mask; }
	bool IsCulled(uint8 layer) { return (_cullingMask & (1 << layer)) != 0; }
private:
	PROJECTION_TYPE _projType = PROJECTION_TYPE::PERSPECTIVE;

	float _near = 1.0f;			// �� ���
	float _far = 1000.0f;		// �� ���
	float _fov = XM_PI / 4.f;	// �þ߰�, 45��
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

