#include "AudioListener.hpp"
#include "../Managers/AssetManager.hpp"
#include "../Managers/EventManager.hpp"
#include "../Events/EventFuncs.hpp"

#include <raylib.h>

namespace ooh {

AudioListener::AudioListener()
{
  masterVolume = 1.0f;
  soundVolume = 1.0f;
  musicVolume = 50.0f;

  // Setting the default volume values
  SetMasterVolume(masterVolume);

  // Listen to OnSoundPlay
  EventManager::Get().ListenToEvent<OnSoundPlay>([&](std::string&& sound){
    SetSoundVolume(AssetManager::Get().GetSound(sound), soundVolume);
    PlaySound(AssetManager::Get().GetSound(sound));
  });

  // Listen to OnMusicPlay
  EventManager::Get().ListenToEvent<OnMusicPlay>([&](std::string&& music){
    SetMusicVolume(AssetManager::Get().GetMusic(music), musicVolume);
    PlayMusicStream(AssetManager::Get().GetMusic(music));
  });
  
  // Listen to OnMusicStop
  EventManager::Get().ListenToEvent<OnMusicStop>([&](std::string& music){
    PauseMusicStream(AssetManager::Get().GetMusic(music)); 
  });
}

AudioListener::~AudioListener()
{}
  
}
