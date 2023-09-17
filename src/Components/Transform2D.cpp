#include "Transform2D.hpp"

#include <raylib.h>

namespace ooh {

void Transform2D::Move(Vector2 velocity)
{
  position.x += velocity.x * GetFrameTime();
  position.y += velocity.y * GetFrameTime();
}

void Transform2D::Rotate(float rotation)
{
  rotation += rotation;
}

void Transform2D::Scale(Vector2 factor)
{
  scale.x += factor.x;
  scale.y += factor.y;
}
  
}
