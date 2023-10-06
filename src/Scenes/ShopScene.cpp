#include "ShopScene.hpp"
#include "../Events/EventFuncs.hpp"
#include "../Managers/EventManager.hpp"
#include "../Managers/AssetManager.hpp"
#include "../Enums/SceneType.hpp"
#include "../Enums/ShopItem.hpp"
#include "../Enums/ButtonState.hpp"
#include "../Enums/Anchor.hpp"
#include "../Enums/TextType.hpp"
#include "../UI/Button.hpp"
#include "../UI/Text.hpp"
#include "../UI/ItemFrame.hpp"
#include "../Utils/Globals.hpp"
#include "../Utils/Util.hpp"
#include "../Metadata/ShopItemsMetadata.hpp"

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
  m_blood = util::GetDataFromFile<uint32_t>(global::BLD_DAT_FILE_NAME);
  m_wave = util::GetDataFromFile<uint32_t>(global::WV_DAT_FILE_NAME);

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
  // one weapon and one armor. The potion can either be ignored or purchased.
  startButton->isActive = m_hasWeapon && m_hasArmor;

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
  m_blood = util::GetDataFromFile<uint32_t>(global::BLD_DAT_FILE_NAME);
  m_wave = util::GetDataFromFile<uint32_t>(global::WV_DAT_FILE_NAME);
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
  m_wpnMD = util::LoadWeaponMetadata(weapons[0]->title);
  weapons[0]->SetDesc(m_GetFormatedWeaponDesc(m_wpnMD));

  weapons.push_back(std::make_unique<ItemFrame>(AssetManager::Get().GetSprite("Medium_Sword"), 
                                              Anchor::TOP_LEFT, 
                                              "Medium-Sword",
                                              1000,
                                              Vector2{wpnOff.x + 150.0f, wpnOff.y}));
  m_wpnMD = util::LoadWeaponMetadata(weapons[1]->title);
  weapons[1]->SetDesc(m_GetFormatedWeaponDesc(m_wpnMD));

  weapons.push_back(std::make_unique<ItemFrame>(AssetManager::Get().GetSprite("Heavy_Sword"), 
                                              Anchor::TOP_LEFT, 
                                              "Heavy-Sword", 
                                              2000,
                                              Vector2{wpnOff.x + 300, wpnOff.y}));
  m_wpnMD = util::LoadWeaponMetadata(weapons[2]->title);
  weapons[2]->SetDesc(m_GetFormatedWeaponDesc(m_wpnMD));

  weapons.push_back(std::make_unique<ItemFrame>(AssetManager::Get().GetSprite("Spear"), 
                                              Anchor::TOP_LEFT, 
                                              "Spear",
                                              250,
                                              Vector2{wpnOff.x + 450.0f, wpnOff.y}));
  m_wpnMD = util::LoadWeaponMetadata(weapons[3]->title);
  weapons[3]->SetDesc(m_GetFormatedWeaponDesc(m_wpnMD));

  // Adding the armors
  Vector2 armrOff = Vector2{380.0f, 300.0f};
  armors.push_back(std::make_unique<ItemFrame>(AssetManager::Get().GetSprite("Light_Armor"), 
                                              Anchor::TOP_LEFT, 
                                              "Light-Armor", 
                                              500,
                                              armrOff));
  m_armrMD = util::LoadArmorMetadata(armors[0]->title);
  armors[0]->SetDesc(m_GetFormatedArmorDesc(m_armrMD));
  
  armors.push_back(std::make_unique<ItemFrame>(AssetManager::Get().GetSprite("Medium_Armor"), 
                                              Anchor::TOP_LEFT, 
                                              "Medium-Armor", 
                                              1000,
                                              Vector2{armrOff.x + 150.0f, armrOff.y}));
  m_armrMD = util::LoadArmorMetadata(armors[1]->title);
  armors[1]->SetDesc(m_GetFormatedArmorDesc(m_armrMD));

  armors.push_back(std::make_unique<ItemFrame>(AssetManager::Get().GetSprite("Heavy_Armor"), 
                                              Anchor::TOP_LEFT, 
                                              "Heavy-Armor", 
                                              2000,
                                              Vector2{armrOff.x + 300, armrOff.y}));
  m_armrMD = util::LoadArmorMetadata(armors[2]->title);
  armors[2]->SetDesc(m_GetFormatedArmorDesc(m_armrMD));

  armors.push_back(std::make_unique<ItemFrame>(AssetManager::Get().GetSprite("Naked_Armor"), 
                                              Anchor::TOP_LEFT, 
                                              "Naked-Armor", 
                                              100,
                                              Vector2{armrOff.x + 450.0f, armrOff.y}));
  m_armrMD = util::LoadArmorMetadata(armors[3]->title);
  armors[3]->SetDesc(m_GetFormatedArmorDesc(m_armrMD));
  
  // Adding the potions
  Vector2 ptinOff = Vector2{380.0f, 470.0f};
  potions.push_back(std::make_unique<ItemFrame>(AssetManager::Get().GetSprite("Health_Potion"), 
                                              Anchor::TOP_LEFT, 
                                              "HP-Potion", 
                                              500,
                                              ptinOff));
  m_ptnMD = util::LoadPotionMetadata(potions[0]->title);
  potions[0]->SetDesc(m_GetFormatedPotionDesc(m_ptnMD));
  
  potions.push_back(std::make_unique<ItemFrame>(AssetManager::Get().GetSprite("Damage_Potion"), 
                                              Anchor::TOP_LEFT, 
                                              "DAM-Potion", 
                                              500,
                                              Vector2{ptinOff.x + 150.0f, ptinOff.y}));
  m_ptnMD = util::LoadPotionMetadata(potions[1]->title);
  potions[1]->SetDesc(m_GetFormatedPotionDesc(m_ptnMD));

  potions.push_back(std::make_unique<ItemFrame>(AssetManager::Get().GetSprite("Durability_Potion"), 
                                              Anchor::TOP_LEFT, 
                                              "DUR-Potion", 
                                              500,
                                              Vector2{ptinOff.x + 300, ptinOff.y}));
  m_ptnMD = util::LoadPotionMetadata(potions[2]->title);
  potions[2]->SetDesc(m_GetFormatedPotionDesc(m_ptnMD));

  potions.push_back(std::make_unique<ItemFrame>(AssetManager::Get().GetSprite("Dexterity_Potion"), 
                                              Anchor::TOP_LEFT, 
                                              "DEX-Potion", 
                                              500,
                                              Vector2{ptinOff.x + 450.0f, ptinOff.y}));
  m_ptnMD = util::LoadPotionMetadata(potions[3]->title);
  potions[3]->SetDesc(m_GetFormatedPotionDesc(m_ptnMD));
}
    
const std::string ShopScene::m_GetFormatedWeaponDesc(WeaponMetadata md)
{
  return "DAM = " + std::to_string(md.damage) + 
         "\nDUR = " + std::to_string(md.durability) + 
         "\nLBS = " + std::to_string((int)md.weight) +  
         "\nRAN = " + std::to_string((int)md.range) +
         "\nSPEED = " + std::to_string((int)md.speed);
}

const std::string ShopScene::m_GetFormatedArmorDesc(ArmorMetadata md)
{
  return "DEF = " + std::to_string(md.defense) + 
         "\nDUR = " + std::to_string(md.durability) + 
         "\nLBS = " + std::to_string((int)md.weight);
}

const std::string ShopScene::m_GetFormatedPotionDesc(PotionMetadata md)
{
  // Finding out which potion this is
  if(md.damage > 0)
    return "DAM + " + std::to_string(md.damage);
  else if(md.durability > 0)
    return "DUR + " + std::to_string(md.durability);
  else if(md.health > 0)
    return "HP + " + std::to_string(md.health);
  else 
    return "DEX + " + std::to_string((int)md.weight);
}
    
void ShopScene::m_EquipWeapon()
{
  for(auto& item : weapons)
  {
    if(item->button->OnPressed() && m_blood > item->cost)
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
    if(item->button->OnPressed() && m_blood > item->cost)
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
    if(item->button->OnPressed() && m_blood > item->cost)
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
