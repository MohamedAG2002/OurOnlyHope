#include "ContactListener.hpp"
#include "../Events/EventFuncs.hpp"
#include "../Managers/EventManager.hpp"
#include "../Utils/Globals.hpp"

#include <box2d/box2d.h>

#include <string>
#include <iostream>

namespace ooh {

ContactListener::ContactListener()
{
  m_currentContact = global::world->GetContactList(); // Get the head 
}

ContactListener::~ContactListener()
{
  // Does nothing for now...
}
    
void ContactListener::Update()
{
  // Will go as long as there is no more contacts to analize
  while(m_currentContact != nullptr)
  {
    // Checking the collisions between two bodies and passing it to the 
    // this function below which will have custom implementations for what 
    // to do when two bodies collide.
    BeginContact(m_currentContact);

    // Move on to the next node in the list
    m_currentContact = m_currentContact->GetNext();
  }
}

void ContactListener::PreSolve(b2Contact* contact, const b2Manifold* oldManifold)
{
  // Does nothing for now...
}

void ContactListener::PostSolve(b2Contact* contact, const b2ContactImpulse* impulse)
{
  // Does nothing for now...
}

void ContactListener::BeginContact(b2Contact* contact) 
{
  b2Body* bodyA = contact->GetFixtureA()->GetBody();
  b2Body* bodyB = contact->GetFixtureB()->GetBody();

  std::string id1 = (const char*)bodyA->GetUserData().pointer;
  std::string id2 = (const char*)bodyB->GetUserData().pointer;

  EventManager::Get().DispatchEvent<OnEntityCollision>(id1, id2);
}

void ContactListener::EndContact(b2Contact* contact) 
{
  // Does nothing for now...
}
  
}
