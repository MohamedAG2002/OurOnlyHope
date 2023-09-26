#pragma once

#include "../Enums/BodyType.hpp"

#include <raylib.h>
#include <box2d/box2d.h>

#include <cstdint>
#include <random>

namespace ooh {
 
namespace util {

// OOH utilites 
float ClampF(float value, float min, float max);
int ClampI(int value, int min, int max);
float GetAngle(Vector2 point1, Vector2 point2);
bool IsColorEqual(Color c1, Color c2);

// Will check if the given "desired" is equal to either "type1" or "type2"
bool CheckEntityType(std::string& type1, std::string& type2, std::string&& desired);

template<typename T>
T GetRandomNumber()
{
  std::random_device rndDevice;
  std::default_random_engine rndEngine(rndDevice());
  std::uniform_int_distribution<T> uniformDist;

  return uniformDist(rndEngine);
}

// Box2D utilties
Vector2 B2Vec2ToVector2(b2Vec2 vec);
b2Vec2 Vector2ToB2Vec2(Vector2 vec);
b2BodyType BodyTypeToB2BodyType(BodyType type);
BodyType B2BodyTypeToBodyType(b2BodyType type);

}

}
