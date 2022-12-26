#include "pch.h"
#include "Engine.h" 
 
void Engine::Init(const WindowInfo& window)
{
	_window = window;

	// �׷��� ȭ�� ũ�⸦ ����
	_viewport = { 0, 0, static_cast<FLOAT>(window.width), static_cast<FLOAT>(window.height), 0.0f, 1.0f };
	_scissorRect = CD3DX12_RECT(0, 0, window.width, window.height);

	_device = make_shared<Device>();
	_cmdQueue = make_shared<CommandQueue>();
	_swapChain = make_shared<SwapChain>(); 
	_rootSignature = make_shared<RootSignature>();
	_constantBuffer = make_shared<ConstantBuffer>();
	_tableDescHeap = make_shared<TableDescriptorHeap>();
	_depthStencilBuffer = make_shared<DepthStencilBuffer>();
	
	_input = make_shared<Input>();
	_timer = make_shared<Timer>();

	_device->Init();
	_cmdQueue->Init(_device->GetDevice(), _swapChain);
	_swapChain->Init(window, _device->GetDevice(), _device->GetDXGI(), _cmdQueue->GetCommandQueue());
	_rootSignature->Init();
	_constantBuffer->Init(sizeof(Transform), 256);
	_tableDescHeap->Init(256); 
	_depthStencilBuffer->Init(_window);

	_input->Init(_window.hwnd);
	_timer->Init();

	ResizeWindow(window.width, window.height);
}

void Engine::Render()
{
	RenderBegin();

	// TODO : ������ ��ü�� �׷��ش�.

	RenderEnd();
}

void Engine::ResizeWindow(int32 width, int32 height)
{
	_window.width = width;
	_window.height = height;

	RECT rect = { 0, 0, _window.width, _window.height };
	::AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, false);
	::SetWindowPos(_window.hwnd, 0, 100, 100, width, height, 0);
	 
	_depthStencilBuffer->Init(_window);
}

void Engine::Update()
{
	_input->Update();
	_timer->Update();

	ShowFPS();
}

void Engine::ShowFPS()
{
	uint32 fps = _timer->GetFPS();

	WCHAR text[100] = L"";
	::wsprintf(text, L"FPS : %d", fps);

	::SetWindowText(_window.hwnd, text);
}

void Engine::RenderBegin()
{
	_cmdQueue->RenderBegin(&_viewport, &_scissorRect);
}

void Engine::RenderEnd()
{
	_cmdQueue->RenderEnd();
}
