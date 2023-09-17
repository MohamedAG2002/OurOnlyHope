#pragma once

#include "Scene.hpp"

#include <raylib.h>

namespace ooh {

class OverLoseScene : public Scene 
{
  public:
    OverLoseScene();
    ~OverLoseScene();

  public:
    void Update(float dt) override;
    void Render() override;
    void Reset() override;
};
  
}
