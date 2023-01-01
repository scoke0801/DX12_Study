#include "pch.h"
#include "Camera.h"
#include "Transform.h"
#include "Scene.h"
#include "SceneManager.h"
#include "GameObject.h"
#include "MeshRenderer.h"
#include "Engine.h"

Matrix Camera::S_MatView = {};
Matrix Camera::S_MatProjection = {};

Camera::Camera() : Component(COMPONENT_TYPE::CAMERA)
{
}

Camera::~Camera()
{
}

void Camera::FinalUpdate()
{
	// 카메라 변환행렬 : 카메라 월드 변환 행렬 -> 역행렬 
	_matView = GetTransform()->GetLocalToWorldMatrix().Invert();

	float width = static_cast<float>(GEngine->GetWindow().width);
	float height = static_cast<float>(GEngine->GetWindow().height);

	if (_projType == PROJECTION_TYPE::PERSPECTIVE) {
		_matProjection = ::XMMatrixPerspectiveFovLH(_fov, width / height, _near, _far);
	}
	else{
		_matProjection = ::XMMatrixOrthographicLH(width * _scale, height * _scale, _near, _far);
	}
	_frustum.FinalUpdate();
}

void Camera::Render()
{ 
	S_MatView = _matView;
	S_MatProjection = _matProjection;

	shared_ptr<Scene> scene = GET_SINGLETON(SceneManager)->GetActiveScene();

	// TODO : Layer 구분
	const vector<shared_ptr<GameObject>>& gameObjects = scene->GetGameObjects();

	for (auto& gameObject : gameObjects)
	{
		if (!gameObject->GetMeshRenderer()) {
			continue;
		}

		if (IsCulled(gameObject->GetlayerIndex())) {
			continue;
		}

		if (gameObject->GetCheckFrustum()) {
			if (!_frustum.ContainSphere(gameObject->GetTransform()->GetWorldPosition(),
				gameObject->GetTransform()->GetBoundingSphereRadius()))
			{
				continue;
			}
		}

		gameObject->GetMeshRenderer()->Render();
	}
}

void Camera::SetCullingMaskLayerLayerOff(uint8 layer, bool on)
{
	if (on) {
		_cullingMask |= (1 << layer);
	}
	else
	{
		_cullingMask &= ~(1 << layer);
	}
}
