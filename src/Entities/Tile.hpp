#pragma once

#include "Entity.hpp"
#include "../Components/PhysicsBody.hpp"
#include "../Components/Collider.hpp"
#include "../Enums/BodyType.hpp"
#include "../Metadata/BodyMetadata.hpp"

#include <raylib.h>

namespace ooh {

// Consts 
const int TILE_SIZE = 32;

class Tile : public Entity 
{
  public:
    Tile(const std::string& tileID, const Vector2 pos, const Vector2 size);
    ~Tile();

  public:
    BodyMetadata bodyMetadata;
    PhysicsBody body;
    Collider collider;

  public:
    void Update(float dt) override;
    void Render() override;
};
  
}
