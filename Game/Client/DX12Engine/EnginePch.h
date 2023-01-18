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

#include <DirectXTex.h>
#include <DirectXTex.inl>

#include "FBX/fbxsdk.h"

// 각종 lib
#pragma comment(lib, "d3d12")
#pragma comment(lib, "dxgi")
#pragma comment(lib, "dxguid")
#pragma comment(lib, "d3dcompiler")

#ifdef _DEBUG
#pragma comment(lib, "DX12\\DirectXTex_debug.lib")
#else
#pragma comment(lib, "DX12\\DirectXTex_Release.lib")
#endif

#ifdef _DEBUG
#pragma comment(lib, "FBX\\debug\\libfbxsdk-md.lib")
#pragma comment(lib, "FBX\\debug\\libxml2-md.lib")
#pragma comment(lib, "FBX\\debug\\zlib-md.lib")
#else
#pragma comment(lib, "FBX\\release\libfbxsdk-md.lib")
#pragma comment(lib, "FBX\\release\libxml2-md.lib")
#pragma comment(lib, "FBX\\release\\zlib-md.lib")
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
using Vec2 = DirectX::SimpleMath::Vector2;
using Vec3 = DirectX::SimpleMath::Vector3;
using Vec4 = DirectX::SimpleMath::Vector4;
using Matrix = DirectX::SimpleMath::Matrix;

#include "Defines.h"
#include "Types.h"

extern unique_ptr<class Engine> GEngine;

// Utils
wstring s2ws(const string& s);
string ws2s(const wstring& s);