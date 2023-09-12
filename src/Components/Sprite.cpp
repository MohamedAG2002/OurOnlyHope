#include "Sprite.hpp"
#include "Sprite.hpp"
#include "../Utils/Vector2.hpp"
#include "../Managers/AssetManager.hpp"

#include <SDL2/SDL.h>

#include <string>

Sprite::Sprite(const std::string& spriteID, Vector2 spriteSize)
  :size(spriteSize)
{
  m_texture = AssetManager::Get().GetSprite(spriteID); 
  m_rect = SDL_FRect{0.0f, 0.0f, size.x, size.y};
}

Sprite::Sprite()
{
  size = Vector2::ZERO;
  m_texture = nullptr; // This is bad. Don't let it happen!
  m_rect = SDL_FRect{0.0f, 0.0f, 0.0f, 0.0f};
}

Sprite::~Sprite()
{}

void Sprite::Render(SDL_Renderer* renderer, Transform& transform)
{
  Vector2 scaledSize = size * transform.scale;

  m_rect = SDL_FRect{transform.position.x - scaledSize.x / 2.0f, 
                     transform.position.y - scaledSize.y / 2.0f, 
                     scaledSize.x, 
                     scaledSize.y};

  SDL_RenderCopyF(renderer, m_texture, nullptr, &m_rect);
}
