#pragma once

namespace __DX12Engine
{
	class Scene
	{
	public:
		Scene() {}
		virtual ~Scene() {}

	public:
		virtual void Update(float deltaTime);
		virtual void LateUpdate(float deltaTime);
	};
}

