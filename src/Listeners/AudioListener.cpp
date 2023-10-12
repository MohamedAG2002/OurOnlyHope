#include "AudioListener.hpp"
#include "../Managers/AssetManager.hpp"
#include "../Managers/EventManager.hpp"
#include "../Events/EventFuncs.hpp"
#include "../Utils/Globals.hpp"

#include <raylib.h>

namespace ooh {

// Extern variables initialization
float global::masterVolume = 1.0f;
float global::soundVolume = 20.0f;
float global::musicVolume = 50.0f;

AudioListener::AudioListener()
{
  // Setting the default volume values
  SetMasterVolume(global::masterVolume);

  // Listen to OnSoundPlay
  EventManager::Get().ListenToEvent<OnSoundPlay>([&](std::string&& sound){
    SetSoundVolume(AssetManager::Get().GetSound(sound), global::soundVolume);
    PlaySound(AssetManager::Get().GetSound(sound));
  });

  // Listen to OnMusicPlay
  EventManager::Get().ListenToEvent<OnMusicPlay>([&](std::string&& music){
    SetMusicVolume(AssetManager::Get().GetMusic(music), global::musicVolume);
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
