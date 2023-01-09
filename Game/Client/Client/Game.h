#pragma once

#include "DX12Engine.h"
class Game
{
public:
	void Init(__DX12Engine::WindowInfo& info);

	void OnUpdate();

private:
	std::shared_ptr<__DX12Engine::DX12Engine> _engine;
};

