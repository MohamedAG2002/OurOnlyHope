#pragma once

#include "../Utils/Vector2.hpp"
#include "../Enums/BodyType.hpp"

#include <box2d/box2d.h>

class PhysicsBody
{
  public:
    PhysicsBody(b2World* world, const Vector2 pos, BodyType type);
    ~PhysicsBody();

  public:
    Vector2 GetBodyPosition();
    void ApplyForce(Vector2 force);

  private:
    b2Body* m_body; 
    b2BodyDef m_bodyDef;
};
