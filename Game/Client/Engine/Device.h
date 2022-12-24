#pragma once

// �η� �繫��...
// ���� ��ü�� �����ϰų� �ϴ� �κ��� ���
// Dx9������ ��κ��� ����� Device���� ���
// ������ �ö󰡸鼭 ����� �и��� swpachin ���
class Device
{
public:
	void Init();

	ComPtr<IDXGIFactory> GetDXGI() { return _dxgi; }
	ComPtr<ID3D12Device> GetDevice() { return _device; }

private:
	// Com(Component Object Model)
	// DX�� ���α׷��� ��� �������� ���� ȣȯ���� �����ϰ� �ϴ� ���
	// COM��ü(COM �������̽�)�� ���, ���� ������ �츮���״� ������
	// ComPtr - COM��ü�� �ٷ�� ������ ����Ʈ ������
	ComPtr<ID3D12Debug>			_debugController;
	ComPtr<IDXGIFactory>		_dxgi;		// ȭ�� ���� ��ɵ�
	ComPtr<ID3D12Device>		_device;	// ���� ��ü ����
};

 