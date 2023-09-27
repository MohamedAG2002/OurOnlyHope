#include "BloodManager.hpp"
#include "EventManager.hpp"
#include "../Events/EventFuncs.hpp"
#include "../Utils/Util.hpp"

#include <raylib.h>

#include <cstdint>

namespace ooh {
  
BloodManager::BloodManager()
{
  blood = 0;
  totalBlood = util::GetDataFromFile<uint32_t>("data/bld.dat"); 

  // Listen to events 
  EventManager::Get().ListenToEvent<OnBloodInc>([&](int value){
    blood += value;
  });

  EventManager::Get().ListenToEvent<OnWaveEnd>([&](){
    totalBlood += blood;
    util::SaveDataToFile<uint32_t>("data/bld.dat", totalBlood);
  });
}

BloodManager::~BloodManager()
{}

}
