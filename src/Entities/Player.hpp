#pragma once

#include "Entity.hpp"
#include "../Components/Sprite.hpp"
#include "../Components/PhysicsBody.hpp"
#include "../Components/Collider.hpp"

#include <raylib.h>

namespace ooh {

// Consts 
const float PLAYER_MOVE_SPEED = 400.0f;
const float PLAYER_ROTATION_SPEED = 200.0f;

class Player : public Entity
{
  public:
    Player(const Vector2 startPos);
    ~Player();

  public:
    int health, maxHealth;
    Sprite sprite;
    PhysicsBody body;
    Collider collider;

  public:
    void Update(float dt) override;
    void Render() override;

  private:
    Vector2 m_velocity;
    float m_attackCooldown, m_attackTimer;
    bool m_canAttack;

  private:
    void m_GetKeyInput();
    void m_GetJoystickInput();
    void m_Attack();
    void m_HandleHealth();
    void m_HandleMovement(float dt);
    void m_HandleCombat();
};

}
