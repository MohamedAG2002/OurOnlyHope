#pragma once

#include "Scene.hpp"
#include "../Managers/EntityManager.hpp"
#include "../Managers/TileManager.hpp"
#include "../Managers/WaveManager.hpp"
#include "../Managers/ParticleManager.hpp"
#include "../UI/Button.hpp"
#include "../UI/Text.hpp"

#include <raylib.h>

namespace ooh {

class GameScene : public Scene 
{
  public:
    GameScene();
    ~GameScene();

  public:
    std::unique_ptr<EntityManager> enttMgr;
    std::unique_ptr<TileManager> tileMgr;
    std::unique_ptr<ParticleManager> prtclMgr;
    Text pausedText, healthText, waveText;
    Button menuButton;
    WaveManager wvMgr;

  public:
    void Update(float dt) override;
    void Render() override;
    void Reset() override;

  private:
    bool m_isPaused;
};
  
}
