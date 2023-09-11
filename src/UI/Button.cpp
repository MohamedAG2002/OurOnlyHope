#include "Button.hpp"
#include "../Enums/ButtonState.hpp"
#include "../Enums/Anchor.hpp"
#include "../Enums/TextType.hpp"
#include "../Utils/Vector2.hpp"
#include "../Utils/Globals.hpp"
#include "../Utils/Utils.hpp"
#include "../Events/EventFuncs.hpp"
#include "../Managers/EventManager.hpp"

#include <SDL2/SDL.h>

#include <memory>
#include <string> 

Button::Button(const std::string& str, Anchor anc, TextType textType, SDL_Color color, SDL_Color outlineColor, Vector2 offset)
  :anchor(anc), color(color), outlineColor(outlineColor), offset(offset)   
{
  m_state = ButtonState::IDLE;
  m_text = std::make_unique<Text>(str, anc, textType, global::BLACK, offset);
  hasClicked = false;
  size = Vector2(m_text->surfaceSize.x + 15.0f, m_text->surfaceSize.y + 15.0f);
  position = Vector2(m_text->position.x + m_text->surfaceSize.x / 2.0f, m_text->position.y + m_text->surfaceSize.y / 2.0f) + offset;
  rect = {position.x - size.x / 2.0f, position.y - size.y / 2.0f, size.x, size.y};
}

Button::~Button()
{

}
    
void Button::ProcessEvents(SDL_Event event)
{
  // Useful function for later use
  Vector2 mousePos = Vector2(event.button.x, event.button.y);
  bool isMouseColliding = PointVSRect(rect, mousePos);

  // Checking for mouse being hovered
  if(isMouseColliding)
    m_state = ButtonState::HOVER;
  else 
    m_state = ButtonState::IDLE;

  // Checking for mouse being clicked
  if(event.type != SDL_MOUSEBUTTONDOWN)
    return;

  if(event.button.button == 1 && isMouseColliding && m_state != ButtonState::DISABLE)
  {
    EventManager::Get().DispatchEvent<OnSoundPlay>("Button_Click");
    m_state = ButtonState::CLICK;
    hasClicked = true;
  }
}

void Button::Render(SDL_Renderer* renderer)
{
  // Changing the alpha based on the state
  switch(m_state)
  {
    case ButtonState::IDLE:
      color.a = 255;
      break;
    case ButtonState::HOVER:
      color.a = 160;
      break;
    case ButtonState::CLICK:
      color.a = 128;
      break;
    case ButtonState::DISABLE:
      color.a = 96;
      break;
  }

  // Drawing the button
  SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
  SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
  SDL_RenderFillRectF(renderer, &rect);
  
  // Drawing the button's outline
  SDL_SetRenderDrawColor(renderer, outlineColor.r, outlineColor.g, outlineColor.b, outlineColor.a);
  SDL_FRect outRect = {rect.x - 1, rect.y - 1, size.x + 1, size.y + 1.5f};
  SDL_RenderDrawRectF(renderer, &outRect); 

  // Drawing the text
  m_text->Render(renderer);
}
    
void Button::Reset()
{
  hasClicked = false;
  m_state = ButtonState::IDLE;
}
