#include "SettingScene.hpp"
#include "../Events/EventFuncs.hpp"
#include "../Managers/EventManager.hpp"
#include "../Enums/SceneType.hpp"
#include "../UI/Button.hpp"
#include "../UI/Text.hpp"
#include "../UI/Checkbox.hpp"
#include "../UI/Slider.hpp"
#include "../Enums/Anchor.hpp"
#include "../Enums/TextType.hpp"
#include "../Utils/Globals.hpp"

#include <raylib.h>

#include <iostream>
#include <memory>

namespace ooh {

SettingScene::SettingScene()
{
  title = std::make_unique<Text>("SETTINGS", Anchor::TOP_CENTER, TextType::BIG);
  fullScreenText = std::make_unique<Text>("FULLSCREEN:", Anchor::CENTER_LEFT, TextType::MEDIUM, global::UI_TEXT_COLOR, Vector2{30.0f, 0.0f});
  
  menuButton = std::make_unique<Button>("MENU", Anchor::BOTTOM_LEFT, TextType::SMALL, Vector2{15.0f, 0.0f});
  
  fullScreenCheckBox = std::make_unique<Checkbox>(Anchor::CENTER_LEFT, global::UI_BOX_COLOR, Vector2{fullScreenText->size.x + 70.0f, 0.0f});

  sliders[0] = std::make_unique<Slider>("Master Volume", &global::masterVolume, Anchor::CENTER_LEFT, Vector2{100.0f, 50.0f});
  sliders[1] = std::make_unique<Slider>("Music Volume", &global::musicVolume, Anchor::CENTER_LEFT, Vector2{100.0f, 100.0f});
  sliders[2] = std::make_unique<Slider>("Sound Volume", &global::soundVolume, Anchor::CENTER_LEFT, Vector2{100.0f, 150.0f});
}

SettingScene::~SettingScene()
{}

void SettingScene::Update(float dt)
{
  if(menuButton->OnPressed())
    EventManager::Get().DispatchEvent<OnSceneChange>(SceneType::MENU);

  if(fullScreenCheckBox->isChecked && !IsWindowFullscreen())
    ToggleFullscreen();
  else if(!fullScreenCheckBox->isChecked && IsWindowFullscreen())
    ToggleFullscreen();
}

void SettingScene::Render()
{
  menuButton->Render();
  fullScreenCheckBox->Render();

  title->Render();  
  fullScreenText->Render();  

  for(auto& slider : sliders)
    slider->Render();
}

void SettingScene::Reset()
{
  menuButton->Reset();
}
  
}
