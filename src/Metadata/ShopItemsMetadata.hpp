#pragma once

#include "../Enums/WeaponType.hpp"
#include "../Enums/ArmorType.hpp"
#include "../Enums/PotionType.hpp"

#include <string>
#include <cstdint>

namespace ooh {
 
struct WeaponMetadata
{
  std::string name;
  WeaponType type;

  int damage, durability;
  float weight, range, speed;
};

struct ArmorMetadata
{
  std::string name;
  ArmorType type; 

  int defense, durability;
  float weight;
};

struct PotionMetadata
{
  std::string name;
  PotionType type;

  // These value will be deducted or applied to the weapon, armor, or the player 
  // as a multiplier.
  int durability, health, damage;
  float weight;
};

}
