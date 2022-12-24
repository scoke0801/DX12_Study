#pragma once

// 같이 정점으로 이루어진 물체의 정보
class Mesh
{
public:
	void Init(std::vector<Vertex>& vec);
	void Render();

private:
	ComPtr<ID3D12Resource>		_vertexBuffer;
	D3D12_VERTEX_BUFFER_VIEW	_vertexBufferView = {};
	uint32						_vertexCount = 0;
};

