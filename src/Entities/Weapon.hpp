#pragma once

#include "Entity.hpp"
#include "../Components/PhysicsBody.hpp"
#include "../Components/Collider.hpp"
#include "../Metadata/ShopItemsMetadata.hpp"

#include <raylib.h>

namespace ooh {
 
class Weapon : public Entity 
{
  public:
    Weapon(Vector2* holderPos, WeaponMetadata& metadata);
    ~Weapon();

  public:
    WeaponMetadata metadata;
    float rotationDest;
    PhysicsBody body;
    Collider collider;

  public:
    void Update(float dt) override;
    void Render() override;

  private:
    Vector2* m_holderPos;
};

}
