#pragma once

#include "../Utils/Vector2.hpp"
#include "Transform.hpp"

#include <SDL2/SDL.h>

#include <string>

class Sprite 
{
  public:
    // Prioritize this CTOR over the default one
    Sprite(const std::string& spriteID, Vector2 spriteSize);

    // Default CTOR
    Sprite(); 

    // Destructor
    ~Sprite();

  public:
    Vector2 size;

  public:
    void Render(SDL_Renderer* renderer, Transform& transform);
  
  private:
    SDL_Texture* m_texture;
    SDL_FRect m_rect;
};
