#include "ZombieManager.hpp"
#include "../Entities/Zombie.hpp"
#include "../Utils/Vector2.hpp"
#include "../Utils/Globals.hpp"
#include "../Utils/Utils.hpp"

#include <SDL2/SDL.h>

#include <array>
#include <memory>

ZombieManager::ZombieManager(Vector2* playerPos)
{
  m_spawnCooldown = 50.0f;
  m_spawnTimer = 0.0f;

  m_spawnPoints[0] = Vector2(global::SCREEN_WIDTH / 2.0f, 10.0f);
  m_spawnPoints[1] = Vector2(global::SCREEN_WIDTH, global::SCREEN_HEIGHT / 2.0f);
  m_spawnPoints[2] = Vector2(global::SCREEN_WIDTH / 2.0f, global::SCREEN_HEIGHT);
  m_spawnPoints[3] = Vector2(10.0f, global::SCREEN_HEIGHT / 2.0f);
  
  // Zombie default init 
  for(int i = 0; i < zombies.size(); i++)
    zombies[i] = std::make_shared<Zombie>(m_spawnPoints[GetRandomInt(0, 3)], playerPos);
}

ZombieManager::~ZombieManager()
{
  
}
    
void ZombieManager::ProcessEvents(SDL_Event event)
{
  // Does nothing here...
}

void ZombieManager::Update(float dt)
{
  for(auto& zombie : zombies)
  {
    if(zombie->isActive)
      zombie->Update(dt);
  }

  m_spawnTimer++;

  if(m_spawnTimer > m_spawnCooldown)
  {
    m_spawnTimer = 0.0f;
    m_SpawnZombie();
  }
}

void ZombieManager::Render(SDL_Renderer* renderer)
{
  for(auto& zombie : zombies)
  {
    if(zombie->isActive)
      zombie->Render(renderer);
  }
}

void ZombieManager::m_SpawnZombie()
{
  // Going through the zombies reserves and picking out the inactive zombies 
  // and activating them, giving a new random position.
  for(auto& zombie : zombies)
  {
    // Remember, we only care about inactive zombies
    if(zombie->isActive)
      continue;

    zombie->isActive = true;

    break; // We only want one zombie
  }
}
