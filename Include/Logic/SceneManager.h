#pragma once

#include <memory>
#include <string>
#include "Scene.h"

class SceneManager
{
public:
    static SceneManager& Get()
    {
        static SceneManager instance;
        return instance;
    }

    Scene& GetCurrent()
    {
        if (!m_Current)
            NewScene();
        return *m_Current;
    }

    void NewScene()
    {
        m_Current = std::make_unique<Scene>();
    }

private:
    std::unique_ptr<Scene> m_Current;
};
