#include "ParticleManager.hpp"
#include "../Entities/Particle.hpp"
#include "../Events/EventFuncs.hpp"
#include "../Managers/EventManager.hpp"

#include <raylib.h>

#include <memory>
#include <array>

namespace ooh {
 
ParticleManager::ParticleManager()
{
  // Default init for all of the particles 
  for(int i = 0; i < MAX_PARTICLES; i++)
    particles[i] = std::make_shared<Particle>();

  // Listen to events 
  EventManager::Get().ListenToEvent<OnParticleSpawn>([&](const Vector2 pos){
    m_SpawnParticle(pos);
  });
}

ParticleManager::~ParticleManager()
{}

void ParticleManager::Update()
{
  for(auto& particle : particles)
  {
    if(particle->isActive)
      particle->Update();
  }
}

void ParticleManager::Render()
{
  for(auto& particle : particles)
  {
    if(particle->isActive)
      particle->Render();
  }
}

void ParticleManager::Reset()
{
  for(auto& particle : particles)
    particle->Reset();
}

void ParticleManager::m_SpawnParticle(const Vector2 pos)
{
  for(auto& par : particles)
  {
    // Skip the active particles
    if(par->isActive)
      continue;
 
    par->position = pos;
    par->isActive = true;
  }
}

}
