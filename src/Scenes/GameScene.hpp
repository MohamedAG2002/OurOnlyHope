#pragma once

#include "Scene.hpp"
#include "../Managers/EntityManager.hpp"
#include "../UI/Button.hpp"
#include "../UI/Text.hpp"

#include <SDL2/SDL.h>

#include <memory>

class GameScene : public Scene 
{
  public:
    GameScene();
    ~GameScene();

  public:
    std::unique_ptr<EntityManager> enttMgr;
    std::unique_ptr<Text> pausedText;
    std::unique_ptr<Button> menuButton;

  public:
    void ProcessEvents(SDL_Event event) override;
    void Update(float dt) override;
    void Render(SDL_Renderer* renderer) override;
    void Reset() override;

  private:
    bool m_isPaused;
};

