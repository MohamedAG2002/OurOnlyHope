#pragma once

#include "Scene.hpp"
#include "../UI/Text.hpp"
#include "../UI/Button.hpp"

#include <raylib.h>

#include <memory>

namespace ooh {

class OverLoseScene : public Scene 
{
  public:
    OverLoseScene();
    ~OverLoseScene();

  public:
    std::unique_ptr<Text> title, waveText;
    std::unique_ptr<Button> menuButton;
    int wave;

  public:
    void Update(float dt) override;
    void Render() override;
    void Reset() override;
};
  
}
