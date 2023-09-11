#pragma once

#include "../Utils/Vector2.hpp"
#include "Transform.hpp"

#include <SDL2/SDL.h>

#include <string>

class Sprite 
{
  public:
    Sprite(const std::string& spriteID, Vector2 spriteSize);
    ~Sprite();

  public:
    void Render(SDL_Renderer* renderer, Transform& transform);
  
  private:
    Vector2 m_spriteSize;
    SDL_Texture* m_texture;
    SDL_FRect m_rect;
};
