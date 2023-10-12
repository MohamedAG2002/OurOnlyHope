#pragma once

#include "Scene.hpp"
#include "../UI/Button.hpp"
#include "../UI/Text.hpp"
#include "../UI/Checkbox.hpp"
#include "../UI/Slider.hpp"

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
    std::array<std::unique_ptr<Slider>, 3> sliders;

  public:
    void Update(float dt) override;
    void Render() override;
    void Reset() override;
};
  
}
