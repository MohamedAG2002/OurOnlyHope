#pragma once

#include "Entity.hpp"
#include "../Utils/Vector2.hpp"
#include "../Components/Sprite.hpp"
#include "../Components/PhysicsBody.hpp"
#include "../Components/Collider.hpp"

#include <SDL2/SDL.h>

// Consts 
const float PLAYER_MOVE_SPEED = 400.0f;

class Player : public Entity 
{
  public:
    Player(const Vector2 starPos);
    ~Player();
  
  public:
    int health, maxHealth;
    Sprite sprite;
    PhysicsBody body;
    Collider collider;
    SDL_FRect rect;

  public:
    void ProcessEvents(SDL_Event event) override;
    void Update(float dt) override;
    void Render(SDL_Renderer* renderer) override;

  private:
    bool m_canSwing;
    float m_swingCooldown, m_cooldownTimer;
    Vector2 m_velocity;

  private:
    void m_HandleHealth();
    void m_HandleMovement();
    void m_HandleSwing();
    void m_GetKeyInput();
};
