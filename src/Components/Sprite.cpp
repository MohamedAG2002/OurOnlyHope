#include "Sprite.hpp"
#include "Sprite.hpp"
#include "../Utils/Vector2.hpp"
#include "../Managers/AssetManager.hpp"

#include <SDL2/SDL.h>

#include <string>

Sprite::Sprite(const std::string& spriteID, Vector2 spriteSize)
  :m_spriteSize(spriteSize)
{
  m_texture = AssetManager::Get().GetSprite(spriteID); 
  m_rect = SDL_FRect{0, 0, 0, 0};
}

Sprite::~Sprite()
{}

void Sprite::Render(SDL_Renderer* renderer, Transform& transform)
{
  m_rect = SDL_FRect{transform.position.x, 
                     transform.position.y, 
                     m_spriteSize.x * transform.scale.x, 
                     m_spriteSize.y * transform.scale.y};

  SDL_RenderCopyF(renderer, m_texture, nullptr, &m_rect);
}
