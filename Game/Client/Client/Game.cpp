#include "stdafx.h"
#include "Game.h"

void Game::Init(__DX12Engine::WindowInfo& info)
{
	_engine = std::make_shared<__DX12Engine::DX12Engine>();
	_engine->Init(info);
}

void Game::OnUpdate()
{
	_engine->PreUpdate();
}
