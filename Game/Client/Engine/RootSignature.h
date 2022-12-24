#pragma once

// [ 계약서 / 결재 ] 
// 재료			-->외주		가공
// CPU [	]	-->외주		GPU [	]
// 한국	[	]	-->외주		베트남 [	]

class RootSignature
{
public:
	void Init(ComPtr<ID3D12Device> device);

	ComPtr<ID3D12RootSignature> GetSignature() { return _signature; }

private:
	ComPtr<ID3D12RootSignature> _signature;
};

