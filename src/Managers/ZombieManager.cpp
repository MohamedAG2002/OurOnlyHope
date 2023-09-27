#include "ZombieManager.hpp"
#include "EventManager.hpp"
#include "../Entities/Zombie.hpp"
#include "../Utils/Globals.hpp"
#include "../Utils/Util.hpp"
#include "../Events/EventFuncs.hpp"

#include <raylib.h>

#include <algorithm>
#include <array>
#include <memory>

namespace ooh {

ZombieManager::ZombieManager(Vector2* playerPos)
{
  m_spawnCooldown = 50.0f;
  m_spawnTimer = 0.0f;

  Vector2 screenSize = Vector2{GetScreenWidth() - 32.0f, GetScreenHeight() - 32.0f};
  m_spawnPoints[0] = Vector2(screenSize.x / 2.0f, 32.0f);
  m_spawnPoints[1] = Vector2(screenSize.x, screenSize.y / 2.0f);
  m_spawnPoints[2] = Vector2(screenSize.x / 2.0f, screenSize.y);
  m_spawnPoints[3] = Vector2(32.0f, screenSize.y / 2.0f);

  m_hasStarted = false;

  // Zombie default init 
  for(int i = 0; i < zombies.size(); i++)
    zombies[i] = std::make_shared<Zombie>(m_spawnPoints[GetRandomValue(0, 3)], playerPos);

  // Listen to events 
  EventManager::Get().ListenToEvent<OnWaveEnd>([&](void){
    m_BuffZombies();
  });
}

ZombieManager::~ZombieManager()
{}

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

  // Once the first zombie spawned, it's safe to assume that the game started up and we can 
  // ignore this check later on. This flag gets to true it never gets set to false again ever 
  // in the game unless the player closes the game and reopens it again.
  if((!m_hasStarted) && m_CountActiveZombies() > 0)
    m_hasStarted = true;

  // This is here to help skip the initial start of the game. If this check wasn't here, as soon the 
  // player starts up the game for the first time he, the event below will fire which is obviously not 
  // what we want. So, in order to skip the initial start of the game, this check is here. Perhaps not 
  // the best of solutions but it works. 
  if(!m_hasStarted)
    return;

  // End the wave when there's no zombies left 
  if(m_CountActiveZombies() == 0)
    EventManager::Get().DispatchEvent<OnWaveEnd>();
}

void ZombieManager::Render()
{
  for(auto& zombie : zombies)
  {
    if(zombie->isActive)
      zombie->Render();
  }
}

void ZombieManager::m_SpawnZombie()
{
  // Go through all of the zombies and spawn only the active ones that have 
  // full health (or at least more than 0). Make sure to spawn only ONE zombie per 
  // function call.
  for(auto& zombie : zombies)
  {
    if(zombie->isActive || zombie->health <= 0)
      continue;
  
    zombie->isActive = true;

    break; // We only want one zombie
  }
}
    
int ZombieManager::m_CountActiveZombies()
{
  int count = 0;

  for(auto& zombie : zombies)
  {
    if(zombie->isActive)
      count++;
  }

  return count;
}
    
void ZombieManager::m_BuffZombies()
{
  for(auto& zombie : zombies)
    zombie->maxHealth += 10;
}
  
}
