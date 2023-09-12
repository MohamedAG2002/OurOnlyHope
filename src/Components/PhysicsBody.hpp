#pragma once

#include "../Utils/Vector2.hpp"
#include "../Enums/BodyType.hpp"

#include <box2d/box2d.h>

#include <string>

class PhysicsBody
{
  public:
    PhysicsBody(std::string& id, const Vector2 pos, BodyType type);
    PhysicsBody();
    ~PhysicsBody();

  public:
    // Returns the position of the body in pixels and not in meters.
    // Use this when you want to pass in values to the engine.
    Vector2 GetBodyPosition();

    // Takes the force in pixles, converts it into meters. and applies force 
    // to the body.
    void ApplyForce(Vector2 force);

    // Attach a fixture defination (collider) to the physics body. 
    // NOTE: Do not use this in gameplay code. When the body gets passed to the collider, 
    // the collider itself will call this function. So there's no need to call it as a user.
    void AttachCollider(const b2FixtureDef& collider);

  private:
    b2Body* m_body; 
    b2BodyDef m_bodyDef;
};
