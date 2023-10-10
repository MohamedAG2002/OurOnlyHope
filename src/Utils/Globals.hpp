#pragma once

#include <raylib.h>
#include <box2d/box2d.h>

namespace ooh {
 
namespace global {

// OOH consts 
const int CURRENT_GAMEPAD = 0;
static const char* BLD_DAT_FILE_NAME = "data/bld.dat";
static const char* WV_DAT_FILE_NAME = "data/wv.dat";
const Color UI_BOX_COLOR = RED;
const Color UI_OUTLINE_COLOR = BLACK;
const Color UI_TEXT_COLOR = DARKGREEN;

// Box2D consts
const int VEL_ITER = 6;
const int POS_ITER = 2;
const float METER_TO_PIXEL = 50.0f;
const float PIXEL_TO_METER = 1.0f / METER_TO_PIXEL;

// GLOBAL VARIABLES??!! YUCK!!!!!!
extern b2World* world; // Everything with the box2d world is handled in GameManager.cpp
extern bool isDebugDraw; // This is declared and initialized in GameManager.cpp

}

}
