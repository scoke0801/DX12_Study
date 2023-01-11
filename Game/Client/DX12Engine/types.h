#pragma once

#include "Commons.h"

namespace __DX12Engine
{
#pragma region EnumCommandQueue
	// CommandQueue�� ���õ� Ÿ���� ����.
	enum class CommandQueueType : uint8
	{
		GRAPHICS,
		COMPUTE,
		RESOURCE,

		END,
	};

	constexpr uint8 COMMAND_LIST_COUNT = static_cast<uint8>(CommandQueueType::END);
#pragma endregion


#pragma region EnumRootSignature
	enum class RootSignatureType : uint8
	{
		GRAPHICS,
		COMPUTE,

		END,
	};

	constexpr uint8 ROOT_SIGNATURE_COUNT = static_cast<uint8>(RootSignatureType::END);
#pragma endregion

#pragma region EnumDescriptorHeap	
	enum class DescriptorHeapType : uint8
	{
		GRAPHICS,
		COMPUTE,
	
		END
	};
	constexpr uint8 DESCRIPTOR_HEAP_COUNT = static_cast<uint8>(DescriptorHeapType::END);
#pragma endregion

#pragma region PIPELINE_TYPE
	// ������������ �������� ����ϴ� Ÿ���� ������ �� ������ �Ʒ��� �߰�.
	enum class PipelineType : uint8
	{
		GRAPHICS,
		COMPUTE,
		
		END,

		// TODO 
		// ���� Ÿ������ �и��ؼ� ������ �� ���� ���� ����� �غ� ��..
		PARTICLE,
		SHADOW,
		STATIC_OBJECT,
	};

	constexpr uint8 PIPELINE_COUNT = static_cast<uint8>(PipelineType::END);
#pragma endregion
}