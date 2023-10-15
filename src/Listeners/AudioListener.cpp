#include "AudioListener.hpp"
#include "../Managers/AssetManager.hpp"
#include "../Managers/EventManager.hpp"
#include "../Events/EventFuncs.hpp"
#include "../Utils/Globals.hpp"

#include <raylib.h>

namespace ooh {

// Extern variables initialization
float global::masterVolume = 0.4f;
float global::soundVolume = 5.0f;
float global::musicVolume = 3.0f;

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
  EventManager::Get().ListenToEvent<OnMusicPlay>([&](const std::string&& music){
    SetMusicVolume(AssetManager::Get().GetMusic(music), global::musicVolume);
    PlayMusicStream(AssetManager::Get().GetMusic(music));
    m_currentMusic = music;
  });
  
  // Listen to OnMusicStop
  EventManager::Get().ListenToEvent<OnMusicStop>([&](std::string&& music){
    StopMusicStream(AssetManager::Get().GetMusic(music)); 
  });
}

AudioListener::~AudioListener()
{}

void AudioListener::Update()
{
  UpdateMusicStream(AssetManager::Get().GetMusic(m_currentMusic));
}
  
}
