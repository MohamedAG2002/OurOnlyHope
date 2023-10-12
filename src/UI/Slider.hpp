#pragma once

#include "../Enums/Anchor.hpp"

#include <raylib.h>

#include <string>

namespace ooh {
 
class Slider 
{
  public:
    Slider(const std::string&& label, float* value, Anchor anc, Vector2 offset = Vector2{0.0f, 0.0f});
    ~Slider();

  public:
    std::string label;
    float* value;
    Anchor anchor;
    Vector2 size, position;
    Rectangle bounds;
    Color color;

  public:
    void Render();

  private:
    Vector2 m_knobPosition;
};

}
