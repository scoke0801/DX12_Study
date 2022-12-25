#pragma once

#include "Device.h"
#include "CommandQueue.h"
#include "SwapChain.h" 
#include "RootSignature.h"
#include "Mesh.h"
#include "Shader.h"
#include "ConstantBuffer.h"
#include "TableDescriptorHeap.h"

class Engine
{
public:
	void Init(const WindowInfo& window);
	void Render();

	void RenderBegin();
	void RenderEnd();

	void ResizeWindow(int32 width, int32 height);

public:
	shared_ptr<Device> GetDevice() { return _device; }
	shared_ptr<CommandQueue> GetCommandQueue() { return _cmdQueue; }
	shared_ptr<SwapChain> GetSwapChain() { return _swapChain; }
	shared_ptr<RootSignature> GetRootSignature() { return _rootSignature; }
	shared_ptr<ConstantBuffer> GetConstantBuffer() { return _constantBuffer; }
	shared_ptr<TableDescriptorHeap> GetTableDescriptorHeap() { return _tableDescHeap; }

private:
	// 그려질 화면 크기 관련
	WindowInfo		_window;
	D3D12_VIEWPORT	_viewport = {};
	D3D12_RECT		_scissorRect = {};

	shared_ptr<Device> _device;
	shared_ptr<CommandQueue> _cmdQueue;
	shared_ptr<SwapChain> _swapChain; 
	shared_ptr<RootSignature> _rootSignature;
	shared_ptr<ConstantBuffer> _constantBuffer;
	shared_ptr<TableDescriptorHeap> _tableDescHeap;
};

