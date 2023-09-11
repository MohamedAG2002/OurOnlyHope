#include "MenuScene.hpp"
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

MenuScene::MenuScene()
{
  // Titles init
  title = std::make_unique<Text>("Our Only Hope", Anchor::TOP_CENTER, TextType::BIG, global::BLACK);
  credits = std::make_unique<Text>("Made By One Guy", Anchor::BOTTOM_LEFT, TextType::LETTER, global::BLACK);
  
  // Buttons init
  playButton = std::make_unique<Button>("Play", Anchor::CENTER, TextType::MEDIUM, global::GREEN, global::BLACK, Vector2(0, -30.0f));
  settingsButton = std::make_unique<Button>("Settings", Anchor::CENTER, TextType::MEDIUM, global::GREEN, global::BLACK);
  quitButton = std::make_unique<Button>("Quit", Anchor::CENTER, TextType::MEDIUM, global::GREEN, global::BLACK, Vector2(0.0f, 30.0f));
}

MenuScene::~MenuScene()
{

}

void MenuScene::ProcessEvents(SDL_Event event)
{
  playButton->ProcessEvents(event);
  settingsButton->ProcessEvents(event);
  quitButton->ProcessEvents(event);
  
  if(playButton->hasClicked)
    EventManager::Get().DispatchEvent<OnSceneChange>(SceneType::SHOP);
  if(settingsButton->hasClicked)
    EventManager::Get().DispatchEvent<OnSceneChange>(SceneType::SETTINGS);
  if(quitButton->hasClicked)
    EventManager::Get().DispatchEvent<OnQuit>();
}

void MenuScene::Update(float dt)
{
}

void MenuScene::Render(SDL_Renderer* renderer)
{
  // Buttons render
  playButton->Render(renderer);
  settingsButton->Render(renderer);
  quitButton->Render(renderer);
  
  // Texts render
  title->Render(renderer);
  credits->Render(renderer);
}

void MenuScene::Reset()
{
  playButton->Reset();
  settingsButton->Reset();
  quitButton->Reset();
}
