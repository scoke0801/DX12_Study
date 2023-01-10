#pragma once

namespace __DX12Engine
{
	class Device
	{
	public:
		void Init();

		ComPtr<IDXGIFactory> GetDXGI() { return _dxgiFactory; }
		ComPtr<ID3D12Device> GetDevice() { return _device; }

	private:
		ComPtr<IDXGIFactory>		_dxgiFactory;	
		ComPtr<ID3D12Device>		_device;

#ifdef _DEBUG
		ComPtr<ID3D12Debug>			_debugController;
#endif
	}; 
}