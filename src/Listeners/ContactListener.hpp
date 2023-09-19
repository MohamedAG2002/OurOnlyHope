#pragma once

#include <box2d/box2d.h>

namespace ooh {

class ContactListener : public b2ContactListener 
{
  public:
    ContactListener();
    ~ContactListener();

  public:
    // Custom functions 
    void Update();

    // Inherited functions
	  void PreSolve(b2Contact* contact, const b2Manifold* oldManifold) override;
	  void PostSolve(b2Contact* contact, const b2ContactImpulse* impulse) override;
    void BeginContact(b2Contact* contact) override;
    void EndContact(b2Contact* contact) override;

  private:
    b2Contact* m_currentContact = nullptr;
};
  
}
