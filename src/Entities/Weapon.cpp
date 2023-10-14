#include "Weapon.hpp"
#include "Entity.hpp"
#include "../Metadata/BodyMetadata.hpp"
#include "../Components/Transform2D.hpp"
#include "../Components/PhysicsBody.hpp"
#include "../Components/Collider.hpp"
#include "../Enums/BodyType.hpp"
#include "../Events/EventFuncs.hpp"
#include "../Managers/EventManager.hpp"
#include "../Managers/AssetManager.hpp"
#include "../Utils/Util.hpp"

#include <raylib.h>
#include <raymath.h>

namespace ooh {

Weapon::Weapon(Vector2* holderPos)
  :m_holderPos(holderPos)
{
  // Inherited variables init
  transform = Transform2D(*m_holderPos);
  UUID = util::GetRandomNumber<uint64_t>();
  isActive = false;

  // Public variables init 
  distTraveled = 0.0f;
  maxDist = 73.0f;
  rotationDest = 0.0f;
  damage = 150;  
  velocity = Vector2{0.0f, 0.0f};
  bodyMetadata = BodyMetadata{"Weapon", UUID, damage};

  // Private variables init 

  // Components init 
  body = PhysicsBody(&bodyMetadata, *m_holderPos, BodyType::KINEMATIC, isActive);
  collider = Collider(body, Vector2{32.0f, 86.0f}, 0.0f, true);
}

Weapon::~Weapon()
{}

void Weapon::Update(float dt)
{
  // Reactivate the body 
  body.SetBodyActive(true);

  // Attack pattern for the spear
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
