#include "Player.hpp"
#include "Entity.hpp"
#include "Weapon.hpp"
#include "../Components/Sprite.hpp"
#include "../Components/PhysicsBody.hpp"
#include "../Components/Collider.hpp"
#include "../Enums/BodyType.hpp"
#include "../Utils/Util.hpp"
#include "../Utils/Globals.hpp"
#include "../Managers/EventManager.hpp"
#include "../Events/EventFuncs.hpp"
#include "../Metadata/BodyMetadata.hpp"
#include "../Metadata/PotionMetadata.hpp"

#include <memory>
#include <raylib.h>

#include <math.h>

namespace ooh {
 
Player::Player(const Vector2 startPos)
{
  // Entity inherited variables init
  transform = Transform2D(startPos);
  UUID = util::GetRandomNumber<uint64_t>();
  isActive = true;

  // Public varaibles init 
  maxHealth = 100;
  health = maxHealth;
  velocity = Vector2{0.0f, 0.0f};
  
  // Private variables init
  m_canAttack = false;
  m_speed = PLAYER_MOVE_SPEED;
  
  // Weapon init 
  weapon = std::make_unique<Weapon>(&transform.position); 
  
  // Metadata init 
  bodyMetadata = BodyMetadata{"Player", UUID, weapon->damage};

  // Components init
  sprite = Sprite("Player_Sprite", Vector2{64.0f, 64.0f});
  body = PhysicsBody(&bodyMetadata, transform.position, BodyType::RIGID, isActive);
  collider = Collider(body, sprite.size, 1.0f, false);

  // Listen to events 
  EventManager::Get().ListenToEvent<OnEntityCollision>([&](BodyMetadata& bodyMD1, BodyMetadata& bodyMD2) {
    // Some util variables for better visualization
    std::string enttType1 = bodyMD1.entityType;
    std::string enttType2 = bodyMD2.entityType;

    // Player VS. Zombie 
    // If the type of the entities are not "Player" and "Zombie" then the player will not care.
    if(util::CheckEntityType(enttType1, enttType2, "Player") && util::CheckEntityType(enttType1, enttType2, "Zombie"))
    {
      // If the player is the first body, it means the zombie is the second body, therefore, 
      // apply the damage of the second body to the player.
      if(bodyMD1.entityUUID == UUID) 
        m_HitPlayer(bodyMD2.entityDamage);
      else if(bodyMD2.entityUUID == UUID)
        m_HitPlayer(bodyMD1.entityDamage);
    }
  });

  EventManager::Get().ListenToEvent<OnItemEquip>([&](const std::string& potion){
    m_ApplyPotion(potion);
  });
}

Player::~Player()
{}

void Player::Update(float dt)
{
  m_HandleHealth();

  if(!isActive)
    return;

  if(weapon->isActive)
    weapon->Update(dt);

  m_HandleMovement(dt);
}

void Player::Render()
{
  sprite.Render(transform);
}
    
void Player::Reset()
{
  // Reset player's variables
  health = maxHealth;
  isActive = true;
  m_speed = PLAYER_MOVE_SPEED + potionMD.speed;

  // Reactivating the body 
  body.SetBodyActive(true);

  // Resetting the player's position and updating the body's position as well
  transform.position = Vector2{GetScreenWidth() / 2.0f, GetScreenHeight() / 2.0f};
  body.SetBodyPosition(transform.position);
  transform.position = body.GetBodyPosition();
 
  // Reset the weapon
  weapon->Reset();
}

void Player::m_GetKeyInput()
{
  // Move horizontally 
  if(IsKeyDown(KEY_A))
    velocity.x = -m_speed; 
  else if(IsKeyDown(KEY_D))
    velocity.x = m_speed; 
  else  
    velocity.x = 0.0f; 
  // Move vertically 
  if(IsKeyDown(KEY_W))
    velocity.y = -m_speed; 
  else if(IsKeyDown(KEY_S))
    velocity.y = m_speed; 
  else  
    velocity.y = 0.0f; 
  
  // Rotate the player based on where the mouse is relative to the screen 
  float angle = util::GetAngle(transform.position, GetMousePosition());
  transform.rotation = angle;

  // Attacking 
  if(!weapon->isActive && IsKeyDown(KEY_SPACE))
    m_Attack();
}
    
void Player::m_Attack()
{
  // Enabling the weapon to attack 
  weapon->body.SetBodyPosition(transform.position);
  weapon->transform.position = transform.position;

  weapon->transform.rotation = transform.rotation;
  weapon->isActive = true;
  weapon->distTraveled = 0.0f;
  EventManager::Get().DispatchEvent<OnSoundPlay>(GetRandomValue(0, 1) == 0 ? "Spear_Throw-1" : "Spear_Throw-2");

  m_canAttack = false;
}
    
void Player::m_HitPlayer(int damage)
{
  // Only take away the defense multiplier when the zombie's damage is eligible
  if(damage == 0) 
    return; 

  // Only apply the defese multiplier if the player choose the defense potion
  health -= potionMD.defense == 0 ? damage : (damage * potionMD.defense);

  // Play a random player hurt sound from the available ones 
  EventManager::Get().DispatchEvent<OnSoundPlay>(GetRandomValue(1, 2) == 1 ? "Player_Hurt-1" : "Player_Hurt-2");
}

void Player::m_HandleHealth()
{
  // Clamp the health from 0 to the max 
  health = util::ClampI(health, 0, maxHealth);

  // KILL HIM!!!... when low on health
  if(health <= 0)
  {
    EventManager::Get().DispatchEvent<OnSoundPlay>("Player_Death");
    isActive = false;
  }
}

void Player::m_HandleMovement(float dt)
{
  m_GetKeyInput();

  // Apply force based on the current velocity
  body.ApplyForce(velocity);

  // Update the pixel position and rotation(in degrees)
  transform.position = body.GetBodyPosition();
}
    
void Player::m_ApplyPotion(const std::string& node)
{
  potionMD = util::LoadPotionMetadata(node);

  // Applying the multipliers to the player and their equipment
  maxHealth += potionMD.health;
  weapon->damage += potionMD.damage;
  m_speed += potionMD.speed; 

  // Reapplying the health to the new max health
  health = maxHealth;
}

}
