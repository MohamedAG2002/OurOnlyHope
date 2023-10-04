#pragma once

#include "Scene.hpp"
#include "../UI/Button.hpp"
#include "../UI/Text.hpp"
#include "../UI/ItemFrame.hpp"

#include <raylib.h>

#include <cstdint>
#include <memory>
#include <vector>

namespace ooh {

class ShopScene : public Scene 
{
  public:
    ShopScene();
    ~ShopScene();

  public:
    std::unique_ptr<Text> title, bloodText, waveText;
    std::unique_ptr<Button> startButton;
    std::vector<std::unique_ptr<ItemFrame>> weapons;
    std::vector<std::unique_ptr<ItemFrame>> armors;
    std::vector<std::unique_ptr<ItemFrame>> potions;

  public:
    void Update(float dt) override;
    void Render() override;
    void Reset() override;

  private:
    bool m_hasWeapon, m_hasArmor, m_hasPotion;
    uint32_t m_blood, m_wave;

  private:
    void m_InitItems();
    void m_EquipWeapon();
    void m_EquipArmor();
    void m_EquipPotion();
};

}
