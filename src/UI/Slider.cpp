#include "Slider.hpp"
#include "../Enums/Anchor.hpp"
#include "../Utils/Util.hpp"
#include "../Utils/Globals.hpp"
#include "../Events/EventFuncs.hpp"
#include "../Managers/EventManager.hpp"

#include <raylib.h>

#include <string>

namespace ooh {
  
Slider::Slider(const std::string&& label, float* value, Anchor anc, Vector2 offset)
  :label(label), value(value), anchor(anc)
{
  size = Vector2{400.0f, 24.0f};
  position = util::SetPositionByAnchor(anchor, size, offset);
  bounds = Rectangle{position.x, position.y, size.x, size.y};
  color = global::UI_BOX_COLOR;

  m_knobPosition = Vector2{position.x, position.y + 12.0f};
}

Slider::~Slider()
{}

void Slider::Render()
{
  bool onMouseCollision = CheckCollisionPointCircle(GetMousePosition(), m_knobPosition, 12.0f);

  // Make the knob follow the mouse when the mouse button is clicked on top of it 
  if(IsMouseButtonDown(0) && onMouseCollision)
    m_knobPosition.x = GetMouseX();

  // Don't let the know go out of the bounds 
  m_knobPosition.x = util::ClampF(m_knobPosition.x, position.x, position.x + size.x);

  // Drawing the label
  int textSize = MeasureText(label.c_str(), 36);
  Vector2 textPos = Vector2{position.x - (textSize + 10), position.y - 7};
  DrawTextEx(GetFontDefault(), label.c_str(), textPos, 36, 1.0f, global::UI_TEXT_COLOR);

  // Drawing the box 
  DrawRectangleRec(bounds, color); 

  // Drawing the slider knob
  DrawCircleV(m_knobPosition, 12.0f, MAROON); 
}

}
