#include "Button.hpp"
#include "../Enums/ButtonState.hpp"
#include "../Enums/Anchor.hpp"
#include "../Enums/TextType.hpp"
#include "../Utils/Globals.hpp"
#include "../Utils/Util.hpp"
#include "../Events/EventFuncs.hpp"
#include "../Managers/EventManager.hpp"

#include <raylib.h>

#include <memory>
#include <string> 

namespace ooh {

Button::Button(const std::string& str, Anchor anc, TextType textType, Color color, Color outlineColor, Vector2 offset)
  :anchor(anc), color(color), outlineColor(outlineColor), offset(offset)   
{
  state = ButtonState::IDLE;
  m_text = std::make_unique<Text>(str, anc, textType, WHITE, offset);
  hasClicked = false;
  isActive = true;
  size = Vector2(m_text->size.x + 50.0f, m_text->size.y + 5.0f);
  position = Vector2{m_text->position.x - 25.0f, m_text->position.y - 2.5f};
  rect = {position.x, position.y, size.x, size.y};
}

Button::~Button()
{}
    
bool Button::OnPressed()
{
  if(!isActive)
  {
    state = ButtonState::DISABLE;
    return false;
  }

  Vector2 mousePos = GetMousePosition();
  bool onCollision = CheckCollisionPointRec(mousePos, rect);

  // On click 
  if(onCollision && IsMouseButtonPressed(0))
  {
    state = ButtonState::CLICK;
    EventManager::Get().DispatchEvent<OnSoundPlay>("Button_Click");    
    return true;
  }

  // Default return value
  state = ButtonState::IDLE;
  return false;
}
    
void Button::Render()
{
  bool onCollision = CheckCollisionPointRec(GetMousePosition(), rect);

  // On Hover 
  if(onCollision && state != ButtonState::CLICK && isActive)
    state = ButtonState::HOVER;
  else if(!onCollision && isActive)
    state = ButtonState::IDLE;

  // Changing the alpha based on the state
  switch(state)
  {
    case ButtonState::IDLE:
      color.a = 255;
      break;
    case ButtonState::HOVER:
      color.a = 160;
      break;
    case ButtonState::CLICK:
      color.a = 100;
      break;
    case ButtonState::DISABLE:
      color.a = 50;
      break;
  }

  // Drawing the button
  rect.x = position.x - m_text->origin.x;
  rect.y = position.y - m_text->origin.y;
  DrawRectangleRec(rect, color);

  // Drawing the button's outline
  DrawRectangleLinesEx(rect, 1.0f, outlineColor);

  // Drawing the text
  m_text->Render();
}
    
void Button::Reset()
{
  hasClicked = false;
  isActive = true;
  state = ButtonState::IDLE;
}

void Button::SetPosition(const Vector2 pos)
{
  position = pos;
  m_text->position = Vector2{(pos.x + size.x / 2.0f) - m_text->size.x / 2.0f, pos.y + 3.0f};
}

}
