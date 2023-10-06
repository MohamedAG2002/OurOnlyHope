#include "Weapon.hpp"
#include "Entity.hpp"
#include "../Components/Transform2D.hpp"
#include "../Components/PhysicsBody.hpp"
#include "../Components/Collider.hpp"
#include "../Metadata/ShopItemsMetadata.hpp"
#include "../Enums/BodyType.hpp"
#include "../Events/EventFuncs.hpp"
#include "../Managers/EventManager.hpp"
#include "../Managers/AssetManager.hpp"
#include "../Utils/Util.hpp"
#include "../Metadata/BodyMetadata.hpp"

#include <raylib.h>
#include <raymath.h>

namespace ooh {

Weapon::Weapon(Vector2* holderPos, WeaponMetadata& metadata)
  :m_holderPos(holderPos), metadata(metadata)
{
  // Inherited variables init
  transform = Transform2D(*m_holderPos);
  UUID = util::GetRandomNumber<uint64_t>();
  isActive = false;

  // Public variables init 
  rotationDest = 0.0f;
  velocity = Vector2{0.0f, 0.0f};
  bodyMetadata = BodyMetadata{"Weapon", UUID, metadata.damage};

  // Private variables init 
  distTraveled = 0.0f;
  maxDist = 100.0f;

  // Components init 
  body = PhysicsBody(&bodyMetadata, *m_holderPos, BodyType::KINEMATIC, isActive);
  collider = Collider(body, Vector2{32.0f, 128.0f}, 0.0f, true);
}

Weapon::~Weapon()
{}

void Weapon::Update(float dt)
{
  // Reactivate the body 
  body.SetBodyActive(true);

  // Attack pattern for swords
  if(metadata.type != WeaponType::SPEAR)
  {
    // Always update the position 
    transform.position = *m_holderPos;
    body.SetBodyPosition(transform.position); 
    transform.position = body.GetBodyPosition();

    // Decrease the rotation ("attack") when active
    transform.rotation -= metadata.speed * dt;
    body.SetBodyRotation(transform.rotation);

    // Once the sword reached its "full swing", decactivate it 
    if(transform.rotation <= rotationDest)
    {
      isActive = false;
      body.SetBodyActive(false);
    }
  }
  // Attack pattern for the spear
  else 
  {
    // Getting the angle at which to throw the spear 
    Vector2 diff = Vector2Subtract(GetMousePosition(), *m_holderPos); 
    diff = Vector2Normalize(diff);
    velocity = Vector2{diff.x * SPEAR_SPEED, diff.y * SPEAR_SPEED};

    // Applying the velocity to the body (i.e throwing the spear)
    body.ApplyForce(velocity);
    transform.position = body.GetBodyPosition();

    distTraveled++;

    // The spear should go back to the player's "inventory" once the spear traveled far enough
    if(distTraveled > maxDist)
    {
      isActive = false;
      body.SetBodyActive(false);
      
      body.SetBodyPosition(*m_holderPos);
      transform.position = body.GetBodyPosition();
    }
  }
}

void Weapon::Render() 
{
  DrawTexture(AssetManager::Get().GetSprite("Spear"), transform.position.x, transform.position.y, WHITE);
}
    
void Weapon::Reset()
{
  distTraveled = 0.0f;
  isActive = false;
  
  body.SetBodyActive(false);
  body.SetBodyPosition(*m_holderPos);
  transform.position = body.GetBodyPosition();
}

}
