#pragma once

#include "Transform2D.hpp"

#include <raylib.h>

#include <string>

namespace ooh {

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
    Vector2 size, origin;

  public:
    void Render(Transform2D& transform);
  
  private:
    Texture2D m_texture;
    Rectangle m_rect;
};
  
}
