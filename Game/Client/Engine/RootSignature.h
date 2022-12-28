#pragma once

// [ ��༭ / ���� ] 
// ���			-->����		����
// CPU [	]	-->����		GPU [	]
// �ѱ�	[	]	-->����		��Ʈ�� [	]
// � �����͸� ��� Ȱ�������� ��Ʈ ���̺�� ���� ����
// ��Ʈ ���̺� ?
// API Bind Slot(�ܺ� �ڵ忡�� ���° ĭ�� �ִ����� ��Ī) / root constant / HLSL bind slot(�������� ����)
// root constant �ڸ���
// root constant or root descriptor(view�뵵, ������ ó�� �ٸ� ���ҽ��� ����Ű��) or root table�� ������ �� ����
// https ://learn.microsoft.com/ko-kr/windows/win32/direct3d12/example-root-signatures

// RootSignature(��Ʈ ����)
// �׸��� ȣ�� ���� ���� ���α׷��� �ݵ�� ������ ���������ο�
// ����� �ϴ� �ڿ����� �����̰� �� �ڿ����� ���̴� �Է� �������͵鿡 ��� �����Ǵ����� �����Ѵ�.
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

