#pragma once 

#include "Vector2.hpp"

#include <SDL2/SDL_rect.h>

bool PointVSRect(SDL_FRect rect, Vector2 point);
