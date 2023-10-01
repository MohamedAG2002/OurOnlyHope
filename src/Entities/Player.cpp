#include "Player.hpp"
#include "Entity.hpp"
#include "Weapon.hpp"
#include "../Components/Sprite.hpp"
#include "../Components/PhysicsBody.hpp"
#include "../Components/Collider.hpp"
#include "../Enums/BodyType.hpp"
#include "../Enums/WeaponType.hpp"
#include "../Utils/Util.hpp"
#include "../Utils/Globals.hpp"
#include "../Managers/EventManager.hpp"
#include "../Events/EventFuncs.hpp"
#include "../Metadata/BodyMetadata.hpp"

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
  
  // Metadata init 
  weaponMD = WeaponMetadata{"Light Sword", 1, WeaponType::LIGHT, 100, 50, 35.2f, 50.0f, 1000.0f};
  armorMD = ArmorMetadata{};
  potionMD = PotionMetadata{};
  bodyMetadata = BodyMetadata{"Player", UUID, weaponMD.damage};

  // Components init
  sprite = Sprite("Player_Sprite", Vector2{64.0f, 64.0f});
  body = PhysicsBody(&bodyMetadata, transform.position, BodyType::KINEMATIC, isActive);
  collider = Collider(body, sprite.size, 1.0f, false);

  // Private variables init
  m_attackCooldown = 20.0f;
  m_attackTimer = 0.0f;
  m_canAttack = false;

  // Weapon init 
  m_weapon = std::make_unique<Weapon>(&transform.position, weaponMD); 

  // Listen to events 
  EventManager::Get().ListenToEvent<OnEntityCollision>([&](BodyMetadata& bodyMD1, BodyMetadata& bodyMD2){
    // Some util variables for better visualization
    std::string enttType1 = bodyMD1.entityType;
    std::string enttType2 = bodyMD2.entityType;

    // Player VS. Zombie 
    // If the type of the entities are not "Player" and "Zombie" then the player will not care.
    if(util::CheckEntityType(enttType1, enttType2, "Player") && util::CheckEntityType(enttType1, enttType2, "Zombie"))
    {
      // If the player is the first body, it means the zombie is the second body, therefore, 
      // apply the damage of the second body to the player.
      /* 
      if(bodyMD1.entityUUID == UUID) 
        health -= bodyMD2.entityDamage; 
      // Vice versa.
      else if(bodyMD2.entityUUID == UUID)
        health -= bodyMD1.entityDamage; 
      */
    }

  });
}

Player::~Player()
{}

void Player::Update(float dt)
{
  m_HandleHealth();

  if(!isActive)
    return;

  if(m_weapon->isActive)
    m_weapon->Update(dt);

  m_HandleMovement(dt);
  m_HandleCombat();
}

void Player::Render()
{
  sprite.Render(transform);
}
    
void Player::Reset()
{
  health = maxHealth;
  isActive = true;
  
  // Resetting the player's position and updating the body's position as well
  transform.position = Vector2{GetScreenWidth() / 2.0f, GetScreenHeight() / 2.0f};
  body.SetBodyPosition(transform.position);
  transform.position = body.GetBodyPosition();

  // @TODO: Reload all of the metadata
  
  m_weapon->Reset();
}

void Player::m_GetKeyInput()
{
  // Move horizontally 
  if(IsKeyDown(KEY_A))
    velocity.x = -PLAYER_MOVE_SPEED; 
  else if(IsKeyDown(KEY_D))
    velocity.x = PLAYER_MOVE_SPEED; 
  else  
    velocity.x = 0.0f; 
  // Move vertically 
  if(IsKeyDown(KEY_W))
    velocity.y = -PLAYER_MOVE_SPEED; 
  else if(IsKeyDown(KEY_S))
    velocity.y = PLAYER_MOVE_SPEED; 
  else  
    velocity.y = 0.0f; 
  
  // Rotate the player based on where the mouse is relative to the screen 
  float angle = util::GetAngle(transform.position, GetMousePosition());
  transform.rotation = angle;

  // Attacking 
  if(m_canAttack && IsKeyDown(KEY_SPACE))
    m_Attack();
}
    
void Player::m_Attack()
{
  // Enabling the weapon to attack depending on the type 
  // (i.e it will attack in a different pattern if it was a spear or a sword).
  m_weapon->transform.rotation = transform.rotation;
  m_weapon->rotationDest = (transform.rotation - 180.0f);
  m_weapon->isActive = true;

  m_canAttack = false;
  EventManager::Get().DispatchEvent<OnSoundPlay>("Sword_Swing");
}

void Player::m_HandleHealth()
{
  // Clamp the health from 0 to the max 
  health = util::ClampI(health, 0, maxHealth);
  
  // KILL HIM!!!... when low on health
  if(health <= 0)
    isActive = false;
}

void Player::m_HandleMovement(float dt)
{
  m_GetKeyInput();

  // Apply force based on the current velocity
  body.ApplyForce(velocity);

  // Update the pixel position and rotation(in degrees)
  transform.position = body.GetBodyPosition();
}

void Player::m_HandleCombat()
{
  // Only start timer when the player already attacked 
  if(!m_canAttack)
    m_attackTimer++;

  // Once the timer runs out, the player can attack again 
  if(m_attackTimer > m_attackCooldown)
  {
    m_canAttack = true;
    m_attackTimer = 0.0f;
  }
}
    
void Player::m_ApplyWeapon()
{

}

void Player::m_ApplyArmor()
{

}

void Player::m_ApplyPotion()
{

}

}
