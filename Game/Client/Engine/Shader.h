#pragma once

#include "Object.h"

enum class SHADER_TYPE : uint8
{
	DEFERRED,
	FORWARD, 
	LIGHTING,
};
enum class RASTERIZER_TYPE
{
	CULL_NONE,
	CULL_FRONT,
	CULL_BACK,	// �⺻
	WIREFRAME,
};

enum class DEPTH_STENCIL_TYPE
{
	LESS,
	LESS_EQAUL,
	GREATER,
	GREATER_EQUAL,
	NO_DEPTH_TEST, // ���� �׽�Ʈ(X) + ���� ���(O)
	NO_DEPTH_TEST_NO_WRITE, // ���� �׽�Ʈ(X) + ���� ���(X)
	LESS_NO_WRITE, // ���� �׽�Ʈ(O) + ���� ���(X)
};

enum class BLEND_TYPE : uint8
{
	DEFAULT,
	ALPHA_BLEND,
	ONE_TO_ONE_BLEND,
	END,
};

struct ShaderInfo
{
	SHADER_TYPE shaderType = SHADER_TYPE::FORWARD;
	RASTERIZER_TYPE resterizerType = RASTERIZER_TYPE::CULL_BACK;
	DEPTH_STENCIL_TYPE depthStencilType = DEPTH_STENCIL_TYPE::LESS;	
	BLEND_TYPE blendType = BLEND_TYPE::DEFAULT;
	D3D12_PRIMITIVE_TOPOLOGY_TYPE topologyType = D3D12_PRIMITIVE_TOPOLOGY_TYPE::D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE;
};
// [�ϰ� �����] ���� �ηµ��� �� �ؾ������� ���
class Shader : public Object
{
public:
	Shader();
	virtual ~Shader();
public:
	void Init(const wstring& path, ShaderInfo info = ShaderInfo(), const string& vs = "VS_Main", const string& ps = "PS_Main");
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

