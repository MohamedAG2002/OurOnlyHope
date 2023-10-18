#include "Collider.hpp"
#include "PhysicsBody.hpp"
#include "../Utils/Util.hpp"

#include <raylib.h>
#include <box2d/box2d.h>

namespace ooh {

Collider::Collider(PhysicsBody& body, Vector2 size, float density, bool sensor)
{
  // @NOTE: Deviding the size by 4 works better than deviding it by 2 for some reason
  b2Vec2 halfSize = util::Vector2ToB2Vec2(Vector2{size.x / 4.0f, size.y / 4.0f});

  m_shape.SetAsBox(halfSize.x, halfSize.y);
  m_fixtureDef.shape = &m_shape;
  m_fixtureDef.isSensor = sensor;
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
    
void Collider::SetSize(Vector2 size)
{
  b2Vec2 halfSize = util::Vector2ToB2Vec2(Vector2{size.x / 4.0f, size.y / 4.0f});

  m_shape.SetAsBox(halfSize.x, halfSize.y);
  m_fixtureDef.shape = &m_shape;
}
  
}
