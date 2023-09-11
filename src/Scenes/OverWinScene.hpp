#pragma once

#include "Scene.hpp"

#include <SDL2/SDL.h>

class OverWinScene : public Scene 
{
  public:
    OverWinScene();
    ~OverWinScene();

  public:
    void ProcessEvents(SDL_Event event) override;
    void Update(float dt) override;
    void Render(SDL_Renderer* renderer) override;
    void Reset() override;
};
