#pragma once

#include "../Enums/PotionType.hpp"

#include <string>

namespace ooh {
 
struct PotionMetadata
{
  std::string name;
  PotionType type;

  // These value will be deducted or applied to the weapon, armor, or the player 
  // as a multiplier.
  int durability, health, damage;
  float speed;
};

}
