#include "pch.h"
#include "Transform.h"

Transform::Transform()
	: Component(COMPONENT_TYPE::TRANSFORM)
{
}

Transform::~Transform()
{
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
