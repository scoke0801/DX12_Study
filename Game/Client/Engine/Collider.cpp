#include "pch.h"
#include "Collider.h"

Collider::Collider(ColliderType colliderType)
	: Component(COMPONENT_TYPE::COLLIDER), _colliderType( colliderType)
{
}

Collider::~Collider()
{
}
