#include "Text.hpp"
#include "../Enums/Anchor.hpp"
#include "../Enums/TextType.hpp"
#include "../Utils/Globals.hpp"
#include "../Managers/AssetManager.hpp"

#include <raylib.h>

#include <string>

namespace ooh {

Text::Text(const std::string& str, Anchor anc, TextType type, Color color, Vector2 offset)
  :str(str), anchor(anc), type(type), color(color), offset(offset)
{
  m_SetFontByType();
  size = MeasureTextEx(GetFontDefault(), str.c_str(), m_fontSize, 1.0f);
  origin = Vector2{size.x / 2.0f, size.y / 2.0f};
  position = m_SetPositionByAnchor();
}

Text::~Text()
{ 
}

void Text::Render()
{
  DrawTextPro(GetFontDefault(), str.c_str(), position, origin, 0.0f, m_fontSize, 1.0f, color);
}

Vector2 Text::m_SetPositionByAnchor()
{
  // Variables for easier visualization
  Vector2 screenSize = {(float)GetScreenWidth(), (float)GetScreenHeight()};
  Vector2 result = Vector2{0.0f, 0.0f};
  Vector2 halfSize = Vector2(size.x / 2.0f, size.y / 2.0f);

  switch(anchor)
  {
    case Anchor::TOP_LEFT:
      result = Vector2{(15.0f + halfSize.x) + offset.x, (15.0f + halfSize.y) + offset.y};
      break;
    case Anchor::TOP_CENTER:
      result = Vector2{screenSize.x / 2.0f + offset.x, (15.0f + halfSize.y) + offset.y};
      break;
    case Anchor::TOP_RIGHT:
      result = Vector2{(screenSize.x - halfSize.x - 15.0f) + offset.x, (15.0f + halfSize.y) + offset.y};
      break;
    case Anchor::CENTER_LEFT:
      result = Vector2{(15.0f + halfSize.x) + offset.x, screenSize.y / 2.0f + offset.y};
      break;
    case Anchor::CENTER:
      result = Vector2{screenSize.x / 2.0f + offset.x, screenSize.y / 2.0f + offset.y};
      break;
    case Anchor::CENTER_RIGHT:
      result = Vector2{(screenSize.x - halfSize.x - 15.0f) + offset.x, screenSize.y / 2.0f + offset.y};
      break;
    case Anchor::BOTTOM_LEFT:
      result = Vector2{(15.0f + halfSize.x) + offset.x, (screenSize.y - halfSize.y - 15.0f) + offset.y};
      break;
    case Anchor::BOTTOM_CENTER:
      result = Vector2{screenSize.x / 2.0f + offset.x, (screenSize.y - halfSize.y - 15.0f) + offset.y};
      break;
    case Anchor::BOTTOM_RIGHT:
      result = Vector2{(screenSize.x - halfSize.x - 15.0f) + offset.x, 
                      (screenSize.y - halfSize.y - 15.0f) + offset.y};
      break;
    default:
      result = Vector2{0.0f, 0.0f};
      break;
  }

  return result;
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
