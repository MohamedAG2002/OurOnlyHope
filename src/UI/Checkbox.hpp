#pragma once

#include "../Enums/Anchor.hpp"

#include <raylib.h>

namespace ooh {
 
class Checkbox 
{
  public:
    Checkbox(Anchor anc, Color color, Vector2 offset = Vector2{0.0f, 0.0f});
    ~Checkbox();

  public:
    Vector2 position, size, origin;
    Color outlineColor, boxColor;
    Rectangle outlineRec, boxRec;
    bool isChecked;

  public:
    void Render();
};

}
