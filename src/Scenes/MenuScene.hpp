#pragma once

#include "Scene.hpp"
#include "../UI/Button.hpp"
#include "../UI/Text.hpp"

#include <SDL2/SDL.h>

#include <memory>

class MenuScene : public Scene 
{
  public:
    MenuScene();
    ~MenuScene();

  public:
    std::unique_ptr<Button> playButton, settingsButton, quitButton;
    std::unique_ptr<Text> title, credits;

  public:
    void ProcessEvents(SDL_Event event) override;
    void Update(float dt) override;
    void Render(SDL_Renderer* renderer) override;
    void Reset() override;
};
