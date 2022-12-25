#pragma once

// [ 계약서 / 결재 ] 
// 재료			-->외주		가공
// CPU [	]	-->외주		GPU [	]
// 한국	[	]	-->외주		베트남 [	]
// 어떤 데이터를 어떻게 활용할지를 루트 테이블로 만들어서 전달
// 루트 테이블 ?
// API Bind Slot(외부 코드에서 몇번째 칸에 있는지를 지칭) / root constant / HLSL bind slot(레지스터 슬롯)
// root constant 자리에
// root constant or root descriptor(view용도, 포인터 처럼 다른 리소스를 가리키는) or root table을 전달할 수 있음
// https ://learn.microsoft.com/ko-kr/windows/win32/direct3d12/example-root-signatures

class RootSignature
{
public:
	void Init(ComPtr<ID3D12Device> device);

	ComPtr<ID3D12RootSignature> GetSignature() { return _signature; }

private:
	ComPtr<ID3D12RootSignature> _signature;
};

