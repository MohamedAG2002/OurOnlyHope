#include "BloodManager.hpp"
#include "EventManager.hpp"
#include "../Enums/SceneType.hpp"
#include "../Events/EventFuncs.hpp"
#include "../Utils/Util.hpp"
#include "../Utils/Globals.hpp"

#include <raylib.h>

#include <cstdint>

namespace ooh {
  
BloodManager::BloodManager()
{
  blood = 0;
  util::SaveDataToFile(global::BLD_DAT_FILE_NAME, 10000000); 
  totalBlood = util::GetDataFromFile<uint32_t>(global::BLD_DAT_FILE_NAME); 

  // Listen to events 
  EventManager::Get().ListenToEvent<OnBloodInc>([&](int value){
    blood += value;
  });

  EventManager::Get().ListenToEvent<OnSceneChange>([&](SceneType st){
    // Will add the total blood to the file in case the player decides to 
    // exit to the main menu. As soon as the game enters the shop scene, 
    // it will add the total blood to the file.
    if(st != SceneType::SHOP)
      return;

    totalBlood += blood;
    util::SaveDataToFile<uint32_t>(global::BLD_DAT_FILE_NAME, totalBlood);
  });

  EventManager::Get().ListenToEvent<OnWaveEnd>([&](){
    totalBlood += blood;
    util::SaveDataToFile<uint32_t>(global::BLD_DAT_FILE_NAME, totalBlood);
  });
  
  EventManager::Get().ListenToEvent<OnItemBuy>([&](const int cost){
    // Don't allow the player to buy an item when there's not enough blood 
    if(totalBlood < cost)
      return;

    totalBlood -= cost;
    util::SaveDataToFile<uint32_t>(global::BLD_DAT_FILE_NAME, totalBlood);
  });
}

BloodManager::~BloodManager()
{}
    
void BloodManager::Reset()
{
  blood = 0;
}

}
