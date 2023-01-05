#pragma once
class SwapChain;
class DescriptorHeap;


//----------------------------------------------------------
// GraphicsCommandQueue
//----------------------------------------------------------
class GraphicsCommandQueue
{
public:
	~GraphicsCommandQueue();

	void Init(ComPtr<ID3D12Device> device, shared_ptr<SwapChain> swapChain);
	void WaitSync();

	void RenderBegin();
	void RenderEnd();

	void FlushResourceCommandQueue();

	ComPtr<ID3D12CommandQueue> GetCommandQueue() { return _cmdQueue; }
	ComPtr<ID3D12GraphicsCommandList> GetCommandList() { return _cmdList; }

	ComPtr<ID3D12GraphicsCommandList> GetResourceCommandList() { return _resCmdList; }
private:
	// CommandQueue : DX12에 등장
	// 외주를 요청할 때, 하나씩 요청하면 비효율적
	// [ 외주 목록 ]에 일감을 차곡차곡 기록했다가 한 방에 요청하는 것.
	ComPtr<ID3D12CommandQueue>			_cmdQueue;	
	ComPtr<ID3D12CommandAllocator>		_cmdAlloc;	// 메모리 공간
	ComPtr<ID3D12GraphicsCommandList>	_cmdList;	// 일감 리스트

	ComPtr<ID3D12CommandAllocator>		_resCmdAlloc; // 외부에서 리소스 사용을 위해
	ComPtr<ID3D12GraphicsCommandList>	_resCmdList;

	// Fence : 울타리(?)
	// CPU / GPU 동기화를 위한 간단한 도구
	ComPtr<ID3D12Fence>					_fence;
	uint32								_fenceValue = 0;
	HANDLE								_fenceEvent = INVALID_HANDLE_VALUE;

	shared_ptr<SwapChain>				_swapChain; 
};

//----------------------------------------------------------
// ComputeCommandQueue
//----------------------------------------------------------
class ComputeCommandQueue
{
public:
	~ComputeCommandQueue();

	void Init(ComPtr<ID3D12Device> device);
	void WaitSync();
	void FlushComputeCommandQueue();
	  
	ComPtr<ID3D12CommandQueue> GetCommandQueue() { return _cmdQueue; }
	ComPtr<ID3D12GraphicsCommandList> GetCommandList() { return _cmdList; }

private:
	// CommandQueue : DX12에 등장
	// 외주를 요청할 때, 하나씩 요청하면 비효율적
	// [ 외주 목록 ]에 일감을 차곡차곡 기록했다가 한 방에 요청하는 것.
	ComPtr<ID3D12CommandQueue>			_cmdQueue;
	ComPtr<ID3D12CommandAllocator>		_cmdAlloc;	// 메모리 공간
	ComPtr<ID3D12GraphicsCommandList>	_cmdList;	// 일감 리스트
	 
	// Fence : 울타리(?)
	// CPU / GPU 동기화를 위한 간단한 도구
	ComPtr<ID3D12Fence>					_fence;
	uint32								_fenceValue = 0;
	HANDLE								_fenceEvent = INVALID_HANDLE_VALUE; 
};