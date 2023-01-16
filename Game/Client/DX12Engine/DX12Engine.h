#pragma once

#include "Device.h"
#include "CommandQueue.h"
#include "SwapChain.h"
#include "RootSignature.h"
#include "Mesh.h"
#include "Shader.h"
#include "ConstantBuffer.h"
#include "DescriptorHeap.h"
#include "Texture.h"
#include "RenderTargetGroup.h"

namespace __DX12Engine
{
	
	class DX12Engine : public Singleton<DX12Engine>
	{
	private:
		friend class DX12Engine;

	public:
		void Init(const WindowInfo& info);

		void PreUpdate();

		void Update(float deltaTime);
		void LateUpdate(float deltaTime);

	public:
		shared_ptr<Device> GetDevice() { return _device; }
		shared_ptr<SwapChain> GetSwapChain() { return _swapChain; }

		//	shared_ptr<RenderTargetGroup> GetRTGroup(RENDER_TARGET_GROUP_TYPE type) { return _rtGroups[static_cast<uint8>(type)]; }

		shared_ptr<RootSignature> GetRootSignature() { return _rootSignature; }
		shared_ptr<GraphicsCommandQueue> GetGraphicsCommandQueue() { return _graphicsCommandQueue; }
		shared_ptr<ComputeCommandQueue> GetComputeCommandQueue() { return _computeCommandQueue; }

		shared_ptr<GraphicsDescriptorHeap> GetGraphicsDescHeap() { return _graphicsDescHeap; }
		shared_ptr<ComputeDescriptorHeap> GetComputeDescHeap() { return _computeDescHeap; }

		shared_ptr<ConstantBuffer> GetConstantBuffer(CONSTANT_BUFFER_TYPE type) { return _constantBuffers[static_cast<uint8>(type)]; }

	private:
#ifdef __SHOW_FPS__
		void ShowFPS();
#endif

		WindowInfo  _info;

		WCHAR		_titleText[50];
		size_t		_titleLength;

	private:
		shared_ptr<Device> _device;
		shared_ptr<GraphicsCommandQueue> _graphicsCommandQueue;
		shared_ptr<ComputeCommandQueue>  _computeCommandQueue;
		shared_ptr<SwapChain> _swapChain;
		shared_ptr<RootSignature> _rootSignature;
		shared_ptr<GraphicsDescriptorHeap> _graphicsDescHeap;
		shared_ptr<ComputeDescriptorHeap> _computeDescHeap;

		vector<shared_ptr<ConstantBuffer>> _constantBuffers;

		shared_ptr< RenderTargetGroup> _Test;

		array<shared_ptr<RenderTargetGroup>, RENDER_TARGET_GROUP_COUNT > _rtGroups;
	};
}

