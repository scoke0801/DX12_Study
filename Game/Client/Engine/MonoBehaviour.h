#pragma once
#include "Component.h"

class MonoBehaviour : public Component
{
public:
	MonoBehaviour();
	virtual ~MonoBehaviour();

private:
	// MonoBehaviour 이하 클래스에서는 사용하지 못하도록.
	virtual void FinalUpdate() sealed {}
};

