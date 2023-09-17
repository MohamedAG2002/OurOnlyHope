#include "EntityManager.hpp"
#include "../Utils/Globals.hpp"
#include "../Entities/Entity.hpp"
#include "../Entities/Player.hpp"
/*
#include "../Entities/Weapon.hpp"
#include "../Managers/ZombieManager.hpp"
*/
#include "../Enums/WeaponType.hpp"

#include <raylib.h>

#include <vector>
#include <memory>

namespace ooh {

EntityManager::EntityManager()
{
  player = std::make_unique<Player>(Vector2{GetScreenWidth() / 2.0f, GetScreenHeight() / 2.0f});
  /*
  zmbMgr = std::make_unique<ZombieManager>(&player->transform.position);
  weapon = std::make_unique<Weapon>(&player->transform.position, WeaponType::LIGHT);
  */
}

EntityManager::~EntityManager()
{}

void EntityManager::Update(float dt)
{
  if(player->isActive)
    player->Update(dt);
 
  /*
  if(weapon->isActive)
    weapon->Update(dt);

  zmbMgr->Update(dt);
  */
}

void EntityManager::Render()
{
  if(player->isActive)
    player->Render();
  
  /*
  if(weapon->isActive)
    weapon->Render(renderer);

  zmbMgr->Render(renderer);
  */
}

void EntityManager::Reset()
{}
  
}
