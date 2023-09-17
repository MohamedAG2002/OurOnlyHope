#include "SettingScene.hpp"
#include "../Events/EventFuncs.hpp"
#include "../Managers/EventManager.hpp"
#include "../Enums/SceneType.hpp"
#include "../UI/Button.hpp"
#include "../UI/Text.hpp"
#include "../Enums/Anchor.hpp"
#include "../Enums/TextType.hpp"
#include "../Utils/Globals.hpp"

#include <raylib.h>

#include <memory>

namespace ooh {

SettingScene::SettingScene()
{
  title = std::make_unique<Text>("SETTINGS", Anchor::TOP_CENTER, TextType::BIG, WHITE);
  menuButton = std::make_unique<Button>("MENU", Anchor::BOTTOM_LEFT, TextType::SMALL, GREEN, WHITE, Vector2{15.0f, 0.0f});
}

SettingScene::~SettingScene()
{

}

void SettingScene::Update(float dt)
{
  if(menuButton->OnPressed())
    EventManager::Get().DispatchEvent<OnSceneChange>(SceneType::MENU);
}

void SettingScene::Render()
{
  menuButton->Render();
  title->Render();  
}

void SettingScene::Reset()
{
  menuButton->Reset();
}
  
}
