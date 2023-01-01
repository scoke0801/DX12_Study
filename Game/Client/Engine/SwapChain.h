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

	ComPtr<IDXGISwapChain> GetSwapChain() { return _swapChain; }
	uint8 GetBackBufferIndex() { return _backBufferIndex; }

private:
	void CreateSwapChain(const WindowInfo& window, ComPtr<IDXGIFactory> dxgi, ComPtr<ID3D12CommandQueue> cmdQueue);

private:
	ComPtr<IDXGISwapChain>			_swapChain;

	uint32							_backBufferIndex = 0;
};

