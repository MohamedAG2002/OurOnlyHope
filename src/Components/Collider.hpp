#pragma once

#include "PhysicsBody.hpp"

#include <raylib.h>
#include <box2d/box2d.h>

namespace ooh{

class Collider 
{
  public:
    Collider(PhysicsBody& body, Vector2 size, float density, bool sensor);
    Collider();
    ~Collider();

  public:
    void SetSize(Vector2 size);

  private:
    b2PolygonShape m_shape;
    b2FixtureDef m_fixtureDef;
};
  
}
