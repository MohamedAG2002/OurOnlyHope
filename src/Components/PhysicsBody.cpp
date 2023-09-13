#include "PhysicsBody.hpp"
#include "../Utils/Vector2.hpp"
#include "../Utils/Utils.hpp"
#include "../Utils/Globals.hpp"
#include "../Enums/BodyType.hpp"

#include <box2d/box2d.h>

#include <cstdint>
#include <string>

PhysicsBody::PhysicsBody(std::string& id, const Vector2 pos, BodyType type)
{
  b2Vec2 meterPos = Vector2ToB2Vec2(pos);

  m_bodyDef.position.Set(meterPos.x, meterPos.y);
  m_bodyDef.type = BodyTypeToB2BodyType(type);
  m_bodyDef.userData.pointer = (uintptr_t)id.c_str(); 

  m_body = global::world->CreateBody(&m_bodyDef);
}

PhysicsBody::PhysicsBody()
{
  m_bodyDef.position.Set(1.0f, 1.0f);
  m_body = nullptr;
}

PhysicsBody::~PhysicsBody()
{}

Vector2 PhysicsBody::GetBodyPosition()
{
  return B2Vec2ToVector2(m_body->GetPosition());
}

void PhysicsBody::ApplyForce(Vector2 force)
{
  m_body->SetLinearVelocity(Vector2ToB2Vec2(force));
  //m_body->ApplyForceToCenter(Vector2ToB2Vec2(force), true);
}
    
void PhysicsBody::AttachCollider(const b2FixtureDef& collider)
{
  m_body->CreateFixture(&collider);
}
