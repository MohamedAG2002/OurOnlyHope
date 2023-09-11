#include "OverLoseScene.hpp"
#include "../Enums/SceneType.hpp"
#include "../Events/EventFuncs.hpp"
#include "../Managers/EventManager.hpp"

#include <SDL2/SDL.h>

OverLoseScene::OverLoseScene()
{

}

OverLoseScene::~OverLoseScene()
{

}

void OverLoseScene::ProcessEvents(SDL_Event event)
{
  switch(event.type)
  {
    case SDL_KEYDOWN:
      if(event.key.keysym.sym == SDLK_m)
        EventManager::Get().DispatchEvent<OnSceneChange>(SceneType::MENU);
      break;
  }
}

void OverLoseScene::Update(float dt)
{

}

void OverLoseScene::Render(SDL_Renderer* renderer)
{

}
void OverLoseScene::Reset()
{

}
