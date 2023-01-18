#pragma once
class Game
{
public:
	void Init(const WindowInfo& info);

	void PreUpdate();

private:
	void Update(float deltaTime);
};

