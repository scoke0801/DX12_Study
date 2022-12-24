#pragma once

// 인력 사무소...
// 각종 객체를 생성하거나 하는 부분을 담당
// Dx9에서는 대부분의 기능을 Device에서 담당
// 버전이 올라가면서 기능이 분리됨 swpachin 등등
class Device
{
public:
	void Init();

	ComPtr<IDXGIFactory> GetDXGI() { return _dxgi; }
	ComPtr<ID3D12Device> GetDevice() { return _device; }

private:
	// Com(Component Object Model)
	// DX의 프로그래밍 언어 독립성과 하위 호환성을 가능하게 하는 기술
	// COM객체(COM 인터페이스)를 사용, 세부 사항은 우리한테는 숨겨짐
	// ComPtr - COM객체를 다루는 일종의 스마트 포인터
	ComPtr<ID3D12Debug>			_debugController;
	ComPtr<IDXGIFactory>		_dxgi;		// 화면 관련 기능들
	ComPtr<ID3D12Device>		_device;	// 각종 객체 생성
};

 