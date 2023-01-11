#pragma once

#include "Commons.h"

namespace __DX12Engine
{
	constexpr int32 CLIENT_WIDTH = 1280;
	constexpr int32 CLIENT_HEIGHT = 768;

	constexpr uint8 TITLE_LENGTH = 50;

	constexpr uint8	SWAP_CHAIN_BUFFER_COUNT = 2;

#define TIMER Timer::Get()
#define SCENE_MANAGER SceneManager::Get()
#define CUR_SCENE SceneManager::Get()->GetCurrentScene()

#define ENGINE DX12Engine::Get()
#define DEVICE DX12Engine::Get()->GetDevice()->GetDevice()

#define GRAPHICS_ROOT_SIGNATURE ENGINE::Get()->GetRootSignature(RootSignatureType::GRAPHICS)
#define COMPUTE_ROOT_SIGNATURE ENGINE::Get()->GetRootSignature(RootSignatureType::COMPUTE)

#define GRAPHCIS_COMMAND_LIST ENGINE::Get()->GetCommandQueue(CommandQueueType::GRAPHICS)
#define COMPUTE_COMMAND_LIST ENGINE:Get()->GetCommandQueue(CommandQueueType::COMPUTE)
#define RESOURCES_COMMAND_LIST ENGINE::Get()->GetCommandQueue(CommandQueueType::RESOURCES)
}