#include "Weapon.hpp"
#include "Entity.hpp"
#include "../Components/Transform2D.hpp"
#include "../Components/PhysicsBody.hpp"
#include "../Components/Collider.hpp"
#include "../Metadata/ShopItemsMetadata.hpp"
#include "../Enums/BodyType.hpp"
#include "../Events/EventFuncs.hpp"
#include "../Managers/EventManager.hpp"

#include <iostream>
#include <raylib.h>

namespace ooh {

Weapon::Weapon(Vector2* holderPos, WeaponMetadata& metadata)
  :m_holderPos(holderPos), metadata(metadata)
{
  // Inherited variables init
  transform = Transform2D(*m_holderPos);
  id = "Weapon";
  isActive = false;

  // Components init 
  body = PhysicsBody(id, *m_holderPos, BodyType::KINEMATIC, isActive);
  collider = Collider(body, Vector2{32.0f, 128.0f}, 0.0f, false);

  // Public variables init 
  rotationDest = 0.0f;

  // Listen to events 
  EventManager::Get().ListenToEvent<OnEntityCollision>([&](std::string& id1, std::string& id2){
    // Weapon VS. Zombie
    if((id1 == id && id2 == "Zombie") || (id1 == "Zombie" && id2 == id))
      std::cout << "WEAPON COLLISION\n";
  });
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

  // Decrease the rotation("attack") when active
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
  // @FIX: Remove this. Only here for debugging purposes
  Rectangle rec = {transform.position.x, transform.position.y, 32.0f, 128.0f};
  DrawRectanglePro(rec, Vector2{16.0f, 64.0f}, transform.rotation, GRAY);
}

}
