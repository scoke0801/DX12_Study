#pragma once

// Depth.. Z���� �������� ȭ�鿡 �׷��� �ȼ��� ����
// Stencil.. buffer�� �Ϻ� ��Ʈ�� Ȱ���Ͽ�, ���ٽ� ��Ʈ�� ������ �κп���
// ������ ó���� �ϴ� ���� �뵵�� ���.
class DepthStencilBuffer
{
public:
	void Init(const WindowInfo& window, DXGI_FORMAT dsvForamt = DXGI_FORMAT_D32_FLOAT);

	D3D12_CPU_DESCRIPTOR_HANDLE GetDSVCpuHandle() { return _dsvHandle; }
	DXGI_FORMAT GetDSVFormat() { return _dsvFormat; }

private:
	// Depth Stencil View
	ComPtr< ID3D12Resource>			_dsvBuffer;
	ComPtr<ID3D12DescriptorHeap>	_dsvHeap;
	D3D12_CPU_DESCRIPTOR_HANDLE		_dsvHandle = {};
	DXGI_FORMAT						_dsvFormat = {};
};

