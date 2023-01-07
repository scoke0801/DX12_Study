#pragma once

#include "Component.h"

enum class ColliderType
{
	Sphere,
};

class Collider : public Component
{
public:
	Collider(ColliderType coliderType);
	virtual ~Collider();

	virtual bool Intersects(Vec4 rayOrigin, Vec4 rayDir, OUT float& distance) = 0;

private:
	ColliderType _colliderType = {};
};

