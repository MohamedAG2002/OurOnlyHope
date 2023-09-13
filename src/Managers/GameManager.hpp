#pragma once

#include "SceneManager.hpp"
#include "../Listeners/AudioListener.hpp"
#include "../Utils/DebugDraw.hpp"

#include <SDL2/SDL.h>

#include <string>
#include <memory>

class GameManager
{
  public:
    GameManager();
    ~GameManager();

  public:
    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;
    bool isRunning;
    SDL_Event event;
    float lastFrame, deltaTime;

  public:
    void ProcessEvents();
    void Update();
    void Render();
    void Run();

  private:
    std::unique_ptr<SceneManager> m_scnMgr;
    std::unique_ptr<AudioListener> m_audioListen;
    std::unique_ptr<DebugDraw> m_debugDraw;
    bool m_isDebugDraw;

  private:
    void m_InitSDLSystems();
    void m_ShutdownSDLSystems();
    void m_InitWindow();
    void m_InitRenderer();
    void m_ExitWithError(const std::string&& msg);
};
