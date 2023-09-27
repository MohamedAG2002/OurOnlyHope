#include "Tile.hpp"
#include "../Components/Transform2D.hpp"
#include "../Components/PhysicsBody.hpp"
#include "../Components/Collider.hpp"
#include "../Enums/BodyType.hpp"
#include "../Utils/Globals.hpp"
#include "../Utils/Util.hpp"
#include "../Metadata/BodyMetadata.hpp"

#include <raylib.h>

namespace ooh {
 
Tile::Tile(const std::string& tileID, const Vector2 pos, const Vector2 size)
{
  // Inherited variables init 
  transform = Transform2D(pos);
  UUID = util::GetRandomNumber<uint64_t>();
  isActive = true;

  // Public variables init 
  bodyMetadata = BodyMetadata{"Tile", UUID, 0};

  // Components init 
  body = PhysicsBody(&bodyMetadata, pos, BodyType::RIGID, isActive);
  collider = Collider(body, size, 0.0f, false);
}

Tile::~Tile()
{}

void Tile::Update(float dt)
{
  // Does nothing here...
}

void Tile::Render()
{
  // Does nothing here...
}
    
void Tile::Reset()
{
  // Does nothing here...
}

}
