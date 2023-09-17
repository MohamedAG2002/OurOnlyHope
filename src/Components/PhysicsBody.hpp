#pragma once

#include "../Enums/BodyType.hpp"

#include <raylib.h>
#include <box2d/box2d.h>

#include <string>

namespace ooh {

class PhysicsBody
{
  public:
    PhysicsBody(std::string& id, const Vector2 pos, BodyType type, bool active);
    PhysicsBody();
    ~PhysicsBody();

  public:
    // Sets the position of the body in pixels and not in meters.
    // Use this carefully as the physics simulation shouldn't have 
    // a sudden, unexpected change in movement.
    void SetBodyPosition(const Vector2 pos);
    
    // Returns the position of the body in pixels and not in meters.
    // Use this when you want to pass in values to the engine.
    Vector2 GetBodyPosition();

    // Sets the body's rotation based on the given rotation in degrees
    void SetBodyRotation(float rotation);
    
    // Retrieve the body's rotation in degrees
    float GetBodyRotation();

    // Takes the force in pixles, converts it into meters, and applies the force 
    // to the body.
    void ApplyForce(Vector2 force);
  
    // Set whether the body is active or not. This is very important since it 
    // can save up a lot on performance if a specific body doesn't activate immediately
    // or isn't active all the time.
    void SetBodyActive(bool active);

    // Attach a fixture defination (collider) to the physics body. 
    // NOTE: Do not use this in gameplay code. When the body gets passed to the collider, 
    // the collider itself will call this function. So there's no need to call it as a user.
    void AttachCollider(const b2FixtureDef& collider);

  private:
    b2Body* m_body; 
    b2BodyDef m_bodyDef;
};
  
}
