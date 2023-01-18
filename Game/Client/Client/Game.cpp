#include "stdafx.h"
#include "Game.h"
#include "Engine.h"
#include "Timer.h"

void Game::Init(const WindowInfo& info)
{
	GEngine->Init(info);
}

void Game::PreUpdate()
{
	Update(DELTA_TIME);
}

void Game::Update(float deltaTime)
{
	GEngine->Update();
//	GEngine->Update(deltaTime);
}
