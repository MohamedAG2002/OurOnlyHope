#include "WaveManager.hpp"
#include "../Utils/Util.hpp"
#include "../Events/EventFuncs.hpp"
#include "../Managers/EventManager.hpp"

#include <cstdint>

namespace ooh {
 

WaveManager::WaveManager()
{
  waveCounter = 0;
  highestWave = 0;

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
    util::SaveDataToFile<uint32_t>("data/wv.dat", highestWave);
  }
}

}
