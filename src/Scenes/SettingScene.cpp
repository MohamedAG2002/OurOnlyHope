#include "SettingScene.hpp"
#include "../Events/EventFuncs.hpp"
#include "../Managers/EventManager.hpp"
#include "../Enums/SceneType.hpp"
#include "../UI/Button.hpp"
#include "../UI/Text.hpp"
#include "../Enums/Anchor.hpp"
#include "../Enums/TextType.hpp"
#include "../Utils/Globals.hpp"

#include <SDL2/SDL.h>

#include <memory>

SettingScene::SettingScene()
{
  title = std::make_unique<Text>("SETTINGS", Anchor::TOP_CENTER, TextType::BIG, global::BLACK);
  menuButton = std::make_unique<Button>("MENU", Anchor::BOTTOM_LEFT, TextType::SMALL, global::GREEN, global::BLACK);
}

SettingScene::~SettingScene()
{

}

void SettingScene::ProcessEvents(SDL_Event event)
{
  menuButton->ProcessEvents(event);
}

void SettingScene::Update(float dt)
{
  if(menuButton->hasClicked)
    EventManager::Get().DispatchEvent<OnSceneChange>(SceneType::MENU);
}

void SettingScene::Render(SDL_Renderer* renderer)
{
  menuButton->Render(renderer);
  title->Render(renderer);  
}

void SettingScene::Reset()
{
  menuButton->Reset();
}
