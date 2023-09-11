#pragma once

#include "../Entities/Entity.hpp"

#include <SDL2/SDL.h>

#include <vector>
#include <memory>

class EntityManager
{
  public:
    EntityManager();
    ~EntityManager();

  public:
    void ProcessEvents(SDL_Event event);
    void Update(float dt);
    void Render(SDL_Renderer* renderer);
    void Reset(); // FIX: Might remove later
};
