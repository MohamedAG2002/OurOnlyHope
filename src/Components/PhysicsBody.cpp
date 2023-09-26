#include "PhysicsBody.hpp"
#include "../Utils/Util.hpp"
#include "../Utils/Globals.hpp"
#include "../Enums/BodyType.hpp"
#include "../Metadata/BodyMetadata.hpp"

#include <raylib.h>
#include <box2d/box2d.h>

#include <cstdint>
#include <string>

namespace ooh {

PhysicsBody::PhysicsBody(BodyMetadata* bodyMD, const Vector2 pos, BodyType type, bool active)
{
  b2Vec2 meterPos = util::Vector2ToB2Vec2(pos);

  m_bodyDef.position.Set(meterPos.x, meterPos.y);
  m_bodyDef.type = util::BodyTypeToB2BodyType(type);
  m_bodyDef.userData.pointer = (uintptr_t)bodyMD; 

  m_body = global::world->CreateBody(&m_bodyDef);
  m_body->SetEnabled(active);
}

PhysicsBody::PhysicsBody()
{
  m_bodyDef.position.Set(1.0f, 1.0f);
  m_body = nullptr;
}

PhysicsBody::~PhysicsBody()
{}

void PhysicsBody::SetBodyPosition(const Vector2 pos)
{
  b2Vec2 meterPos = util::Vector2ToB2Vec2(pos);
  m_body->SetTransform(meterPos, m_body->GetAngle());
}

Vector2 PhysicsBody::GetBodyPosition()
{
  return util::B2Vec2ToVector2(m_body->GetPosition());
}
    
void PhysicsBody::SetBodyRotation(float rotation)
{
  m_body->SetTransform(m_body->GetPosition(), (rotation * DEG2RAD));
}
    
float PhysicsBody::GetBodyRotation()
{
  return m_body->GetAngle() * DEG2RAD;
}

void PhysicsBody::ApplyForce(Vector2 force)
{
  m_body->SetLinearVelocity(util::Vector2ToB2Vec2(force));
}
    
void PhysicsBody::SetBodyActive(bool active)
{
  m_body->SetEnabled(active);
}
    
void PhysicsBody::AttachCollider(const b2FixtureDef& collider)
{
  m_body->CreateFixture(&collider);
}

}
