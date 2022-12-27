#include "pch.h"
#include "Engine.h" 
#include "Material.h"

void Engine::Init(const WindowInfo& window)
{
	_window = window;

	// 그려질 화면 크기를 설정
	_viewport = { 0, 0, static_cast<FLOAT>(window.width), static_cast<FLOAT>(window.height), 0.0f, 1.0f };
	_scissorRect = CD3DX12_RECT(0, 0, window.width, window.height);

	_device = make_shared<Device>();
	_cmdQueue = make_shared<CommandQueue>();
	_swapChain = make_shared<SwapChain>(); 
	_rootSignature = make_shared<RootSignature>();

	_tableDescHeap = make_shared<TableDescriptorHeap>();
	_depthStencilBuffer = make_shared<DepthStencilBuffer>();
	
	_input = make_shared<Input>();
	_timer = make_shared<Timer>();

	_device->Init();
	_cmdQueue->Init(_device->GetDevice(), _swapChain);
	_swapChain->Init(window, _device->GetDevice(), _device->GetDXGI(), _cmdQueue->GetCommandQueue());
	_rootSignature->Init();

	CreateConstantBuffer(CBV_REGISTER::b0, sizeof(Transform), 1);
	CreateConstantBuffer(CBV_REGISTER::b1, sizeof(MaterialParams), 1);

	_tableDescHeap->Init(1); 
	_depthStencilBuffer->Init(_window);

	_input->Init(_window.hwnd);
	_timer->Init();

	ResizeWindow(window.width, window.height);
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

void Engine::CreateConstantBuffer(CBV_REGISTER reg, uint32 bufferSize, uint32 count)
{
	uint8 typeInt = static_cast<uint8>(reg);
	assert(_constantBuffers.size() == typeInt);

	shared_ptr<ConstantBuffer> buffer = make_shared<ConstantBuffer>();
	buffer->Init(reg, bufferSize, count);
	_constantBuffers.push_back(buffer);
}

void Engine::RenderBegin()
{
	_cmdQueue->RenderBegin(&_viewport, &_scissorRect);
}

void Engine::RenderEnd()
{
	_cmdQueue->RenderEnd();
}
