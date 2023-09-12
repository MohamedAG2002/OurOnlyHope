#include "Collider.hpp"
#include "PhysicsBody.hpp"
#include "../Utils/Vector2.hpp"
#include "../Utils/Utils.hpp"

#include <box2d/box2d.h>

Collider::Collider(PhysicsBody& body, Vector2 size, float density)
{
  b2Vec2 halfSize = Vector2ToB2Vec2(Vector2(size.x / 2.0f, size.y / 2.0f));

  m_shape.SetAsBox(halfSize.x, halfSize.y);
  m_fixtureDef.shape = &m_shape;
  m_fixtureDef.density = density;
  m_fixtureDef.friction = 0.0f;
  m_fixtureDef.restitution = 0.0f;

  body.AttachCollider(m_fixtureDef);
}

Collider::Collider()
{
  m_shape.SetAsBox(1.0f, 1.0f);
  m_fixtureDef.shape = &m_shape;
  m_fixtureDef.density = 0.0f;
  m_fixtureDef.friction = 0.0f;
  m_fixtureDef.restitution = 0.0f;
}
    
Collider::~Collider()
{

}
