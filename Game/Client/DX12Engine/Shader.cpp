#include "pch.h"
#include "Shader.h"
#include "GameObject.h"

void __DX12Engine::Shader::Update(float deltaTime)
{
	for (auto& object : _objects)
	{
		object->Update(deltaTime);
	}
}

void __DX12Engine::Shader::LateUpdate(float deltaTime)
{
	for (auto& object : _objects)
	{
		object->LateUpdate(deltaTime);
	}
}
