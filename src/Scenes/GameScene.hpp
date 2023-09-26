#pragma once

#include "Scene.hpp"
#include "../Managers/EntityManager.hpp"
#include "../Managers/TileManager.hpp"
#include "../UI/Button.hpp"
#include "../UI/Text.hpp"

#include <raylib.h>

#include <memory>

namespace ooh {

class GameScene : public Scene 
{
  public:
    GameScene();
    ~GameScene();

  public:
    std::unique_ptr<EntityManager> enttMgr;
    std::unique_ptr<TileManager> tileMgr;
    std::unique_ptr<Text> pausedText, healthText;
    std::unique_ptr<Button> menuButton;

  public:
    void Update(float dt) override;
    void Render() override;
    void Reset() override;

  private:
    bool m_isPaused;
};
  
}
