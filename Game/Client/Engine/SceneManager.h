#pragma once

class Scene;

class SceneManager
{
	DECLARE_SINGLETON(SceneManager);

public:
	void Updaet();

	void LoadScene(wstring sceneName);

public:
	shared_ptr<Scene> GetActiveScene() { return _activeScene;  }

private:
	shared_ptr<Scene> LoadTestScene();

private:
	shared_ptr<Scene> _activeScene;
};

