#include "Util.hpp"
#include "Globals.hpp"
#include "../Enums/BodyType.hpp"

#include <raylib.h>
#include <box2d/box2d.h>

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
