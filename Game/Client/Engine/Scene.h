#pragma once

class GameObject;

class Scene
{
public:
	void Awake();
	void Start();
	void Update();
	void LateUpdate();
	void FinalUpdate();

	void Render();

public:
	void AddGameObject(shared_ptr<GameObject> gameObject);
	void RemoveGameObject(shared_ptr<GameObject> gameObject);

	const vector<shared_ptr<GameObject>>& GetGameObjects() { return _gameObjects; }

private:
	void PushLightData();

private:
	vector<shared_ptr<GameObject>> _gameObjects;

	// TODO
	// ��ü ������ �����ϱ� ���ؼ��� Layer�� �ΰ�
	// 2���� ���� or ���� �迭�� ��ü���� �ٷ絵�� ����.
};

