#include "Particle.hpp"
#include "../Utils/Util.hpp"

#include <raylib.h>

namespace ooh {

Particle::Particle()
{
  isActive = false;
  speed = 400.0f;
  lifeTime = 0.0f;

  float randDirX = util::GetRandomFloat(-1.0f, 1.0f);
  float randDirY = util::GetRandomFloat(-1.0f, 1.0f);
  dir = Vector2{randDirX * speed, randDirY * speed};
  position = Vector2{-1000.0f, -1000.0f}; 
  size = {12.0f, 12.0f};

  color = RED;
  rec = Rectangle{position.x, position.y, size.x, size.y};
}

Particle::~Particle()
{}

void Particle::Update()
{
  // Deactivate the particle once its life time is 0
  if(lifeTime > MAX_PARTICLE_LIFETIME)
  {
    isActive = false;
    lifeTime = 0.0f;
    return;
  }

  // Increase the particle's life time
  lifeTime += GetFrameTime();

  // Accelerate the particle
  position.x += dir.x * GetFrameTime();
  position.y += dir.y * GetFrameTime();

  // Update its position
  rec.x = position.x;
  rec.y = position.y;
}

void Particle::Render()
{
  // Draw the particle
  DrawRectangleRec(rec,color);
}

void Particle::Reset()
{
  lifeTime = 0.0f;
  position = Vector2{0.0f, 0.0f};
  isActive = false;
}

}
