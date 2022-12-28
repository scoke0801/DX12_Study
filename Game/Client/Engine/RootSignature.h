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

// RootSignature(루트 서명)
// 그리기 호출 전에 응용 프로그램이 반드시 렌더링 파이프라인에
// 묶어야 하는 자원들이 무엇이고 그 자원들이 셰이더 입력 레지스터들에 어떻게 대응되는지를 정의한다.
class RootSignature
{
public:
	void Init();

	ComPtr<ID3D12RootSignature> GetSignature() { return _signature; }
	 
private:
	void CreateSamplerDesc();
	void CreateRootSignature();

private:
	ComPtr<ID3D12RootSignature>		_signature;

	D3D12_STATIC_SAMPLER_DESC		_samplerDesc;
};

