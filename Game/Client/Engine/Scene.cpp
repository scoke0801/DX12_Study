#include "pch.h"
#include "Scene.h"
#include "GameObject.h"
#include "Camera.h"
#include "Engine.h"
#include "ConstantBuffer.h"
#include "Light.h"

void Scene::Awake()
{
	// &로 받지 않으면, 레퍼런스 카운트 증감처리가 발생?
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

	for (auto gameObejct : _gameObjects)
	{
		if (!gameObejct->GetCamera()) { continue; }

		gameObejct->GetCamera()->Render();
	}
}

void Scene::AddGameObject(shared_ptr<GameObject> gameObject)
{
	_gameObjects.push_back(gameObject);
}

void Scene::RemoveGameObject(shared_ptr<GameObject> gameObject)
{
	auto res = std::find(_gameObjects.begin(), _gameObjects.end(), gameObject);
	if (res != _gameObjects.end()) 
	{
		_gameObjects.erase(res);
	}
}

void Scene::PushLightData()
{
	LightParams lightParams = {};
	
	for (auto& gameObject : _gameObjects)
	{
		if (!gameObject->GetLight()) { continue; }

		const LightInfo& lightInfo = gameObject->GetLight()->GetLightInfo();

		lightParams.lights[lightParams.lightCount] = lightInfo;
		++lightParams.lightCount;
	}

	CONSTANT_BUFFER(CONSTANT_BUFFER_TYPE::GLOBAL)->PushGlobalData(&lightParams, sizeof(lightParams));
}
