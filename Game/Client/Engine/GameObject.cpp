#include "pch.h"
#include "GameObject.h"
#include "Transform.h"
#include "MonoBehaviour.h"

GameObject::GameObject()
{
}

GameObject::~GameObject()
{
}

void GameObject::Init()
{
	AddComponent(make_shared<Transform>() );
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

void GameObject::LastUpdate()
{
	for (shared_ptr<Component>& component : _components)
	{
		if (component) {
			component->LastUpdate();
		}
	}

	for (shared_ptr<MonoBehaviour>& script : _scripts)
	{
		script->LastUpdate();
	}
}

shared_ptr<Transform> GameObject::GetTransform()
{
	uint8 index = static_cast<uint8>(COMPONENT_TYPE::TRANSFORM);
	return static_pointer_cast<Transform>(_components[index]);
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
