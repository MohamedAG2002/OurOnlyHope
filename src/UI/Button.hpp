#pragma once

#include "Text.hpp"
#include "../Enums/Anchor.hpp"
#include "../Enums/ButtonState.hpp"

#include <raylib.h>

#include <string>

namespace ooh {

class Button 
{
  public:
    Button();
    Button(const std::string& str, Anchor anc, TextType textType, Vector2 offset = Vector2{0.0f, 0.0f});
    ~Button();

  public:
    bool hasClicked, isActive;
    Anchor anchor;
    ButtonState state;
    Color color, outlineColor;
    Vector2 offset, position, size;
    Rectangle rect;

  public:
    bool OnPressed();
    void Render();
    void Reset();
    void SetPosition(const Vector2 pos);

  private:
    Text m_text;
};
  
}
