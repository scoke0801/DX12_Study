#include "pch.h"
#include "Mesh.h"
#include "Engine.h"

void Mesh::Init(vector<Vertex>& vec)
{ 
	_vertexCount = static_cast<uint32>(vec.size());
	uint32 bufferSize = _vertexCount * sizeof(Vertex);

	D3D12_HEAP_PROPERTIES heapProperty = CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD);
	D3D12_RESOURCE_DESC desc = CD3DX12_RESOURCE_DESC::Buffer(bufferSize);

	DEVICE->CreateCommittedResource(&heapProperty
		, D3D12_HEAP_FLAG_NONE
		, &desc
		, D3D12_RESOURCE_STATE_GENERIC_READ
		, nullptr
		, IID_PPV_ARGS(&_vertexBuffer));

	// device를 통해서 복사( CommandList를 통한 작업과 다르게 즉시? 처리)
	// Copy the triangle data to the vertex buffer.
	void* vertexDataBuffer = nullptr;
	CD3DX12_RANGE readRange(0, 0);	// We do not intend to read from this resource on the CPU.
	_vertexBuffer->Map(0, &readRange, &vertexDataBuffer);
	::memcpy(vertexDataBuffer, &vec[0], bufferSize);
	_vertexBuffer->Unmap(0, nullptr);

	// Initialize the vertex buffer view.
	_vertexBufferView.BufferLocation = _vertexBuffer->GetGPUVirtualAddress();
	_vertexBufferView.SizeInBytes = bufferSize;		// 버퍼 크기
	_vertexBufferView.StrideInBytes = sizeof(Vertex);	// 정점 1개 크기.
}

void Mesh::Render()
{
	CMD_LIST->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	CMD_LIST->IASetVertexBuffers(0, 1, &_vertexBufferView); // Slot: (0~15)

	// TableDescriptorHeap 사용
	// 1) buffer에다가 데이터 세팅
	// 2) TableDescHeap 에다가 CBV 전달
	// 3) 모두 세팅이 끝났으면 TableDescHeap 커밋.
	{
		D3D12_CPU_DESCRIPTOR_HANDLE handle = GEngine->GetConstantBuffer()->PushData(0, &_transform, sizeof(_transform));
		GEngine->GetTableDescriptorHeap()->SetCBV(handle, CBV_REGISTER::b0);
	}
	{
		D3D12_CPU_DESCRIPTOR_HANDLE handle = GEngine->GetConstantBuffer()->PushData(0, &_transform, sizeof(_transform));
		GEngine->GetTableDescriptorHeap()->SetCBV(handle, CBV_REGISTER::b1);
	}
	GEngine->GetTableDescriptorHeap()->CommitTable();
	
	// CBV 사용
	// 1) buffer에다가 데이터 세팅
	// 2) buffer의 주소를 register에다가  전송 
	//GEngine->GetConstantBuffer()->PushData(0, &_transform, sizeof(_transform));
	//GEngine->GetConstantBuffer()->PushData(1, &_transform, sizeof(_transform));

	CMD_LIST->DrawInstanced(_vertexCount, 1, 0, 0);
}