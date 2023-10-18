#include "Zombie.hpp"
#include "Entity.hpp"
#include "../Utils/Util.hpp"
#include "../Utils/Globals.hpp"
#include "../Components/Transform2D.hpp"
#include "../Components/Collider.hpp"
#include "../Components/PhysicsBody.hpp"
#include "../Components/Collider.hpp"
#include "../Enums/BodyType.hpp"
#include "../Events/EventFuncs.hpp"
#include "../Managers/EventManager.hpp"
#include "../Metadata/BodyMetadata.hpp"

#include <raylib.h>
#include <raymath.h>

#include <math.h>

namespace ooh {

Zombie::Zombie(Vector2 startPos, Vector2* target)
  :m_startPos(startPos), m_target(target)
{
  // Inherited variables init
  transform = Transform2D(startPos);
  UUID = util::GetRandomNumber<uint64_t>();
  isActive = false;

  // Public variables init
  maxHealth = 50;
  maxDamage = 5;
  health = maxHealth; 
  damage = 0;
  bodyMetadata = BodyMetadata{"Zombie", UUID, damage};

  // Components init
  anim = Animator("Zombie_Sprite", Vector2{64.0f, 64.0f}, 4, 0.2f);
  body = PhysicsBody(&bodyMetadata, transform.position, BodyType::RIGID, isActive);
  collider = Collider(body, Vector2{64.0f, 64.0f}, 1.0f, false);

  // Private variables init
  m_attackTimer = 0.0f;
  m_attackCooldown = 0.0350f;
  m_velocity = Vector2{0.0f, 0.0f};

  // Listen to events 
  EventManager::Get().ListenToEvent<OnEntityCollision>([&](BodyMetadata& bodyMD1, BodyMetadata& bodyMD2){
    // Some util variables for better visualization
    std::string enttType1 = bodyMD1.entityType;
    std::string enttType2 = bodyMD2.entityType;

    // Zombie VS. Weapon 
    // If the type of the entities are not "Zombie" and "Weapon" then the zombie will not care.
    if(util::CheckEntityType(enttType1, enttType2, "Zombie") && util::CheckEntityType(enttType1, enttType2, "Weapon"))
    {
      // Go check the CTOR of the Player class to know more...
      if(bodyMD1.entityUUID == UUID) 
        health -= bodyMD2.entityDamage; 
      else if(bodyMD2.entityUUID == UUID)
        health -= bodyMD1.entityDamage; 
    }
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
  anim.Render(transform);
}
    
void Zombie::Reset() 
{
  isActive = false;
  body.SetBodyActive(false);

  body.SetBodyPosition(m_startPos);
  transform.position = body.GetBodyPosition(); 
  
  health = maxHealth;
  damage = 0;

  m_attackTimer = 0.0f;
}
    
void Zombie::m_HandleHealth()
{
  // Clamp the zombie's health from the 0 to the maximum 
  health = util::ClampI(health, 0, maxHealth);

  // Kill the zombie and set him aside when low on health 
  if(health == 0)
  {
    EventManager::Get().DispatchEvent<OnBloodInc>(GetRandomValue(8, 16)); 
    EventManager::Get().DispatchEvent<OnParticleSpawn>(transform.position); 
    
    // Pick a random sound from the available zombie death sounds and play it
    EventManager::Get().DispatchEvent<OnSoundPlay>(GetRandomValue(0, 1) == 0 ? "Zombie_Death-1" : "Zombie_Death-2"); 

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
    m_attackTimer += GetFrameTime();

  // Put the zombie's damage to the maximum when the timer runs out
  if(m_attackTimer > m_attackCooldown)
  {
    m_attackTimer = 0.0f;
    damage = maxDamage;
  }
  else 
    damage = 0;

  // Update the body metadata and tell it what the new damage is 
  bodyMetadata.entityDamage = damage;
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
