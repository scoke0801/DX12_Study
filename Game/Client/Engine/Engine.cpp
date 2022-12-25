#include "pch.h"
#include "Engine.h" 
 
void Engine::Init(const WindowInfo& window)
{
	_window = window;
	ResizeWindow(window.width, window.height);

	// 그려질 화면 크기를 설정
	_viewport = { 0, 0, static_cast<FLOAT>(window.width), static_cast<FLOAT>(window.height), 0.0f, 1.0f };
	_scissorRect = CD3DX12_RECT(0, 0, window.width, window.height);

	_device = make_shared<Device>();
	_cmdQueue = make_shared<CommandQueue>();
	_swapChain = make_shared<SwapChain>(); 
	_rootSignature = make_shared<RootSignature>();
	_constantBuffer = make_shared<ConstantBuffer>();
	_tableDescHeap = make_shared<TableDescriptorHeap>();

	_device->Init();
	_cmdQueue->Init(_device->GetDevice(), _swapChain);
	_swapChain->Init(window, _device->GetDevice(), _device->GetDXGI(), _cmdQueue->GetCommandQueue());
	_rootSignature->Init(_device->GetDevice());
	_constantBuffer->Init(sizeof(Transform), 256);
	_tableDescHeap->Init(256);

}

void Engine::Render()
{
	RenderBegin();

	// TODO : 나머지 물체를 그려준다.

	RenderEnd();
}

void Engine::ResizeWindow(int32 width, int32 height)
{
	_window.width = width;
	_window.height = height;

	RECT rect = { 0, 0, _window.width, _window.height };
	::AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, false);
	::SetWindowPos(_window.hwnd, 0, 100, 100, width, height, 0);

}

void Engine::RenderBegin()
{
	_cmdQueue->RenderBegin(&_viewport, &_scissorRect);
}

void Engine::RenderEnd()
{
	_cmdQueue->RenderEnd();
}
