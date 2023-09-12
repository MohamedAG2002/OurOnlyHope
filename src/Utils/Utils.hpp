#pragma once 

#include "Vector2.hpp"
#include "../Enums/BodyType.hpp"

#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_scancode.h>
#include <box2d/b2_body.h>
#include <box2d/b2_math.h>

float Clamp(float value, float min, float max);
bool PointVSRect(SDL_FRect rect, Vector2 point);
bool IsKeyDown(SDL_Scancode key);

// Utility functions for better integration with Box2D
Vector2 B2Vec2ToVector2(b2Vec2 vec);
b2Vec2 Vector2ToB2Vec2(Vector2 vec);
BodyType B2BodyTypeToBodyType(b2BodyType type);
b2BodyType BodyTypeToB2BodyType(BodyType type);
