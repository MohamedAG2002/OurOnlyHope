#pragma once

#include "../Entities/Zombie.hpp"

#include <raylib.h>

#include <array>
#include <memory>

namespace ooh {

// Consts 
const int MAX_ZOMBIES = 1;

class ZombieManager
{
  public:
    ZombieManager(Vector2* playerPos);
    ~ZombieManager();

  public:
    std::array<std::shared_ptr<Zombie>, MAX_ZOMBIES> zombies;

  public:
    void Update(float dt);
    void Render();

  private:
    float m_spawnCooldown, m_spawnTimer;
    std::array<Vector2, 4> m_spawnPoints;

  private:
    void m_SpawnZombie();
};
  
}
