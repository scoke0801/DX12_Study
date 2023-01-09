#include "pch.h"
#include "DX12Engine.h"
#include "Timer.h"
#include "Input.h"
#include "SceneManager.h" 
#include "Device.h"

void __DX12Engine::DX12Engine::Init(const WindowInfo& info)
{
	_info = info;
	 
	 _device = make_shared<Device>();
	_device->Init();

#if defined(__SHOW_FPS__)
	_tcscpy_s(_titleText, _T("DX12_MMO("));
	_titleLength = _tcslen(_titleText);
#else
	_tcscpy_s(_titleText, _T("DX12_MMO"));
	_titleLength = _tcslen(_titleText);
#endif
}

void __DX12Engine::DX12Engine::PreUpdate()
{
	TIMER->Update();
	Input::Get()->Update();

	Update(TIMER->GetDeldatTime());

	LateUpdate(TIMER->GetDeldatTime());

#if defined(__SHOW_FPS__)
	ShowFPS();
#endif
}

void __DX12Engine::DX12Engine::Update(float deltaTime)
{
	SCENE_MANAGER->Update(deltaTime);
}

void __DX12Engine::DX12Engine::LateUpdate(float deltaTime)
{
	SCENE_MANAGER->LateUpdate(deltaTime);
}

#if defined(__SHOW_FPS__)
void __DX12Engine::DX12Engine::ShowFPS()
{
	_itow_s(TIMER->GetFPS(),
		_titleText + _titleLength,
		TITLE_LENGTH - _titleLength, 10);
	wcscat_s(_titleText + _titleLength, TITLE_LENGTH - _titleLength, TEXT(" FPS)"));
	SetWindowText(_info.hwnd, _titleText);
}
#endif