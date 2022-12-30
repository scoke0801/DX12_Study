#include "pch.h"
#include "SceneManager.h" 
#include "Scene.h"
#include "Engine.h"
#include "Material.h"
#include "GameObject.h"
#include "MeshRenderer.h"
#include "Camera.h"
#include "Transform.h"
#include "TestCameraScript.h"
#include "Resources.h"

void SceneManager::Update()
{
	if (_activeScene == nullptr) {
		return;
	}

	_activeScene->Update();
	_activeScene->LateUpdate();
	_activeScene->FinalUpdate();
}

// 임시 코드!!!
void SceneManager::Render()
{
	if (!_activeScene) { return; }

	// 무식한 방법으로 카메라를 찾는식으로 일단 테스트..
	const vector<shared_ptr<GameObject>>& gameObjects = _activeScene->GetGameObjects();
	for (auto gameObejct : gameObjects)
	{
		if (!gameObejct->GetCamera()) { continue; }
		
		gameObejct->GetCamera()->Render();
	}
}

void SceneManager::LoadScene(wstring sceneName)
{
	// TODO :: 기존 Scene 정리
	// TODO :: 파일에서 Scene정보 로드
	_activeScene = LoadTestScene();

	_activeScene->Awake();
	_activeScene->Start();
}

shared_ptr<Scene> SceneManager::LoadTestScene()
{
	shared_ptr<Scene> scene = make_shared<Scene>();
	 
#pragma region Camera
	shared_ptr<GameObject> camera = make_shared<GameObject>();
	camera->AddComponent(make_shared<Transform>());
	camera->AddComponent(make_shared<Camera>());
	camera->AddComponent(make_shared<TestCameraScript>());
	camera->GetTransform()->SetLocalPosition(Vec3(0.0f, 100.f, 0.f));
	scene->AddGameObject(camera);
#pragma endregion
	 
#pragma region Sphere
	{
		shared_ptr<GameObject> sphere = make_shared<GameObject>();
		sphere->AddComponent(make_shared<Transform>());
		sphere->GetTransform()->SetLocalScale(Vec3(100.0f, 100.0f, 100.0f));
		sphere->GetTransform()->SetLocalPosition(Vec3(0.f, 100.0f, 200.0f));
		shared_ptr<MeshRenderer> meshRenderer = make_shared<MeshRenderer>();
		{
			shared_ptr<Mesh> sphereMesh = GET_SINGLETON(Resources)->LoadSphereMesh();
			meshRenderer->SetMesh(sphereMesh);
		}
		{
			shared_ptr<Shader> shader = make_shared<Shader>();
			shared_ptr<Texture> texture = make_shared<Texture>();
			shader->Init(L"..\\Resources\\Shader\\default.hlsli");
			texture->Init(L"..\\Resources\\Texture\\Test.jpg"); 

			shared_ptr<Material> material = make_shared<Material>();
			material->SetShader(shader);
			material->SetTexture(0, texture);

			meshRenderer->SetMaterial(material);
		}
		sphere->AddComponent(meshRenderer);
		scene->AddGameObject(sphere); 
	}
#pragma endregion

#pragma region Cube
	{
		shared_ptr<GameObject> cube = make_shared<GameObject>();
		cube->AddComponent(make_shared<Transform>());
		cube->GetTransform()->SetLocalScale(Vec3(100.f, 100.f, 100.f));
		cube->GetTransform()->SetLocalPosition(Vec3(150.f, 100.f, 200.f));
		
		shared_ptr<MeshRenderer> meshRenderer = make_shared<MeshRenderer>();
		{
			shared_ptr<Mesh> mesh = make_shared<Mesh>();
			mesh = GET_SINGLETON(Resources)->LoadCubeMesh();
			meshRenderer->SetMesh(mesh);
		}
		{
			shared_ptr<Shader> shader = make_shared<Shader>();
			shader->Init(L"..\\Resources\\Shader\\default.hlsli");

			shared_ptr<Texture> texture = make_shared<Texture>();
			texture->Init(L"..\\Resources\\Texture\\Test.jpg");

			shared_ptr<Material> material = make_shared<Material>();
			material->SetShader(shader);
			material->SetTexture(0, texture);

			meshRenderer->SetMaterial(material);
		}

		cube->AddComponent(meshRenderer);
		scene->AddGameObject(cube);
	}
#pragma endregion
	return scene;
}
