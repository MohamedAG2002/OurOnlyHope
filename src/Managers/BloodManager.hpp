#pragma once

#include <cstdint>

namespace ooh {
 
class BloodManager 
{
  public:
    BloodManager();
    ~BloodManager();

  public:
    uint32_t blood, totalBlood;

  public:
    void Reset();
};

}
