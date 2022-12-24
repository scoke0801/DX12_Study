#include "pch.h"
#include "SwapChain.h"

void SwapChain::Init(const WindowInfo& window, ComPtr<IDXGIFactory> dxgi, ComPtr<ID3D12CommandQueue> cmdQueue)
{
	// ������ ���� ���� ������.
	_swapChain.Reset();

	DXGI_SWAP_CHAIN_DESC desc;
	desc.BufferDesc.Width = static_cast<uint32>(window.width); // ������ �ػ� ����
	desc.BufferDesc.Height = static_cast<uint32>(window.height);// ������ �ػ� ����
	desc.BufferDesc.RefreshRate.Numerator = 60;	// ȭ�� ���� ����
	desc.BufferDesc.RefreshRate.Denominator = 1; // ȭ�� ���� ����
	desc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;// ������ ���÷��� ����
	desc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED; 
	desc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
	desc.SampleDesc.Count = 1;	// ��Ƽ ���ø� off
	desc.SampleDesc.Quality = 0;
	desc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT; // ������ ��
	desc.BufferCount = SWAP_CHAIN_BUFFER_COUNT;	// ���� + �ĸ� ����
	desc.OutputWindow = window.hwnd;
	desc.Windowed = window.windowed;
	desc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD; // ����<->�ĸ� ���� ��ü ��, ���� ������ ���� ����
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
