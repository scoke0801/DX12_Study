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
	// ������ ���� ���� ������.
	_swapChain.Reset();

	DXGI_SWAP_CHAIN_DESC desc;
	desc.BufferDesc.Width = static_cast<uint32>(window.width); // ������ �ػ� ����
	desc.BufferDesc.Height = static_cast<uint32>(window.height);// ������ �ػ� ����
	desc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	desc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
	desc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;// ������ ���÷��� ����

#if defined(__USE_VSYNC__)	
	desc.BufferDesc.RefreshRate.Numerator = 0;	// ȭ�� ���� ����
	desc.BufferDesc.RefreshRate.Denominator = 1; // ȭ�� ���� ����
#else
	desc.BufferDesc.RefreshRate.Numerator = 60;	// ȭ�� ���� ����
	desc.BufferDesc.RefreshRate.Denominator = 1; // ȭ�� ���� ����
#endif

	desc.SampleDesc.Count = 1;	// ��Ƽ ���ø� off
	desc.SampleDesc.Quality = 0;
	desc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT; // ������ ��
	desc.BufferCount = SWAP_CHAIN_BUFFER_COUNT;	// ���� + �ĸ� ����
	desc.OutputWindow = window.hwnd;
	desc.Windowed = window.windowed;
	desc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD; // ����<->�ĸ� ���� ��ü ��, ���� ������ ���� ����
	desc.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;

	dxgi->CreateSwapChain(cmdQueue.Get(), &desc, &_swapChain);

#if !defined(__USE_SWAPCHAIN_FULLSCREEN_STATAE__)
	// ALT + EnterŰ�� ��üȭ������ ��ȯ�ϴ� ���� ����.
	dxgi->MakeWindowAssociation(window.hwnd, DXGI_MWA_NO_ALT_ENTER);
#endif
}
