#include "GameScene.hpp"
#include "../Enums/SceneType.hpp"
#include "../Events/EventFuncs.hpp"
#include "../Managers/EventManager.hpp"
#include "../Managers/EntityManager.hpp"
#include "../Managers/TileManager.hpp"
#include "../Managers/WaveManager.hpp"
#include "../Managers/ParticleManager.hpp"
#include "../UI/Button.hpp"
#include "../UI/Text.hpp"
#include "../Enums/Anchor.hpp"
#include "../Enums/TextType.hpp"
#include "../Utils/Globals.hpp"

#include <raylib.h>

#include <string>

namespace ooh {

GameScene::GameScene()
{
  enttMgr = std::make_unique<EntityManager>();
  tileMgr = std::make_unique<TileManager>();
  prtclMgr = std::make_unique<ParticleManager>();  

  pausedText = Text("Paused", Anchor::CENTER, TextType::BIG, WHITE);
  healthText = Text("HP: ", Anchor::TOP_LEFT, TextType::LETTER, GREEN);
  waveText = Text(std::to_string(wvMgr.waveCounter), Anchor::TOP_CENTER, TextType::MEDIUM, BLACK);
  
  menuButton = Button("Menu", Anchor::BOTTOM_LEFT, TextType::SMALL, Vector2{15.0f, 0.0f});

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
  if(IsKeyPressed(KEY_P))
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
  if(menuButton.OnPressed() && m_isPaused)
    EventManager::Get().DispatchEvent<OnSceneChange>(SceneType::MENU);
 
  // Don't update if the game is paused
  if(m_isPaused)
    return;

  // Updating the health text, blood text, and wave text 
  healthText.ChangeText("HP: " + std::to_string(enttMgr->player->health));
  waveText.ChangeText(std::to_string(wvMgr.waveCounter));

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
  
  healthText.Render();
  waveText.Render();

  if(!m_isPaused)
    return;

  menuButton.Render(); 
  pausedText.Render();
}

void GameScene::Reset()
{
  EventManager::Get().DispatchEvent<OnMusicStop>("Menu_Hymn");
  EventManager::Get().DispatchEvent<OnMusicPlay>("Combat_Hymn");

  enttMgr->Reset();
  prtclMgr->Reset();

  m_isPaused = false;
}
  
}
