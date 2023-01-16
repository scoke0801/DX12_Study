#pragma once

namespace __DX12Engine
{
	class RootSignature
	{
	public:
		virtual void Init() = 0;

	public:

	protected:
		D3D12_STATIC_SAMPLER_DESC			_samplerDesc;
		ComPtr<ID3D12RootSignature>			_rootSignature;
	};

	class GraphicsRootSignature : public RootSignature
	{
	public:
		virtual void Init() override;

	public:
	};

	class ComputeRootSignature : public RootSignature
	{
	public:
		virtual void Init() override;

	public:
	};
}

