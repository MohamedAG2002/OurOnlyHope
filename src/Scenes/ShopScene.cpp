#include "ShopScene.hpp"
#include "../Events/EventFuncs.hpp"
#include "../Managers/EventManager.hpp"
#include "../Managers/AssetManager.hpp"
#include "../Enums/SceneType.hpp"
#include "../Enums/PotionType.hpp"
#include "../Enums/ButtonState.hpp"
#include "../Enums/Anchor.hpp"
#include "../Enums/TextType.hpp"
#include "../UI/Button.hpp"
#include "../UI/Text.hpp"
#include "../UI/ItemFrame.hpp"
#include "../Utils/Globals.hpp"
#include "../Utils/Util.hpp"
#include "../Metadata/PotionMetadata.hpp"

#include <raylib.h>

#include <cstdint>
#include <memory>
#include <string>

namespace ooh {

ShopScene::ShopScene()
{
  m_hasPotion = false;
  m_wave = util::GetDataFromFile<uint32_t>(global::WV_DAT_FILE_NAME);

  title = std::make_unique<Text>("Make Your Choice...", Anchor::TOP_CENTER, TextType::BIG);
  waveText = std::make_unique<Text>("BEST WAVE: " + std::to_string(m_wave), Anchor::BOTTOM_LEFT, TextType::SMALL, WHITE);
  
  startButton = std::make_unique<Button>("Start", Anchor::BOTTOM_RIGHT, TextType::SMALL, Vector2{-15.0f, 0.0f});

  m_InitItems();
}

ShopScene::~ShopScene()
{
  potions.clear();
}

void ShopScene::Update(float dt)
{
  // The player is only able to press the start button when they purchased at least 
  // one potion. 
  startButton->isActive = m_hasPotion;

  // Start the game
  if(startButton->OnPressed())
    EventManager::Get().DispatchEvent<OnSceneChange>(SceneType::GAME);

  // Only make the player choose a potion once
  if(!m_hasPotion)
    m_EquipPotion();
}

void ShopScene::Render()
{
  startButton->Render();
  
  title->Render();
  waveText->Render();

  // Render the item frames only if the player still did not choose either of them 
  if(!m_hasPotion)
  {
    for(auto& item : potions)
      item->Render();
  }
}

void ShopScene::Reset()
{
  // Reset private members
  m_wave = util::GetDataFromFile<uint32_t>(global::WV_DAT_FILE_NAME);
  m_hasPotion = false;

  // Reset the texts
  waveText->ChangeText("BEST WAVE: " + std::to_string(m_wave));
  
  // Reset the item frames 
  for(auto& item : potions)
    item->Reset();
}
    
void ShopScene::m_InitItems()
{
  // Adding the potions
  Vector2 ptinOff = Vector2{380.0f, 300.0f};
  potions.push_back(std::make_unique<ItemFrame>(AssetManager::Get().GetSprite("Health_Potion"), 
                                              Anchor::TOP_LEFT, 
                                              "HP-Potion", 
                                              ptinOff));
  m_ptnMD = util::LoadPotionMetadata(potions[0]->title);
  potions[0]->SetDesc(m_GetFormatedPotionDesc(m_ptnMD));
  
  potions.push_back(std::make_unique<ItemFrame>(AssetManager::Get().GetSprite("Damage_Potion"), 
                                              Anchor::TOP_LEFT, 
                                              "DAM-Potion", 
                                              Vector2{ptinOff.x + 150.0f, ptinOff.y}));
  m_ptnMD = util::LoadPotionMetadata(potions[1]->title);
  potions[1]->SetDesc(m_GetFormatedPotionDesc(m_ptnMD));

  potions.push_back(std::make_unique<ItemFrame>(AssetManager::Get().GetSprite("Durability_Potion"), 
                                              Anchor::TOP_LEFT, 
                                              "DUR-Potion", 
                                              Vector2{ptinOff.x + 300, ptinOff.y}));
  m_ptnMD = util::LoadPotionMetadata(potions[2]->title);
  potions[2]->SetDesc(m_GetFormatedPotionDesc(m_ptnMD));

  potions.push_back(std::make_unique<ItemFrame>(AssetManager::Get().GetSprite("Dexterity_Potion"), 
                                              Anchor::TOP_LEFT, 
                                              "DEX-Potion", 
                                              Vector2{ptinOff.x + 450.0f, ptinOff.y}));
  m_ptnMD = util::LoadPotionMetadata(potions[3]->title);
  potions[3]->SetDesc(m_GetFormatedPotionDesc(m_ptnMD));
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
    return "DEX + " + std::to_string((int)md.speed);
}

void ShopScene::m_EquipPotion()
{
  for(auto& item : potions)
  {
    if(item->button->OnPressed())
    {
      EventManager::Get().DispatchEvent<OnItemEquip>(item->title);
       
      item->button->isActive = false; 
      m_hasPotion = true;
    }
  }
}

}
