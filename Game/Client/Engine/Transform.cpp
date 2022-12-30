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
	// World View Projection...
	// ����� WorldTransform�� ���Ǿ�����.
	Matrix matWorldViewProj = _matWorld * Camera::S_MatView * Camera::S_MatProjection;

	CONSTANT_BUFFER(CONSTANT_BUFFER_TYPE::TRANSFORM)->PushData(&matWorldViewProj, sizeof(matWorldViewProj));
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
