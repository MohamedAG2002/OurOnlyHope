#include "EntityManager.hpp"
#include "../Utils/Globals.hpp"
#include "../Entities/Entity.hpp"
#include "../Entities/Player.hpp"
#include "../Managers/ZombieManager.hpp"

#include <raylib.h>

#include <vector>
#include <memory>

namespace ooh {

EntityManager::EntityManager()
{
  player = std::make_unique<Player>(Vector2{GetScreenWidth() / 2.0f, GetScreenHeight() / 2.0f});
  zmbMgr = std::make_unique<ZombieManager>(&player->transform.position);
}

EntityManager::~EntityManager()
{}

void EntityManager::Update(float dt)
{
  if(player->isActive)
    player->Update(dt);

  zmbMgr->Update(dt);
}

void EntityManager::Render()
{
  if(player->isActive)
    player->Render();

  zmbMgr->Render();
}

void EntityManager::Reset()
{
  zmbMgr->Reset();
  player->Reset();
}
    
void EntityManager::PauseEntities(bool paused)
{
  zmbMgr->PauseZombies(paused);

  player->body.SetBodyActive(!paused);
  //player->velocity = Vector2{0.0f, 0.0f};
  //player->body.ApplyForce(player->velocity);
}
  
}
