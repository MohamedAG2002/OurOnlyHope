#pragma once

#include "../Scenes/Scene.hpp"
#include "../Enums/SceneType.hpp"

#include <SDL2/SDL.h>

#include <unordered_map>
#include <memory>

class SceneManager
{
  public:
    SceneManager();
    ~SceneManager();

  public:
    void ProcessEvents(SDL_Event event);
    void Update(float dt);
    void Render(SDL_Renderer* renderer);

  private:
    std::unordered_map<SceneType, std::shared_ptr<Scene>> m_scenes;
    std::shared_ptr<Scene> m_currentScene;
};
