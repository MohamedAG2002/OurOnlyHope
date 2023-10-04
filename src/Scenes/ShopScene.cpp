#include "ShopScene.hpp"
#include "../Events/EventFuncs.hpp"
#include "../Managers/EventManager.hpp"
#include "../Managers/AssetManager.hpp"
#include "../Enums/SceneType.hpp"
#include "../Enums/ShopItem.hpp"
#include "../Enums/ButtonState.hpp"
#include "../Enums/Anchor.hpp"
#include "../Enums/TextType.hpp"
#include "../Enums/DataPosition.hpp"
#include "../UI/Button.hpp"
#include "../UI/Text.hpp"
#include "../UI/ItemFrame.hpp"
#include "../Utils/Globals.hpp"
#include "../Utils/Util.hpp"

#include <raylib.h>

#include <cstdint>
#include <memory>
#include <string>

namespace ooh {

ShopScene::ShopScene()
{
  m_hasWeapon = false;
  m_hasArmor = false;
  m_hasPotion = false;
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
  weapons.clear();
  armors.clear();
  potions.clear();
}

void ShopScene::Update(float dt)
{
  // The player is only able to press the start button when they purchased at least 
  // one item out of the three catagories in the shop.
  startButton->isActive = m_hasWeapon && m_hasArmor && m_hasPotion;

  // Start the game
  if(startButton->OnPressed())
    EventManager::Get().DispatchEvent<OnSceneChange>(SceneType::GAME);

  // Only make the player choose one of the shop items if they didn't do it before
  if(!m_hasWeapon)
    m_EquipWeapon();
  if(!m_hasArmor)
    m_EquipArmor();
  if(!m_hasPotion)
    m_EquipPotion();
}

void ShopScene::Render()
{
  startButton->Render();
  
  title->Render();
  bloodText->Render();
  waveText->Render();

  // Render the item frames only if the player still did not choose either of them 
  if(!m_hasWeapon)
  {
    for(auto& item : weapons)
      item->Render();
  }
  
  if(!m_hasArmor)
  {
    for(auto& item : armors)
      item->Render();
  }
  
  if(!m_hasPotion)
  {
    for(auto& item : potions)
      item->Render();
  }
}

void ShopScene::Reset()
{
  // Reset private members
  m_blood = util::GetDataFromFile<uint32_t>("data/dat.bin", DATPOS_BLOOD);
  m_wave = util::GetDataFromFile<uint32_t>("data/dat.bin", DATPOS_WAVE);
  m_hasWeapon = false;
  m_hasArmor = false;
  m_hasPotion = false;

  // Reset the texts
  bloodText->ChangeText("BLOOD: " + std::to_string(m_blood));
  waveText->ChangeText("BEST WAVE: " + std::to_string(m_wave));
  
  // Reset the item frames 
  for(auto& item : weapons)
    item->Reset();
  for(auto& item : armors)
    item->Reset();
  for(auto& item : potions)
    item->Reset();
}
    
void ShopScene::m_InitItems()
{
  // Adding the weapons
  Vector2 wpnOff = Vector2{380.0f, 130.0f};
  weapons.push_back(std::make_unique<ItemFrame>(AssetManager::Get().GetSprite("Light_Sword"), 
                                              Anchor::TOP_LEFT, 
                                              "Light-Sword",
                                              500,
                                              wpnOff));
  
  weapons.push_back(std::make_unique<ItemFrame>(AssetManager::Get().GetSprite("Medium_Sword"), 
                                              Anchor::TOP_LEFT, 
                                              "Medium-Sword",
                                              1000,
                                              Vector2{wpnOff.x + 150.0f, wpnOff.y}));

  weapons.push_back(std::make_unique<ItemFrame>(AssetManager::Get().GetSprite("Heavy_Sword"), 
                                              Anchor::TOP_LEFT, 
                                              "Heavy-Sword", 
                                              2000,
                                              Vector2{wpnOff.x + 300, wpnOff.y}));

  weapons.push_back(std::make_unique<ItemFrame>(AssetManager::Get().GetSprite("Spear"), 
                                              Anchor::TOP_LEFT, 
                                              "Spear",
                                              250,
                                              Vector2{wpnOff.x + 450.0f, wpnOff.y}));

  // Adding the armors
  Vector2 armrOff = Vector2{380.0f, 300.0f};
  armors.push_back(std::make_unique<ItemFrame>(AssetManager::Get().GetSprite("Light_Armor"), 
                                              Anchor::TOP_LEFT, 
                                              "Light-Armor", 
                                              500,
                                              armrOff));
  
  armors.push_back(std::make_unique<ItemFrame>(AssetManager::Get().GetSprite("Medium_Armor"), 
                                              Anchor::TOP_LEFT, 
                                              "Medium-Armor", 
                                              1000,
                                              Vector2{armrOff.x + 150.0f, armrOff.y}));

  armors.push_back(std::make_unique<ItemFrame>(AssetManager::Get().GetSprite("Heavy_Armor"), 
                                              Anchor::TOP_LEFT, 
                                              "Heavy-Armor", 
                                              2000,
                                              Vector2{armrOff.x + 300, armrOff.y}));

  armors.push_back(std::make_unique<ItemFrame>(AssetManager::Get().GetSprite("Naked_Armor"), 
                                              Anchor::TOP_LEFT, 
                                              "Naked-Armor", 
                                              0,
                                              Vector2{armrOff.x + 450.0f, armrOff.y}));
  
  // Adding the potions
  Vector2 ptinOff = Vector2{380.0f, 470.0f};
  potions.push_back(std::make_unique<ItemFrame>(AssetManager::Get().GetSprite("Health_Potion"), 
                                              Anchor::TOP_LEFT, 
                                              "HP-Potion", 
                                              500,
                                              ptinOff));
  
  potions.push_back(std::make_unique<ItemFrame>(AssetManager::Get().GetSprite("Damage_Potion"), 
                                              Anchor::TOP_LEFT, 
                                              "DAM-Potion", 
                                              500,
                                              Vector2{ptinOff.x + 150.0f, ptinOff.y}));

  potions.push_back(std::make_unique<ItemFrame>(AssetManager::Get().GetSprite("Durability_Potion"), 
                                              Anchor::TOP_LEFT, 
                                              "DUR-Potion", 
                                              500,
                                              Vector2{ptinOff.x + 300, ptinOff.y}));

  potions.push_back(std::make_unique<ItemFrame>(AssetManager::Get().GetSprite("Dexterity_Potion"), 
                                              Anchor::TOP_LEFT, 
                                              "DEX-Potion", 
                                              500,
                                              Vector2{ptinOff.x + 450.0f, ptinOff.y}));
}
    
void ShopScene::m_EquipWeapon()
{
  for(auto& item : weapons)
  {
    if(item->button->OnPressed())
    {
      EventManager::Get().DispatchEvent<OnItemEquip>(ShopItem::WEAPON, item->title);
      EventManager::Get().DispatchEvent<OnItemBuy>(item->cost);
       
      item->button->isActive = false;
      m_hasWeapon = true;
      
      m_blood -= item->cost;
      bloodText->ChangeText("BLOOD: " + std::to_string(m_blood));
    }
  }
}

void ShopScene::m_EquipArmor()
{
  for(auto& item : armors)
  {
    if(item->button->OnPressed())
    {
      EventManager::Get().DispatchEvent<OnItemEquip>(ShopItem::ARMOR, item->title);
      EventManager::Get().DispatchEvent<OnItemBuy>(item->cost);
       
      item->button->isActive = false; 
      m_hasArmor = true; 

      m_blood -= item->cost;
      bloodText->ChangeText("BLOOD: " + std::to_string(m_blood));
    }
  }
}

void ShopScene::m_EquipPotion()
{
  for(auto& item : potions)
  {
    if(item->button->OnPressed())
    {
      EventManager::Get().DispatchEvent<OnItemEquip>(ShopItem::POTION, item->title);
      EventManager::Get().DispatchEvent<OnItemBuy>(item->cost);
       
      item->button->isActive = false; 
      m_hasPotion = true;

      m_blood -= item->cost;
      bloodText->ChangeText("BLOOD: " + std::to_string(m_blood));
    }
  }
}

}
