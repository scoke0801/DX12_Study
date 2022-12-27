#pragma once

#include "Component.h"

class Transform;
class MeshRenderer;
class MonoBehaviour;

// ���� raw pointer�� �������ϴ�
// shared_ptr�� ����� ���� enable_shared_from_this�� ����Ѵ�
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

