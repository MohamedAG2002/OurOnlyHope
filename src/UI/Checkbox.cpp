#include "Checkbox.hpp"
#include "../Enums/Anchor.hpp"
#include "../Utils/Util.hpp"
#include "../Events/EventFuncs.hpp"
#include "../Managers/EventManager.hpp"

#include <raylib.h>

namespace ooh {


Checkbox::Checkbox(Anchor anc, Color color, Vector2 offset)
  :outlineColor(color), boxColor(color)
{
  size = Vector2{32.0f, 32.0f};
  origin = Vector2{size.x / 2.0f, size.y / 2.0f};
  position = util::SetPositionByAnchor(anc, size, offset);
  outlineRec = Rectangle{position.x - origin.x, position.y - origin.y, size.x, size.y};
  boxRec = Rectangle{(position.x - origin.x) + 5.0f, (position.y - origin.y) + 5.0f, size.x - 10.0f, size.y - 10.0f};
  isChecked = true;
}

Checkbox::~Checkbox()
{}

void Checkbox::Render()
{
  if(CheckCollisionPointRec(GetMousePosition(), boxRec) && IsMouseButtonPressed(0))
  {
    isChecked = !isChecked;
    EventManager::Get().DispatchEvent<OnSoundPlay>("Button_Click");
  }

  // Draw the outline
  DrawRectangleLinesEx(outlineRec, 3.0f, outlineColor);
  
  if(!isChecked)
    return;

  // Draw the box only if the isChecked flag is set to true
  DrawRectangleRec(boxRec, boxColor);
}

}
