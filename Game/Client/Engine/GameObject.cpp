#include "pch.h"
#include "GameObject.h"
#include "Transform.h"
#include "MonoBehaviour.h"
#include "Camera.h"
#include "MeshRenderer.h"

GameObject::GameObject()
	:Object(OBJECT_TYPE::GAMEOBJECT)
{
}

GameObject::~GameObject()
{
}

void GameObject::Init()
{

}

void GameObject::Awake()
{
	for (shared_ptr<Component>& component: _components)
	{
		if (component) {
			component->Awake();
		}
	}

	for (shared_ptr<MonoBehaviour> &script : _scripts)
	{
		script->Awake();
	}
}

void GameObject::Start()
{
	for (shared_ptr<Component>& component : _components)
	{
		if (component) {
			component->Start();
		}
	}

	for (shared_ptr<MonoBehaviour>& script : _scripts)
	{
		script->Start();
	}
}

void GameObject::Update()
{
	for (shared_ptr<Component>& component : _components)
	{
		if (component) {
			component->Update();
		}
	}

	for (shared_ptr<MonoBehaviour>& script : _scripts)
	{
		script->Update();
	}
}

void GameObject::LateUpdate()
{
	for (shared_ptr<Component>& component : _components)
	{
		if (component) {
			component->LateUpdate();
		}
	}

	for (shared_ptr<MonoBehaviour>& script : _scripts)
	{
		script->LateUpdate();
	}
}

void GameObject::FinalUpdate()
{
	for (shared_ptr<Component>& component : _components)
	{
		if (component) {
			component->FinalUpdate();
		}
	} 
}

shared_ptr<Transform> GameObject::GetTransform()
{
	shared_ptr<Component> component = GetFixedComponent(COMPONENT_TYPE::TRANSFORM);
	return static_pointer_cast<Transform>(component);
}

shared_ptr<MeshRenderer> GameObject::GetMeshRenderer()
{
	shared_ptr<Component> component = GetFixedComponent(COMPONENT_TYPE::MESH_RENDERER);
	return static_pointer_cast<MeshRenderer>(component);
}

shared_ptr<Camera> GameObject::GetCamera()
{
	shared_ptr<Component> component = GetFixedComponent(COMPONENT_TYPE::CAMERA);
	return static_pointer_cast<Camera>(component);
}

shared_ptr<Component> GameObject::GetFixedComponent(COMPONENT_TYPE type)
{
	uint8 index = static_cast<uint8>(type);
	assert(index < FIXED_COMPONENT_COUNT);
	return _components[index];
}

void GameObject::AddComponent(shared_ptr<Component> component)
{
	// shared_from_this는 enable_shared_from_this를 상속받아서 생성된 함수
	// 자기 자신에 대한 weak_ptr를 들고 있다가, 필요할 때 shared_ptr를 넘겨줌
	component->SetGameObject(shared_from_this());

	uint8 index = static_cast<uint8>(component->GetType());
	if (index < FIXED_COMPONENT_COUNT)
	{
		_components[index] = component;
	}
	else
	{
		// smart_ptr에서 dynamic_cast를 사용하기 위해 dynamic_pointer_cast를 사용
		_scripts.push_back(dynamic_pointer_cast<MonoBehaviour>(component));
	}
}
