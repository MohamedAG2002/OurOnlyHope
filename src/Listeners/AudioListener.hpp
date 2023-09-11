#pragma once

class AudioListener 
{
  public:
    AudioListener();
    ~AudioListener();

  public:
    float masterVolume, soundVolume, musicVolume;
};
