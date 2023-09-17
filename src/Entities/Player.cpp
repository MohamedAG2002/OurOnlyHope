#include "Player.hpp"
#include "Entity.hpp"
#include "../Components/Sprite.hpp"
#include "../Components/PhysicsBody.hpp"
#include "../Components/Collider.hpp"
#include "../Enums/BodyType.hpp"
#include "../Utils/Util.hpp"
#include "../Utils/Globals.hpp"
#include "../Managers/EventManager.hpp"
#include "../Events/EventFuncs.hpp"

#include <raylib.h>

#include <math.h>

namespace ooh {
 
Player::Player(const Vector2 startPos)
{
  // Entity inherited variables init
  transform = Transform2D(startPos);
  id = "Player";
  isActive = true;

  // Public varaibles init 
  maxHealth = 100;
  health = maxHealth;

  // Components init
  sprite = Sprite("Player_Sprite", Vector2{64.0f, 64.0f});
  body = PhysicsBody(id, transform.position, BodyType::KINEMATIC, isActive);
  collider = Collider(body, sprite.size, 1.0f, false);

  // Private variables init
  m_velocity = Vector2{0.0f, 0.0f};
  m_attackCooldown = 50.0f;
  m_attackTimer = 0.0f;
  m_canAttack = false;
}

Player::~Player()
{}

void Player::Update(float dt)
{
  m_HandleHealth();

  if(!isActive)
    return;

  m_HandleMovement(dt);
  m_HandleCombat();
}

void Player::Render()
{
  sprite.Render(transform);
}

void Player::m_GetKeyInput()
{
  // Move horizontally 
  if(IsKeyDown(KEY_A))
    m_velocity.x = -PLAYER_MOVE_SPEED; 
  else if(IsKeyDown(KEY_D))
    m_velocity.x = PLAYER_MOVE_SPEED; 
  else  
    m_velocity.x = 0.0f; 
  // Move vertically 
  if(IsKeyDown(KEY_W))
    m_velocity.y = -PLAYER_MOVE_SPEED; 
  else if(IsKeyDown(KEY_S))
    m_velocity.y = PLAYER_MOVE_SPEED; 
  else  
    m_velocity.y = 0.0f; 
  
  // Rotate the player based on where the mouse is relative to the screen
  Vector2 mousePos = GetMousePosition();
  Vector2 diff = Vector2{mousePos.x - transform.position.x, mousePos.y - transform.position.y};
  float angle = atan2f(diff.y * PLAYER_ROTATION_SPEED, diff.x * PLAYER_ROTATION_SPEED); 
  transform.rotation = angle * RAD2DEG;

  // Attacking 
  if(m_canAttack && IsKeyDown(KEY_SPACE))
    m_Attack();
}

void Player::m_GetJoystickInput()
{
  // Getting the left analog(L)'s value(between -1 and 1)
  Vector2 leftAnalogValue = Vector2{GetGamepadAxisMovement(global::CURRENT_GAMEPAD, 0),
                                    GetGamepadAxisMovement(global::CURRENT_GAMEPAD, 1)};
  
  // Getting the right analog(R)'s value(between -1 and 1)
  Vector2 rightAnalogValue = Vector2{GetGamepadAxisMovement(global::CURRENT_GAMEPAD, 2),
                                     GetGamepadAxisMovement(global::CURRENT_GAMEPAD, 3)};

  // Movements
  m_velocity.x = leftAnalogValue.x * PLAYER_MOVE_SPEED;
  m_velocity.y =  leftAnalogValue.y * PLAYER_MOVE_SPEED;

  // Rotations
  float angle = atan2f(rightAnalogValue.y * PLAYER_ROTATION_SPEED, rightAnalogValue.x * PLAYER_ROTATION_SPEED); 
  transform.rotation = angle * RAD2DEG;

  // Attacking(when pressing R2 on a Dualshock or RT on an xbox controller)
  if(m_canAttack && IsGamepadButtonDown(global::CURRENT_GAMEPAD, GAMEPAD_BUTTON_RIGHT_TRIGGER_2))
    m_Attack();  
}
    
void Player::m_Attack()
{
  // TODO: Add attack functionality
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
  if(IsGamepadAvailable(global::CURRENT_GAMEPAD))
    m_GetJoystickInput();
  else 
    m_GetKeyInput();

  // Apply force based on the current velocity and rotate the body based on the current rotation
  body.ApplyForce(m_velocity);
  body.SetBodyRotation(transform.rotation);

  // Update the pixel position and rotation(in degrees)
  transform.position = body.GetBodyPosition();
  //transform.rotation = body.GetBodyRotation();
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

}
