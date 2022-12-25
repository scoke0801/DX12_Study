#include "pch.h"
#include "CommandQueue.h"
#include "SwapChain.h" 
#include "Engine.h"

CommandQueue::~CommandQueue()
{
	::CloseHandle(_fenceEvent);
}

void CommandQueue::Init(ComPtr<ID3D12Device> device, shared_ptr<SwapChain> swapChain)
{
	_swapChain = swapChain; 

	D3D12_COMMAND_QUEUE_DESC queueDesc = {};
	queueDesc.Type = D3D12_COMMAND_LIST_TYPE_DIRECT;
	queueDesc.Flags = D3D12_COMMAND_QUEUE_FLAG_NONE;

	device->CreateCommandQueue(&queueDesc, IID_PPV_ARGS(&_cmdQueue));

	// - D3D12_COMMAND_LIST_TYPE_DIRECT : GPU�� ���� �����ϴ� ��� ���
	device->CreateCommandAllocator(D3D12_COMMAND_LIST_TYPE_DIRECT, IID_PPV_ARGS(&_cmdAlloc));

	// GPU�� �ϳ��� �ý��ۿ����� 0����
	// Direct or Bundle
	// Allocator
	// �ʱ���� (�׸��� ����� nullptr�� ����)
	device->CreateCommandList(0, D3D12_COMMAND_LIST_TYPE_DIRECT, _cmdAlloc.Get(), nullptr, IID_PPV_ARGS(&_cmdList));

	// CommandList�� Close / Open���°� �ִµ�
	// Open ���¿����� Command�� �ִٰ� Close�� ���� �����ϴ� ����.
	_cmdList->Close();

	// CreateFence
	// - CPU�� GPU�� ����ȭ �������� ���
	device->CreateFence(0, D3D12_FENCE_FLAG_NONE, IID_PPV_ARGS(&_fence));
	_fenceEvent = ::CreateEvent(nullptr, FALSE, FALSE, nullptr);
}

void CommandQueue::WaitSync()
{ 
	++_fenceValue;

	_cmdQueue->Signal(_fence.Get(), _fenceValue);

	// GPU �۾� �Ϸ���� ���
	if (_fence->GetCompletedValue() < _fenceValue)
	{
		// GPU�� ���� �۾� �Ϸ��ϸ� event�� ����
		_fence->SetEventOnCompletion(_fenceValue, _fenceEvent);

		// GPU�� ���� �۾��� �Ϸ��Ҷ����� ���
		::WaitForSingleObject(_fenceEvent, INFINITE);
	}
}

void CommandQueue::RenderBegin(const D3D12_VIEWPORT* vp, const D3D12_RECT* rect)
{
	_cmdAlloc->Reset();
	_cmdList->Reset(_cmdAlloc.Get(), nullptr);
	 
	D3D12_RESOURCE_BARRIER barrier = CD3DX12_RESOURCE_BARRIER::Transition(
		_swapChain->GetBackRTVBuffer().Get(),
		D3D12_RESOURCE_STATE_PRESENT,			// ȭ�� ���
		D3D12_RESOURCE_STATE_RENDER_TARGET		// ���� �����
	);

	_cmdList->SetGraphicsRootSignature(ROOT_SIGNATURE.Get());
	GEngine->GetConstantBuffer()->Clear();

	_cmdList->ResourceBarrier(1, &barrier);

	// viewport, scissor rect ����, Ŀ��帮��Ʈ�� ���µǾ����� �ٽ� �����������.
	_cmdList->RSSetViewports(1, vp);
	_cmdList->RSSetScissorRects(1, rect);

	// � ���ۿ��ٰ� �׸��� �׸� ������ ����.
	D3D12_CPU_DESCRIPTOR_HANDLE backBufferView = _swapChain->GetBackRTV();
	_cmdList->ClearRenderTargetView(backBufferView, Colors::LightSteelBlue, 0, nullptr);
	_cmdList->OMSetRenderTargets(1, &backBufferView, FALSE, nullptr);
}

void CommandQueue::RenderEnd()
{
	D3D12_RESOURCE_BARRIER barrier = CD3DX12_RESOURCE_BARRIER::Transition(
		_swapChain->GetBackRTVBuffer().Get(),
		D3D12_RESOURCE_STATE_RENDER_TARGET,			// ���� �����
		D3D12_RESOURCE_STATE_PRESENT				// ȭ�� ���
	);

	_cmdList->ResourceBarrier(1, &barrier);
	_cmdList->Close();

	// Ŀ��� ����Ʈ ����.
	ID3D12CommandList* cmdListArr[] = { _cmdList.Get() };
	_cmdQueue->ExecuteCommandLists(_countof(cmdListArr), cmdListArr);

	_swapChain->Present();

	WaitSync();

	_swapChain->SwapIndex();
}
