#include "stdafx.h"
#include "Game.h"

void Game::Init(__DX12Engine::WindowInfo& info)
{
	__DX12Engine::DX12Engine::Get()->Init(info);
}

void Game::OnUpdate()
{
	// TODO.
	// �� �������� ȣ��ɰǵ�, �̱������� ȣ��Ǵ� �Ͱ� ���� ��ü�� ���� �� �ٷ���� ��
	// ���� ���̰� �߻��ϴ� ��, �߻��Ѵٸ� ������� ������ �������̰� ������ Ȯ���غ� ��.
	__DX12Engine::DX12Engine::Get()->PreUpdate();
}
