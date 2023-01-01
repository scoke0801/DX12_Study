#pragma once

#include "GameObject.h"
#include "Material.h"
#include "Mesh.h"
#include "Shader.h"
#include "Texture.h"

class Resources
{
	DECLARE_SINGLETON(Resources);

public:
	void Init();

	template<typename T>
	shared_ptr<T> Load(const wstring& key, const wstring& path);

	template<typename T>
	bool Add(const wstring& key, shared_ptr<T> object);

	template<typename T>
	shared_ptr<T> Get(const wstring& key);

	template<typename T>
	OBJECT_TYPE GetObjectType();

	shared_ptr<Mesh> LoadCubeMesh();
	shared_ptr<Mesh> LoadSphereMesh();
	shared_ptr<Mesh> LoadRectangleMesh();

	shared_ptr<Texture> CreateTexture(const wstring& name, DXGI_FORMAT format, uint32 width, uint32 height,
		const D3D12_HEAP_PROPERTIES& heapProperty, D3D12_HEAP_FLAGS heapFlags,
		D3D12_RESOURCE_FLAGS resFlags, Vec4 clearColor = Vec4());

	// 이미 있는 정보에서 텍스쳐를 생성할 때. ex) 스왑체인getbuffer
	shared_ptr<Texture> CreateTextureFromResource(const wstring& name, ComPtr<ID3D12Resource> tex2D);
private:
	void CreateDefaultShader();
	void CreateDefaultMaterial();

private:
	using KeyObjMap = std::map<wstring, shared_ptr<Object>>;
	array<KeyObjMap, OBJECT_TYPE_COUNT > _resources;
};

#include "Resources.inl"