#pragma once

#include "Scene.hpp"
#include "../UI/Button.hpp"
#include "../UI/Text.hpp"

#include <raylib.h>

#include <cstdint>
#include <memory>

namespace ooh {

class ShopScene : public Scene 
{
  public:
    ShopScene();
    ~ShopScene();

  public:
    std::unique_ptr<Text> title, bloodText, waveText;
    std::unique_ptr<Button> startButton;

  public:
    void Update(float dt) override;
    void Render() override;
    void Reset() override;

  private:
    uint32_t m_blood, m_wave;
};

}
