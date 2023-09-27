#pragma once

#include "Entity.hpp"
#include "Weapon.hpp"
#include "../Components/Sprite.hpp"
#include "../Components/PhysicsBody.hpp"
#include "../Components/Collider.hpp"
#include "../Metadata/ShopItemsMetadata.hpp"
#include "../Metadata/BodyMetadata.hpp"

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
    WeaponMetadata weaponMD;
    ArmorMetadata armorMD;
    PotionMetadata potionMD;
    
    int health, maxHealth;
    Sprite sprite;
    PhysicsBody body;
    Collider collider;

  public:
    void Update(float dt) override;
    void Render() override;
    void Reset() override;

  private:
    std::unique_ptr<Weapon> m_weapon;
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

    // Retrieve and apply all of the multipliers from the different 
    // shop items' metadata.
    void m_ApplyWeapon();
    void m_ApplyArmor();
    void m_ApplyPotion();
};

}
