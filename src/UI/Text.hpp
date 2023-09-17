#pragma once

#include "../Enums/Anchor.hpp"
#include "../Enums/TextType.hpp"

#include <raylib.h>

#include <string>

namespace ooh {

class Text 
{
  public:
    Text(const std::string& str, Anchor anc, TextType type, Color color, Vector2 offset = Vector2{0.0f, 0.0f});
    ~Text();

  public:
    std::string str;
    Anchor anchor;
    TextType type;
    Color color;
    Vector2 offset, position, size, origin;

  public:
    void Render();

  private:
    int m_fontSize;

  private:
    Vector2 m_SetPositionByAnchor();
    void m_SetFontByType();
};
  
}
