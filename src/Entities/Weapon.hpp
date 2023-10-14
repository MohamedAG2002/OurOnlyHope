#pragma once

#include "Entity.hpp"
#include "../Components/PhysicsBody.hpp"
#include "../Components/Collider.hpp"
#include "../Metadata/BodyMetadata.hpp"

#include <raylib.h>

namespace ooh {

const float SPEAR_SPEED = 1000.0f;

class Weapon : public Entity 
{
  public:
    Weapon(Vector2* holderPos);
    ~Weapon();

  public:
    BodyMetadata bodyMetadata;
    int damage;
    float rotationDest, distTraveled, maxDist;
    Vector2 velocity;
    PhysicsBody body;
    Collider collider;

  public:
    void Update(float dt) override;
    void Render() override;
    void Reset() override;

  private:
    Vector2* m_holderPos;
};

}
