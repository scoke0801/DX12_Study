#include "pch.h"
#include "Material.h"
#include "Engine.h" 

void Material::Update()
{
	// CBV 업로드
	CONSTANT_BUFFER(CONSTANT_BUFFER_TYPE::MATERIAL)->PushData(&_params, sizeof(_params));

	// SRV 업로드
	for (size_t i = 0; i < _textures.size(); ++i)
	{
		if (_textures[i] == nullptr) { continue; }

		SRV_REGISTER reg = SRV_REGISTER(static_cast<uint8>(SRV_REGISTER::t0) + i);

		GEngine->GetTableDescriptorHeap()->SetSRV(_textures[i]->GetCPUHandle(), reg);
	} 

	// 파이프라인 세팅
	_shader->Update();
}
