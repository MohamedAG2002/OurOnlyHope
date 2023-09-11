#pragma once

#include "../Components/Transform.hpp"

#include <SDL2/SDL.h>

#include <string>

class Entity 
{
  public:
    Transform transform; 
    std::string id;
    bool isActive;

  public:
    virtual void ProcessEvents(SDL_Event event) = 0;
    virtual void Update(float dt) = 0;
    virtual void Render(SDL_Renderer* renderer) = 0;
};
