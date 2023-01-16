#include "pch.h"
#include "ConstantBuffer.h"

__DX12Engine::ConstantBuffer::ConstantBuffer()
{
}

__DX12Engine::ConstantBuffer::~ConstantBuffer()
{
}

void __DX12Engine::ConstantBuffer::Init(CBV_REGISTER reg, uint32 size, uint32 count)
{
}

void __DX12Engine::ConstantBuffer::Clear()
{
}

void __DX12Engine::ConstantBuffer::PushGraphicsData(void* buffer, uint32 size)
{
}

void __DX12Engine::ConstantBuffer::SetGraphicsGlobalData(void* buffer, uint32 size)
{
}

void __DX12Engine::ConstantBuffer::PushComputeData(void* buffer, uint32 size)
{
}

D3D12_GPU_VIRTUAL_ADDRESS __DX12Engine::ConstantBuffer::GetGpuVirtualAddress(uint32 index)
{
	return D3D12_GPU_VIRTUAL_ADDRESS();
}

D3D12_CPU_DESCRIPTOR_HANDLE __DX12Engine::ConstantBuffer::GetCpuHandle(uint32 index)
{
	return D3D12_CPU_DESCRIPTOR_HANDLE();
}

void __DX12Engine::ConstantBuffer::CreateBuffer()
{
}

void __DX12Engine::ConstantBuffer::CreateView()
{
}
