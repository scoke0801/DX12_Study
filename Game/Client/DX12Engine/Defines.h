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

#define ENGINE DX12Engine::Get()
#define DEVICE ENGINE->GetDevice()->GetDevice()

#define GRAPHICS_ROOT_SIGNATURE ENGINE->GetRootSignature()->GetGraphicsRootSignature()
#define COMPUTE_ROOT_SIGNATURE ENGINE->GetRootSignature()->GetComputeRootSignature()

#define GRAPHCIS_COMMAND_LIST  ENGINE->GetGraphicsCommandQueue()->GetGraphicsCmdList()
#define COMPUTE_COMMAND_LIST ENGINE->GetComputeCommandQueue()->GetComputeCmdList()
#define RESOURCES_COMMAND_LIST ENGINE->GetCommandQueue(CommandQueueType::RESOURCES)->GetCommandList()
}