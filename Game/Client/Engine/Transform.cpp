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

	// 아래 회전행렬방식은 짐벌락 현상 발생 가능성..
	// 쿼터니언으로 수정할 것!
	Matrix matRotation = Matrix::CreateRotationX(_localRotation.x);
	matRotation *= Matrix::CreateRotationY(_localRotation.y);
	matRotation *= Matrix::CreateRotationX(_localRotation.z);
	
	Matrix matTranslation = Matrix::CreateTranslation(_localPosition);

	// S * R * T
	_matLocal = matScale * matRotation * matTranslation;
	_matWorld = _matLocal;

	// 부모가 있는 경우, 부모님의 로컬좌표계로 변경하는 과정을 포함하도록
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

	CONSTANT_BUFFER(CONSTANT_BUFFER_TYPE::TRANSFORM)->PushGraphicsData(&transformParams, sizeof(transformParams));
} 

// CBV 사용
// 1) buffer에다가 데이터 세팅
// 2) buffer의 주소를 register에다가  전송 
//GEngine->GetConstantBuffer()->PushData(0, &_transform, sizeof(_transform));
//GEngine->GetConstantBuffer()->PushData(1, &_transform, sizeof(_transform));
// 
// TableDescriptorHeap 사용
// 1) buffer에다가 데이터 세팅
// 2) TableDescHeap 에다가 CBV 전달
// 3) 모두 세팅이 끝났으면 TableDescHeap 커밋. 
// GEngine->GetConstantBuffer(CONSTANT_BUFFER_TYPE::TRANSFORM)->PushData(&_transform, sizeof(_transform));
