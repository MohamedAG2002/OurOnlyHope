#pragma once

#include "Entity.hpp"
#include "../Components/Animator.hpp"
#include "../Components/PhysicsBody.hpp"
#include "../Components/Collider.hpp"
#include "../Metadata/BodyMetadata.hpp"

#include <raylib.h>

namespace ooh {

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
    BodyMetadata bodyMetadata;
    Animator anim;
    PhysicsBody body;
    Collider collider;

  public:
    void Update(float dt) override;
    void Render() override;
    void Reset() override;

  private:
    float m_attackCooldown, m_attackTimer;
    Vector2 m_velocity, m_startPos;
    Vector2* m_target;

  private:
    void m_HandleHealth();
    void m_HandleDamage();
    void m_HandleMovement();
};
  
}
