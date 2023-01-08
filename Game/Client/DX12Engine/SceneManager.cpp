#include "pch.h"
#include "SceneManager.h"
#include "GameScene.h"

__DX12Engine::SceneManager::SceneManager()
{
	_activeScene = make_shared<GameScene>();
}

void __DX12Engine::SceneManager::Update(float deltaTime)
{
	_activeScene->Update(deltaTime);
}

void __DX12Engine::SceneManager::LateUpdate(float deltaTime)
{
	_activeScene->LateUpdate(deltaTime);
}
