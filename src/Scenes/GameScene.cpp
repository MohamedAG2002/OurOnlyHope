#include "GameScene.hpp"
#include "../Enums/SceneType.hpp"
#include "../Events/EventFuncs.hpp"
#include "../Managers/EventManager.hpp"
#include "../Managers/EntityManager.hpp"
#include "../Managers/TileManager.hpp"
#include "../Managers/BloodManager.hpp"
#include "../Managers/WaveManager.hpp"
#include "../UI/Button.hpp"
#include "../UI/Text.hpp"
#include "../Enums/Anchor.hpp"
#include "../Enums/TextType.hpp"
#include "../Utils/Globals.hpp"

#include <raylib.h>

#include <memory>
#include <string>

namespace ooh {

GameScene::GameScene()
{
  enttMgr = std::make_unique<EntityManager>();
  tileMgr = std::make_unique<TileManager>("Map");
  
  pausedText = std::make_unique<Text>("Paused", Anchor::CENTER, TextType::BIG, WHITE);
  healthText = std::make_unique<Text>("HP: ", Anchor::TOP_CENTER, TextType::LETTER, WHITE);
  bloodText = std::make_unique<Text>("BLOOD: ", Anchor::TOP_LEFT, TextType::LETTER, WHITE);
  waveText = std::make_unique<Text>("WAVE: ", Anchor::TOP_RIGHT, TextType::LETTER, WHITE);
  menuButton = std::make_unique<Button>("Menu", Anchor::BOTTOM_LEFT, TextType::SMALL, GREEN, WHITE, Vector2{15.0f, 0.0f});

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

  // Updating the health text, blood text, and wave text 
  healthText->ChangeText("HP: " + std::to_string(enttMgr->player->health));
  bloodText->ChangeText("BLOOD: " + std::to_string(bldMgr.blood));
  waveText->ChangeText("WAVE: " + std::to_string(wvMgr.waveCounter));
  

  enttMgr->Update(dt);
  wvMgr.Update();

  // Make sure to switch the scenes when the player dies 
  if(!enttMgr->player->isActive)
    EventManager::Get().DispatchEvent<OnSceneChange>(SceneType::OVER_LOSE);
}

void GameScene::Render()
{
  //tileMgr->Render();
  enttMgr->Render();
  healthText->Render();
  bloodText->Render();
  waveText->Render();

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
