#include "Zombie.hpp"
#include "Entity.hpp"
#include "../Utils/Vector2.hpp"
#include "../Utils/Utils.hpp"
#include "../Components/Sprite.hpp"
#include "../Components/PhysicsBody.hpp"
#include "../Components/Collider.hpp"
#include "../Enums/BodyType.hpp"
#include "../Events/EventFuncs.hpp"
#include "../Managers/EventManager.hpp"

#include <SDL2/SDL.h>

#include <math.h>

Zombie::Zombie(Vector2* target)
{
  transform = Transform(Vector2(-4000.0f, -4000.0f));
  id = "Zombie";
  isActive = false;

  maxHealth = 100;
  maxDamage = 100;
  health = maxHealth; 
  damage = 0;
  sprite = Sprite("Zombie_Sprite", Vector2(64.0f, 64.0f));
  body = PhysicsBody(id, transform.position, BodyType::KINEMATIC);
  collider = Collider(body, sprite.size, 1.0f);

  m_attackTimer = 0.0f;
  m_attackCooldown = 100.0f;
  m_velocity = Vector2::ZERO;
  m_target = target;
}

Zombie::~Zombie()
{

}

void Zombie::ProcessEvents(SDL_Event event)
{
  // Do nothing here...
}

void Zombie::Update(float dt)
{
}

void Zombie::Render(SDL_Renderer* renderer) 
{
  sprite.Render(renderer, transform);
}
    
void Zombie::m_HandleHealth()
{
  // Clamp the zombie's health from the 0 to the maximum 
  health = Clamp(health, 0, maxHealth);

  // Kill the zombie and set him aside when low on health 
  if(health == 0)
  {
    transform.position = Vector2(-4000.0f, -4000.0f);
    isActive = false;
  }
}

void Zombie::m_HandleDamage()
{
  damage = Clamp(damage, 0, maxDamage);
  
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
  Vector2 diff = transform.position - *m_target;
  float angle = atan2f(diff.y * ZOMBIE_ROTATION_SPEED, diff.x * ZOMBIE_ROTATION_SPEED);
  diff.Normalize();
  // TODO: Set the rotation based on the angle
 
  // Moving the zombie based on the position of the player
  m_velocity = diff * ZOMBIE_MOVE_SPEED;

  body.ApplyForce(m_velocity);
  transform.position = body.GetBodyPosition();
}
