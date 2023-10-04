#include "BloodManager.hpp"
#include "EventManager.hpp"
#include "../Enums/DataPosition.hpp"
#include "../Enums/SceneType.hpp"
#include "../Events/EventFuncs.hpp"
#include "../Utils/Util.hpp"

#include <raylib.h>

#include <cstdint>

namespace ooh {
  
BloodManager::BloodManager()
{
  blood = 0;
  totalBlood = util::GetDataFromFile<uint32_t>("data/dat.bin", DATPOS_BLOOD); 

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
    util::SaveDataToFile<uint32_t>("data/dat.bin", totalBlood, DATPOS_BLOOD);
  });

  EventManager::Get().ListenToEvent<OnWaveEnd>([&](){
    totalBlood += blood;
    util::SaveDataToFile<uint32_t>("data/dat.bin", totalBlood, DATPOS_BLOOD);
  });
  
  EventManager::Get().ListenToEvent<OnItemBuy>([&](const int cost){
    totalBlood -= cost;
    util::SaveDataToFile<uint32_t>("data/dat.bin", totalBlood, DATPOS_BLOOD);
  });
}

BloodManager::~BloodManager()
{}
    
void BloodManager::Reset()
{
  blood = 0;
}

}
