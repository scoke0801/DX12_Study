#pragma once

namespace __DX12Engine
{
	class CommandQueue
	{
	public:
		virtual ~CommandQueue();

	public:
		void Init(ComPtr<ID3D12Device> device);

		virtual void RenderBegin() = 0;
		virtual void RenderEnd() = 0;

		void WaitSync();

	public:
		ComPtr<ID3D12CommandQueue>	GetCommandQueue() { return _cmdQueue; }
		
		ComPtr<ID3D12GraphicsCommandList> GetCommandList() { return _cmdList; }

	protected:
		shared_ptr<class SwapChain>					_swapChain;

		ComPtr<ID3D12CommandQueue>					_cmdQueue;
		ComPtr<ID3D12CommandAllocator>				_cmdAlloc;
		ComPtr<ID3D12GraphicsCommandList>			_cmdList;		
		
		ComPtr<ID3D12Fence>							_fence;
		uint32										_fenceValue = 0;
		HANDLE										_fenceEvent = INVALID_HANDLE_VALUE;

	private:
	};

	class GraphicsCommandQueue : public CommandQueue
	{
	public:
		virtual void RenderBegin() override;
		virtual void RenderEnd() override;
	};

	class ComputeCommandQueue : public CommandQueue
	{
		virtual void RenderBegin() sealed;
		virtual void RenderEnd() override;
	};
}

