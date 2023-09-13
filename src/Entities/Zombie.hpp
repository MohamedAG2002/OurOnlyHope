#pragma once

#include "Entity.hpp"
#include "../Utils/Vector2.hpp"
#include "../Components/Sprite.hpp"
#include "../Components/PhysicsBody.hpp"
#include "../Components/Collider.hpp"

#include <SDL2/SDL.h>

// Consts 
const float ZOMBIE_MOVE_SPEED = 200.0f;
const float ZOMBIE_ROTATION_SPEED = 300.0f;

class Zombie : public Entity 
{
  public:
    Zombie(Vector2 startPos, Vector2* target);
    ~Zombie();

  public:
    int maxHealth, maxDamage, health, damage;
    Sprite sprite;
    PhysicsBody body;
    Collider collider;

  public:
    void ProcessEvents(SDL_Event event) override;
    void Update(float dt) override;
    void Render(SDL_Renderer* renderer) override;

  private:
    float m_attackCooldown, m_attackTimer;
    Vector2 m_velocity;
    Vector2* m_target;

  private:
    void m_HandleHealth();
    void m_HandleDamage();
    void m_HandleMovement();
};
