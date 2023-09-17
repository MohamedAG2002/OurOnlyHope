#include "ShopScene.hpp"
#include "../Events/EventFuncs.hpp"
#include "../Managers/EventManager.hpp"
#include "../Enums/SceneType.hpp"
#include "../UI/Button.hpp"
#include "../UI/Text.hpp"
#include "../Enums/Anchor.hpp"
#include "../Enums/TextType.hpp"
#include "../Utils/Globals.hpp"

#include <raylib.h>

#include <memory>

namespace ooh {

ShopScene::ShopScene()
{
  title = std::make_unique<Text>("Make Your Choice...", Anchor::TOP_CENTER, TextType::BIG, WHITE);
  startButton = std::make_unique<Button>("Start", Anchor::BOTTOM_RIGHT, TextType::SMALL, GREEN, WHITE, Vector2{-15.0f, 0.0f});
}

ShopScene::~ShopScene()
{

}

void ShopScene::Update(float dt)
{
  if(startButton->OnPressed())
    EventManager::Get().DispatchEvent<OnSceneChange>(SceneType::GAME);
}

void ShopScene::Render()
{
  startButton->Render();
  title->Render();
}

void ShopScene::Reset()
{
  startButton->Reset();
}

}
