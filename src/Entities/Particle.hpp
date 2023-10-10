#pragma once

#include <raylib.h>

namespace ooh {

const float MAX_PARTICLE_LIFETIME = 0.4f;

class Particle
{
  public:
    Particle();
    ~Particle();

  public:
    bool isActive;
    float speed, lifeTime;
    Vector2 dir, position, size;
    Color color;
    Rectangle rec;

  public:
    void Update();
    void Render();
    void Reset();
};

}
