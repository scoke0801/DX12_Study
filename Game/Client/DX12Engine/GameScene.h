#pragma once
#include "Scene.h"

namespace __DX12Engine
{
    class GameScene : public Scene
    {

    private:
        // Scene���� Shader���� ����
        // Shader�鿡�� ������ Shader�� ���� ������ �Ǵ� ��ü���� ����.
        vector< shared_ptr<class Shader >>  _shaders;
    };
}

