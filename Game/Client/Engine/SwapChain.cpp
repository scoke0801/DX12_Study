#include "pch.h"
#include "SwapChain.h"

void SwapChain::Init(const WindowInfo& window, ComPtr<IDXGIFactory> dxgi, ComPtr<ID3D12CommandQueue> cmdQueue)
{
	// 이전에 만든 정보 날린다.
	_swapChain.Reset();

	DXGI_SWAP_CHAIN_DESC desc;
	desc.BufferDesc.Width = static_cast<uint32>(window.width); // 버퍼의 해상도 넓이
	desc.BufferDesc.Height = static_cast<uint32>(window.height);// 버퍼의 해상도 높이
	desc.BufferDesc.RefreshRate.Numerator = 60;	// 화면 갱신 비율
	desc.BufferDesc.RefreshRate.Denominator = 1; // 화면 갱신 비율
	desc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;// 버퍼의 디스플레이 형식
	desc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED; 
	desc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
	desc.SampleDesc.Count = 1;	// 멀티 샘플링 off
	desc.SampleDesc.Quality = 0;
	desc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT; // 렌더링 용
	desc.BufferCount = SWAP_CHAIN_BUFFER_COUNT;	// 전면 + 후면 버퍼
	desc.OutputWindow = window.hwnd;
	desc.Windowed = window.windowed;
	desc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD; // 전면<->후면 버퍼 교체 시, 이전 프레임 정보 버림
	desc.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;

	dxgi->CreateSwapChain(cmdQueue.Get(), &desc, &_swapChain);

	for (int i = 0; i < SWAP_CHAIN_BUFFER_COUNT; ++i)
	{
		_swapChain->GetBuffer(i, IID_PPV_ARGS(&_renderTargets[i]));
	}

}

void SwapChain::Present()
{
	_swapChain->Present(0, 0);
}

void SwapChain::SwapIndex()
{
	_backBufferIndex = (_backBufferIndex + 1) % SWAP_CHAIN_BUFFER_COUNT;
}
