#include "pch.h"
#include "SwapChain.h"
#include "Engine.h"

void SwapChain::Init(const WindowInfo& window, ComPtr<ID3D12Device> device, ComPtr<IDXGIFactory> dxgi, ComPtr<ID3D12CommandQueue> cmdQueue)
{ 
	CreateSwapChain(window, dxgi, cmdQueue);
}

void SwapChain::Present()
{
#if defined(__USE_VSYNC__)
	// Lock to screen refresh rate.
	_swapChain->Present(1, 0);
#else
	// present as fast as possible.
	_swapChain->Present(0, 0);
#endif
}

void SwapChain::SwapIndex()
{
	_backBufferIndex = (_backBufferIndex + 1) % SWAP_CHAIN_BUFFER_COUNT;
}


void SwapChain::CreateSwapChain(const WindowInfo& window, ComPtr<IDXGIFactory> dxgi, ComPtr<ID3D12CommandQueue> cmdQueue)
{
	// 이전에 만든 정보 날린다.
	_swapChain.Reset();

	DXGI_SWAP_CHAIN_DESC desc;
	desc.BufferDesc.Width = static_cast<uint32>(window.width); // 버퍼의 해상도 넓이
	desc.BufferDesc.Height = static_cast<uint32>(window.height);// 버퍼의 해상도 높이
	desc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	desc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
	desc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;// 버퍼의 디스플레이 형식

#if defined(__USE_VSYNC__)	
	desc.BufferDesc.RefreshRate.Numerator = 0;	// 화면 갱신 비율
	desc.BufferDesc.RefreshRate.Denominator = 1; // 화면 갱신 비율
#else
	desc.BufferDesc.RefreshRate.Numerator = 60;	// 화면 갱신 비율
	desc.BufferDesc.RefreshRate.Denominator = 1; // 화면 갱신 비율
#endif

	desc.SampleDesc.Count = 1;	// 멀티 샘플링 off
	desc.SampleDesc.Quality = 0;
	desc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT; // 렌더링 용
	desc.BufferCount = SWAP_CHAIN_BUFFER_COUNT;	// 전면 + 후면 버퍼
	desc.OutputWindow = window.hwnd;
	desc.Windowed = window.windowed;
	desc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD; // 전면<->후면 버퍼 교체 시, 이전 프레임 정보 버림
	desc.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;

	dxgi->CreateSwapChain(cmdQueue.Get(), &desc, &_swapChain);

#if !defined(__USE_SWAPCHAIN_FULLSCREEN_STATAE__)
	// ALT + Enter키로 전체화면으로 전환하는 것을 막음.
	dxgi->MakeWindowAssociation(window.hwnd, DXGI_MWA_NO_ALT_ENTER);
#endif
}
