#pragma once

#include "Scene.hpp"
#include "../UI/Button.hpp"
#include "../UI/Text.hpp"

#include <raylib.h>

#include <memory>

namespace ooh {

class MenuScene : public Scene 
{
  public:
    MenuScene();
    ~MenuScene();

  public:
    std::unique_ptr<Button> playButton, settingsButton, quitButton;
    std::unique_ptr<Text> title, credits;

  public:
    void Update(float dt) override;
    void Render() override;
    void Reset() override;
};
  
}
