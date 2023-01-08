#pragma once

class Game
{
public:
	void Init(__DX12Engine::WindowInfo& info) {}

	void OnUpdate() {}

private:
	DX12Engine* _engine;
};

