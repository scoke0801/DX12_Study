#include "pch.h"
#include "StructuredBuffer.h"
#include "Engine.h"

StructuredBuffer::StructuredBuffer()
{
}

StructuredBuffer::~StructuredBuffer()
{
}

void StructuredBuffer::Init(uint32 elementSize, uint32 elementCount)
{
	_elementCount = elementCount;
	_elementSize = elementSize;
	_resourceState = D3D12_RESOURCE_STATE_COMMON;

	// Buffer
	{
		uint64 bufferSize = static_cast<uint64>(_elementSize) * _elementCount;
		D3D12_RESOURCE_DESC desc = CD3DX12_RESOURCE_DESC::Buffer(bufferSize, D3D12_RESOURCE_FLAG_ALLOW_UNORDERED_ACCESS);
		D3D12_HEAP_PROPERTIES heapProperties = CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_DEFAULT);

		DEVICE->CreateCommittedResource(
			&heapProperties,
			D3D12_HEAP_FLAG_NONE,
			&desc,
			_resourceState,
			nullptr,
			IID_PPV_ARGS(&_buffer)
		);
	}

	// SRV
	{
		D3D12_DESCRIPTOR_HEAP_DESC srvHeapDesc = {};
		srvHeapDesc.NumDescriptors = 1;
		srvHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV;
		srvHeapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_NONE;
		DEVICE->CreateDescriptorHeap(&srvHeapDesc, IID_PPV_ARGS(&_srvHeap));

		_srvHeapBegin = _srvHeap->GetCPUDescriptorHandleForHeapStart();

		D3D12_SHADER_RESOURCE_VIEW_DESC srvDesc = {};
		srvDesc.Shader4ComponentMapping = D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING;
		srvDesc.Format = DXGI_FORMAT_UNKNOWN;
		srvDesc.ViewDimension = D3D12_SRV_DIMENSION_BUFFER;
		srvDesc.Buffer.FirstElement = 0;
		srvDesc.Buffer.Flags = D3D12_BUFFER_SRV_FLAG_NONE;
		srvDesc.Buffer.StructureByteStride = _elementSize;
		srvDesc.Buffer.NumElements = _elementCount;

		DEVICE->CreateShaderResourceView(_buffer.Get(), &srvDesc, _srvHeapBegin);
	}

	// UAV
	{
		D3D12_DESCRIPTOR_HEAP_DESC heapDesc = {};
		heapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV;
		heapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_NONE; 
		heapDesc.NumDescriptors = 1;
		DEVICE->CreateDescriptorHeap(&heapDesc, IID_PPV_ARGS(&_uavHeap));

		_uavHeapBegin = _uavHeap->GetCPUDescriptorHandleForHeapStart();

		D3D12_UNORDERED_ACCESS_VIEW_DESC uavDesc = {};
		uavDesc.Format = DXGI_FORMAT_UNKNOWN;
		uavDesc.ViewDimension = D3D12_UAV_DIMENSION_BUFFER;
		uavDesc.Buffer.FirstElement = 0;
		uavDesc.Buffer.StructureByteStride = _elementSize;
		uavDesc.Buffer.NumElements = _elementCount;
		uavDesc.Buffer.CounterOffsetInBytes = 0;
		uavDesc.Buffer.Flags = D3D12_BUFFER_UAV_FLAG_NONE;

		DEVICE->CreateUnorderedAccessView(_buffer.Get(), nullptr, &uavDesc, _uavHeapBegin);
	}
}

void StructuredBuffer::PushGraphicsData(SRV_REGISTER reg)
{
	GEngine->GetGraphicsDescriptorHeap()->SetSRV(_srvHeapBegin, reg);
}

void StructuredBuffer::PushComputeSRVData(SRV_REGISTER reg)
{
	GEngine->GetComputeDescriptorHeap()->SetSRV(_srvHeapBegin, reg);
}

void StructuredBuffer::PushComputeUAVData(UAV_REGISTER reg)
{
	GEngine->GetComputeDescriptorHeap()->SetUAV(_srvHeapBegin, reg);
}
