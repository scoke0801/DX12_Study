#include "pch.h"
#include "CommandQueue.h"
#include "DX12Engine.h"
#include "SwapChain.h"
#include "DescriptorHeap.h"
#include "RootSignature.h"
#include "DescriptorHeap.h"
#include "Texture.h"

__DX12Engine::GraphicsCommandQueue::~GraphicsCommandQueue()
{
	::CloseHandle(_fenceEvent);
}

void __DX12Engine::GraphicsCommandQueue::Init(ComPtr<ID3D12Device> device, shared_ptr<SwapChain> swapChain)
{
	_swapChain = swapChain;

	D3D12_COMMAND_QUEUE_DESC queueDesc = {};
	queueDesc.Type = D3D12_COMMAND_LIST_TYPE_DIRECT;
	queueDesc.Flags = D3D12_COMMAND_QUEUE_FLAG_NONE;

	device->CreateCommandQueue(&queueDesc, IID_PPV_ARGS(&_cmdQueue));

	device->CreateCommandAllocator(D3D12_COMMAND_LIST_TYPE_DIRECT, IID_PPV_ARGS(&_cmdAlloc));
	device->CreateCommandList(0, D3D12_COMMAND_LIST_TYPE_DIRECT, _cmdAlloc.Get(), nullptr, IID_PPV_ARGS(&_cmdList));
	_cmdList->Close();

	device->CreateCommandAllocator(D3D12_COMMAND_LIST_TYPE_DIRECT, IID_PPV_ARGS(&_resCmdAlloc));
	device->CreateCommandList(0, D3D12_COMMAND_LIST_TYPE_DIRECT, _resCmdAlloc.Get(), nullptr, IID_PPV_ARGS(&_resCmdList));

	// CreateFence
	// - CPU와 GPU의 동기화 수단으로 쓰인다
	device->CreateFence(0, D3D12_FENCE_FLAG_NONE, IID_PPV_ARGS(&_fence));
	_fenceEvent = ::CreateEvent(nullptr, FALSE, FALSE, nullptr);
}

void __DX12Engine::GraphicsCommandQueue::WaitSync()
{
	// Advance the fence value to mark commands up to this fence point.
	_fenceValue++;

	// Add an instruction to the command queue to set a new fence point.  Because we 
	// are on the GPU timeline, the new fence point won't be set until the GPU finishes
	// processing all the commands prior to this Signal().
	_cmdQueue->Signal(_fence.Get(), _fenceValue);

	// Wait until the GPU has completed commands up to this fence point.
	if (_fence->GetCompletedValue() < _fenceValue)
	{
		// Fire event when GPU hits current fence.  
		_fence->SetEventOnCompletion(_fenceValue, _fenceEvent);

		// Wait until the GPU hits current fence event is fired.
		::WaitForSingleObject(_fenceEvent, INFINITE);
	}
}

void __DX12Engine::GraphicsCommandQueue::RenderBegin()
{
	_cmdAlloc->Reset();
	_cmdList->Reset(_cmdAlloc.Get(), nullptr);

	//int8 backIndex = _swapChain->GetBackBufferIndex();

	//D3D12_RESOURCE_BARRIER barrier = CD3DX12_RESOURCE_BARRIER::Transition(
	//	ENGINE->GetRTGroup(RENDER_TARGET_GROUP_TYPE::SWAP_CHAIN)->GetRTTexture(backIndex)->GetTex2D().Get(),
	//	D3D12_RESOURCE_STATE_PRESENT, // 화면 출력
	//	D3D12_RESOURCE_STATE_RENDER_TARGET); // 외주 결과

	//_cmdList->SetGraphicsRootSignature(GRAPHICS_ROOT_SIGNATURE.Get());

	//ENGINE->GetConstantBuffer(CONSTANT_BUFFER_TYPE::TRANSFORM)->Clear();
	//ENGINE->GetConstantBuffer(CONSTANT_BUFFER_TYPE::MATERIAL)->Clear();

	//ENGINE->GetGraphicsDescHeap();
	//ENGINE->GetGraphicsDescHeap()->Clear();

	//ID3D12DescriptorHeap* descHeap = ENGINE->GetGraphicsDescHeap()->GetDescriptorHeap().Get();
	//_cmdList->SetDescriptorHeaps(1, &descHeap);

	//_cmdList->ResourceBarrier(1, &barrier);
}

void __DX12Engine::GraphicsCommandQueue::RenderEnd()
{
}

void __DX12Engine::GraphicsCommandQueue::FlushResourceCommandQueue()
{
}

__DX12Engine::ComputeCommandQueue::~ComputeCommandQueue()
{
}

void __DX12Engine::ComputeCommandQueue::Init(ComPtr<ID3D12Device> device)
{
}

void __DX12Engine::ComputeCommandQueue::WaitSync()
{
}

void __DX12Engine::ComputeCommandQueue::FlushComputeCommandQueue()
{
}
