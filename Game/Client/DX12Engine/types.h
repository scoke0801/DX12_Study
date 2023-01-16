#pragma once

#include "Commons.h"

namespace __DX12Engine
{
	enum class CBV_REGISTER : uint8
	{
		b0,
		b1,
		b2,
		b3,
		b4,

		END
	};

	enum class SRV_REGISTER : uint8
	{
		t0 = static_cast<uint8>(CBV_REGISTER::END),
		t1,
		t2,
		t3,
		t4,
		t5,
		t6,
		t7,
		t8,
		t9,

		END
	};

	enum class UAV_REGISTER : uint8
	{
		u0 = static_cast<uint8>(SRV_REGISTER::END),
		u1,
		u2,
		u3,
		u4,

		END,
	};

	constexpr uint8 SWAP_CHAIN_BUFFER_COUNT = 2;
	constexpr uint8	CBV_REGISTER_COUNT = static_cast<uint8>(CBV_REGISTER::END);
	constexpr uint8 SRV_REGISTER_COUNT = static_cast<uint8>(SRV_REGISTER::END) - CBV_REGISTER_COUNT;
	constexpr uint8 CBV_SRV_REGISTER_COUNT = CBV_REGISTER_COUNT + SRV_REGISTER_COUNT;
	constexpr uint8 UAV_REGISTER_COUNT = static_cast<uint8>(UAV_REGISTER::END) - CBV_SRV_REGISTER_COUNT;
	constexpr uint8 TOTAL_REGISTER_COUNT = CBV_SRV_REGISTER_COUNT + UAV_REGISTER_COUNT;
	

	enum class RENDER_TARGET_GROUP_TYPE : uint8
	{
		SWAP_CHAIN, // BACK_BUFFER, FRONT_BUFFER
		SHADOW, // SHADOW
		G_BUFFER, // POSITION, NORMAL, COLOR
		LIGHTING, // DIFFUSE LIGHT, SPECULAR LIGHT	
		END,
	};

	constexpr uint8 RENDER_TARGET_SHADOW_GROUP_MEMBER_COUNT = 1;
	constexpr uint8 RENDER_TARGET_G_BUFFER_GROUP_MEMBER_COUNT = 3;
	constexpr uint8 RENDER_TARGET_LIGHTING_GROUP_MEMBER_COUNT = 2;
	constexpr uint8 RENDER_TARGET_GROUP_COUNT = static_cast<uint8>(RENDER_TARGET_GROUP_TYPE::END);

}