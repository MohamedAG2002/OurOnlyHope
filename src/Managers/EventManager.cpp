#include "EventManager.hpp"

EventManager& EventManager::Get()
{
  static EventManager instance;
  return instance;
}

void EventManager::UnloadEvents()
{
  m_sceneEvents.clear();
  m_soundEvents.clear();
  m_musicPlayEvents.clear();
  m_musicStopEvents.clear();
}
