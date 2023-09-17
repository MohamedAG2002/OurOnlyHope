#include "GameManager.hpp"
#include "AssetManager.hpp"
#include "EventManager.hpp"
#include "SceneManager.hpp"
#include "../Events/EventFuncs.hpp"
#include "../Listeners/AudioListener.hpp"
#include "../Utils/Globals.hpp"

#include <raylib.h>
#include <box2d/box2d.h>

#include <memory>

namespace ooh {

b2World* global::world;

GameManager::GameManager()
  :m_isRunning(true)
{
  // Raylib init
  InitWindow(640, 480, "Our Only Hope");
  SetTargetFPS(60);
  InitAudioDevice();
  
  // Box2D init
  global::world = new b2World(b2Vec2(0.0f, 0.0f));

  // Singletons init 
  AssetManager::Get().LoadAssets();

  // Managers/Listeners init 
  m_audioListen = std::make_unique<AudioListener>();
  m_scnMgr = std::make_unique<SceneManager>(); 

  // Listen to events 
  EventManager::Get().ListenToEvent<OnQuit>([&](){
    m_isRunning = false;
  });
}

GameManager::~GameManager()
{
  // Singletons de-init 
  AssetManager::Get().UnloadAssets();
  EventManager::Get().UnloadEvents();

  // Raylib de-init
  CloseAudioDevice();
  CloseWindow();
}

void GameManager::Update()
{
  // Box2D update 
  global::world->Step(GetFrameTime(), global::VEL_ITER, global::POS_ITER);

  m_scnMgr->Update(GetFrameTime());
}

void GameManager::Render()
{
  BeginDrawing();
  ClearBackground(BLACK);

  m_scnMgr->Render();

  DrawFPS(10, 10);
  EndDrawing();
}

void GameManager::Run()
{
  while(!WindowShouldClose() && m_isRunning)
  {
    Update();
    Render();
  }
}

}
