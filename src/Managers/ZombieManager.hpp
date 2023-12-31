#pragma once

#include "../Entities/Zombie.hpp"

#include <raylib.h>

#include <array>
#include <memory>

namespace ooh {

// Consts 
const int MAX_ZOMBIES = 50;
const int HEALTH_CAP = 400;
const int DAMAGE_CAP = 50;
const int SPAWN_LIMIT_CAP = 150;

class ZombieManager
{
  public:
    ZombieManager(Vector2* playerPos);
    ~ZombieManager();

  public:
    std::array<std::shared_ptr<Zombie>, MAX_ZOMBIES> zombies;
    int spawnedZombies;

  public:
    void Update(float dt);
    void Render();
    void Reset();
    void PauseZombies(bool paused);

  private:
    float m_spawnCooldown, m_spawnTimer;
    float m_gruntTimer, m_gruntCooldown;
    int m_zombieSpawnLimit, m_zombiesKilled;
    bool m_hasStarted;
    std::array<Vector2, 4> m_spawnPoints;

  private:
    void m_SpawnZombie();
    int m_CountActiveZombies();
    void m_BuffZombies();
};
  
}
