#include "pch.h"
#include "Transform.h"

Transform::Transform()
	: Component(COMPONENT_TYPE::TRANSFORM)
{
}

Transform::~Transform()
{
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
