#include "PhysicsBody.hpp"
#include "../Utils/Vector2.hpp"
#include "../Utils/Utils.hpp"
#include "../Utils/Globals.hpp"
#include "../Enums/BodyType.hpp"

#include <box2d/box2d.h>

PhysicsBody::PhysicsBody(b2World* world, const Vector2 pos, BodyType type)
{
  m_bodyDef.type = BodyTypeToB2BodyType(type);
  m_bodyDef.position.Set(pos.x * global::METER_TO_PIXEL, pos.y * global::METER_TO_PIXEL);
  m_body = world->CreateBody(&m_bodyDef);
}

PhysicsBody::~PhysicsBody()
{}

Vector2 PhysicsBody::GetBodyPosition()
{
  return B2Vec2ToVector2(m_body->GetPosition());
}

void PhysicsBody::ApplyForce(Vector2 force)
{
  m_body->ApplyForceToCenter(Vector2ToB2Vec2(force), true);
}
