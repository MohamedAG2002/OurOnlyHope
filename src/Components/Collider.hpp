#pragma once

#include "PhysicsBody.hpp"
#include "../Utils/Vector2.hpp"

#include <box2d/box2d.h>

class Collider 
{
  public:
    Collider(PhysicsBody& body, Vector2 size, float density);
    Collider();
    ~Collider();

  private:
    b2PolygonShape m_shape;
    b2FixtureDef m_fixtureDef;
};
