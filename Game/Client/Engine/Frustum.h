#pragma once

enum class PLANE_TYPE : uint8
{
	PLANE_FRONT,
	PLANE_BACK,
	PLANE_UP,
	PLANE_DOWN,
	PLANE_LEFT,
	PLANE_RIGHT,
	
	END
};

class Frustum
{
public:
	void FinalUpdate();
	bool ContainSphere(const Vec3& pos, float radius);

private:
	array<Vec4, static_cast<uint8>(PLANE_TYPE::END)> _planes;
};

