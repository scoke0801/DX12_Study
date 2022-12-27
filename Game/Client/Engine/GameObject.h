#pragma once

#include "Component.h"

class Transform;
class MeshRenderer;
class MonoBehaviour;

// 같은 raw pointer를 포인팅하는
// shared_ptr를 만들기 위해 enable_shared_from_this를 사용한다
class GameObject : public enable_shared_from_this<GameObject>
{
public:
	GameObject();
	virtual ~GameObject();

	void Init();

	void Awake();
	void Start();
	void Update();
	void LastUpdate();

	shared_ptr<Transform> GetTransform();

	void AddComponent(shared_ptr<Component> component);
private:
	array<shared_ptr<Component>, FIXED_COMPONENT_COUNT> _components;

	vector<shared_ptr<MonoBehaviour>> _scripts;
};

