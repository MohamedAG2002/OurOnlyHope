#pragma once

#include <SDL2/SDL_render.h>
#include <SDL2/SDL_pixels.h>
#include <box2d/box2d.h>

namespace global {

// Screen size
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

// Colors
const SDL_Color RED = SDL_Color{255, 0, 0, 255};
const SDL_Color GREEN = SDL_Color{0, 255, 0, 255};
const SDL_Color BLUE = SDL_Color{0, 0, 255, 255};
const SDL_Color WHITE = SDL_Color{255, 255, 255, 255};
const SDL_Color BLACK = SDL_Color{0, 0, 0, 255};
const SDL_Color PINK = SDL_Color{255, 0, 255, 255};
const SDL_Color YELLOW = SDL_Color{255, 255, 0, 255};
const SDL_Color CYAN = SDL_Color{0, 255, 255, 255};
const SDL_Color GRAY = SDL_Color{138, 138, 138, 255};
const SDL_Color BROWN = SDL_Color{142, 66, 0, 255};

// Box2D 
const int VEL_ITER = 6;
const int POS_ITER = 2;
const float METER_TO_PIXEL = 50.0f;
const float PIXEL_TO_METER = 1.0f / METER_TO_PIXEL;

// GLOBAL VARIABLES??!! YUCK!!!!!!
extern b2World* world; // Everything with the box2d world is handled in the GameManager.cpp
}
