#include "pch.h"
#include "Input.h"

void Input::Init(HWND hWnd)
{
	_hWnd = hWnd;
	_states.resize(KEY_TYPE_COUNT, KEY_STATE::NONE);
}

void Input::Update()
{
	HWND hWnd = ::GetActiveWindow();
	if (_hWnd != hWnd) 
	{
		for (uint32 key = 0; key < KEY_TYPE_COUNT; ++key)
		{
			_states[key] = KEY_STATE::NONE;
		}
		return;
	}

	for (uint32 key = 0; key < KEY_TYPE_COUNT; ++key)
	{
		KEY_STATE& state = _states[key];
		// 키가 눌려있으면 true
		if(::GetAsyncKeyState(key) & 0x8000) 
		{ 
			// 이전 프레임 마우스 누른 상태라면 PRESS
			if (state == KEY_STATE::PRESS || state == KEY_STATE::DOWN) 
			{
				state = KEY_STATE::PRESS;
			}
			else
			{
				state = KEY_STATE::DOWN;
			}
		}
		else
		{ 
			// 이전 프레임에 마우스 누른 상태라면 UP
			if (state == KEY_STATE::PRESS || state == KEY_STATE::DOWN)
			{
				state = KEY_STATE::UP;
			}
			else
			{
				state = KEY_STATE::NONE;
			}
		}
	}
}
