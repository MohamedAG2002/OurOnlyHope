#pragma once

#include "Transform2D.hpp"

#include <raylib.h>

#include <string>

namespace ooh {
 
class Animator 
{
  public:
    Animator();
    Animator(const std::string&& anim, Vector2 frameSize, int frames, float speed);
    ~Animator();

  public:
    bool isAnimating;
    Texture2D animation;
    int frameCount, currentFrame;
    float animationSpeed;
    Vector2 frameSize;

  public:
    void Render(Transform2D& transform);

  private:
    int m_animationDir;
    float m_timer;
};

}
