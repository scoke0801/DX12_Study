#pragma once

// 교환 사슬
// [외주과정]
// - 현재 게임 세상에 있는 상황을 묘사
// - 어떤 공식으로 어떻게 계산할지를 던져줌
// - GPU가 열심히 계산(외주)
// - 결과물을 받아서 화면에 그려준다.

// [외주 결과물]을 어디에 받지?
// - 어떤 종이(Buffer)에 그려서 건내달라고 부탁해보자
// - 특수 종이를 만들어서 -> 처음에 건내주고 -> 결과물을 해당 종이에 받는다.
// - 우리 화면에 특수 종이(외주 결과물)를 출력해준다.

// [?]
// - 그런데 화면에 현재 결과물 출력는 와중에, 다음 화면도 외주를 맡겨야 함.
// - 현재 화면 결과물은 이미 화면 출력에 사용중.
// - 특수 종이를 2개 만들어서, 하나는 현재 화면을 그려주고 하나는 외주 맡기고
// - Double Buffering

// - [1] [2]
// 현재화면 [1] <-> GPU작업 [2] BackBuffer
class SwapChain
{
public:
	void Init(const WindowInfo& window, ComPtr<ID3D12Device> device, ComPtr <IDXGIFactory> dxgi, ComPtr<ID3D12CommandQueue> cmdQueue);

	void Present();
	void SwapIndex();

	ComPtr<IDXGISwapChain> GetSwapChain() { return _swapChain; }
	uint8 GetBackBufferIndex() { return _backBufferIndex; }

private:
	void CreateSwapChain(const WindowInfo& window, ComPtr<IDXGIFactory> dxgi, ComPtr<ID3D12CommandQueue> cmdQueue);

private:
	ComPtr<IDXGISwapChain>			_swapChain;

	uint32							_backBufferIndex = 0;
};

