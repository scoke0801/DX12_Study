#pragma once
#include "Object.h"

namespace __DX12Engine
{
	class Component : public Object
	{
	public:
		virtual ~Component() {}

	public:
		virtual void Update(float deltaTime) {}
		virtual void LateUpdate(float deltaTime) {}
	};
}

