#include "Weapon.hpp"
#include "Entity.hpp"
#include "../Components/Transform2D.hpp"
#include "../Components/PhysicsBody.hpp"
#include "../Components/Collider.hpp"
#include "../Metadata/ShopItemsMetadata.hpp"
#include "../Enums/BodyType.hpp"
#include "../Events/EventFuncs.hpp"
#include "../Managers/EventManager.hpp"
#include "../Utils/Util.hpp"
#include "../Metadata/BodyMetadata.hpp"

#include <iostream>
#include <raylib.h>

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
  bodyMetadata = BodyMetadata{"Weapon", UUID, metadata.damage};

  // Components init 
  body = PhysicsBody(&bodyMetadata, *m_holderPos, BodyType::KINEMATIC, isActive);
  collider = Collider(body, Vector2{32.0f, 128.0f}, 0.0f, true);

  // Listen to events 
  //EventManager::Get().ListenToEvent<OnEntityCollision>([&](BodyMetadata& bodyMD1, BodyMetadata& bodyMD2){
  //});
}

Weapon::~Weapon()
{

}

void Weapon::Update(float dt)
{
  // Reactivate the body 
  body.SetBodyActive(true);
  
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

void Weapon::Render() 
{
  // Does nothing here...
}

}
