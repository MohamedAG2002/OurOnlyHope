#pragma once

#include <SDL2/SDL.h>

class Scene 
{
  public:
    virtual void ProcessEvents(SDL_Event event) = 0;
    virtual void Update(float dt) = 0;
    virtual void Render(SDL_Renderer* renderer) = 0;
    virtual void Reset() = 0;
};
