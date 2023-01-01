#pragma once

#include "Object.h"

enum class SHADER_TYPE : uint8
{
	DEFERRED,
	FORWARD,
};
enum class RASTERIZER_TYPE
{
	CULL_NONE,
	CULL_FRONT,
	CULL_BACK,	// 기본
	WIREFRAME,
};

enum class DEPTH_STENCIL_TYPE
{
	LESS,
	LESS_EQAUL,
	GREATER,
	GREATER_EQUAL,
};

struct ShaderInfo
{
	SHADER_TYPE shaderType = SHADER_TYPE::FORWARD;
	RASTERIZER_TYPE resterizerType = RASTERIZER_TYPE::CULL_BACK;
	DEPTH_STENCIL_TYPE depthStencilType = DEPTH_STENCIL_TYPE::LESS;
	D3D12_PRIMITIVE_TOPOLOGY_TYPE topologyType = D3D12_PRIMITIVE_TOPOLOGY_TYPE::D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE;
};
// [일감 기술서] 외주 인력들이 뭘 해야할지를 기술
class Shader : public Object
{
public:
	Shader();
	virtual ~Shader();
public:
	void Init(const wstring& path, const ShaderInfo& info = ShaderInfo());
	void Update();

public:
	ShaderInfo GetShaderInfo() { return _shaderInfo; }
	SHADER_TYPE GetShaderType() { return _shaderInfo.shaderType; }

private:
	void CreateShader(const wstring& path, const string& name, const string& version, ComPtr<ID3DBlob>& blob, D3D12_SHADER_BYTECODE& shaderByteCode );
	void CreateVertexShader(const wstring& path, const string& name, const string& version );
	void CreatePixelShader(const wstring& path, const string& name, const string& version );

private:
	ShaderInfo				_shaderInfo;

	ComPtr<ID3DBlob>		_vsBlob;
	ComPtr<ID3DBlob>		_psBlob;
	ComPtr<ID3DBlob>		_errBlob;

	ComPtr<ID3D12PipelineState>			_pipelineState;
	D3D12_GRAPHICS_PIPELINE_STATE_DESC _pipelineDesc = {};
};

