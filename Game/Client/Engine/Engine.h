#pragma once

#include "Device.h"
#include "CommandQueue.h"
#include "SwapChain.h" 
#include "RootSignature.h"
#include "Mesh.h"
#include "Shader.h"
#include "ConstantBuffer.h"
#include "TableDescriptorHeap.h" 
#include "RenderTargetGroup.h"

class Engine
{
public:
	void Init(const WindowInfo& window);

	void Update();
	void LateUpdate();
	 
public:
	void Render();

	void RenderBegin();
	void RenderEnd();

public:
	shared_ptr<Device> GetDevice() { return _device; }
	shared_ptr<GraphicsCommandQueue> GetGraphicsCommandQueue() { return _graphicsCmdQueue; }
	shared_ptr<ComputeCommandQueue> GetComputeCommandQueue() { return _computeCmdQueue; }
	shared_ptr<SwapChain> GetSwapChain() { return _swapChain; }
	shared_ptr<RootSignature> GetRootSignature() { return _rootSignature; } 
	shared_ptr<GraphicsDescriptorHeap> GetGraphicsDescriptorHeap() { return _graphicsDescHeap; }
	shared_ptr<ComputeDescriptorHeap> GetComputeDescriptorHeap() { return _computeDescHeap; }
	
	shared_ptr<ConstantBuffer> GetConstantBuffer(CONSTANT_BUFFER_TYPE type) { return _constantBuffers[static_cast<uint8>(type)]; }
	shared_ptr<RenderTargetGroup> GetRTGroup(RENDER_TARGET_GROUP_TYPE type) { return _renderTargetGroup[static_cast<uint8>(type)]; }

	const WindowInfo& GetWindow() { return _window; }

public:
	void ResizeWindow(int32 width, int32 height);

private:
	void ShowFPS();

	void CreateConstantBuffer(CBV_REGISTER reg, uint32 bufferSize, uint32 count);

	void CreateRenderTargetGroups();

private:
	// 그려질 화면 크기 관련
	WindowInfo		_window;
	D3D12_VIEWPORT	_viewport = {};
	D3D12_RECT		_scissorRect = {};

	shared_ptr<Device> _device;
	shared_ptr<GraphicsCommandQueue> _graphicsCmdQueue;
	shared_ptr<ComputeCommandQueue> _computeCmdQueue;
	shared_ptr<SwapChain> _swapChain; 
	shared_ptr<RootSignature> _rootSignature;
	std::vector<shared_ptr<ConstantBuffer>> _constantBuffers;
	shared_ptr<GraphicsDescriptorHeap> _graphicsDescHeap;
	shared_ptr<ComputeDescriptorHeap> _computeDescHeap;

	array< shared_ptr<RenderTargetGroup>, RENDER_TARGET_GROUP_COUNT> _renderTargetGroup;
};

