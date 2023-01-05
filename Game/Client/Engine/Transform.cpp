#include "pch.h"
#include "Transform.h"
#include "Engine.h"
#include "Camera.h"

Transform::Transform()
	: Component(COMPONENT_TYPE::TRANSFORM)
{
}

Transform::~Transform()
{
}

void Transform::FinalUpdate()
{
	Matrix matScale = Matrix::CreateScale(_localScale);

	// �Ʒ� ȸ����Ĺ���� ������ ���� �߻� ���ɼ�..
	// ���ʹϾ����� ������ ��!
	Matrix matRotation = Matrix::CreateRotationX(_localRotation.x);
	matRotation *= Matrix::CreateRotationY(_localRotation.y);
	matRotation *= Matrix::CreateRotationX(_localRotation.z);
	
	Matrix matTranslation = Matrix::CreateTranslation(_localPosition);

	// S * R * T
	_matLocal = matScale * matRotation * matTranslation;
	_matWorld = _matLocal;

	// �θ� �ִ� ���, �θ���� ������ǥ��� �����ϴ� ������ �����ϵ���
	shared_ptr<Transform> parent = GetParent().lock();
	if (parent)
	{
		_matWorld = _matLocal * parent->GetLocalToWorldMatrix();
	}
}

void Transform::PushData()
{ 
	TransformParams transformParams = {};
	transformParams.matWorld = _matWorld;
	transformParams.matView = Camera::S_MatView;
	transformParams.matProjection = Camera::S_MatProjection;
	transformParams.matMV = _matWorld * Camera::S_MatView;
	transformParams.matWorldViewProj = _matWorld * Camera::S_MatView * Camera::S_MatProjection; 
	transformParams.matViewInv = Camera::S_MatView.Invert();

	CONSTANT_BUFFER(CONSTANT_BUFFER_TYPE::TRANSFORM)->PushGraphicsData(&transformParams, sizeof(transformParams));
} 


void Transform::LookAt(const Vec3& dir)
{
	// �ٶ󺸴� ���� ����
	Vec3 front = dir;
	front.Normalize();

	// �ӽ÷� Up���Ϳ� front ���͸� �����Ͽ� ������ ���͸� ���
	Vec3 right = Vec3::Up.Cross(dir);
	if (right == Vec3::Zero) {
		right = Vec3::Forward.Cross(dir);
	}

	right.Normalize();

	// right�� front���͸� �����Ͽ� ������ �����ϴ� Up���͸� ���.
	Vec3 up = front.Cross(right);
	up.Normalize();

	Matrix matrix = XMMatrixIdentity();
	matrix.Right(right);
	matrix.Up(up);
	matrix.Backward(front);	// ���̺귯���� ��������ǥ�迩�� front�� �ƴ� backward

	_localRotation = DecomposeRotationMatrix(matrix);
}

bool Transform::CloseEnough(const float& a, const float& b, const float& epsilon)
{
	return (epsilon > std::abs(a - b));
}

Vec3 Transform::DecomposeRotationMatrix(const Matrix& rotation)
{
	Vec4 v[4];
	XMStoreFloat4(&v[0], rotation.Right());
	XMStoreFloat4(&v[1], rotation.Up());
	XMStoreFloat4(&v[2], rotation.Backward());
	XMStoreFloat4(&v[3], rotation.Translation());

	Vec3 ret;
	if (CloseEnough(v[0].z, -1.0f))
	{
		float x = 0;
		float y = XM_PI / 2;
		float z = x + atan2(v[1].x, v[2].x);
		ret = Vec3{ x, y, z };
	}
	else if (CloseEnough(v[0].z, 1.0f))
	{
		float x = 0;
		float y = -XM_PI / 2;
		float z = -x + atan2(-v[1].x, -v[2].x);
		ret = Vec3{ x, y, z };
	}
	else
	{
		float y1 = -asin(v[0].z);
		float y2 = XM_PI - y1;

		float x1 = atan2f(v[1].z / cos(y1), v[2].z / cos(y1));
		float x2 = atan2f(v[1].z / cos(y2), v[2].z / cos(y2));

		float z1 = atan2f(v[0].y / cos(y1), v[0].x / cos(y1));
		float z2 = atan2f(v[0].y / cos(y2), v[0].x / cos(y2));

		if ((std::abs(x1) + std::abs(y1) + std::abs(z1)) <= (std::abs(x2) + std::abs(y2) + std::abs(z2)))
		{
			ret = Vec3{ x1, y1, z1 };
		}
		else
		{
			ret = Vec3{ x2, y2, z2 };
		}
	}

	return ret;
}

// CBV ���
// 1) buffer���ٰ� ������ ����
// 2) buffer�� �ּҸ� register���ٰ�  ���� 
//GEngine->GetConstantBuffer()->PushData(0, &_transform, sizeof(_transform));
//GEngine->GetConstantBuffer()->PushData(1, &_transform, sizeof(_transform));
// 
// TableDescriptorHeap ���
// 1) buffer���ٰ� ������ ����
// 2) TableDescHeap ���ٰ� CBV ����
// 3) ��� ������ �������� TableDescHeap Ŀ��. 
// GEngine->GetConstantBuffer(CONSTANT_BUFFER_TYPE::TRANSFORM)->PushData(&_transform, sizeof(_transform));
