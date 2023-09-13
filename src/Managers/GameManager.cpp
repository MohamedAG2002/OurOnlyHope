#include "GameManager.hpp"
#include "../Utils/Globals.hpp"
#include "../Utils/DebugDraw.hpp"
#include "AssetManager.hpp"
#include "../Events/EventFuncs.hpp"
#include "EventManager.hpp"
#include "SceneManager.hpp"
#include "../Listeners/AudioListener.hpp"

#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <box2d/box2d.h>

#include <iostream>
#include <string>
#include <memory>

// Extern variables init 
b2World* global::world = new b2World(b2Vec2(0.0f, 0.0f));

GameManager::GameManager()
{
  m_InitSDLSystems();
  m_InitWindow();
  m_InitRenderer();

  isRunning = true;
  lastFrame = 0.0f;
  deltaTime = 0.0f;

  // Box2D init
  global::world->SetContinuousPhysics(true);
  m_debugDraw = std::make_unique<DebugDraw>(renderer);
  global::world->SetDebugDraw(m_debugDraw.get());
  m_isDebugDraw = false;

  // Managers init
  AssetManager::Get().LoadAssets(renderer);
  m_scnMgr = std::make_unique<SceneManager>();
  
  // Listeners init 
  m_audioListen = std::make_unique<AudioListener>();

  // Listening to events 
  EventManager::Get().ListenToEvent<OnQuit>([&](){
    isRunning = false;
  });
 
  // Dispatching events
  EventManager::Get().DispatchEvent<OnMusicPlay>("Menu_Hymn");
}

GameManager::~GameManager()
{
  // Managers de-init 
  AssetManager::Get().UnloadAssets();
  EventManager::Get().UnloadEvents();

  // SDL de-init
  m_ShutdownSDLSystems();
}

void GameManager::ProcessEvents()
{
  if(!SDL_PollEvent(&event))
    return;

  m_scnMgr->ProcessEvents(event);

  switch (event.type) 
  {
    case SDL_QUIT:
      isRunning = false;
      break;
    case SDL_KEYDOWN:
      if(event.key.keysym.sym == SDLK_ESCAPE)
        isRunning = false;
      if(event.key.keysym.sym == SDLK_F2)
        m_isDebugDraw = !m_isDebugDraw;
      break;
  }
}

void GameManager::Update()
{
  // Getting the difference between the last frame and the time since
  // SDL's initialization and converting it to seconds(since the result
  // will be in milliseconds)
  deltaTime = (SDL_GetTicks() - lastFrame) / 1000.0;
  lastFrame = SDL_GetTicks();

  // Box2D update
  global::world->Step(deltaTime, global::VEL_ITER, global::POS_ITER);

  // Scenes update
  m_scnMgr->Update(deltaTime);
}

void GameManager::Render()
{
  SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
  SDL_RenderClear(renderer);

  if(m_isDebugDraw)
    global::world->DebugDraw();

  m_scnMgr->Render(renderer);

  SDL_RenderPresent(renderer);
}

void GameManager::Run()
{
  while(isRunning)
  {
    ProcessEvents();
    Update();
    Render();
  }
}
    
void GameManager::m_InitSDLSystems()
{
  if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS | SDL_INIT_AUDIO) != 0)
    m_ExitWithError(SDL_GetError());
 
  if(TTF_Init() != 0)
    m_ExitWithError(TTF_GetError());

  IMG_Init(IMG_INIT_PNG);
  Mix_Init(MIX_INIT_OGG);
  
  // Open the audio so that sounds comes out. It can err, so best check for errors
  if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 4096) != 0)
    m_ExitWithError(Mix_GetError());
}

void GameManager::m_ShutdownSDLSystems()
{
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  
  Mix_Quit();
  IMG_Quit();
  TTF_Quit();
  SDL_Quit();
}

void GameManager::m_InitWindow()
{
  window = SDL_CreateWindow("Our Only Hope", 
                            SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                            global::SCREEN_WIDTH, global::SCREEN_HEIGHT,
                            SDL_WINDOW_SHOWN);

  if(!window)
    m_ExitWithError(SDL_GetError());
}

void GameManager::m_InitRenderer()
{
  renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

  if(!renderer)
    m_ExitWithError(SDL_GetError());
}

void GameManager::m_ExitWithError(const std::string&& msg)
{
  isRunning = false;
  std::cerr << "ERROR: " << msg << '\n';
}
