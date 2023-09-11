#pragma once

#include "Scene.hpp"

#include <SDL2/SDL.h>

class SecretScene : public Scene 
{
  public:
    SecretScene();
    ~SecretScene();

  public:
    void ProcessEvents(SDL_Event event) override;
    void Update(float dt) override;
    void Render(SDL_Renderer* renderer) override;
    void Reset() override;
};
