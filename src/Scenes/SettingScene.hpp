#pragma once

#include "Scene.hpp"
#include "../UI/Button.hpp"
#include "../UI/Text.hpp"

#include <SDL2/SDL.h>

#include <memory>

class SettingScene : public Scene 
{
  public:
    SettingScene();
    ~SettingScene();

  public:
    std::unique_ptr<Text> title;
    std::unique_ptr<Button> menuButton;

  public:
    void ProcessEvents(SDL_Event event) override;
    void Update(float dt) override;
    void Render(SDL_Renderer* renderer) override;
    void Reset() override;
};
