#include "pch.h"
#include "Engine.h" 
#include "Material.h"
#include "Transform.h"
#include "Input.h"
#include "Timer.h"
#include "SceneManager.h"

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

	_device->Init();
	_cmdQueue->Init(_device->GetDevice(), _swapChain);
	_swapChain->Init(window, _device->GetDevice(), _device->GetDXGI(), _cmdQueue->GetCommandQueue());
	_rootSignature->Init();

	CreateConstantBuffer(CBV_REGISTER::b0, sizeof(TransformParams), 5);
	CreateConstantBuffer(CBV_REGISTER::b1, sizeof(MaterialParams), 5);

	_tableDescHeap->Init(5); 
	_depthStencilBuffer->Init(_window);

	ResizeWindow(window.width, window.height);
	 
	GET_SINGLETON(Input)->Init(_window.hwnd);
	GET_SINGLETON(Timer)->Init(); 
}

void Engine::Update()
{
	INPUT->Update();
	TIMER->Update(); 
	GET_SINGLETON(SceneManager)->Update();

	Render();

	ShowFPS();
}

void Engine::LateUpdate()
{
	// TODO
}

void Engine::Render()
{
	RenderBegin();

	GET_SINGLETON(SceneManager)->Render();

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

void Engine::ShowFPS()
{
	uint32 fps = TIMER->GetFPS();

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
