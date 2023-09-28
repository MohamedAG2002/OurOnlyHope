#include "ShopScene.hpp"
#include "../Events/EventFuncs.hpp"
#include "../Managers/EventManager.hpp"
#include "../Enums/SceneType.hpp"
#include "../UI/Button.hpp"
#include "../UI/Text.hpp"
#include "../Enums/Anchor.hpp"
#include "../Enums/TextType.hpp"
#include "../Utils/Globals.hpp"
#include "../Utils/Util.hpp"
#include "../Enums/DataPosition.hpp"

#include <raylib.h>

#include <cstdint>
#include <memory>
#include <string>

namespace ooh {

ShopScene::ShopScene()
{
  m_blood = util::GetDataFromFile<uint32_t>("data/dat.bin", DATPOS_BLOOD);
  m_wave = util::GetDataFromFile<uint32_t>("data/dat.bin", DATPOS_WAVE);

  title = std::make_unique<Text>("Make Your Choice...", Anchor::TOP_CENTER, TextType::BIG, WHITE);
  bloodText = std::make_unique<Text>("BLOOD: " + std::to_string(m_blood), Anchor::BOTTOM_LEFT, TextType::SMALL, RED);
  waveText = std::make_unique<Text>("BEST WAVE: " + std::to_string(m_wave), Anchor::BOTTOM_LEFT, TextType::SMALL, GREEN, Vector2{0.0f, -30.0f});
  
  startButton = std::make_unique<Button>("Start", Anchor::BOTTOM_RIGHT, TextType::SMALL, GREEN, WHITE, Vector2{-15.0f, 0.0f});
}

ShopScene::~ShopScene()
{}

void ShopScene::Update(float dt)
{
  if(startButton->OnPressed())
    EventManager::Get().DispatchEvent<OnSceneChange>(SceneType::GAME);
}

void ShopScene::Render()
{
  startButton->Render();
  
  title->Render();
  bloodText->Render();
  waveText->Render();
}

void ShopScene::Reset()
{
  //bloodText->ChangeText("BLOOD: " + std::to_string(m_blood));
  //waveText->ChangeText("BEST WAVE: " + std::to_string(m_wave));
}

}
