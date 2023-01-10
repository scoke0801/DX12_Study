#pragma once

namespace __DX12Engine
{
	class SwapChain
	{
	public:
		void Init(const WindowInfo& info, ComPtr<ID3D12Device> device, ComPtr<IDXGIFactory> dxgi, ComPtr<ID3D12CommandQueue> cmdQueue);
		void Present();
		void SwapIndex();

		uint8 GetBackBufferIndex() { return _backBufferIndex; }
	
	private:
		void CreateSwapChain(const WindowInfo& info, ComPtr<IDXGIFactory> dxgi, ComPtr<ID3D12CommandQueue> cmdQueue);

	private:
		ComPtr<IDXGISwapChain>		_swapChain;
		uint8						_backBufferIndex;
	};
}

