#include "GameScene.hpp"
#include "../Enums/SceneType.hpp"
#include "../Events/EventFuncs.hpp"
#include "../Managers/EventManager.hpp"
#include "../Managers/EntityManager.hpp"
#include "../UI/Button.hpp"
#include "../UI/Text.hpp"
#include "../Enums/Anchor.hpp"
#include "../Enums/TextType.hpp"
#include "../Utils/Globals.hpp"

#include <SDL2/SDL.h>

#include <memory>

GameScene::GameScene()
{
  enttMgr = std::make_unique<EntityManager>();
  pausedText = std::make_unique<Text>("Paused", Anchor::CENTER, TextType::BIG, global::BLACK);
  menuButton = std::make_unique<Button>("Menu", Anchor::BOTTOM_LEFT, TextType::SMALL, global::GREEN, global::BLACK);
  m_isPaused = false;
}

GameScene::~GameScene()
{

}

void GameScene::ProcessEvents(SDL_Event event)
{
  enttMgr->ProcessEvents(event);
  menuButton->ProcessEvents(event); 

  if(event.type != SDL_KEYDOWN)
    return;

  if(event.key.keysym.sym == SDLK_p)
    m_isPaused = !m_isPaused;
}

void GameScene::Update(float dt)
{
  if(menuButton->hasClicked)
    EventManager::Get().DispatchEvent<OnSceneChange>(SceneType::MENU);
  
  if(m_isPaused)
    return;

  enttMgr->Update(dt);
}

void GameScene::Render(SDL_Renderer* renderer)
{
  enttMgr->Render(renderer);

  if(!m_isPaused)
    return;

  menuButton->Render(renderer); 
  pausedText->Render(renderer);
}

void GameScene::Reset()
{
  enttMgr->Reset();
  menuButton->Reset();
  m_isPaused = false;
}
