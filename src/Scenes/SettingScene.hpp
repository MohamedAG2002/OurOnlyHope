#pragma once

#include "Scene.hpp"
#include "../UI/Button.hpp"
#include "../UI/Text.hpp"
#include "../UI/Checkbox.hpp"

#include <raylib.h>

namespace ooh {

class SettingScene : public Scene 
{
  public:
    SettingScene();
    ~SettingScene();

  public:
    Text title, fullScreenText;
    Button menuButton;
    Checkbox fullScreenCheckBox;

  public:
    void Update(float dt) override;
    void Render() override;
    void Reset() override;
};
  
}
