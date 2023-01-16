#include "pch.h"
#include "RenderTargetGroup.h"
#include "DX12Engine.h"
#include "Device.h"
#include "CommandQueue.h"

void __DX12Engine::RenderTargetGroup::Create(RENDER_TARGET_GROUP_TYPE groupType, vector<RenderTarget>& rtVec, shared_ptr<Texture> dsTexture)
{
	_groupType = groupType;
	_rtVec = rtVec;
	_rtCount = static_cast<uint32>(rtVec.size());
	_dsTexture = dsTexture;

	D3D12_DESCRIPTOR_HEAP_DESC heapDesc = {};
	heapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_RTV;
	heapDesc.NumDescriptors = _rtCount;
	heapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_NONE;
	heapDesc.NodeMask = 0;

	DEVICE->CreateDescriptorHeap(&heapDesc, IID_PPV_ARGS(&_rtvHeap));

	_rtvHeapSize = DEVICE->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV);
	_rtvHeapBegin = _rtvHeap->GetCPUDescriptorHandleForHeapStart();
	_dsvHeapBegin = _dsTexture->GetDSV()->GetCPUDescriptorHandleForHeapStart();

	for (uint32 i = 0; i < _rtCount; i++)
	{
		uint32 destSize = 1;
		D3D12_CPU_DESCRIPTOR_HANDLE destHandle = CD3DX12_CPU_DESCRIPTOR_HANDLE(_rtvHeapBegin, i * _rtvHeapSize);

		uint32 srcSize = 1;
		ComPtr<ID3D12DescriptorHeap> srcRtvHeapBegin = _rtVec[i].target->GetRTV();
		D3D12_CPU_DESCRIPTOR_HANDLE srcHandle = srcRtvHeapBegin->GetCPUDescriptorHandleForHeapStart();

		DEVICE->CopyDescriptors(1, &destHandle, &destSize, 1, &srcHandle, &srcSize, D3D12_DESCRIPTOR_HEAP_TYPE_RTV);
	}

	for (uint32 i = 0; i < _rtCount; ++i)
	{
		_targetToResource[i] = CD3DX12_RESOURCE_BARRIER::Transition(_rtVec[i].target->GetTex2D().Get(),
			D3D12_RESOURCE_STATE_RENDER_TARGET, D3D12_RESOURCE_STATE_COMMON);

		_resourceToTarget[i] = CD3DX12_RESOURCE_BARRIER::Transition(_rtVec[i].target->GetTex2D().Get(),
			D3D12_RESOURCE_STATE_COMMON, D3D12_RESOURCE_STATE_RENDER_TARGET);
	}
}

void __DX12Engine::RenderTargetGroup::OMSetRenderTargets(uint32 count, uint32 offset)
{
	D3D12_VIEWPORT vp = D3D12_VIEWPORT{ 0.f, 0.f, _rtVec[0].target->GetWidth() , _rtVec[0].target->GetHeight(), 0.f, 1.f };
	D3D12_RECT rect = D3D12_RECT{ 0, 0, static_cast<LONG>(_rtVec[0].target->GetWidth()),  static_cast<LONG>(_rtVec[0].target->GetHeight()) };

	GRAPHCIS_COMMAND_LIST->RSSetViewports(1, &vp);
	GRAPHCIS_COMMAND_LIST->RSSetScissorRects(1, &rect);

	D3D12_CPU_DESCRIPTOR_HANDLE rtvHandle = CD3DX12_CPU_DESCRIPTOR_HANDLE(_rtvHeapBegin, offset * _rtvHeapSize);
	GRAPHCIS_COMMAND_LIST->OMSetRenderTargets(count, &rtvHandle, FALSE/*1°³*/, &_dsvHeapBegin);
}

void __DX12Engine::RenderTargetGroup::OMSetRenderTargets()
{
	D3D12_VIEWPORT vp = D3D12_VIEWPORT{ 0.f, 0.f, _rtVec[0].target->GetWidth() , _rtVec[0].target->GetHeight(), 0.f, 1.f };
	D3D12_RECT rect = D3D12_RECT{ 0, 0, static_cast<LONG>(_rtVec[0].target->GetWidth()),  static_cast<LONG>(_rtVec[0].target->GetHeight()) };

	GRAPHCIS_COMMAND_LIST->RSSetViewports(1, &vp);
	GRAPHCIS_COMMAND_LIST->RSSetScissorRects(1, &rect);

	GRAPHCIS_COMMAND_LIST->OMSetRenderTargets(_rtCount, &_rtvHeapBegin, TRUE/*´ÙÁß*/, &_dsvHeapBegin);
}

void __DX12Engine::RenderTargetGroup::ClearRenderTargetView(uint32 index)
{
	D3D12_CPU_DESCRIPTOR_HANDLE rtvHandle = CD3DX12_CPU_DESCRIPTOR_HANDLE(_rtvHeapBegin, index * _rtvHeapSize);
	GRAPHCIS_COMMAND_LIST->ClearRenderTargetView(rtvHandle, _rtVec[index].clearColor, 0, nullptr);

	GRAPHCIS_COMMAND_LIST->ClearDepthStencilView(_dsvHeapBegin, D3D12_CLEAR_FLAG_DEPTH, 1.f, 0, 0, nullptr);
}

void __DX12Engine::RenderTargetGroup::ClearRenderTargetView()
{
	WaitResourceToTarget();

	for (uint32 i = 0; i < _rtCount; i++)
	{
		D3D12_CPU_DESCRIPTOR_HANDLE rtvHandle = CD3DX12_CPU_DESCRIPTOR_HANDLE(_rtvHeapBegin, i * _rtvHeapSize);
		GRAPHCIS_COMMAND_LIST->ClearRenderTargetView(rtvHandle, _rtVec[i].clearColor, 0, nullptr);
	}

	GRAPHCIS_COMMAND_LIST->ClearDepthStencilView(_dsvHeapBegin, D3D12_CLEAR_FLAG_DEPTH, 1.f, 0, 0, nullptr);
}

void __DX12Engine::RenderTargetGroup::WaitTargetToResource()
{
	GRAPHCIS_COMMAND_LIST->ResourceBarrier(_rtCount, _targetToResource);
}

void __DX12Engine::RenderTargetGroup::WaitResourceToTarget()
{
	GRAPHCIS_COMMAND_LIST->ResourceBarrier(_rtCount, _resourceToTarget);
}
