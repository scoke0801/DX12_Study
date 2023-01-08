﻿#pragma once
 
#include "d3dx12.h"
#include "SimpleMath.h"
#include <d3d12.h>
#include <wrl.h>
#include <d3dcompiler.h>
#include <dxgi.h>
#include <DirectXMath.h>
#include <DirectXPackedVector.h>
#include <DirectXColors.h>
using namespace DirectX;
using namespace DirectX::PackedVector;
using namespace Microsoft::WRL;
 
#include <DX12/DirectXTex.h>
#include <DX12/DirectXTex.inl>

// 각종 lib
#pragma comment(lib, "d3d12")
#pragma comment(lib, "dxgi")
#pragma comment(lib, "dxguid")
#pragma comment(lib, "d3dcompiler")

#ifdef _DEBUG
#pragma comment(lib, "DirectXTex_Debug.lib")
#else
#pragma comment(lib, "DirectXTex_Release.lib")
#endif

namespace __DX12Engine
{	
	// 각종 typedef
	using int8 = __int8;
	using int16 = __int16;
	using int32 = __int32;
	using int64 = __int64;
	using uint8 = unsigned __int8;
	using uint16 = unsigned __int16;
	using uint32 = unsigned __int32;
	using uint64 = unsigned __int64;
	using Vec2 = DirectX::SimpleMath::Vector2;
	using Vec3 = DirectX::SimpleMath::Vector3;
	using Vec4 = DirectX::SimpleMath::Vector4;
	using Matrix = DirectX::SimpleMath::Matrix;

	struct WindowInfo
	{
		HWND	hwnd; // 출력 윈도우
		int32	width; // 너비
		int32	height; // 높이
		bool	windowed; // 창모드 or 전체화면
	}; 
}