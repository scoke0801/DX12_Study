#include "pch.h"
#include "Frustum.h"
#include "Camera.h"

void Frustum::FinalUpdate()
{
	Matrix matViewInv = Camera::S_MatView.Invert();
	Matrix matProjectionInv = Camera::S_MatProjection.Invert();
	Matrix matInv = matProjectionInv * matViewInv;

	// 투영 공간에서 World공간으로 변환
	vector<Vec3> worldPos =
	{
		::XMVector3TransformCoord(Vec3(-1.f, 1.f, 0.f), matInv),
		::XMVector3TransformCoord(Vec3(1.f, 1.f, 0.f), matInv),
		::XMVector3TransformCoord(Vec3(1.f, -1.f, 0.f), matInv),
		::XMVector3TransformCoord(Vec3(-1.f, -1.f, 0.f), matInv),
		::XMVector3TransformCoord(Vec3(-1.f, 1.f, 1.f), matInv),
		::XMVector3TransformCoord(Vec3(1.f, 1.f, 1.f), matInv),
		::XMVector3TransformCoord(Vec3(1.f, -1.f, 1.f), matInv),
		::XMVector3TransformCoord(Vec3(-1.f, -1.f, 1.f), matInv)
	};

	_planes[static_cast<uint8>(PLANE_TYPE::PLANE_FRONT)] = ::XMPlaneFromPoints(worldPos[0], worldPos[1], worldPos[2]); // CW
	_planes[static_cast<uint8>(PLANE_TYPE::PLANE_BACK)] = ::XMPlaneFromPoints(worldPos[4], worldPos[7], worldPos[5]); // CCW
	_planes[static_cast<uint8>(PLANE_TYPE::PLANE_UP)] = ::XMPlaneFromPoints(worldPos[4], worldPos[5], worldPos[1]); // CW
	_planes[static_cast<uint8>(PLANE_TYPE::PLANE_DOWN)] = ::XMPlaneFromPoints(worldPos[7], worldPos[3], worldPos[6]); // CCW
	_planes[static_cast<uint8>(PLANE_TYPE::PLANE_LEFT)] = ::XMPlaneFromPoints(worldPos[4], worldPos[0], worldPos[7]); // CW
	_planes[static_cast<uint8>(PLANE_TYPE::PLANE_RIGHT)] = ::XMPlaneFromPoints(worldPos[5], worldPos[6], worldPos[1]); // CCW
}

bool Frustum::ContainSphere(const Vec3& pos, float radius)
{
	// DX의 BoundingFrustum을 사용해도 됨.
	for (const Vec4& plane : _planes)
	{
		// n = (a,b,c)
		Vec3 normal = Vec3(plane.x, plane.y, plane.z);

		// ax + by + cz + d > radius
		if (normal.Dot(pos) + plane.w > radius) {
			return false;
		}
	}
	return true;
}
