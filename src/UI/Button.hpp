#pragma once

#include "Text.hpp"
#include "../Enums/Anchor.hpp"
#include "../Enums/ButtonState.hpp"
#include "../Utils/Vector2.hpp"

#include <SDL2/SDL.h>

#include <memory>
#include <string>

class Button 
{
  public:
    Button(const std::string& str, Anchor anc, TextType textType, 
           SDL_Color color, SDL_Color outlineColor, Vector2 offset = Vector2::ZERO);
    ~Button();

  public:
    bool hasClicked;
    Anchor anchor;
    SDL_Color color, outlineColor;
    Vector2 offset, position, size;
    SDL_FRect rect;

  public:
    void ProcessEvents(SDL_Event event);
    void Render(SDL_Renderer* renderer);
    void Reset();

  private:
    ButtonState m_state;
    std::unique_ptr<Text> m_text;
};
