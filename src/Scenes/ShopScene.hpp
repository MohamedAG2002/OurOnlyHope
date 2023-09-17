#pragma once

#include "Scene.hpp"
#include "../UI/Button.hpp"
#include "../UI/Text.hpp"

#include <raylib.h>

#include <memory>

namespace ooh {

class ShopScene : public Scene 
{
  public:
    ShopScene();
    ~ShopScene();

  public:
    std::unique_ptr<Text> title;
    std::unique_ptr<Button> startButton;

  public:
    void Update(float dt) override;
    void Render() override;
    void Reset() override;
};

}
