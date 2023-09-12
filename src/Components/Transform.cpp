#include "Transform.hpp"
#include "../Utils/Vector2.hpp"

void Transform::Move(Vector2 velocity, float dt)
{
  position += velocity * dt;
}

void Transform::Rotate(Vector2 offset)
{
  rotation += offset;
}

void Transform::Scale(Vector2 factor)
{
  scale += factor;
}
