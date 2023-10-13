#pragma once

#include <string>

namespace ooh {

class AudioListener 
{
  public:
    AudioListener();
    ~AudioListener();

  public:
    void Update();

  private: 
    std::string m_currentMusic;
};
  
}
