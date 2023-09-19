#pragma once

#include "../Listeners/AudioListener.hpp"
#include "SceneManager.hpp"
#include "../Utils/DebugDraw.hpp"

#include <memory>

namespace ooh {

class GameManager
{
  public:
    GameManager();
    ~GameManager();

  public:
    void Update();
    void Render();
    void Run();

  private:
    bool m_isRunning;
    std::unique_ptr<AudioListener> m_audioListen;
    std::unique_ptr<SceneManager> m_scnMgr;
    std::unique_ptr<DebugDraw> m_debugDraw;
};

}
