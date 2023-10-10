#include "GameManager.hpp"
#include "AssetManager.hpp"
#include "EventManager.hpp"
#include "SceneManager.hpp"
#include "../Events/EventFuncs.hpp"
#include "../Listeners/AudioListener.hpp"
#include "../Listeners/ContactListener.hpp"
#include "../Utils/Globals.hpp"

#include <raylib.h>
#include <box2d/box2d.h>

#include <memory>

namespace ooh {

b2World* global::world;
bool global::isDebugDraw;

GameManager::GameManager()
  :m_isRunning(true)
{
  // Raylib init
  InitWindow(1270, 720, "Our Only Hope");
  SetTargetFPS(60);
  SetExitKey(KEY_F1);
  ToggleFullscreen(); 
  InitAudioDevice();
  
  // Box2D init
  global::world = new b2World(b2Vec2(0.0f, 0.0f));
  
  m_debugDraw = std::make_unique<DebugDraw>();
  global::world->SetDebugDraw(m_debugDraw.get());
  
  m_contactListen = std::make_unique<ContactListener>();
  global::world->SetContactListener(m_contactListen.get());

  // Singletons init 
  AssetManager::Get().LoadAssets();

  // Managers/Listeners init 
  m_audioListen = std::make_unique<AudioListener>();
  m_scnMgr = std::make_unique<SceneManager>(); 

  // Other globals init 
  global::isDebugDraw = false;

  // Private variables init 
  m_isRunning = true;

  // Listen to events 
  EventManager::Get().ListenToEvent<OnQuit>([&](bool running){
    m_isRunning = running;
  });
}

GameManager::~GameManager()
{
  // Singletons de-init 
  AssetManager::Get().UnloadAssets();
  EventManager::Get().UnloadEvents();

  // Box2D de-init 
  delete global::world;

  // Raylib de-init
  CloseAudioDevice();
  CloseWindow();
}

void GameManager::Update()
{
  // Box2D update
  global::world->Step(GetFrameTime(), global::VEL_ITER, global::POS_ITER);
  m_contactListen->Update();

  // Scenes update
  m_scnMgr->Update(GetFrameTime());
}

void GameManager::Render()
{
  BeginDrawing();
  ClearBackground(SKYBLUE);

  m_scnMgr->Render();
  
  if(global::isDebugDraw)
    global::world->DebugDraw();

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
