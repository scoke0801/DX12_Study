#pragma once

class GameObject;

class Scene
{
public:
	void Awake();
	void Start();
	void Update();
	void LastUpdate();

	void AddGameObject(shared_ptr<GameObject> gameObject);
	void RemoveGameObject(shared_ptr<GameObject> gameObject);

private:
	vector<shared_ptr<GameObject>> _gameObjects;

	// TODO
	// ��ü ������ �����ϱ� ���ؼ��� Layer�� �ΰ�
	// 2���� ���� or ���� �迭�� ��ü���� �ٷ絵�� ����.
};

