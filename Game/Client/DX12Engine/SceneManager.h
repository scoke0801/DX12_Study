#pragma once

namespace __DX12Engine
{
	class Scene;

	class SceneManager : public Singleton<SceneManager>
	{
	private:
		friend class Singleton;
		SceneManager();

	public:
		void Update(float deltaTime);
		void LateUpdate(float deltaTime);

		shared_ptr<Scene> GetCurrentScene() { return _activeScene; }

	private:
		shared_ptr<Scene> _activeScene;
	};
}
