#pragma once

#include "Scene.hpp"
#include "../UI/Button.hpp"
#include "../UI/Text.hpp"

#include <raylib.h>

namespace ooh {

class MenuScene : public Scene 
{
  public:
    MenuScene();
    ~MenuScene();

  public:
    Button playButton, settingsButton, quitButton;
    Text title, credits;

  public:
    void Update(float dt) override;
    void Render() override;
    void Reset() override;
};
  
}
