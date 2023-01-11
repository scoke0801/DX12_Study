#pragma once

namespace __DX12Engine 
{
	class DescriptorHeap
	{
	public:
		void Init();
		
		void Clear();
		
		void SetCBV();
		void SetSRV();

		ComPtr<ID3D12DescriptorHeap> GetDescriptorHeap() { return _descriptorHeap; }
	
	private:
		ComPtr<ID3D12DescriptorHeap>		_descriptorHeap;
		
		uint64	_handleSize = 0;
		uint64	_groupSize = 0;
		uint64	_groupCount = 0;
	};
}
