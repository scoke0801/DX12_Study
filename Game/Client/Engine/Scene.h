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
	// 객체 관리를 용이하기 위해서는 Layer를 두고
	// 2차원 벡터 or 벡터 배열로 객체들을 다루도록 수정.
};

