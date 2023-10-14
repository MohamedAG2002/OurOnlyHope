#pragma once

#include "Entity.hpp"
#include "Weapon.hpp"
#include "../Components/Sprite.hpp"
#include "../Components/PhysicsBody.hpp"
#include "../Components/Collider.hpp"
#include "../Metadata/BodyMetadata.hpp"
#include "../Metadata/PotionMetadata.hpp"

#include <raylib.h>

#include <memory>

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
    BodyMetadata bodyMetadata;
    PotionMetadata potionMD;
    
    int health, maxHealth;
    Vector2 velocity;
    
    Sprite sprite;
    PhysicsBody body;
    Collider collider;
    
    std::unique_ptr<Weapon> weapon;

  public:
    void Update(float dt) override;
    void Render() override;
    void Reset() override;

  private:
    float m_speed;
    bool m_canAttack;

  private:
    void m_GetKeyInput();
    void m_Attack();
    void m_HitPlayer(int damage);
    void m_HandleHealth();
    void m_HandleMovement(float dt);

    // Retrieve and apply all of the multipliers from the different 
    // potion metadata.
    void m_ApplyPotion(const std::string& node);
};

}
