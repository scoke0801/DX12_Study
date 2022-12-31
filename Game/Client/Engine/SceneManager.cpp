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
#include "Light.h"

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

	_activeScene->Render();
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
	camera->AddComponent(make_shared<Camera>()); // Near=1, Far=1000, FOV=45도
	camera->AddComponent(make_shared<TestCameraScript>());
	camera->GetTransform()->SetLocalPosition(Vec3(0.f, 0.f, 0.f));
	scene->AddGameObject(camera);
#pragma endregion
	 
#pragma region Skybox
	{
		shared_ptr<GameObject> skybox = make_shared<GameObject>();
		skybox->AddComponent(make_shared<Transform>());
		skybox->SetCheckFrustum(false);
		shared_ptr<MeshRenderer> meshRenderer = make_shared<MeshRenderer>();
		{
			shared_ptr<Mesh> mesh = GET_SINGLETON(Resources)->LoadSphereMesh();
			meshRenderer->SetMesh(mesh);
		}
		{
			shared_ptr<Shader> shader = make_shared<Shader>();
			shared_ptr<Texture> texture = make_shared<Texture>();
			shader->Init(L"..\\Resources\\Shader\\skybox.hlsli",
				{ RASTERIZER_TYPE::CULL_NONE, DEPTH_STENCIL_TYPE::LESS_EQAUL });
			texture->Init(L"..\\Resources\\Texture\\Sky01.jpg");
			shared_ptr<Material> material = make_shared<Material>();
			material->SetShader(shader);
			material->SetTexture(0, texture);
			meshRenderer->SetMaterial(material);
		}
		skybox->AddComponent(meshRenderer);
		scene->AddGameObject(skybox);
	}
#pragma endregion
//#pragma region Sphere
//	{
//		shared_ptr<GameObject> sphere = make_shared<GameObject>();
//		sphere->AddComponent(make_shared<Transform>());
//		sphere->GetTransform()->SetLocalScale(Vec3(100.0f, 100.0f, 100.0f));
//		sphere->GetTransform()->SetLocalPosition(Vec3(0.f, 0.0f, 150.0f));
//		shared_ptr<MeshRenderer> meshRenderer = make_shared<MeshRenderer>();
//		{
//			shared_ptr<Mesh> sphereMesh = GET_SINGLETON(Resources)->LoadSphereMesh();
//			meshRenderer->SetMesh(sphereMesh);
//		}
//		{
//			shared_ptr<Shader> shader = make_shared<Shader>();
//			shared_ptr<Texture> texture = make_shared<Texture>();
//			shader->Init(L"..\\Resources\\Shader\\default.hlsli");
//			texture->Init(L"..\\Resources\\Texture\\Stone_Floor.jpg"); 
//
//			shared_ptr<Material> material = make_shared<Material>();
//			material->SetShader(shader);
//			material->SetTexture(0, texture);
//
//			meshRenderer->SetMaterial(material);
//		}
//		sphere->AddComponent(meshRenderer);
//		scene->AddGameObject(sphere); 
//	}
//#pragma endregion

#pragma region Cube
	{
		shared_ptr<GameObject> cube = make_shared<GameObject>();
		cube->AddComponent(make_shared<Transform>()); 
		cube->GetTransform()->SetLocalScale(Vec3(100.0f, 100.0f, 100.0f));
		cube->GetTransform()->SetLocalPosition(Vec3(0.f, 0.0f, 150.0f));
		/*cube->GetTransform()->SetLocalScale(Vec3(100.f, 100.f, 100.f));
		cube->GetTransform()->SetLocalPosition(Vec3(150.f, 100.f, 200.f));*/
		
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
			texture->Init(L"..\\Resources\\Texture\\Stone_Floor.jpg");

			shared_ptr<Texture> textureNormal = make_shared<Texture>();
			textureNormal->Init(L"..\\Resources\\Texture\\Stone_Floor_Normal.jpg");

			shared_ptr<Material> material = make_shared<Material>();
			material->SetShader(shader);
			material->SetTexture(0, texture);
			material->SetTexture(1, textureNormal);

			meshRenderer->SetMaterial(material);
		}

		cube->AddComponent(meshRenderer);
		scene->AddGameObject(cube);
	}
#pragma endregion

#pragma region Directional Light
	{
		shared_ptr<GameObject> light = make_shared<GameObject>();
		light->AddComponent(make_shared<Transform>());
		// 방향성 광원은 위치에 영향을 받지않음
		//light->GetTransform()->SetLocalPosition(Vec3(0.f, 150.f, 150.f));
		light->AddComponent(make_shared<Light>());
		light->GetLight()->SetLightDirection(Vec3(1.f, 0.f, 1.0f));
		light->GetLight()->SetLightType(LIGHT_TYPE::DIRECTIONAL_LIGHT);
		light->GetLight()->SetDiffuse(Vec3(0.5f, 0.5f, 0.5f));
		light->GetLight()->SetAmbient(Vec3(0.1f, 0.1f, 0.1f));
		light->GetLight()->SetSpecular(Vec3(0.5f, 0.5f, 0.5f));

		scene->AddGameObject(light);
	} 
#pragma endregion

#pragma region Point Light
	{
		shared_ptr<GameObject> light = make_shared<GameObject>();
		light->AddComponent(make_shared<Transform>());
		light->GetTransform()->SetLocalPosition(Vec3(150.f, 150.f, 150.f));
		light->AddComponent(make_shared<Light>());
		//light->GetLight()->SetLightDirection(Vec3(0.f, -1.f, 0.f));
		light->GetLight()->SetLightType(LIGHT_TYPE::POINT_LIGHT);
		light->GetLight()->SetDiffuse(Vec3(1.f, 0.1f, 0.1f));
		light->GetLight()->SetAmbient(Vec3(0.1f, 0.f, 0.f));
		light->GetLight()->SetSpecular(Vec3(0.1f, 0.1f, 0.1f));
		light->GetLight()->SetLightRange(10000.f);
		//light->GetLight()->SetLightAngle(XM_PI / 4);
		scene->AddGameObject(light);
	}
#pragma endregion

#pragma region Spot Light
	{
		shared_ptr<GameObject> light = make_shared<GameObject>();
		light->AddComponent(make_shared<Transform>());
		light->GetTransform()->SetLocalPosition(Vec3(-150.f, 0.f, 150.f));
		light->AddComponent(make_shared<Light>());
		light->GetLight()->SetLightDirection(Vec3(1.f, 0.f, 0.f));
		light->GetLight()->SetLightType(LIGHT_TYPE::SPOT_LIGHT);
		light->GetLight()->SetDiffuse(Vec3(0.f, 0.1f, 1.f));
		//light->GetLight()->SetAmbient(Vec3(0.f, 0.f, 0.1f));
		light->GetLight()->SetSpecular(Vec3(0.1f, 0.1f, 0.1f));
		light->GetLight()->SetLightRange(10000.f);
		light->GetLight()->SetLightAngle(XM_PI / 4);
		scene->AddGameObject(light);
	}
#pragma endregion

	return scene;
}
