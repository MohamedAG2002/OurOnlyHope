#include "WaveManager.hpp"
#include "../Utils/Util.hpp"
#include "../Utils/Globals.hpp"
#include "../Events/EventFuncs.hpp"
#include "../Managers/EventManager.hpp"
#include "../Enums/DataPosition.hpp"

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
}
    
WaveManager::~WaveManager()
{}

void WaveManager::Update()
{
  // Saving the highest wave count 
  if(waveCounter > highestWave)
  {
    highestWave = waveCounter;
    util::SaveDataToFile<uint32_t>("data/dat.bin", highestWave, DATPOS_WAVE);
  }
}

void WaveManager::Reset()
{
}

}
