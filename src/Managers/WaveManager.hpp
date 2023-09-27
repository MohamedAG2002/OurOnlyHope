#pragma once

#include <cstdint>

namespace ooh {
 
class WaveManager 
{
  public:
    WaveManager();
    ~WaveManager();

  public:
    uint32_t waveCounter, highestWave; 

  public:
    void Update();
    void Reset();
};

}
