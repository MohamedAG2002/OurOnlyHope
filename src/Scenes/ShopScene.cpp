#include "ShopScene.hpp"
#include "../Events/EventFuncs.hpp"
#include "../Managers/EventManager.hpp"
#include "../Enums/SceneType.hpp"
#include "../UI/Button.hpp"
#include "../UI/Text.hpp"
#include "../Enums/Anchor.hpp"
#include "../Enums/TextType.hpp"
#include "../Utils/Globals.hpp"

#include <SDL2/SDL.h>

#include <memory>

ShopScene::ShopScene()
{
  title = std::make_unique<Text>("Make Your Choice...", Anchor::TOP_CENTER, TextType::BIG, global::BLACK);
  startButton = std::make_unique<Button>("Start", Anchor::BOTTOM_RIGHT, TextType::MEDIUM, global::GREEN, global::BLACK);
}

ShopScene::~ShopScene()
{

}

void ShopScene::ProcessEvents(SDL_Event event)
{
  startButton->ProcessEvents(event);
}

void ShopScene::Update(float dt)
{
  if(startButton->hasClicked)
    EventManager::Get().DispatchEvent<OnSceneChange>(SceneType::GAME);
}

void ShopScene::Render(SDL_Renderer* renderer)
{
  startButton->Render(renderer);
  title->Render(renderer);
}

void ShopScene::Reset()
{
  startButton->Reset();
}
