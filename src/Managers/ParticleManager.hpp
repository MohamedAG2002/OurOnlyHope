#pragma once

#include "../Entities/Particle.hpp"

#include <raylib.h>

#include <memory>
#include <array>

namespace ooh {

const int MAX_PARTICLES = 10;

class ParticleManager 
{
  public:
    ParticleManager();
    ~ParticleManager();

  public:
    std::array<std::shared_ptr<Particle>, MAX_PARTICLES> particles;

  public:
    void Update();
    void Render();
    void Reset();

  private:
    void m_SpawnParticle(const Vector2 pos);
};

}
