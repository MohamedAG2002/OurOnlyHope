#include "WaveManager.hpp"
#include "../Utils/Util.hpp"
#include "../Utils/Globals.hpp"
#include "../Events/EventFuncs.hpp"
#include "../Managers/EventManager.hpp"
#include "../Enums/DataPosition.hpp"
#include "../Enums/SceneType.hpp"

#include <cstdint>

namespace ooh {

WaveManager::WaveManager()
{
  waveCounter = 1;
  highestWave = util::GetDataFromFile<uint32_t>("data/dat.bin", DATPOS_WAVE);

  // Listen to events 
  EventManager::Get().ListenToEvent<OnWaveEnd>([&](){
    waveCounter++;
  });
 
  EventManager::Get().ListenToEvent<OnSceneChange>([&](SceneType st){
    // Only restart the wave counter when the player dies or goes back 
    // to the main menu scene.
    if(st == SceneType::MENU || st == SceneType::OVER_LOSE) 
      waveCounter = 1;
  });
}
    
WaveManager::~WaveManager()
{}

void WaveManager::Update()
{
  // Saving the highest wave count 
  if(waveCounter > highestWave)
  {
    highestWave = 10;
    util::SaveDataToFile<uint32_t>("data/dat.bin", highestWave, DATPOS_WAVE);
  }
}

void WaveManager::Reset()
{}

}
