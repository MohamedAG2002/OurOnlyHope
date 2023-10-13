#include "GameScene.hpp"
#include "../Enums/SceneType.hpp"
#include "../Events/EventFuncs.hpp"
#include "../Managers/EventManager.hpp"
#include "../Managers/EntityManager.hpp"
#include "../Managers/TileManager.hpp"
#include "../Managers/BloodManager.hpp"
#include "../Managers/WaveManager.hpp"
#include "../Managers/ParticleManager.hpp"
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
  tileMgr = std::make_unique<TileManager>();
  prtclMgr = std::make_unique<ParticleManager>();  

  pausedText = std::make_unique<Text>("Paused", Anchor::CENTER, TextType::BIG, WHITE);
  healthText = std::make_unique<Text>("HP: ", Anchor::TOP_LEFT, TextType::LETTER, GREEN);
  bloodText = std::make_unique<Text>("BLOOD: ", Anchor::TOP_LEFT, TextType::LETTER, RED, Vector2{0.0f, 20.0f});
  waveText = std::make_unique<Text>(std::to_string(wvMgr.waveCounter), Anchor::TOP_CENTER, TextType::SMALL, BLACK);
  
  menuButton = std::make_unique<Button>("Menu", Anchor::BOTTOM_LEFT, TextType::SMALL, Vector2{15.0f, 0.0f});

  m_isPaused = false;

  // Listen to events 
  EventManager::Get().ListenToEvent<OnWaveEnd>([&](){
    EventManager::Get().DispatchEvent<OnSceneChange>(SceneType::SHOP); 
  });
}

GameScene::~GameScene()
{}

void GameScene::Update(float dt)
{
  // Pause/unpause game
  if(IsKeyPressed(KEY_ESCAPE))
  {
    m_isPaused = !m_isPaused;

    // Have to pause the zombies and the player otherwise 
    // they will move despite the game being paused. Box2D, man.
    enttMgr->PauseEntities(m_isPaused);
  }

  // Turn on/off debug draw 
  if(IsKeyPressed(KEY_F2))
    global::isDebugDraw = !global::isDebugDraw;

  // Go to the menu (only possible if paused).
  if(menuButton->OnPressed() && m_isPaused)
    EventManager::Get().DispatchEvent<OnSceneChange>(SceneType::MENU);
 
  // Don't update if the game is paused
  if(m_isPaused)
    return;

  // Updating the health text, blood text, and wave text 
  healthText->ChangeText("HP: " + std::to_string(enttMgr->player->health));
  bloodText->ChangeText("BLOOD: " + std::to_string(bldMgr.blood));
  waveText->ChangeText(std::to_string(wvMgr.waveCounter));

  enttMgr->Update(dt);
  prtclMgr->Update();
  wvMgr.Update();

  // Make sure to switch the scenes when the player dies 
  if(!enttMgr->player->isActive)
  {
    Reset();
    EventManager::Get().DispatchEvent<OnSceneChange>(SceneType::OVER_LOSE);
  }
}

void GameScene::Render()
{
  tileMgr->Render();
  enttMgr->Render();
  prtclMgr->Render();
  
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
  EventManager::Get().DispatchEvent<OnMusicStop>("Menu_Hymn");
  // @TODO: Play cool combat music

  enttMgr->Reset();
  prtclMgr->Reset();
  bldMgr.Reset();

  m_isPaused = false;
}
  
}
