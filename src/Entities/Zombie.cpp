#include "Zombie.hpp"
#include "Entity.hpp"
#include "../Utils/Util.hpp"
#include "../Utils/Globals.hpp"
#include "../Components/Transform2D.hpp"
#include "../Components/Sprite.hpp"
#include "../Components/PhysicsBody.hpp"
#include "../Components/Collider.hpp"
#include "../Enums/BodyType.hpp"
#include "../Events/EventFuncs.hpp"
#include "../Managers/EventManager.hpp"

#include <raylib.h>
#include <raymath.h>

#include <math.h>

namespace ooh {

Zombie::Zombie(Vector2 startPos, Vector2* target)
  :m_startPos(startPos), m_target(target)
{
  // Inherited variables init
  transform = Transform2D(startPos);
  id = "Zombie";
  isActive = false;

  // Public variables init
  maxHealth = 100;
  maxDamage = 100;
  health = maxHealth; 
  damage = 0;

  // Components init
  sprite = Sprite("Zombie_Sprite", Vector2(64.0f, 64.0f));
  body = PhysicsBody(id, transform.position, BodyType::RIGID, isActive);
  collider = Collider(body, sprite.size, 0.2f, false);

  // Private variables init
  m_attackTimer = 0.0f;
  m_attackCooldown = 100.0f;
  m_velocity = Vector2{0.0f, 0.0f};

  // Listen to events 
  EventManager::Get().ListenToEvent<OnEntityCollision>([&](std::string& id1, std::string& id2){
    if((id1 == "Weapon" && id2 == "Zombie") || (id1 == "Zombie" && id2 == "Weapon"))
      std::cout << "ZOMBIE COLLISION\n";
  });
}

Zombie::~Zombie()
{}

void Zombie::Update(float dt)
{
  m_HandleHealth();
  body.SetBodyActive(isActive);

  if(!isActive)
    return;

  m_HandleDamage();
  m_HandleMovement();
}

void Zombie::Render() 
{
  sprite.Render(transform);
}
    
void Zombie::m_HandleHealth()
{
  // Clamp the zombie's health from the 0 to the maximum 
  health = util::ClampI(health, 0, maxHealth);

  // Kill the zombie and set him aside when low on health 
  if(health == 0)
  {
    body.SetBodyPosition(m_startPos);
    transform.position = body.GetBodyPosition();
    isActive = false;
  }
}

void Zombie::m_HandleDamage()
{
  damage = util::ClampI(damage, 0, maxDamage);
  
  // Only tick the attack timer when the zombie cannot attack
  if(damage == 0)
    m_attackTimer++;

  // Put the zombie's damage to the maximum when the timer runs out
  if(m_attackTimer > m_attackCooldown)
  {
    m_attackTimer = 0.0f;
    damage = maxDamage;
    EventManager::Get().DispatchEvent<OnSoundPlay>("Zombie_Grunt");
  }
  else 
    damage = 0;
}

void Zombie::m_HandleMovement()
{
  // Rotate the zombie towards the player
  float angle = util::GetAngle(transform.position, *m_target);
  transform.rotation = angle;

  // Moving the zombie based on the position of the player
  Vector2 diff = Vector2{m_target->x - transform.position.x, m_target->y - transform.position.y};
  diff = Vector2Normalize(diff);
  m_velocity = Vector2{diff.x * ZOMBIE_MOVE_SPEED, diff.y * ZOMBIE_MOVE_SPEED};
 
  // Applying the velocity
  body.ApplyForce(m_velocity);

  // Updating the position
  transform.position = body.GetBodyPosition();
}
  
}
