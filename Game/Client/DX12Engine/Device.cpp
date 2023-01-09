#include "pch.h"
#include "Device.h"

void __DX12Engine::Device::Init()
{
#ifdef _DEBUG
	::D3D12GetDebugInterface(IID_PPV_ARGS(&_debugController));
	_debugController->EnableDebugLayer();
#endif

	::CreateDXGIFactory(IID_PPV_ARGS(&_dxgiFactory));

	::D3D12CreateDevice(nullptr, D3D_FEATURE_LEVEL_11_0, IID_PPV_ARGS(&_device));
}
