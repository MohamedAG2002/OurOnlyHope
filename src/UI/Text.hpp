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
    void ChangeText(const std::string&& newStr);

  private:
    int m_fontSize;

  private:
    void m_SetFontByType();
};
  
}
