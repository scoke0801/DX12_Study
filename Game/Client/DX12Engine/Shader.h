#pragma once

namespace __DX12Engine
{
	class GameObject;

	class Shader
	{
	public:
		void Update(float deltaTime);
		void LateUpdate(float deltaTime);

		vector<shared_ptr<GameObject>> _objects;
	};
}

