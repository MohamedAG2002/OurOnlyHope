#include "SceneManager.hpp"
#include "../Scenes/Scene.hpp"
#include "../Scenes/MenuScene.hpp"
#include "../Scenes/SettingScene.hpp"
#include "../Scenes/ShopScene.hpp"
#include "../Scenes/GameScene.hpp"
#include "../Scenes/OverWinScene.hpp"
#include "../Scenes/OverLoseScene.hpp"
#include "../Scenes/SecretScene.hpp"
#include "../Enums/SceneType.hpp"
#include "../Events/EventFuncs.hpp"
#include "EventManager.hpp"

#include <raylib.h>

#include <iostream>
#include <unordered_map>
#include <memory>

namespace ooh {

SceneManager::SceneManager()
{
  // Scenes init  
  m_scenes[SceneType::MENU] = std::make_shared<MenuScene>();
  m_scenes[SceneType::SETTINGS] = std::make_shared<SettingScene>();
  m_scenes[SceneType::SHOP] = std::make_shared<ShopScene>();
  m_scenes[SceneType::GAME] = std::make_shared<GameScene>();
  m_scenes[SceneType::OVER_WIN] = std::make_shared<OverWinScene>();
  m_scenes[SceneType::OVER_LOSE] = std::make_shared<OverLoseScene>();
  m_scenes[SceneType::SECRET_ENDING] = std::make_shared<SecretScene>();
  
  // Setting default values
  m_currentScene = m_scenes[SceneType::GAME];

  // Listen to scene change event
  EventManager::Get().ListenToEvent<OnSceneChange>([&](SceneType st){
    m_scenes[st]->Reset();
    m_currentScene = m_scenes[st];
  });
}

SceneManager::~SceneManager()
{
  m_scenes.clear();
}

void SceneManager::Update(float dt)
{
  m_currentScene->Update(dt);
}

void SceneManager::Render()
{
  m_currentScene->Render();
}
  
}
