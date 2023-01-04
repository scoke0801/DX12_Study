#pragma once
#include "Object.h"

class Material;
// ���� �������� �̷���� ��ü�� ����
class Mesh : public Object
{
public:
	Mesh();
	virtual ~Mesh();

public:
	void Init(const vector<Vertex>& vertexBuffer, const vector<uint32>& indexBuffer);
	void Render(uint32 instanceCount = 1);
	void Render(shared_ptr<class InstancingBuffer>& buffer);
	 
private:
	void CreateVertexBuffer(const vector<Vertex>& buffer);
	void CreateIndexBufer(const vector<uint32>&buffer);

private:
	ComPtr<ID3D12Resource>		_vertexBuffer;
	D3D12_VERTEX_BUFFER_VIEW	_vertexBufferView = {};
	uint32						_vertexCount = 0;

	ComPtr<ID3D12Resource>		_indexBuffer;
	D3D12_INDEX_BUFFER_VIEW		_indexBufferView = {};
	uint32						_indexCount = 0; 
};

