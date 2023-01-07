#include "stdafx.h"
#include "Game.h"
#include "Engine.h"
#include "SceneManager.h"
  
void Game::Init(const WindowInfo& window)
{
	GEngine->Init(window); 

	GET_SINGLE(SceneManager)->LoadScene(L"TestScene"); 
}

void Game::Update()
{
	GEngine->Update(); 
	
	/*float deltaTime = DELTA_TIME;
	float speed = 1.0f;
	if (INPUT->GetButton(KEY_TYPE::W)) 
	{
		t.offset.y += speed * deltaTime;
	}
	if (INPUT->GetButton(KEY_TYPE::S)) 
	{
		t.offset.y -= speed * deltaTime;
	}
	if (INPUT->GetButton(KEY_TYPE::A))
	{
		t.offset.x -= speed * deltaTime;
	}
	if (INPUT->GetButton(KEY_TYPE::D))
	{
		t.offset.x += speed * deltaTime;
	}*/  

	//gameObject->Update(); 
}
