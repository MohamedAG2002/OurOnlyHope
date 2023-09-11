#include "Utils.hpp"
#include "Vector2.hpp"

#include <SDL2/SDL_rect.h>


bool PointVSRect(SDL_FRect rect, Vector2 point)
{
  return (point.x > rect.x && point.x < (rect.x + rect.w)) && 
         (point.y > rect.y && point.y < (rect.y + rect.h));
}
