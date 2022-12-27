#include "pch.h"
#include "Scene.h"
#include "GameObject.h"

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

void Scene::LastUpdate()
{
	for (shared_ptr<GameObject>& gameObject : _gameObjects) {
		gameObject->LastUpdate();
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
