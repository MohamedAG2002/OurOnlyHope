#pragma once

#include "../Scenes/Scene.hpp"
#include "../Enums/SceneType.hpp"

#include <raylib.h>

#include <unordered_map>
#include <memory>

namespace ooh {

class SceneManager
{
  public:
    SceneManager();
    ~SceneManager();

  public:
    void Update(float dt);
    void Render();

  private:
    std::unordered_map<SceneType, std::shared_ptr<Scene>> m_scenes;
    std::shared_ptr<Scene> m_currentScene;
};
  
}
