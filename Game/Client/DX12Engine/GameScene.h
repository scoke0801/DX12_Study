#pragma once
#include "Scene.h"

namespace __DX12Engine
{
    class GameScene : public Scene
    {

    private:
        // Scene에서 Shader들을 관리
        // Shader들에서 동일한 Shader를 통해 렌더링 되는 객체들을 관리.
        vector< shared_ptr<class Shader >>  _shaders;
    };
}

