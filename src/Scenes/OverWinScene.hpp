#pragma once

#include "Scene.hpp"

#include <raylib.h>

namespace ooh {

class OverWinScene : public Scene 
{
  public:
    OverWinScene();
    ~OverWinScene();

  public:
    void Update(float dt) override;
    void Render() override;
    void Reset() override;
};
  
}
