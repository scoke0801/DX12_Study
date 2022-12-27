#pragma once

#include "Component.h"

class Mesh;
class Material;

class MeshRenderer : public Component
{
public:
	MeshRenderer();
	virtual ~MeshRenderer();

	virtual void Update() override { Render(); }

	void Render();

public:
	void SetMaterial(shared_ptr<Material> material) { _material = material; }
	void SetMesh(shared_ptr<Mesh> mesh) { _mesh = mesh; }

private:
	shared_ptr<Mesh>		_mesh;
	shared_ptr<Material>	_material;
};

