#include "Sprite.hpp"
#include "../Utils/Globals.hpp"
#include "../Managers/AssetManager.hpp"

#include <raylib.h>

#include <string>

namespace ooh {

Sprite::Sprite(const std::string& spriteID, Vector2 spriteSize)
  :size(spriteSize)
{
  origin = Vector2{size.x / 2.0f, size.y / 2.0f};
  m_texture = AssetManager::Get().GetSprite(spriteID); 
  m_rect = Rectangle{0.0f, 0.0f, size.x, size.y};
}

Sprite::Sprite()
{
  size = Vector2{0.0f, 0.0f};
  m_texture = {};
  m_rect = Rectangle{0.0f, 0.0f, 0.0f, 0.0f};
}

Sprite::~Sprite()
{}

void Sprite::Render(Transform2D& transform)
{
  m_rect = Rectangle{transform.position.x, transform.position.y, 
                     size.x * transform.scale.x, size.y * transform.scale.y};
 
  DrawTexturePro(m_texture, Rectangle{0, 0, size.x, size.y}, m_rect, origin, transform.rotation, WHITE);
}
  
}
