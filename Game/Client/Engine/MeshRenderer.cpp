#include "pch.h"
#include "MeshRenderer.h"
#include "Material.h"
#include "Mesh.h"
#include "Transform.h"
#include "InstancingBuffer.h"
#include "Resources.h"

MeshRenderer::MeshRenderer()
	: Component(COMPONENT_TYPE::MESH_RENDERER)
{
}

MeshRenderer::~MeshRenderer()
{
}

void MeshRenderer::Render()
{
	for (uint32 i = 0; i < _materials.size(); i++)
	{
		shared_ptr<Material>& material = _materials[i];

		if (material == nullptr || material->GetShader() == nullptr)
			continue;

		GetTransform()->PushData();
		material->PushGraphicsData();
		_mesh->Render(1, i);
	} 
}

void MeshRenderer::Render(shared_ptr<InstancingBuffer>& buffer)
{
	for (uint32 i = 0; i < _materials.size(); i++)
	{
		shared_ptr<Material>& material = _materials[i];

		if (material == nullptr || material->GetShader() == nullptr)
			continue;

		buffer->PushData();
		material->PushGraphicsData();
		_mesh->Render(buffer, i);
	}
}

void MeshRenderer::RenderShadow()
{
	GetTransform()->PushData();
	GET_SINGLETON(Resources)->Get<Material>(L"Shadow")->PushGraphicsData();
	_mesh->Render();
}

void MeshRenderer::SetMaterial(shared_ptr<Material> material, uint32 index)
{
	if (_materials.size() <= static_cast<size_t>(index)) {
		_materials.resize(static_cast<size_t>(index + 1));
	}

	_materials[index] = material;
}

uint64 MeshRenderer::GetInstanceID()
{
	if (_mesh == nullptr || _materials.empty())
		return 0;

	//uint64 id = (_mesh->GetID() << 32) | _material->GetID();
	InstanceID instanceID{ _mesh->GetID(), _materials[0]->GetID() };
	return instanceID.id;
}