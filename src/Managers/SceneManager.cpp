#include "SceneManager.hpp"
#include "../Scenes/Scene.hpp"
#include "../Scenes/MenuScene.hpp"
#include "../Scenes/SettingScene.hpp"
#include "../Scenes/ShopScene.hpp"
#include "../Scenes/GameScene.hpp"
#include "../Scenes/OverLoseScene.hpp"
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
  m_scenes[SceneType::OVER_LOSE] = std::make_shared<OverLoseScene>();
  
  // Setting default values
  m_currentScene = m_scenes[SceneType::MENU];

  // Listen to scene change event
  EventManager::Get().ListenToEvent<OnSceneChange>([&](SceneType st){
    m_currentScene = m_scenes[st];
    m_scenes[st]->Reset();
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
