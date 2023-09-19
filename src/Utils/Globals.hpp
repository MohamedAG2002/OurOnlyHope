#pragma once

#include <box2d/box2d.h>

namespace ooh {
 
namespace global {

// OOH consts 
const int CURRENT_GAMEPAD = 0;

// Box2D consts
const int VEL_ITER = 6;
const int POS_ITER = 2;
const float METER_TO_PIXEL = 50.0f;
const float PIXEL_TO_METER = 1.0f / METER_TO_PIXEL;

// GLOBAL VARIABLES??!! YUCK!!!!!!
extern b2World* world; // Everything with the box2d world is handled in the GameManager.cpp
extern bool isDebugDraw;

}

}
