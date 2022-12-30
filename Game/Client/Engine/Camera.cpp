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
	// ī�޶� ��ȯ��� : ī�޶� ���� ��ȯ ��� -> ����� 
	_matView = GetTransform()->GetLocalToWorldMatrix().Invert();

	float width = static_cast<float>(GEngine->GetWindow().width);
	float height = static_cast<float>(GEngine->GetWindow().height);

	if (_projType == PROJECTION_TYPE::PERSPECTIVE) {
		_matProjection = ::XMMatrixPerspectiveFovLH(_fov, width / height, _near, _far);
	}
	else{
		_matProjection = ::XMMatrixOrthographicLH(width, height, _near, _far);
	}

	S_MatView = _matView;
	S_MatProjection = _matProjection;
}

void Camera::Render()
{
	shared_ptr<Scene> scene = GET_SINGLETON(SceneManager)->GetActiveScene();

	// TODO : Layer ����
	const vector<shared_ptr<GameObject>>& gameObjects = scene->GetGameObjects();

	for (auto& gameObject : gameObjects)
	{
		if (!gameObject->GetMeshRenderer()) {
			continue;
		}

		gameObject->GetMeshRenderer()->Render();
	}
}