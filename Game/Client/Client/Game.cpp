#include "stdafx.h"
#include "Game.h"

void Game::Init(__DX12Engine::WindowInfo& info)
{
	__DX12Engine::DX12Engine::Get()->Init(info);
}

void Game::OnUpdate()
{
	// TODO.
	// 매 루프마다 호출될건데, 싱글톤으로 호출되는 것과 별도 객체로 생성 후 다루어질 때
	// 성능 차이가 발생하는 지, 발생한다면 어느정도 수준의 성능차이가 생길지 확인해볼 것.
	__DX12Engine::DX12Engine::Get()->PreUpdate();
}
