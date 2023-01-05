#include "pch.h"
#include "Scene.h"
#include "GameObject.h"
#include "Camera.h"
#include "Engine.h"
#include "ConstantBuffer.h"
#include "Light.h"
#include "Resources.h"

void Scene::Awake()
{
	// &�� ���� ������, ���۷��� ī��Ʈ ����ó���� �߻�?
	for (shared_ptr<GameObject>& gameObject : _gameObjects) {
		gameObject->Awake();
	}
}

void Scene::Start()
{
	for (shared_ptr<GameObject>& gameObject : _gameObjects) {
		gameObject->Start();
	}
}

void Scene::Update()
{
	for (shared_ptr<GameObject>& gameObject : _gameObjects) {
		gameObject->Update();
	}
}

void Scene::LateUpdate()
{
	for (shared_ptr<GameObject>& gameObject : _gameObjects) {
		gameObject->LateUpdate();
	}
}

void Scene::FinalUpdate()
{
	for (shared_ptr<GameObject>& gameObject : _gameObjects) {
		gameObject->FinalUpdate();
	}
}

void Scene::Render()
{  
	PushLightData();

	PushLightData();

	ClearRTV();

	RenderShadow();

	RenderDeferred();

	RenderLights();

	RenderFinal();

	RenderForward(); 
}

void Scene::ClearRTV()
{
	// SwapChain Group �ʱ�ȭ
	int8 backIndex = GEngine->GetSwapChain()->GetBackBufferIndex();
	GEngine->GetRTGroup(RENDER_TARGET_GROUP_TYPE::SWAP_CHAIN)->ClearRenderTargetView(backIndex);
	// Shadow Group �ʱ�ȭ
	GEngine->GetRTGroup(RENDER_TARGET_GROUP_TYPE::SHADOW)->ClearRenderTargetView();
	// Deferred Group �ʱ�ȭ
	GEngine->GetRTGroup(RENDER_TARGET_GROUP_TYPE::G_BUFFER)->ClearRenderTargetView();
	// Lighting Group �ʱ�ȭ
	GEngine->GetRTGroup(RENDER_TARGET_GROUP_TYPE::LIGHTING)->ClearRenderTargetView();
}

void Scene::RenderShadow()
{
	GEngine->GetRTGroup(RENDER_TARGET_GROUP_TYPE::SHADOW)->OMSetRenderTargets();

	for (auto& light : _lights)
	{
		if (light->GetLightType() != LIGHT_TYPE::DIRECTIONAL_LIGHT)
			continue;

		light->RenderShadow();
	}

	GEngine->GetRTGroup(RENDER_TARGET_GROUP_TYPE::SHADOW)->WaitTargetToResource();
}

void Scene::RenderDeferred()
{
	// Deferred OMSet
	GEngine->GetRTGroup(RENDER_TARGET_GROUP_TYPE::G_BUFFER)->OMSetRenderTargets();

	shared_ptr<Camera> mainCamera = _cameras[0];
	mainCamera->SortGameObject();
	mainCamera->Render_Deferred();

	GEngine->GetRTGroup(RENDER_TARGET_GROUP_TYPE::G_BUFFER)->WaitTargetToResource();
}

void Scene::RenderLights()
{
	// ���� ī�޶� ����.
	// ������ ī�޶�� ������ matrix�������� �����ϱ� ����
	// ����ƽ�� �ƴϾ����� ���������...
	shared_ptr<Camera> mainCamera = _cameras[0];
	Camera::S_MatView = mainCamera->GetViewMatrix();
	Camera::S_MatProjection = mainCamera->GetProjectionMatrix();

	GEngine->GetRTGroup(RENDER_TARGET_GROUP_TYPE::LIGHTING)->OMSetRenderTargets();

	// ������ �׸���.
	for (auto& light : _lights)
	{
		light->Render();
	}

	GEngine->GetRTGroup(RENDER_TARGET_GROUP_TYPE::LIGHTING)->WaitTargetToResource();
}

void Scene::RenderFinal()
{	
	// Swapchain OMSet
	int8 backIndex = GEngine->GetSwapChain()->GetBackBufferIndex();
	GEngine->GetRTGroup(RENDER_TARGET_GROUP_TYPE::SWAP_CHAIN)->OMSetRenderTargets(1, backIndex);

	GET_SINGLETON(Resources)->Get<Material>(L"Final")->PushGraphicsData();
	GET_SINGLETON(Resources)->Get<Mesh>(L"Rectangle")->Render();
}

void Scene::RenderForward()
{
	shared_ptr<Camera> mainCamera = _cameras[0];
	mainCamera->Render_Forward();

	for (auto& camera : _cameras)
	{
		if (camera == mainCamera)
			continue;

		camera->SortGameObject();
		camera->Render_Forward();
	}
}

void Scene::AddGameObject(shared_ptr<GameObject> gameObject)
{
	if (gameObject->GetCamera() != nullptr)
	{
		_cameras.push_back(gameObject->GetCamera());
	}
	else if (gameObject->GetLight() != nullptr)
	{
		_lights.push_back(gameObject->GetLight());
	}
	_gameObjects.push_back(gameObject);
}

void Scene::RemoveGameObject(shared_ptr<GameObject> gameObject)
{
	if (gameObject->GetCamera())
	{
		auto findIt = std::find(_cameras.begin(), _cameras.end(), gameObject->GetCamera());
		if (findIt != _cameras.end())
			_cameras.erase(findIt);
	}
	else if (gameObject->GetLight())
	{
		auto findIt = std::find(_lights.begin(), _lights.end(), gameObject->GetLight());
		if (findIt != _lights.end())
			_lights.erase(findIt);
	}

	auto res = std::find(_gameObjects.begin(), _gameObjects.end(), gameObject);
	if (res != _gameObjects.end()) 
	{
		_gameObjects.erase(res);
	}
}

void Scene::PushLightData()
{
	LightParams lightParams = {};
	
	for (auto& light : _lights)
	{
		const LightInfo& lightInfo = light->GetLightInfo();

		light->SetLightIndex(lightParams.lightCount);

		lightParams.lights[lightParams.lightCount] = lightInfo;
		++lightParams.lightCount;
	}

	CONSTANT_BUFFER(CONSTANT_BUFFER_TYPE::GLOBAL)->PushGraphicsGlobalData(&lightParams, sizeof(lightParams));
}
