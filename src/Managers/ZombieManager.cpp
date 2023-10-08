#include "ZombieManager.hpp"
#include "EventManager.hpp"
#include "../Entities/Zombie.hpp"
#include "../Utils/Globals.hpp"
#include "../Utils/Util.hpp"
#include "../Events/EventFuncs.hpp"

#include <raylib.h>

#include <array>
#include <memory>

namespace ooh {

ZombieManager::ZombieManager(Vector2* playerPos)
{
  spawnedZombies = 0;
 
  m_spawnCooldown = 10.0f;
  m_spawnTimer = 0.0f;
  m_zombieSpawnLimit = 50;
  m_zombiesKilled = 0;
  m_hasStarted = false;

  Vector2 screenSize = Vector2{GetScreenWidth() - 32.0f, GetScreenHeight() - 32.0f};
  m_spawnPoints[0] = Vector2(screenSize.x / 2.0f, 32.0f);
  m_spawnPoints[1] = Vector2(screenSize.x, screenSize.y / 2.0f);
  m_spawnPoints[2] = Vector2(screenSize.x / 2.0f, screenSize.y);
  m_spawnPoints[3] = Vector2(32.0f, screenSize.y / 2.0f);

  // Zombie default init 
  for(int i = 0; i < zombies.size(); i++)
    zombies[i] = std::make_shared<Zombie>(m_spawnPoints[GetRandomValue(0, 3)], playerPos);

  // Listen to events 
  EventManager::Get().ListenToEvent<OnWaveEnd>([&](void){
    m_BuffZombies();
    m_zombieSpawnLimit += 10; // Increase the amount of zombies that spawn each wave
  });

  EventManager::Get().ListenToEvent<OnBloodInc>([&](int value){
    m_zombiesKilled++;
    spawnedZombies--;
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
  // ignore this check later on. This "m_hasStarted" flag will get reset every time the zombie manager 
  // get reset.
  if((!m_hasStarted) && spawnedZombies > 0)
    m_hasStarted = true;

  // This is here to help skip the initial start of the game. If this check wasn't here, as soon the 
  // player starts up the game, the event below will fire which is obviously not 
  // what we want. So, in order to skip the initial start of the game, this check is here. Perhaps not 
  // the best of solutions but it works. 
  if(!m_hasStarted)
    return;

  // End the wave when there's no zombies left 
  if(m_zombiesKilled >= m_zombieSpawnLimit)
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
    
void ZombieManager::Reset()
{
  for(auto& zombie : zombies)
    zombie->Reset();

  spawnedZombies = 0;
  m_spawnTimer = 0.0f;
  m_hasStarted = false;
  m_zombiesKilled = 0;
}
    
void ZombieManager::PauseZombies(bool paused)
{
  for(auto& zombie : zombies)
  {
    if(!zombie->isActive)
      continue; 
        
    zombie->body.SetBodyActive(!paused);
    zombie->body.SetBodyPosition(zombie->transform.position);
    zombie->anim.isAnimating = !paused;
  }
}

void ZombieManager::m_SpawnZombie()
{
  // We want a limit on the amount of zombies that spawn each wave. 
  // This number can increase after each wave ends. If the spawn limit on a 
  // wave is 20, then there can't be more than 20 zombies on that wave.
  if(spawnedZombies >= (m_zombieSpawnLimit - m_zombiesKilled))
    return;
  
  // Go through all of the zombies and spawn only the active ones, reactivating them and 
  // giving them full health. Make sure to spawn only ONE zombie per 
  // function call.
  for(auto& zombie : zombies)
  {
    if(zombie->isActive)
      continue;

    zombie->Reset();
    zombie->isActive = true;
    zombie->body.SetBodyActive(true);

    spawnedZombies++;

    break; // We only want one zombie
  }
}
    
void ZombieManager::m_BuffZombies()
{
  for(auto& zombie : zombies)
    zombie->maxHealth += 10;
}
  
}
