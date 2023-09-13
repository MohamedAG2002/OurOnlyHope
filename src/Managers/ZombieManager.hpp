#pragma once

#include "../Entities/Zombie.hpp"
#include "../Utils/Vector2.hpp"

#include <SDL2/SDL.h>

#include <array>
#include <memory>

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
    void ProcessEvents(SDL_Event event);
    void Update(float dt);
    void Render(SDL_Renderer* renderer);

  private:
    float m_spawnCooldown, m_spawnTimer;
    std::array<Vector2, 4> m_spawnPoints;

  private:
    void m_SpawnZombie();
};
