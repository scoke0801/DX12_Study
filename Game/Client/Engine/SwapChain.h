#pragma once

// ��ȯ �罽
// [���ְ���]
// - ���� ���� ���� �ִ� ��Ȳ�� ����
// - � �������� ��� ��������� ������
// - GPU�� ������ ���(����)
// - ������� �޾Ƽ� ȭ�鿡 �׷��ش�.

// [���� �����]�� ��� ����?
// - � ����(Buffer)�� �׷��� �ǳ��޶�� ��Ź�غ���
// - Ư�� ���̸� ���� -> ó���� �ǳ��ְ� -> ������� �ش� ���̿� �޴´�.
// - �츮 ȭ�鿡 Ư�� ����(���� �����)�� ������ش�.

// [?]
// - �׷��� ȭ�鿡 ���� ����� ��´� ���߿�, ���� ȭ�鵵 ���ָ� �ðܾ� ��.
// - ���� ȭ�� ������� �̹� ȭ�� ��¿� �����.
// - Ư�� ���̸� 2�� ����, �ϳ��� ���� ȭ���� �׷��ְ� �ϳ��� ���� �ñ��
// - Double Buffering

// - [1] [2]
// ����ȭ�� [1] <-> GPU�۾� [2] BackBuffer
class SwapChain
{
public:
	void Init(const WindowInfo& window, ComPtr<ID3D12Device> device, ComPtr <IDXGIFactory> dxgi, ComPtr<ID3D12CommandQueue> cmdQueue);

	void Present();
	void SwapIndex();

	ComPtr<IDXGISwapChain> GetSwaPChain() { return _swapChain; }
	ComPtr<ID3D12Resource> GetRenderTarget(int32 index) { return _rtvBuffer[index]; }
	 
	ComPtr<ID3D12Resource> GetBackRTVBuffer() { return _rtvBuffer[_backBufferIndex]; }
	 
	D3D12_CPU_DESCRIPTOR_HANDLE GetBackRTV() { return _rtvHandle[_backBufferIndex]; }

private:
	void CreateSwapChain(const WindowInfo& window, ComPtr<IDXGIFactory> dxgi, ComPtr<ID3D12CommandQueue> cmdQueue);
	void CreateRTV(ComPtr<ID3D12Device> device);

private:
	ComPtr<IDXGISwapChain>			_swapChain;

	ComPtr<ID3D12DescriptorHeap>	_rtvHeap;
	D3D12_CPU_DESCRIPTOR_HANDLE		_rtvHandle[SWAP_CHAIN_BUFFER_COUNT]; 
	ComPtr<ID3D12Resource>			_rtvBuffer[SWAP_CHAIN_BUFFER_COUNT];

	uint32							_backBufferIndex = 0;
};

