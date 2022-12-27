#pragma once

// std::byte 사용하지 않음
#define _HAS_STD_BYTE 0

// 각종 include
#include <windows.h>
#include <tchar.h>
#include <memory>
#include <string>
#include <vector>
#include <array>
#include <list>
#include <map>
using namespace std;

#include <filesystem>
namespace fs = std::filesystem;

#include "d3dx12.h"
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

#include <DirectXTex.h>
#include <DirectXTex.inl>

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

// 각종 typedef
using int8 = __int8;
using int16 = __int16;
using int32 = __int32;
using int64 = __int64;
using uint8 = unsigned __int8;
using uint16 = unsigned __int16;
using uint32 = unsigned __int32;
using uint64 = unsigned __int64;
using Vec2 = XMFLOAT2;
using Vec3 = XMFLOAT3;
using Vec4 = XMFLOAT4;
using Matrix = XMMATRIX;
 
struct WindowInfo
{
	HWND	hwnd;		// 출력 윈도우
	int32	width;		//너비
	int32	height;		// 높이
	bool	windowed;	// 창모드 or 전체화면
}; 

struct Vertex
{
	Vec3 pos;
	Vec4 color;
	Vec2 uv;
};

enum class CBV_REGISTER : uint8
{
	b0,
	b1,
	b2,
	b3,
	b4,

	END
};


// CBV_REGISTER::END부터 시작하는 이유?
// RootDesciptorTable을 사용하는 방식에 의해서..?
enum class SRV_REGISTER : uint8
{
	t0 = static_cast<uint8>(CBV_REGISTER::END),
	t1,
	t2,
	t3,
	t4,

	END
};

enum
{
	SWAP_CHAIN_BUFFER_COUNT = 2,
	CBV_REGISTER_COUNT = CBV_REGISTER::END,
	SRV_REGISTER_COUNT = static_cast<uint8>(SRV_REGISTER::END) - CBV_REGISTER_COUNT,
	REGISTER_COUNT = CBV_REGISTER_COUNT + SRV_REGISTER_COUNT,
};
 
class Engine;
extern unique_ptr<Engine> GEngine;
 
#define DEVICE GEngine->GetDevice()->GetDevice()
#define CMD_LIST GEngine->GetCommandQueue()->GetCommandList()
#define RESOURCE_CMD_LIST GEngine->GetCommandQueue()->GetResourceCommandList()
#define ROOT_SIGNATURE GEngine->GetRootSignature()->GetSignature() 

#define INPUT GEngine->GetInput()
#define DELTA_TIME GEngine->GetTimer()->GetDeltaTime();

#define CONSTANT_BUFFER(type) GEngine->GetConstantBuffer(type)

#define __USE_VSYNC__