#include "AudioListener.hpp"
#include "../Managers/AssetManager.hpp"
#include "../Managers/EventManager.hpp"
#include "../Events/EventFuncs.hpp"

#include <SDL2/SDL_mixer.h>

#include <iostream>

AudioListener::AudioListener()
{
  masterVolume = 100.0f;
  soundVolume = 100.0f;
  musicVolume = 50.0f;

  // Setting the default volume values
  Mix_MasterVolume(masterVolume);
  Mix_VolumeMusic(musicVolume);

  // Listen to OnSoundPlay
  EventManager::Get().ListenToEvent<OnSoundPlay>([&](std::string&& sound){
    Mix_Volume(-1, soundVolume);
    Mix_PlayChannel(-1, AssetManager::Get().GetSound(sound), 0);
  });

  // Listen to OnMusicPlay
  EventManager::Get().ListenToEvent<OnMusicPlay>([&](std::string&& music){
    //Mix_PlayMusic(AssetManager::Get().GetMusic(music), 1); 
  });
  
  // Listen to OnMusicStop
  EventManager::Get().ListenToEvent<OnMusicStop>([&](std::string& music){
    Mix_PauseMusic(); 
  });
}

AudioListener::~AudioListener()
{}
