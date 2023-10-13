#include "SettingScene.hpp"
#include "../Events/EventFuncs.hpp"
#include "../Managers/EventManager.hpp"
#include "../Enums/SceneType.hpp"
#include "../UI/Button.hpp"
#include "../UI/Text.hpp"
#include "../UI/Checkbox.hpp"
#include "../Enums/Anchor.hpp"
#include "../Enums/TextType.hpp"
#include "../Utils/Globals.hpp"

#include <raylib.h>

#include <iostream>
#include <memory>
#include <string>

namespace ooh {

SettingScene::SettingScene()
{
  title = std::make_unique<Text>("SETTINGS", Anchor::TOP_CENTER, TextType::BIG);
  fullScreenText = std::make_unique<Text>("FULLSCREEN:", Anchor::CENTER_LEFT, TextType::MEDIUM, global::UI_TEXT_COLOR, Vector2{30.0f, 0.0f});
  
  menuButton = std::make_unique<Button>("MENU", Anchor::BOTTOM_LEFT, TextType::SMALL, Vector2{15.0f, 0.0f});
  
  fullScreenCheckBox = std::make_unique<Checkbox>(Anchor::CENTER_LEFT, global::UI_BOX_COLOR, Vector2{fullScreenText->size.x + 70.0f, 0.0f});
}

SettingScene::~SettingScene()
{}

void SettingScene::Update(float dt)
{
  // Go back to the menu
  if(menuButton->OnPressed())
    EventManager::Get().DispatchEvent<OnSceneChange>(SceneType::MENU);

  // Enable/disable fullscreen mode
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
}

void SettingScene::Reset()
{
  menuButton->Reset();
}
  
}
