#pragma once

#include "Scene.hpp"

#include <raylib.h>

namespace ooh {

class SecretScene : public Scene 
{
  public:
    SecretScene();
    ~SecretScene();

  public:
    void Update(float dt) override;
    void Render() override;
    void Reset() override;
};
  
}
