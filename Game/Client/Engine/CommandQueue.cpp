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

	// - D3D12_COMMAND_LIST_TYPE_DIRECT : GPU가 직접 실행하는 명령 목록
	device->CreateCommandAllocator(D3D12_COMMAND_LIST_TYPE_DIRECT, IID_PPV_ARGS(&_cmdAlloc));

	// GPU가 하나인 시스템에서는 0으로
	// Direct or Bundle
	// Allocator
	// 초기상태 (그리기 명령은 nullptr로 지정)
	device->CreateCommandList(0, D3D12_COMMAND_LIST_TYPE_DIRECT, _cmdAlloc.Get(), nullptr, IID_PPV_ARGS(&_cmdList));

	// CommandList는 Close / Open상태가 있는데
	// Open 상태에서는 Command를 넣다가 Close한 다음 제출하는 개념.
	_cmdList->Close();

	// CreateFence
	// - CPU와 GPU의 동기화 수단으로 사용
	device->CreateFence(0, D3D12_FENCE_FLAG_NONE, IID_PPV_ARGS(&_fence));
	_fenceEvent = ::CreateEvent(nullptr, FALSE, FALSE, nullptr);
}

void CommandQueue::WaitSync()
{ 
	++_fenceValue;

	_cmdQueue->Signal(_fence.Get(), _fenceValue);

	// GPU 작업 완료까지 대기
	if (_fence->GetCompletedValue() < _fenceValue)
	{
		// GPU가 현재 작업 완료하면 event가 실행
		_fence->SetEventOnCompletion(_fenceValue, _fenceEvent);

		// GPU가 현재 작업을 완료할때까지 대기
		::WaitForSingleObject(_fenceEvent, INFINITE);
	}
}

void CommandQueue::RenderBegin(const D3D12_VIEWPORT* vp, const D3D12_RECT* rect)
{
	_cmdAlloc->Reset();
	_cmdList->Reset(_cmdAlloc.Get(), nullptr);
	 
	D3D12_RESOURCE_BARRIER barrier = CD3DX12_RESOURCE_BARRIER::Transition(
		_swapChain->GetBackRTVBuffer().Get(),
		D3D12_RESOURCE_STATE_PRESENT,			// 화면 출력
		D3D12_RESOURCE_STATE_RENDER_TARGET		// 외주 결과물
	);

	_cmdList->SetGraphicsRootSignature(ROOT_SIGNATURE.Get());
	GEngine->GetConstantBuffer()->Clear();

	_cmdList->ResourceBarrier(1, &barrier);

	// viewport, scissor rect 설정, 커멘드리스트가 리셋되었으면 다시 설정해줘야함.
	_cmdList->RSSetViewports(1, vp);
	_cmdList->RSSetScissorRects(1, rect);

	// 어떤 버퍼에다가 그림을 그릴 것인지 지정.
	D3D12_CPU_DESCRIPTOR_HANDLE backBufferView = _swapChain->GetBackRTV();
	_cmdList->ClearRenderTargetView(backBufferView, Colors::LightSteelBlue, 0, nullptr);
	_cmdList->OMSetRenderTargets(1, &backBufferView, FALSE, nullptr);
}

void CommandQueue::RenderEnd()
{
	D3D12_RESOURCE_BARRIER barrier = CD3DX12_RESOURCE_BARRIER::Transition(
		_swapChain->GetBackRTVBuffer().Get(),
		D3D12_RESOURCE_STATE_RENDER_TARGET,			// 외주 결과물
		D3D12_RESOURCE_STATE_PRESENT				// 화면 출력
	);

	_cmdList->ResourceBarrier(1, &barrier);
	_cmdList->Close();

	// 커멘드 리스트 수행.
	ID3D12CommandList* cmdListArr[] = { _cmdList.Get() };
	_cmdQueue->ExecuteCommandLists(_countof(cmdListArr), cmdListArr);

	_swapChain->Present();

	WaitSync();

	_swapChain->SwapIndex();
}
