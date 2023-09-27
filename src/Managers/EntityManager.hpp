#pragma once

#include "../Entities/Entity.hpp"
#include "../Entities/Player.hpp"
#include "../Managers/ZombieManager.hpp"

#include <raylib.h>

#include <vector>
#include <memory>

namespace ooh {

class EntityManager
{
  public:
    EntityManager();
    ~EntityManager();

  public:
    std::unique_ptr<Player> player;
    std::unique_ptr<ZombieManager> zmbMgr;

  public:
    void Update(float dt);
    void Render();
    void Reset(); 
};
  
}
