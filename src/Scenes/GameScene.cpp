#include "GameScene.hpp"
#include "../Enums/SceneType.hpp"
#include "../Events/EventFuncs.hpp"
#include "../Managers/EventManager.hpp"
#include "../Managers/EntityManager.hpp"
#include "../Managers/TileManager.hpp"
#include "../UI/Button.hpp"
#include "../UI/Text.hpp"
#include "../Enums/Anchor.hpp"
#include "../Enums/TextType.hpp"
#include "../Utils/Globals.hpp"

#include <raylib.h>

#include <memory>

namespace ooh {

GameScene::GameScene()
{
  enttMgr = std::make_unique<EntityManager>();
  tileMgr = std::make_unique<TileManager>("Map");
  pausedText = std::make_unique<Text>("Paused", Anchor::CENTER, TextType::BIG, WHITE);
  menuButton = std::make_unique<Button>("Menu", Anchor::BOTTOM_LEFT, TextType::SMALL, GREEN, WHITE, Vector2{15.0f, 0.0f});
  cam = Camera2D{Vector2{GetScreenWidth() / 2.0f, GetScreenHeight() / 2.0f}, enttMgr->player->transform.position, 0.0f, 1.0f}; 

  m_isPaused = false;
}

GameScene::~GameScene()
{

}

void GameScene::Update(float dt)
{
  if(IsKeyPressed(KEY_P))
    m_isPaused = !m_isPaused;

  if(menuButton->OnPressed())
    EventManager::Get().DispatchEvent<OnSceneChange>(SceneType::MENU);
  
  if(m_isPaused)
    return;

  enttMgr->Update(dt);
  
  // Update the camera's position
  cam.target = enttMgr->player->transform.position;
}

void GameScene::Render()
{
  BeginMode2D(cam);
  
  tileMgr->Render();
  enttMgr->Render();

  EndMode2D();

  if(!m_isPaused)
    return;

  menuButton->Render(); 
  pausedText->Render();
}

void GameScene::Reset()
{
  enttMgr->Reset();
  menuButton->Reset();
  m_isPaused = false;
}
  
}
