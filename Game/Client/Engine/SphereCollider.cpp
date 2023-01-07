#include "pch.h"
#include "SphereCollider.h"
#include "GameObject.h"
#include "Transform.h"

SphereCollider::SphereCollider()
	: Collider(ColliderType::Sphere)
{
}

SphereCollider::~SphereCollider()
{
}

void SphereCollider::FinalUpdate()
{
	_boundingSphere.Center = GetGameObject()->GetTransform()->GetWorldPosition();

	Vec3 scale = GetGameObject()->GetTransform()->GetLocalScale();
	_boundingSphere.Radius = 0.5f * max(max(scale.x, scale.y), scale.z);
}

bool SphereCollider::Intersects(Vec4 rayOrigin, Vec4 rayDir, float& distance)
{
	return _boundingSphere.Intersects(rayOrigin, rayDir, OUT distance);
}
