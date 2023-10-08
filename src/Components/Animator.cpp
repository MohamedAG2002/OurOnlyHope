#include "Animator.hpp"
#include "Transform2D.hpp"
#include "../Managers/AssetManager.hpp"
#include "../Utils/Util.hpp"

#include <raylib.h>

namespace ooh {

Animator::Animator()
{
  animation = Texture2D{};
  frameSize = Vector2{0.0f, 0.0f};
  frameCount = 0;
  animationSpeed = 0.0f;
  isAnimating = false;
  currentFrame = 0;

  m_timer = 0.0f;
  m_animationDir = 0;
}

Animator::Animator(const std::string&& anim, Vector2 frameSize, int frames, float speed)
  :frameSize(frameSize), frameCount(frames), animationSpeed(speed)
{
  animation = AssetManager::Get().GetSprite(anim);
  isAnimating = true;
  currentFrame = 0;

  m_timer = 0.0f;
  m_animationDir = 1;
}

Animator::~Animator()
{}
    
void Animator::Render(Transform2D& transform)
{
  if(isAnimating)
  {
    // The timer ticks as long as the animator can animate
    m_timer += GetFrameTime();

    // Move the frame by one once the timer runs out
    if(m_timer > animationSpeed)
    {
      m_timer = 0.0f;
      currentFrame += m_animationDir;
    }

    // Switch directions of the animation once the last frame has been reached
    // or when the first animation was reached. Basically, ping pong back and forth
    if(currentFrame == (frameCount - 1))
      m_animationDir = -1;
    else if(currentFrame == 0)
      m_animationDir = 1;
  }

  // Make sure the frame counter doesn't exceed the max frames nor go below 0 
  currentFrame = util::ClampI(currentFrame, 0, frameCount - 1);

  // Set some variables for better visualization
  Rectangle srcRec = {frameSize.x * currentFrame, 0, frameSize.x, frameSize.y};
  Rectangle destRec = {transform.position.x, transform.position.y, 
                      frameSize.x * transform.scale.x, frameSize.y * transform.scale.y};
  Vector2 origin = {frameSize.x / 2.0f, frameSize.y / 2.0f};

  // Draw the animation
  DrawTexturePro(animation, srcRec, destRec, origin, transform.rotation, WHITE);
}

}
