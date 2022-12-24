#include "stdafx.h"
#include "Game.h"
#include "Engine.h"

shared_ptr<Mesh> mesh = make_shared<Mesh>();
shared_ptr<Shader> shader = make_shared<Shader>();

void Game::Init(const WindowInfo& window)
{
	GEngine->Init(window);


	vector<Vertex> vec(3);
	vec[0].pos = { 0.f, 0.5f, 0.5f };
	vec[0].color = {1.0f, 0.0f, 0.0f, 1.0f };
	vec[1].pos = { 0.5f, -0.5f, 0.5f };
	vec[1].color = { 0.0f, 1.0f, 0.0f, 1.0f };
	vec[2].pos = { -0.5f, -0.5f, 0.5f };
	vec[2].color = { 0.0f, 0.0f, 1.0f, 1.0f };
	mesh->Init(vec);

	shader->Init(L"..\\Resources\\Shader\\default.hlsli");

	GEngine->GetCommandQueue()->WaitSync();
}

void Game::Update()
{
	//GEngine->Render(); 
	GEngine->RenderBegin();

	shader->Update();
	mesh->Render();

	GEngine->RenderEnd();
}
