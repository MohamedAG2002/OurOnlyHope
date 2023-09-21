#include "Tile.hpp"
#include "../Components/Transform2D.hpp"
#include "../Components/PhysicsBody.hpp"
#include "../Components/Collider.hpp"
#include "../Enums/BodyType.hpp"
#include "../Utils/Globals.hpp"

#include <raylib.h>

namespace ooh {
 
Tile::Tile(const std::string& tileID, const Vector2 pos, const Vector2 size)
{
  // Inherited variables init 
  transform = Transform2D(pos);
  id = tileID;
  isActive = true;

  // Components init 
  body = PhysicsBody(id, pos, BodyType::RIGID, isActive);
  collider = Collider(body, size, 0.0f, false);
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
  // Does nothing here...
}

}
