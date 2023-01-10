#pragma once

namespace __DX12Engine
{
	class RootSignature
	{
	public:
		virtual void Init() = 0;

	public:
		virtual RootSignatureType GetRootSignatureType() = 0;

		ComPtr<ID3D12RootSignature>	GetRootSignature() { return _rootSignature; }

	protected:
		D3D12_STATIC_SAMPLER_DESC			_samplerDesc;
		ComPtr<ID3D12RootSignature>			_rootSignature;
	};

	class GraphicsRootSignature : public RootSignature
	{
	public:
		virtual void Init() override;

	public:
		virtual RootSignatureType GetRootSignatureType() override { return RootSignatureType::GRAPHICS; }
	};

	class ComputeRootSignature : public RootSignature
	{
	public:
		virtual void Init() override;

	public:
		virtual RootSignatureType GetRootSignatureType() override { return RootSignatureType::COMPUTE; }
	};
}

