#include "Util.hpp"
#include "Globals.hpp"
#include "../Enums/BodyType.hpp"
#include "../Enums/Anchor.hpp"
#include "../Enums/WeaponType.hpp"
#include "../Enums/ArmorType.hpp"
#include "../Enums/PotionType.hpp"
#include "../Metadata/ShopItemsMetadata.hpp"

#include <ostream>
#include <raylib.h>
#include <box2d/box2d.h>
#include <yaml-cpp/yaml.h>

#include <math.h>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <cstdint>

namespace ooh {
 
namespace util {
 
float ClampF(float value, float min, float max)
{
  if(value < min)
    return min;
  else if(value > max)
    return max;
  else 
    return value;
}

int ClampI(int value, int min, int max)
{
  if(value < min)
    return min;
  else if(value > max)
    return max;
  else 
    return value;
}

float GetRandomFloat(float min, float max)
{
  float random = ((float) rand()) / (float)RAND_MAX;
  float diff = max - min;
  float trueRand = random * diff;

  return min + trueRand;
}

float GetAngle(Vector2 point1, Vector2 point2)
{
  Vector2 diff = Vector2{point1.x - point2.x, point1.y - point2.y};
  return atan2f(diff.y, diff.x) * RAD2DEG;
}

bool IsColorEqual(Color c1, Color c2)
{
  return (c1.r == c2.r) && (c1.g == c2.g) && 
         (c1.b == c2.b) && (c1.a == c2.a);
}

bool CheckEntityType(std::string& type1, std::string& type2, std::string&& desired)
{
  return (type1 == desired) || (type2 == desired);
}

Vector2 SetPositionByAnchor(Anchor anc, Vector2 size, Vector2 offset)
{
  // Variables for easier visualization
  Vector2 screenSize = {(float)GetScreenWidth(), (float)GetScreenHeight()};
  Vector2 result = Vector2{0.0f, 0.0f};
  Vector2 halfSize = Vector2(size.x / 2.0f, size.y / 2.0f);

  switch(anc)
  {
    case Anchor::TOP_LEFT:
      result = Vector2{(15.0f + halfSize.x) + offset.x, (15.0f + halfSize.y) + offset.y};
      break;
    case Anchor::TOP_CENTER:
      result = Vector2{screenSize.x / 2.0f + offset.x, (15.0f + halfSize.y) + offset.y};
      break;
    case Anchor::TOP_RIGHT:
      result = Vector2{(screenSize.x - halfSize.x - 15.0f) + offset.x, (15.0f + halfSize.y) + offset.y};
      break;
    case Anchor::CENTER_LEFT:
      result = Vector2{(15.0f + halfSize.x) + offset.x, screenSize.y / 2.0f + offset.y};
      break;
    case Anchor::CENTER:
      result = Vector2{screenSize.x / 2.0f + offset.x, screenSize.y / 2.0f + offset.y};
      break;
    case Anchor::CENTER_RIGHT:
      result = Vector2{(screenSize.x - halfSize.x - 15.0f) + offset.x, screenSize.y / 2.0f + offset.y};
      break;
    case Anchor::BOTTOM_LEFT:
      result = Vector2{(15.0f + halfSize.x) + offset.x, (screenSize.y - halfSize.y - 15.0f) + offset.y};
      break;
    case Anchor::BOTTOM_CENTER:
      result = Vector2{screenSize.x / 2.0f + offset.x, (screenSize.y - halfSize.y - 15.0f) + offset.y};
      break;
    case Anchor::BOTTOM_RIGHT:
      result = Vector2{(screenSize.x - halfSize.x - 15.0f) + offset.x, 
                      (screenSize.y - halfSize.y - 15.0f) + offset.y};
      break;
    default:
      result = Vector2{0.0f, 0.0f};
      break;
  }

  return result;
}

WeaponMetadata LoadWeaponMetadata(const std::string& node)
{
  WeaponMetadata md = {};
  YAML::Node data = YAML::LoadFile("data/weapon_md.yaml");
  
  // Err if there is no node called as the node given
  if(!data[node])   
  {
    std::cerr << "ERROR: No node called " << node << std::endl;
    return md;
  }

  // Filling in the metadata from the value in the equivelant yaml file
  YAML::Node weapon = data[node];
  md.name = node;
  md.type = (WeaponType)weapon["type"].as<int>();
  md.damage = weapon["damage"].as<int>();
  md.durability = weapon["durability"].as<int>();
  md.weight = weapon["weight"].as<float>();
  md.range = weapon["range"].as<float>();
  md.speed = weapon["speed"].as<float>();

  return md;
}

ArmorMetadata LoadArmorMetadata(const std::string& node)
{
  ArmorMetadata md = {};
  YAML::Node data = YAML::LoadFile("data/armor_md.yaml");
  
  // Err if there is no node called as the node given
  if(!data[node])   
  {
    std::cerr << "ERROR: No node called " << node << std::endl;
    return md;
  }

  // Filling in the metadata from the value in the equivelant yaml file
  YAML::Node armor = data[node];
  md.name = node;
  md.type = (ArmorType)armor["type"].as<int>();
  md.defense = armor["defense"].as<int>(); 
  md.durability = armor["durability"].as<int>();
  md.weight = armor["weight"].as<float>();
  
  return md;
}

PotionMetadata LoadPotionMetadata(const std::string& node)
{
  PotionMetadata md = {};
  YAML::Node data = YAML::LoadFile("data/potion_md.yaml");
  
  // Err if there is no node called as the node given
  if(!data[node])   
  {
    std::cerr << "ERROR: No node called " << node << std::endl;
    return md;
  }

  // Filling in the metadata from the value in the equivelant yaml file
  YAML::Node potion = data[node];
  md.name = node;
  md.type = (PotionType)potion["type"].as<int>();
  md.durability = potion["durability"].as<int>();
  md.health = potion["health"].as<int>();
  md.damage = potion["damage"].as<int>();
  md.weight = potion["weight"].as<float>();
  
  return md;
}

Vector2 B2Vec2ToVector2(b2Vec2 vec)
{
  return Vector2(vec.x * global::METER_TO_PIXEL, vec.y * global::METER_TO_PIXEL);
}

b2Vec2 Vector2ToB2Vec2(Vector2 vec)
{
  return b2Vec2(vec.x * global::PIXEL_TO_METER, vec.y * global::PIXEL_TO_METER);
}

b2BodyType BodyTypeToB2BodyType(BodyType type)
{
  switch(type)
  {
    case BodyType::STATIC:
      return b2_staticBody;
      break;
    case BodyType::RIGID:
      return b2_dynamicBody;
      break;
    case BodyType::KINEMATIC:
      return b2_kinematicBody;
      break;
    default:
      return b2_staticBody;
      break;
  }
}

BodyType B2BodyTypeToBodyType(b2BodyType type)
{
  switch(type)
  {
    case b2_staticBody:
      return BodyType::STATIC;
      break;
    case b2_dynamicBody:
      return BodyType::RIGID;
      break;
    case b2_kinematicBody:
      return BodyType::KINEMATIC;
      break;
    default:
      return BodyType::STATIC;
      break;
  }
}

}

}
