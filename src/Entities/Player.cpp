#include "Player.hpp"
#include "Entity.hpp"
#include "../Utils/Vector2.hpp"
#include "../Components/Sprite.hpp"
#include "../Components/Transform.hpp"
#include "../Utils/Utils.hpp"
#include "../Events/EventFuncs.hpp"
#include "../Managers/EventManager.hpp"

#include <SDL2/SDL.h>

Player::Player(const Vector2 pos)
{
  transform = Transform(pos);
  id = "Player";
  isActive = true;
  
  maxHealth = 100;
  health = maxHealth;
  sprite = Sprite("Player_Sprite", Vector2(64.0f, 64.0f));
  rect = SDL_FRect{transform.position.x, transform.position.y, sprite.size.x, sprite.size.y};

  m_canSwing = true;
  m_swingCooldown = 100.0f;
  m_cooldownTimer = 0.0f;
  m_velocity = Vector2();
}

Player::~Player()
{}

void Player::ProcessEvents(SDL_Event event)
{
  // Nothing to do here for now...
}

void Player::Update(float dt)
{
  // Clamping the health from 0 to the max health 
  health = (int)Clamp(health, 0, maxHealth); 

  // DO NOT let the player update when low on health 
  if(health == 0)
    return;

  m_GetKeyInput();
  transform.Move(m_velocity, dt);

  // Only starting the cooldown timer when the player can't swing 
  if(!m_canSwing)
    m_cooldownTimer++;

  // Resetting the timer and re-enabling the swinging if the timer runs out
  if(m_cooldownTimer > m_swingCooldown)
  {
    m_cooldownTimer = 0.0f;
    m_canSwing = true;
  }    
}

void Player::Render(SDL_Renderer* renderer) 
{
  sprite.Render(renderer, transform);
}
    
void Player::m_GetKeyInput()
{
  // Moving vertically
  if(IsKeyDown(SDL_SCANCODE_W))
    m_velocity.y = -PLAYER_MOVE_SPEED;
  else if(IsKeyDown(SDL_SCANCODE_S))
    m_velocity.y = PLAYER_MOVE_SPEED;
  else 
    m_velocity.y = 0.0f;

  // Moving horizontally
  if(IsKeyDown(SDL_SCANCODE_A))
    m_velocity.x = -PLAYER_MOVE_SPEED;
  else if(IsKeyDown(SDL_SCANCODE_D))
    m_velocity.x = PLAYER_MOVE_SPEED;
  else 
    m_velocity.x = 0.0f;

  // Swing the weapon
  if(m_canSwing && IsKeyDown(SDL_SCANCODE_SPACE))
  {
    EventManager::Get().DispatchEvent<OnSoundPlay>("Sword_Swing");
    m_canSwing = false;
  }
}
