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

	void Render();

	const Matrix& GetView() { return _matView; }
	const Matrix& GetProjection() { return _matProjection; }

private:
	PROJECTION_TYPE _projType = PROJECTION_TYPE::PERSPECTIVE;

	float _near = 1.0f;			// �� ���
	float _far = 1000.0f;		// �� ���
	float _fov = XM_PI / 4.f;	// �þ߰�, 45��
	float _scale = 1.0f;

	Matrix _matView = {};
	Matrix _matProjection = {}; 

	Frustum	_frustum;
public:
	// TEMP
	static Matrix S_MatView;
	static Matrix S_MatProjection;
};

