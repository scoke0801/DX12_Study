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
		// Ű�� ���������� true
		if(::GetAsyncKeyState(key) & 0x8000) 
		{ 
			// ���� ������ ���콺 ���� ���¶�� PRESS
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
			// ���� �����ӿ� ���콺 ���� ���¶�� UP
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
