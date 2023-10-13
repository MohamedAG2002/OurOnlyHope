#pragma once

#include "Scene.hpp"
#include "../UI/Button.hpp"
#include "../UI/Text.hpp"
#include "../UI/Checkbox.hpp"

#include <raylib.h>

#include <memory>
#include <array>

namespace ooh {

class SettingScene : public Scene 
{
  public:
    SettingScene();
    ~SettingScene();

  public:
    std::unique_ptr<Text> title, fullScreenText;
    std::unique_ptr<Button> menuButton;
    std::unique_ptr<Checkbox> fullScreenCheckBox;

  public:
    void Update(float dt) override;
    void Render() override;
    void Reset() override;
};
  
}
