#include "Tile.hpp"
#include "../Components/Transform2D.hpp"
#include "../Components/Sprite.hpp"
#include "../Components/PhysicsBody.hpp"
#include "../Components/Collider.hpp"
#include "../Enums/BodyType.hpp"

#include <raylib.h>

namespace ooh {
 
Tile::Tile(const std::string& tileID, const Vector2 pos, const BodyType type)
{
  // Inherited variables init 
  transform = Transform2D(pos);
  id = tileID;
  isActive = true;

  // Components init 
  sprite = Sprite(id, Vector2{TILE_SIZE, TILE_SIZE});
  body = PhysicsBody(id, pos, type, isActive);
  collider = Collider(body, sprite.size, 0.0f, false);
}

Tile::~Tile()
{

}

void Tile::Update(float dt)
{
  // Does nothing here...
}

void Tile::Render()
{
  sprite.Render(transform);
}

}
