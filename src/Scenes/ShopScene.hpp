#pragma once

#include "Scene.hpp"
#include "../UI/Button.hpp"
#include "../UI/Text.hpp"
#include "../UI/ItemFrame.hpp"
#include "../Metadata/PotionMetadata.hpp"

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
    std::unique_ptr<Text> title, waveText;
    std::unique_ptr<Button> startButton;
    std::vector<std::unique_ptr<ItemFrame>> potions;

  public:
    void Update(float dt) override;
    void Render() override;
    void Reset() override;

  private:
    bool m_hasPotion;
    uint32_t m_wave;
    PotionMetadata m_ptnMD;

  private:
    void m_InitItems();
    const std::string m_GetFormatedPotionDesc(PotionMetadata md);
    void m_EquipPotion();
};

}
