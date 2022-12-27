#pragma once

#include "Device.h"
#include "CommandQueue.h"
#include "SwapChain.h" 
#include "RootSignature.h"
#include "Mesh.h"
#include "Shader.h"
#include "ConstantBuffer.h"
#include "TableDescriptorHeap.h"
#include "Texture.h"
#include "DepthStencilBuffer.h"
#include "Input.h"
#include "Timer.h"

class Engine
{
public:
	void Init(const WindowInfo& window);

	void ResizeWindow(int32 width, int32 height);

public:
	void Update();
	void LateUpdate();
	 
public:
	void Render();

	void RenderBegin();
	void RenderEnd();

public:
	shared_ptr<Device> GetDevice() { return _device; }
	shared_ptr<CommandQueue> GetCommandQueue() { return _cmdQueue; }
	shared_ptr<SwapChain> GetSwapChain() { return _swapChain; }
	shared_ptr<RootSignature> GetRootSignature() { return _rootSignature; } 
	shared_ptr<TableDescriptorHeap> GetTableDescriptorHeap() { return _tableDescHeap; }
	shared_ptr<DepthStencilBuffer> GetDepthStencilBuffer() { return _depthStencilBuffer; }

	shared_ptr<ConstantBuffer> GetConstantBuffer(CONSTANT_BUFFER_TYPE type) { return _constantBuffers[static_cast<uint8>(type)]; }

public:
	shared_ptr<Input> GetInput() { return _input; }
	shared_ptr<Timer> GetTimer() { return _timer; }

private:
	void ShowFPS();

	void CreateConstantBuffer(CBV_REGISTER reg, uint32 bufferSize, uint32 count);

private:
	// 그려질 화면 크기 관련
	WindowInfo		_window;
	D3D12_VIEWPORT	_viewport = {};
	D3D12_RECT		_scissorRect = {};

	shared_ptr<Device> _device;
	shared_ptr<CommandQueue> _cmdQueue;
	shared_ptr<SwapChain> _swapChain; 
	shared_ptr<RootSignature> _rootSignature;
	std::vector<shared_ptr<ConstantBuffer>> _constantBuffers;
	shared_ptr<TableDescriptorHeap> _tableDescHeap;
	shared_ptr<DepthStencilBuffer> _depthStencilBuffer;

	shared_ptr<Input> _input;
	shared_ptr<Timer> _timer;
};

