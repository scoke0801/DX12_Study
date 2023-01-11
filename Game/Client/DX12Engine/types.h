#pragma once

#include "Commons.h"

namespace __DX12Engine
{
#pragma region EnumCommandQueue
	// CommandQueue에 관련된 타입을 정의.
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
	// 파이프라인을 공통으로 사용하는 타입을 정의할 수 있으면 아래에 추가.
	enum class PipelineType : uint8
	{
		GRAPHICS,
		COMPUTE,
		
		END,

		// TODO 
		// 별도 타입으로 분리해서 적용을 할 지에 대한 고민을 해볼 것..
		PARTICLE,
		SHADOW,
		STATIC_OBJECT,
	};

	constexpr uint8 PIPELINE_COUNT = static_cast<uint8>(PipelineType::END);
#pragma endregion
}