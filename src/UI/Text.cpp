#include "Text.hpp"
#include "../Enums/Anchor.hpp"
#include "../Enums/TextType.hpp"
#include "../Utils/Vector2.hpp"
#include "../Utils/Globals.hpp"
#include "../Managers/AssetManager.hpp"

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include <string>

Text::Text(const std::string& str, Anchor anc, TextType type, SDL_Color color, Vector2 offset)
  :m_str(str), anchor(anc), type(type), color(color), offset(offset)
{
  m_SetFontByType();
  
  m_surface = TTF_RenderText_Solid(m_font, m_str.c_str(), color);
  surfaceSize = Vector2((float)m_surface->w, (float)m_surface->h);
  
  position = m_SetPositionByAnchor();
  m_rect = SDL_Rect{(int)position.x + (int)offset.x, (int)position.y + (int)offset.y, 
                    (int)surfaceSize.x, (int)surfaceSize.y};
}

Text::~Text()
{ 
  SDL_DestroyTexture(m_texture);
  SDL_FreeSurface(m_surface);
}

void Text::Render(SDL_Renderer* renderer)
{
  SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);

  m_texture = SDL_CreateTextureFromSurface(renderer, m_surface);
  SDL_RenderCopy(renderer, m_texture, nullptr, &m_rect);
}

void Text::ChangeText(const std::string&& newStr)
{
  SDL_FreeSurface(m_surface);
  
  m_surface = TTF_RenderText_Solid(m_font, newStr.c_str(), color);
  surfaceSize = Vector2((float)m_surface->w, (float)m_surface->h);
  
  position = m_SetPositionByAnchor();
  m_rect = SDL_Rect{(int)position.x + (int)offset.x, (int)position.y + (int)offset.y, (int)surfaceSize.x, (int)surfaceSize.y};
}

Vector2 Text::m_SetPositionByAnchor()
{
  // Variables for easier visualization
  Vector2 screenSize = {global::SCREEN_WIDTH, global::SCREEN_HEIGHT};
  Vector2 result = Vector2();
  Vector2 halfSize = Vector2(surfaceSize.x / 2.0f, surfaceSize.y / 2.0f);

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
      result = Vector2::ZERO;
      break;
  }

  result -= halfSize;
  return result;
}

void Text::m_SetFontByType()
{
  switch(type)
  {
    case TextType::BIG:
      m_font = AssetManager::Get().GetFont("Big");
      break;
    case TextType::MEDIUM:
      m_font = AssetManager::Get().GetFont("Medium");
      break;
    case TextType::SMALL:
      m_font = AssetManager::Get().GetFont("Small");
      break;
    case TextType::LETTER:
      m_font = AssetManager::Get().GetFont("Letter");
      break;
 }
}
