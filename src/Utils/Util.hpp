#pragma once

#include "../Enums/BodyType.hpp"

#include <raylib.h>
#include <box2d/box2d.h>

namespace ooh {
 
namespace util {

// OOH utilites 
float ClampF(float value, float min, float max);
int ClampI(int value, int min, int max);
float GetAngle(Vector2 point1, Vector2 point2);
bool IsColorEqual(Color c1, Color c2);

// Box2D utilties
Vector2 B2Vec2ToVector2(b2Vec2 vec);
b2Vec2 Vector2ToB2Vec2(Vector2 vec);
b2BodyType BodyTypeToB2BodyType(BodyType type);
BodyType B2BodyTypeToBodyType(b2BodyType type);

}

}
