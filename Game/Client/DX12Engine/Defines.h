#pragma once

#include "Commons.h"

namespace __DX12Engine
{
	constexpr int32 CLIENT_WIDTH = 1280;
	constexpr int32 CLIENT_HEIGHT = 768;

	constexpr uint8 TITLE_LENGTH = 50;

#define TIMER Timer::Get()
#define SCENE_MANAGER SceneManager::Get()
#define CUR_SCENE SceneManager::Get()->GetCurrentScene()
}