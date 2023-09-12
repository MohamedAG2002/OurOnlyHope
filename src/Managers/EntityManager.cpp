#include "EntityManager.hpp"
#include "../Entities/Entity.hpp"
#include "../Entities/Player.hpp"

#include <SDL2/SDL.h>

#include <vector>
#include <memory>

EntityManager::EntityManager()
{
  player = std::make_unique<Player>(Vector2(300.0f, 200.0f));
}

EntityManager::~EntityManager()
{}

void EntityManager::ProcessEvents(SDL_Event event)
{
  if(player->isActive)
    player->ProcessEvents(event);
}

void EntityManager::Update(float dt)
{
  if(player->isActive)
    player->Update(dt);
}

void EntityManager::Render(SDL_Renderer* renderer)
{
  if(player->isActive)
    player->Render(renderer);
}

void EntityManager::Reset()
{}
