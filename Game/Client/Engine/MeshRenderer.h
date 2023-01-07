#pragma once

#include "Component.h"

class Mesh;
class Material;

// [32][32]
union InstanceID
{
	struct
	{
		uint32 meshID;
		uint32 materialID;
	};
	uint64 id;
};

class MeshRenderer : public Component
{
public:
	MeshRenderer();
	virtual ~MeshRenderer();
	  
	void Render();
	void Render(shared_ptr<class InstancingBuffer>& buffer);

	void RenderShadow();

public:
	shared_ptr<Material> GetMaterial(uint32 index = 0) { return _materials[index]; }

	void SetMaterial(shared_ptr<Material> material, uint32 index = 0);
	void SetMesh(shared_ptr<Mesh> mesh) { _mesh = mesh; }

	uint64 GetInstanceID();
private:
	shared_ptr<Mesh>		_mesh;

	vector<shared_ptr<Material>> _materials; 
};

