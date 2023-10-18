#include "MenuScene.hpp"
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

MenuScene::MenuScene()
{
  // Texts init
  title = std::make_unique<Text>("Our Only Hope", Anchor::TOP_CENTER, TextType::BIG);
  credits = std::make_unique<Text>("Made By One Guy And A Bunch Of Free Assets", Anchor::BOTTOM_LEFT, TextType::LETTER);
  
  // Buttons init
  playButton = std::make_unique<Button>("Play", Anchor::CENTER, TextType::MEDIUM, Vector2{0, -50.0f});
  settingsButton = std::make_unique<Button>("Settings", Anchor::CENTER, TextType::MEDIUM);
  quitButton = std::make_unique<Button>("Quit", Anchor::CENTER, TextType::MEDIUM, Vector2{0.0f, 50.0f});

  EventManager::Get().DispatchEvent<OnMusicPlay>("Menu_Hymn");
}

MenuScene::~MenuScene()
{

}

void MenuScene::Update(float dt)
{
  if(playButton->OnPressed())
    EventManager::Get().DispatchEvent<OnSceneChange>(SceneType::SHOP);
  if(settingsButton->OnPressed())
    EventManager::Get().DispatchEvent<OnSceneChange>(SceneType::SETTINGS);
  if(quitButton->OnPressed())
    EventManager::Get().DispatchEvent<OnQuit>(false);
}

void MenuScene::Render()
{
  // Buttons render
  playButton->Render();
  settingsButton->Render();
  quitButton->Render();
  
  // Texts render
  title->Render();
  credits->Render();
}

void MenuScene::Reset()
{
  EventManager::Get().DispatchEvent<OnMusicStop>("Combat_Hymn");
  EventManager::Get().DispatchEvent<OnMusicStop>("Over_Hymn");
  EventManager::Get().DispatchEvent<OnMusicPlay>("Menu_Hymn");
}

}
