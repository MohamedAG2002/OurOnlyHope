#include "Transform.hpp"
#include "../Utils/Vector2.hpp"

Transform::Transform(Vector2 pos, Vector2 rotation, Vector2 scale)
  :position(pos), rotation(rotation), scale(scale)
{}

Transform::~Transform()
{}

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
