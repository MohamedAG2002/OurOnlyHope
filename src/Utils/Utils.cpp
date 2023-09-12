#include "Utils.hpp"
#include "Vector2.hpp"
#include "Globals.hpp"

#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_scancode.h>
#include <SDL2/SDL_keyboard.h>
#include <box2d/box2d.h>

float Clamp(float value, float min, float max)
{
  if(value < min)
    return min;
  else if(value > max)
    return max;
  else 
    return value;
}

bool PointVSRect(SDL_FRect rect, Vector2 point)
{
  return (point.x > rect.x && point.x < (rect.x + rect.w)) && 
         (point.y > rect.y && point.y < (rect.y + rect.h));
}

bool IsKeyDown(SDL_Scancode key)
{
  const Uint8* keys = SDL_GetKeyboardState(NULL);
  return keys[key];
}

Vector2 B2Vec2ToVector2(b2Vec2 vec)
{
  return Vector2(vec.x * global::METER_TO_PIXEL, vec.y * global::METER_TO_PIXEL);
}

b2Vec2 Vector2ToB2Vec2(Vector2 vec)
{
  return b2Vec2(vec.x * global::PIXEL_TO_METER, vec.y * global::PIXEL_TO_METER);
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
  }
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
  }
}
