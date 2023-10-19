#include "Text.hpp"
#include "../Enums/Anchor.hpp"
#include "../Enums/TextType.hpp"
#include "../Utils/Globals.hpp"
#include "../Utils/Util.hpp"
#include "../Managers/AssetManager.hpp"

#include <raylib.h>

#include <string>

namespace ooh {

Text::Text()
{
  str = "DEFUALT_CTOR";
  anchor = Anchor::TOP_LEFT;
  type = TextType::LETTER;
  color = MAGENTA;
  offset = Vector2{0.0f, 0.0f};
  position = Vector2{0.0f, 0.0f};
  size = Vector2{0.0f, 0.0f};
  origin = Vector2{0.0f, 0.0f};

  m_fontSize = 0;
}

Text::Text(const std::string& str, Anchor anc, TextType type, Color color, Vector2 offset)
  :str(str), anchor(anc), type(type), color(color), offset(offset)
{
  m_SetFontByType();
  size = MeasureTextEx(GetFontDefault(), str.c_str(), m_fontSize, 1.0f);
  origin = Vector2{size.x / 2.0f, size.y / 2.0f};
  position = util::SetPositionByAnchor(anchor, size, offset);
}

Text::~Text()
{ 
}

void Text::Render()
{
  DrawTextPro(GetFontDefault(), str.c_str(), position, origin, 0.0f, m_fontSize, 1.0f, color);
}
    
void Text::ChangeText(const std::string&& newStr)
{
  str = newStr;
  size = MeasureTextEx(GetFontDefault(), str.c_str(), m_fontSize, 1.0f);
  origin = Vector2{size.x / 2.0f, size.y / 2.0f}; 
  position = util::SetPositionByAnchor(anchor, size, offset);
}

void Text::m_SetFontByType()
{
  switch(type)
  {
    case TextType::BIG:
      m_fontSize = 48;
      break;
    case TextType::MEDIUM:
      m_fontSize = 36;
      break;
    case TextType::SMALL:
      m_fontSize = 24;
      break;
    case TextType::LETTER:
      m_fontSize = 12;
      break;
 }
}
  
}
