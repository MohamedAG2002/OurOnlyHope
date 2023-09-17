#pragma once

namespace ooh {

class AudioListener 
{
  public:
    AudioListener();
    ~AudioListener();

  public:
    float masterVolume, soundVolume, musicVolume;
};
  
}
