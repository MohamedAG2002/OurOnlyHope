#pragma once

#include "Scene.hpp"
#include "../UI/Text.hpp"
#include "../UI/Button.hpp"

#include <raylib.h>

namespace ooh {

class OverLoseScene : public Scene 
{
  public:
    OverLoseScene();
    ~OverLoseScene();

  public:
    Text title, waveText;
    Button menuButton;
    int wave;

  public:
    void Update(float dt) override;
    void Render() override;
    void Reset() override;
};
  
}
