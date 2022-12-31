#pragma once

#include "Component.h"
#include "Object.h"

class MeshRenderer;
class MonoBehaviour;

// ���� raw pointer�� �������ϴ�
// shared_ptr�� ����� ���� enable_shared_from_this�� ����Ѵ�
class GameObject : public Object, public enable_shared_from_this<GameObject>
{
public:
	GameObject();
	virtual ~GameObject();

	void Init();

	void Awake();
	void Start();
	void Update();
	void LateUpdate();
	void FinalUpdate();

	shared_ptr<class Transform> GetTransform();
	shared_ptr<class MeshRenderer> GetMeshRenderer();
	shared_ptr<class Camera> GetCamera();
	shared_ptr<class Light> GetLight();

	shared_ptr<Component> GetFixedComponent(COMPONENT_TYPE type);

	void AddComponent(shared_ptr<Component> component);

	void SetCheckFrustum(bool checkFrustum) { _checkFrustum = checkFrustum; }
	bool GetCheckFrustum() { return _checkFrustum; }

private:
	array<shared_ptr<Component>, FIXED_COMPONENT_COUNT> _components;

	vector<shared_ptr<MonoBehaviour>> _scripts;

	bool _checkFrustum = true;
};

