#include "ShopScene.hpp"
#include "../Events/EventFuncs.hpp"
#include "../Managers/EventManager.hpp"
#include "../Managers/AssetManager.hpp"
#include "../Enums/SceneType.hpp"
#include "../UI/Button.hpp"
#include "../UI/Text.hpp"
#include "../UI/ItemFrame.hpp"
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

  m_InitItems();
}

ShopScene::~ShopScene()
{
  items.clear();
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
  bloodText->Render();
  waveText->Render();

  for(auto& item : items)
    item->Render();
}

void ShopScene::Reset()
{
  m_blood = util::GetDataFromFile<uint32_t>("data/dat.bin", DATPOS_BLOOD);
  m_wave = util::GetDataFromFile<uint32_t>("data/dat.bin", DATPOS_WAVE);
  
  bloodText->ChangeText("BLOOD: " + std::to_string(m_blood));
  waveText->ChangeText("BEST WAVE: " + std::to_string(m_wave));
}
    
void ShopScene::m_InitItems()
{
  // Adding the weapons
  Vector2 wpnOff = Vector2{380.0f, 130.0f};
  items.push_back(std::make_unique<ItemFrame>(AssetManager::Get().GetSprite("Light_Sword"), 
                                              Anchor::TOP_LEFT, 
                                              "Light Sword I", 
                                              wpnOff));
  
  items.push_back(std::make_unique<ItemFrame>(AssetManager::Get().GetSprite("Medium_Sword"), 
                                              Anchor::TOP_LEFT, 
                                              "Medium Sword I", 
                                              Vector2{wpnOff.x + 150.0f, wpnOff.y}));

  items.push_back(std::make_unique<ItemFrame>(AssetManager::Get().GetSprite("Heavy_Sword"), 
                                              Anchor::TOP_LEFT, 
                                              "Heavy Sword I", 
                                              Vector2{wpnOff.x + 300, wpnOff.y}));

  items.push_back(std::make_unique<ItemFrame>(AssetManager::Get().GetSprite("Spear"), 
                                              Anchor::TOP_LEFT, 
                                              "Spear I", 
                                              Vector2{wpnOff.x + 450.0f, wpnOff.y}));

  // Adding the armors
  Vector2 armrOff = Vector2{380.0f, 300.0f};
  items.push_back(std::make_unique<ItemFrame>(AssetManager::Get().GetSprite("Light_Armor"), 
                                              Anchor::TOP_LEFT, 
                                              "Light Armor I", 
                                              armrOff));
  
  items.push_back(std::make_unique<ItemFrame>(AssetManager::Get().GetSprite("Medium_Armor"), 
                                              Anchor::TOP_LEFT, 
                                              "Medium Armor I", 
                                              Vector2{armrOff.x + 150.0f, armrOff.y}));

  items.push_back(std::make_unique<ItemFrame>(AssetManager::Get().GetSprite("Heavy_Armor"), 
                                              Anchor::TOP_LEFT, 
                                              "Heavy Armor I", 
                                              Vector2{armrOff.x + 300, armrOff.y}));

  items.push_back(std::make_unique<ItemFrame>(AssetManager::Get().GetSprite("Naked_Armor"), 
                                              Anchor::TOP_LEFT, 
                                              "Naked Armor", 
                                              Vector2{armrOff.x + 450.0f, armrOff.y}));
  
  // Adding the potions
  Vector2 ptinOff = Vector2{380.0f, 470.0f};
  items.push_back(std::make_unique<ItemFrame>(AssetManager::Get().GetSprite("Health_Potion"), 
                                              Anchor::TOP_LEFT, 
                                              "HP Potion I", 
                                              ptinOff));
  
  items.push_back(std::make_unique<ItemFrame>(AssetManager::Get().GetSprite("Damage_Potion"), 
                                              Anchor::TOP_LEFT, 
                                              "DAM Potion I", 
                                              Vector2{ptinOff.x + 150.0f, ptinOff.y}));

  items.push_back(std::make_unique<ItemFrame>(AssetManager::Get().GetSprite("Durability_Potion"), 
                                              Anchor::TOP_LEFT, 
                                              "DUR Potion I", 
                                              Vector2{ptinOff.x + 300, ptinOff.y}));

  items.push_back(std::make_unique<ItemFrame>(AssetManager::Get().GetSprite("Dexterity_Potion"), 
                                              Anchor::TOP_LEFT, 
                                              "DEX Potion", 
                                              Vector2{ptinOff.x + 450.0f, ptinOff.y}));
}

}
