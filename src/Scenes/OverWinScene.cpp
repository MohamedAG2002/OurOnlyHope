#include "OverWinScene.hpp"
#include "../Events/EventFuncs.hpp"
#include "../Managers/EventManager.hpp"
#include "../Enums/SceneType.hpp"

#include <SDL2/SDL.h>

OverWinScene::OverWinScene()
{

}

OverWinScene::~OverWinScene()
{

}

void OverWinScene::ProcessEvents(SDL_Event event)
{
  switch(event.type)
  {
    case SDL_KEYDOWN:
      if(event.key.keysym.sym == SDLK_m)
        EventManager::Get().DispatchEvent<OnSceneChange>(SceneType::MENU);
      break;
  }
}

void OverWinScene::Update(float dt)
{

}

void OverWinScene::Render(SDL_Renderer* renderer)
{

}
void OverWinScene::Reset()
{

}
