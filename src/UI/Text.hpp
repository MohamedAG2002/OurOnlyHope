#pragma once

#include "../Enums/Anchor.hpp"
#include "../Enums/TextType.hpp"
#include "../Utils/Vector2.hpp"

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include <string>

class Text 
{
  public:
    Text(const std::string& str, Anchor anc, TextType type, SDL_Color color, Vector2 offset = Vector2::ZERO);
    ~Text();

  public:
    Anchor anchor;
    TextType type;
    SDL_Color color;
    Vector2 offset, position, surfaceSize;

  public:
    void Render(SDL_Renderer* renderer);
    void ChangeText(const std::string&& newStr);

  private:
    std::string m_str;
    TTF_Font* m_font = nullptr;
    SDL_Surface* m_surface = nullptr;
    SDL_Texture* m_texture = nullptr;
    SDL_Rect m_rect;

  private:
    Vector2 m_SetPositionByAnchor();
    void m_SetFontByType();
};
